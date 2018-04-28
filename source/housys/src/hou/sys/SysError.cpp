// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_error.hpp"



namespace hou
{

std::string get_text(sys_error ec)
{
  switch(ec)
  {
    case sys_error::file_close:
      return u8"Error closing ph_file (fid = %d).";
    case sys_error::file_flush:
      return u8"Error flushing ph_file buffer.";
    case sys_error::file_open:
      return u8"Error opening ph_file: '%s'.";
    case sys_error::file_read:
      return u8"Error reading from ph_file.";
    case sys_error::file_seek:
      return u8"Error setting ph_file cursor.";
    case sys_error::file_tell:
      return u8"Error getting ph_file cursor.";
    case sys_error::file_write:
      return u8"Error writing to ph_file.";
    case sys_error::image_bmp_read:
      return u8"Error reading BMP ph_image from path '%s'.";
    case sys_error::image_bmp_write:
      return u8"Error writing BMP ph_image to path '%s'.";
    case sys_error::image_png_read:
      return u8"Error reading PNG ph_image from path '%s'.";
    case sys_error::image_jpg_read:
      return u8"Error reading JPG ph_image from path '%s'.";
    default:
      return u8"";
  }
}

}

