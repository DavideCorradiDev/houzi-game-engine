// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_exceptions.hpp"



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



read_error::read_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to read data.")
{}



write_error::write_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to write data.")
{}



cursor_error::cursor_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to set or get the file cursor position.")
{}



invalid_image_data::invalid_image_data(const std::string& path, uint line)
  : exception(path, line, u8"Invalid or corrupted image data.")
{}



platform_error::platform_error(
  const std::string& path, uint line, const std::string& description)
  : exception(path, line,
      format_string(
        u8"A platform-specific error occurred:\n%s", description.c_str()))
{}

}  // namespace hou
