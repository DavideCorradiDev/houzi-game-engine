// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename... FormattingVariables>
std::string format_error_message(
  const std::string& file_path, int line, const std::string& message,
  const FormattingVariables&... vars)
{
#if defined(HOU_SYSTEM_WINDOWS)
  constexpr char path_separator = '\\';
#else
  constexpr char path_separator = '/';
#endif
  return format_string(
    u8"%s:%d - %s",
    file_path.substr(file_path.find_last_of(path_separator) + 1).c_str(), line,
    format_string(message, vars...).c_str());
}

}  // namespace hou
