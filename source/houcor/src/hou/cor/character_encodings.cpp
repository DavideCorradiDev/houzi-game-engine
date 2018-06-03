// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/character_encodings.hpp"



namespace hou
{

template std::string convert_encoding<utf8, utf16>(const std::u16string& s);
template std::string convert_encoding<utf8, utf32>(const std::u32string& s);
template std::string convert_encoding<utf8, wide>(const std::wstring& s);

template std::u16string convert_encoding<utf16, utf8>(const std::string& s);
template std::u16string convert_encoding<utf16, utf32>(const std::u32string& s);
template std::u16string convert_encoding<utf16, wide>(const std::wstring& s);

template std::u32string convert_encoding<utf32, utf8>(const std::string& s);
template std::u32string convert_encoding<utf32, utf16>(const std::u16string& s);
template std::u32string convert_encoding<utf32, wide>(const std::wstring& s);

template std::wstring convert_encoding<wide, utf8>(const std::string& s);
template std::wstring convert_encoding<wide, utf16>(const std::u16string& s);
template std::wstring convert_encoding<wide, utf32>(const std::u32string& s);



template <>
std::string convert_encoding<utf8, utf8>(const std::string& s)
{
  return s;
}



template <>
HOU_COR_API std::u16string convert_encoding<utf16, utf16>(
  const std::u16string& s)
{
  return s;
}



template <>
HOU_COR_API std::u32string convert_encoding<utf32, utf32>(
  const std::u32string& s)
{
  return s;
}



template <>
HOU_COR_API std::wstring convert_encoding<wide, wide>(const std::wstring& s)
{
  return s;
}

}  // namespace hou
