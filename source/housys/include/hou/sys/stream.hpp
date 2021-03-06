// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_STREAM_HPP
#define HOU_SYS_STREAM_HPP

#include "hou/sys/sys_config.hpp"



namespace hou
{

/**
 * Base stream interface.
 */
class HOU_SYS_API stream
{
public:
  /**
   * Destructor.
   */
  virtual ~stream(){};

  /**
   * Checks the end of stream indicator.
   *
   * \return true if the end of file indicator is set.
   */
  virtual bool eof() const noexcept = 0;

  /**
   * Checks the error indicator.
   *
   * \return true if the error indicator is set.
   */
  virtual bool error() const noexcept = 0;

  /**
   * Retrieves the total number of bytes in the stream.
   *
   * \return the size of the stream in bytes.
   */
  virtual size_t get_byte_count() const noexcept = 0;
};

}  // namespace hou

#endif
