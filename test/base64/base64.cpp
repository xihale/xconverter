
#include <base64.hpp>
#include <array>
#include <format>
#include <stdexcept>
#include <string>
#include <source_location>

// #include "../../src/base64/base64.cpp"

using namespace xihale::converter::base64;

template <typename Out=std::string>
  requires Output<Out>
void test_encode(auto in, auto comp, std::source_location loc = std::source_location::current()){
  
  auto s = encode<Out>(in);
  
  for(size_t i=0; i<comp.size(); ++i){
    if(s[i]!=comp[i]) throw std::runtime_error(std::format("Encode error, Line: {}", loc.line()));
  }

}

template <typename Out=std::string>
  requires Output<Out>
void test_decode(auto in, auto comp, std::source_location loc = std::source_location::current()){

  auto s = decode<Out>(in);

  for(size_t i=0; i<comp.size(); ++i){
    if(s[i]!=comp[i]) throw std::runtime_error(std::format("Encode error, Line: {}\n{}", loc.line(), s));
  }

}

int main(){

  std::array<char, 20> comp={'N', 'z', 'I', 'w', 'M', 'j', 'A', '1', 'N', 'z', 'E', 'y', 'O', 'T', 'g', 'w', 'N', 'A', '=', '='};
  std::array<char, 13> in{'7','2','0','2','0','5','7','1','2','9','8', '0', '4'};

  test_encode(std::string("7202057129804"), comp);
  test_encode(in, comp);

  test_encode<std::u8string>(std::string("7202057129804"), comp);
  test_encode<std::u8string>(in, comp);

  test_decode(comp, in);

  test_encode(std::string("12"), std::string("MTI="));
  test_decode(std::string("MTI="), std::string("12"));

  return 0;

}