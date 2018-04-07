// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_STREAM_HPP
#define HOU_SYS_STREAM_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

/** Base stream interface.
 */
class HOU_SYS_API Stream
{
public:
  /** Destructor.
   */
  virtual ~Stream() {};

  /** Checks the end of file indicator.
   *
   *  \return true if the end of file indicator is set.
   */
  virtual bool eof() const = 0;

  /** Checks the error indicator.
   *
   *  \return true if the error indicator is set.
   */
  virtual bool error() const = 0;

  /** Retrieves the total number of bytes in the stream.
   *
   *  \return the size of the stream in bytes.
   */
  virtual size_t getByteCount() const = 0;
};

}

#endif

