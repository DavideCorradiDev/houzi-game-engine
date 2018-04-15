// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/StdString.hpp"



namespace hou
{

std::string replaceAll(std::string s, const std::string& from
  , const std::string& to)
{
  size_t start = 0u;
  while((start = s.find(from, start)) != std::string::npos)
  {
    s.replace(start, from.length(), to);
    start += to.length();
  }
  return s;
}



std::string formatRegex(std::string s)
{
  static const std::vector<std::string> reservedChars =
  {
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

  for(const auto& c : reservedChars)
  {
    s = replaceAll(s, c, u8"\\" + c);
  }
  return s;
}



std::string toString(bool value)
{
  return value ? "true" : "false";
}

}

