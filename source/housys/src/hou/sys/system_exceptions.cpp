// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/system_exceptions.hpp"



namespace hou
{

file_open_error::file_open_error(
  const std::string& path, uint line, const std::string& filepath)
  : exception(path, line,
      format_string(u8"Failed to open file '%s'.", filepath.c_str()))
{}



file_read_error::file_read_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to read from a file.")
{}



file_write_error::file_write_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to write to a file.")
{}



file_cursor_error::file_cursor_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to set the cursor position in a file.")
{}



image_read_error::image_read_error(
  const std::string& path, uint line, const std::string& filepath)
  : exception(path, line,
      format_string(u8"Failed to read from image file '%s'.", filepath.c_str()))
{}



image_write_error::image_write_error(
  const std::string& path, uint line, const std::string& filepath)
  : exception(path, line,
      format_string(u8"Failed to write to image file '%s'.", filepath.c_str()))
{}

}  // namespace
