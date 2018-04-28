// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_OPEN_MODE_HPP
#define HOU_SYS_FILE_OPEN_MODE_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for ph_file open mode. */
enum class file_open_mode
{
  /** read mode. */
  read,
  /** write mode. */
  write,
  /** append mode. */
  append,
};

/** Writes a file_open_mode enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param fom the file_open_mode enum.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, file_open_mode fom);

}

#endif

