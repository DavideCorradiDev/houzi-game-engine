// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/cor/CharacterEncodings.hpp"



namespace hou
{

template<> std::basic_string<Utf8::CodeUnit> convertEncoding<Utf16, Utf8>
  (const std::basic_string<Utf16::CodeUnit>&);
template<> std::basic_string<Utf8::CodeUnit> convertEncoding<Utf32, Utf8>
  (const std::basic_string<Utf32::CodeUnit>&);
template<> std::basic_string<Utf8::CodeUnit> convertEncoding<Wide, Utf8>
  (const std::basic_string<Wide::CodeUnit>&);
template<> std::basic_string<Utf16::CodeUnit> convertEncoding<Utf8, Utf16>
  (const std::basic_string<Utf8::CodeUnit>&);
template<> std::basic_string<Utf16::CodeUnit> convertEncoding<Utf32, Utf16>
  (const std::basic_string<Utf32::CodeUnit>&);
template<> std::basic_string<Utf16::CodeUnit> convertEncoding<Wide, Utf16>
  (const std::basic_string<Wide::CodeUnit>&);
template<> std::basic_string<Utf32::CodeUnit> convertEncoding<Utf8, Utf32>
  (const std::basic_string<Utf8::CodeUnit>&);
template<> std::basic_string<Utf32::CodeUnit> convertEncoding<Utf16, Utf32>
  (const std::basic_string<Utf16::CodeUnit>&);
template<> std::basic_string<Utf32::CodeUnit> convertEncoding<Wide, Utf32>
  (const std::basic_string<Wide::CodeUnit>&);

}

