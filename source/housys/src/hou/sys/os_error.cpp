// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/os_error.hpp"



namespace hou
{

os_error::os_error(const std::string& path, uint line, os_error_code ec)
  : exception(path, line,
      format_string(
        u8"OS error with code %d: %d", ec, get_os_error_message(ec).c_str()))
{}

}  // namespace hou
