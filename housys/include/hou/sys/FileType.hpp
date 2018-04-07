// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_FILE_TYPE_HPP
#define HOU_SYS_FILE_TYPE_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for a file type. */
enum class FileType
{
  /** Binary file. */
  Binary,
  /** Text file. */
  Text,
};

/** Writes a FileType enum into a stream.
 *
 *  \param os the stream.
 *  \param fom the FileType enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, FileType fom);

}

#endif

