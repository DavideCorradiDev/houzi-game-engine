// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/character_encodings.hpp"



namespace hou
{

template<> std::basic_string<utf8::code_unit> convertEncoding<utf16, utf8>
  (const std::basic_string<utf16::code_unit>&);
template<> std::basic_string<utf8::code_unit> convertEncoding<utf32, utf8>
  (const std::basic_string<utf32::code_unit>&);
template<> std::basic_string<utf8::code_unit> convertEncoding<wide, utf8>
  (const std::basic_string<wide::code_unit>&);
template<> std::basic_string<utf16::code_unit> convertEncoding<utf8, utf16>
  (const std::basic_string<utf8::code_unit>&);
template<> std::basic_string<utf16::code_unit> convertEncoding<utf32, utf16>
  (const std::basic_string<utf32::code_unit>&);
template<> std::basic_string<utf16::code_unit> convertEncoding<wide, utf16>
  (const std::basic_string<wide::code_unit>&);
template<> std::basic_string<utf32::code_unit> convertEncoding<utf8, utf32>
  (const std::basic_string<utf8::code_unit>&);
template<> std::basic_string<utf32::code_unit> convertEncoding<utf16, utf32>
  (const std::basic_string<utf16::code_unit>&);
template<> std::basic_string<utf32::code_unit> convertEncoding<wide, utf32>
  (const std::basic_string<wide::code_unit>&);

}

