// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_TYPE_HPP
#define HOU_SYS_FILE_TYPE_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for a file type. */
enum class file_type
{
  /** Binary file. */
  binary,
  /** Text file. */
  text,
};

/** Writes a file_type enum into a ph_stream.
 *
 * \param os the ph_stream.
 *
 * \param fom the file_type enum.
 *
 * \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, file_type fom);

}  // namespace hou

#endif
