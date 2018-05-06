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



file_close_error::file_close_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to close the file.")
{}



file_read_error::file_read_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to read from the file.")
{}



file_write_error::file_write_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to write to the file.")
{}



file_cursor_error::file_cursor_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to set the cursor position in the file.")
{}



image_read_error::image_read_error(
  const std::string& path, uint line, const std::string& filepath)
  : exception(path, line,
      format_string(
        u8"Failed to read the image from file '%s'.", filepath.c_str()))
{}



image_write_error::image_write_error(
  const std::string& path, uint line, const std::string& filepath)
  : exception(path, line,
      format_string(
        u8"Failed to write the image to file '%s'.", filepath.c_str()))
{}

}  // namespace hou
