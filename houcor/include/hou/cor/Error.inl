// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename... FormattingVariables>
  std::string formatErrorMessage(const std::string& filePath, int line
  , const std::string& message, const FormattingVariables&... vars)
{
#if defined(HOU_SYSTEM_WINDOWS)
  constexpr char sPathSeparator = '\\';
#else
  constexpr char sPathSeparator = '/';
#endif
  return formatString(u8"%s:%d - %s"
    , filePath.substr(filePath.find_last_of(sPathSeparator) + 1).c_str()
    , line
    , formatString(message, vars...).c_str());
}

}

