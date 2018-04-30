// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_ERROR_HPP
#define HOU_SYS_SYS_ERROR_HPP

#include "hou/sys/sys_export.hpp"

#include <string>



namespace hou
{

/** system module error codes. */
enum class sys_error
{
  file_close,
  file_flush,
  file_open,
  file_read,
  file_seek,
  file_tell,
  file_write,
  image_bmp_read,
  image_bmp_write,
  image_png_read,
  image_jpg_read,
};

/** Retrieves the message string associated to a system module error code.
 *
 * \param ec the error code.
 */
HOU_SYS_API std::string get_text(sys_error ec);

}  // namespace hou

#endif
