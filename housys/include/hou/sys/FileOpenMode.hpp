// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_FILE_OPEN_MODE_HPP
#define HOU_SYS_FILE_OPEN_MODE_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for file open mode. */
enum class FileOpenMode
{
  /** Read mode. */
  Read,
  /** Write mode. */
  Write,
  /** Append mode. */
  Append,
};

/** Writes a FileOpenMode enum into a stream.
 *
 *  \param os the stream.
 *  \param fom the FileOpenMode enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, FileOpenMode fom);

}

#endif

