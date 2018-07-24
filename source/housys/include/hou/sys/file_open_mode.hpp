// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_FILE_OPEN_MODE_HPP
#define HOU_SYS_FILE_OPEN_MODE_HPP

#include "hou/sys/sys_config.hpp"

#include <iostream>



namespace hou
{

/**
 * Enumeration for file open mode. */
enum class file_open_mode
{
  /**
   * Read mode. */
  read,
  /**
   * Write mode. */
  write,
  /**
   * Append mode. */
  append,
};

/**
 * Writes a file_open_mode enum into a stream.
 *
 * \param os the stream.
 *
 * \param fom the file_open_mode enum.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, file_open_mode fom);

}  // namespace hou

#endif
