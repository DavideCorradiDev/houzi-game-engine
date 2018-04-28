// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename... FormattingVariables>
  std::string formatWinErrorMessage(std::string filename, int line
    , std::string message, FormattingVariables... vars)
{
  return format_error_message(filename, line
    , message + u8" - " + getLastWinErrorMessage(), vars...);
}

}

