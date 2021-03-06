// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/std_string.hpp"



namespace hou
{

std::string replace_all(
  std::string s, const std::string& from, const std::string& to)
{
  size_t start = 0u;
  while((start = s.find(from, start)) != std::string::npos)
  {
    s.replace(start, from.length(), to);
    start += to.length();
  }
  return s;
}



std::string escape_regex(std::string s)
{
  static const std::vector<std::string> reserved_chars = {
    // \ must be first in the list to avoid replacing it recursively.
    u8"\\",
    u8".",
    u8"^",
    u8"$",
    u8"*",
    u8"+",
    u8"?",
    u8"(",
    u8")",
    u8"[",
    u8"{",
    u8"|",
  };

  for(const auto& c : reserved_chars)
  {
    s = replace_all(s, c, u8"\\" + c);
  }
  return s;
}



std::string to_string(bool value)
{
  return value ? "true" : "false";
}

}  // namespace hou
