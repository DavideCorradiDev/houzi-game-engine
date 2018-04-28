// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_STREAM_HPP
#define HOU_SYS_BINARY_STREAM_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/sys/stream.hpp"



namespace hou
{

/** binary ph_stream interface.
 */
class HOU_SYS_API binary_stream
  : public stream
{
public:
  /** Position indicator representing the number of bytes from the beginning
   *  of the ph_file
   */
  using byte_position = long;

  /** Offset of the byte position indicator in bytes.
   */
  using byte_offset = long;

public:
  /** Destructor.
   */
  virtual ~binary_stream() {};

  /** Gets the current byte position indicator.
   *
   *  \return the current byte position indicator.
   */
  virtual byte_position get_byte_pos() const = 0;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative.
   *  Derived classes may have different behaviour when the position is set
   *  over the end of the ph_file.
   *  A value in the interval [0; byteCount] is always valid.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this ph_stream.
   */
  virtual binary_stream& set_byte_pos(byte_position pos) = 0;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position.
   *  Derived classes may have different behaviour when the position is set
   *  over the end of the ph_file.
   *  A value in the interval [0; byteCount] is always valid.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this ph_stream.
   */
  virtual binary_stream& move_byte_pos(byte_offset offset) = 0;
};

}

#endif


