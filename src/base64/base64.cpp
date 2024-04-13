/**
 * @file base64.cpp
 * @brief Base64 Encoder/Decoder (source)
 * @author xihale
 * @date 2024.4.13
 */

#pragma once

#include <base64.hpp>

namespace xihale {
namespace converter {
namespace base64 {

namespace utils {

// encode char set
static auto ecs =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// decode char set A->0 a->25 0->51 +->62 /->63
static constexpr char dcs[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57,
    58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,
    7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
};

} // namespace utils

template <typename Out, typename In>
  requires Input<In> && Output<Out>
Out encode(const In &in) {

  using size_t = unsigned long;
  const auto &ecs = utils::ecs;

  const auto len = in.size() / 3;
  const bool is_more = (in.size() - len * 3) > 0; // tail

  Out res;                               // result
  res.resize(((len + is_more) << 2), 0); // per 3 input corresponds 4 output

  // <(left hand side) >(right hand side)
  // 0x3f: 00111111
  //  0x3: 00000011
  //  0xf: 00001111
  // 0xf0: 11110000
  // 0xc0: 11000000
  // 0x30: 00110000
  // 0x3c: 00111100
  constexpr int R6 = 0x3f, R2 = 0x3, R4 = 0xf, L4 = 0xf0, L2 = 0xc0, ML2 = 0x30,
                M4 = 0x3c;

  for (size_t idx = 0; idx < len; ++idx) {

    const size_t i = idx * 3, o = idx << 2; // input pos && output pos

    res[o] = ecs[(in[i] >> 2) & R6];
    res[o + 1] = ecs[((in[i] << 4) & ML2) | ((in[i + 1] >> 4) & R4)];
    res[o + 2] = ecs[((in[i + 1] << 2) & M4) | ((in[i + 2] >> 6) & R2)];
    res[o + 3] = ecs[in[i + 2] & R6];
  }

  if (in.size() - len * 3 == 1) {

    const size_t i = len * 3, o = len << 2;

    res[o] = ecs[(in[i] >> 2) & R6];
    res[o + 1] = ecs[(in[i] << 4) & ML2];
    res[o + 2] = res[o + 3] = '=';

  } else if (in.size() - len * 3 == 2) {

    const size_t i = len * 3, o = len << 2;

    res[o] = ecs[(in[i] >> 2) & R6];
    res[o + 1] = ecs[((in[i] << 4) & ML2) | ((in[i + 1] >> 4) & R4)];
    res[o + 2] = ecs[(in[i + 1] << 2) & M4];
    res[o + 3] = '=';
  }

  return res;
}

template <typename Out, typename In>
  requires Input<In> && Output<Out>
Out decode(const In &in) {

  using size_t = unsigned long;
  using tiny_t = unsigned char;
  const auto &dcs = utils::dcs;

  auto len = in.size();
  tiny_t tail_len = (in[len - 1] == '=') + (in[len - 2] == '=');

  len >>= 2; // len /= 4;

  Out res; // result
  res.resize(len * 3 - tail_len, 0);

  if (tail_len)
    --len;

  for (size_t idx = 0; idx < len; ++idx) {

    const size_t i = idx << 2, o = idx * 3;

    res[o] = (dcs[in[i]] << 2) | (dcs[in[i + 1]] >> 4);
    res[o + 1] = (dcs[in[i + 1]] << 4) | (dcs[in[i + 2]] >> 2);
    res[o + 2] = (dcs[in[i + 2]] << 6) | dcs[in[i + 3]];
  }

  if (tail_len >= 1) {

    const auto i = len << 2, o = len * 3;

    res[o] = (dcs[in[i]] << 2) | (dcs[in[i + 1]] >> 4);
    // `=` refers to 3 meaningful chars, yet `==` refers to 2
    if (tail_len == 1)
      res[o + 1] = (dcs[in[i + 1]] << 4) | (dcs[in[i + 2]] >> 2);
  }

  return res;
}

} // namespace base64

} // namespace converter
} // namespace xihale