// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_BASIC_STATIC_STRING_FWD_HPP
#define HOU_COR_BASIC_STATIC_STRING_FWD_HPP

#include "hou/cor/cor_export.hpp"

#include <string>



namespace hou
{

template <typename CharT, size_t N, typename Traits>
class basic_static_string;

template <size_t N>
using static_string = basic_static_string<char, N, std::char_traits<char>>;

template <size_t N>
using static_wstring
  = basic_static_string<wchar_t, N, std::char_traits<wchar_t>>;

template <size_t N>
using static_u16string
  = basic_static_string<char16_t, N, std::char_traits<char16_t>>;

template <size_t N>
using static_u32string
  = basic_static_string<char32_t, N, std::char_traits<char32_t>>;

}  // namespace hou

#endif
