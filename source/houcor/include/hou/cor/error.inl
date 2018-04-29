// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename... FormattingVariables>
  std::string format_error_message(const std::string& filePath, int line
  , const std::string& message, const FormattingVariables&... vars)
{
#if defined(HOU_SYSTEM_WINDOWS)
  constexpr char sPathSeparator = '\\';
#else
  constexpr char sPathSeparator = '/';
#endif
  return format_string(u8"%s:%d - %s"
    , filePath.substr(filePath.find_last_of(sPathSeparator) + 1).c_str()
    , line
    , format_string(message, vars...).c_str());
}

}

