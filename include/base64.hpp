/**
 * @file base64.hpp
 * @brief Base64 Encoder/Decoder
 * @author xihale
 * @date 2024.4.13
 */

#pragma once

namespace xihale {
namespace converter {
namespace base64 {

template <typename In>
concept Input = requires(In s) {
  s.size();
  s[0];
};

template <typename Out>
concept Output = requires(Out o) {
  o.resize(0,0);
  o[0];
};

/// @brief Base64 encoder, in should be able to call .size() and operator[]
template <typename Out, typename In>
  requires Input<In> && Output<Out>
Out encode(const In &in);

/// @brief Base64 decoder, in should be able to call .size() and operator[]
template <typename Out, typename In>
  requires Input<In> && Output<Out>
Out decode(const In &in);

/// @brief forward to encode
template <typename Out, typename In>
  requires Input<In> && Output<Out>
inline Out encrypt(const In &in) {
  return encode<Out, In>(in);
}

/// @brief forward to decode
template <typename Out, typename In>
  requires Input<In> && Output<Out>
inline Out decrypt(const In &in) {
  return decode<Out, In>(in);
}

} // namespace base64
} // namespace converter
} // namespace xihale

// impl
#include "../src/base64/base64.cpp"