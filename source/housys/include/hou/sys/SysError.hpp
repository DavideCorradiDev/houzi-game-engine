// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYS_ERROR_HPP
#define HOU_SYS_SYS_ERROR_HPP

#include "hou/sys/SysExport.hpp"

#include <string>



namespace hou
{

/** System module error codes. */
enum class SysError
{
  FileClose,
  FileFlush,
  FileOpen,
  FileRead,
  FileSeek,
  FileTell,
  FileWrite,
  ImageBmpRead,
  ImageBmpWrite,
  ImagePngRead,
  ImageJpgRead,
};

/** Retrieves the message string associated to a system module error code.
 *
 *  \param ec the error code.
 */
HOU_SYS_API std::string get_text(SysError ec);

}

#endif

