// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename... FormattingVariables>
std::string format_win_error_message(std::string filename, int line,
  std::string message, FormattingVariables... vars)
{
  return format_error_message(
    filename, line, message + u8" - " + get_last_win_error_message(), vars...);
}

}  // namespace hou
