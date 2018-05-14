// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_STREAM_HPP
#define HOU_SYS_BINARY_STREAM_HPP

#include "hou/sys/stream.hpp"

#include "hou/sys/sys_export.hpp"



namespace hou
{

/** binary stream interface.
 */
class HOU_SYS_API binary_stream : public stream
{
public:
  /** Position indicator representing the number of bytes from the beginning
   * of the file
   */
  using byte_position = long;

  /** Offset of the byte position indicator in bytes.
   */
  using byte_offset = long;

public:

  /** Gets the current byte position indicator.
   *
   * \throws hou::cursor_error in case of an error.
   *
   * \return the current byte position indicator.
   */
  virtual byte_position get_byte_pos() const = 0;

  /** Sets the current byte position indicator.
   *
   * Throws if pos is negative.
   * Derived classes may have different behaviour when the position is set
   * over the end of the file.
   * a value in the interval [0; byte_count] is always valid.
   *
   * \param pos the byte position indicator value.
   *
   * \throws hou::cursor_error in case of an error.
   *
   * \return a reference to this stream.
   */
  virtual binary_stream& set_byte_pos(byte_position pos) = 0;

  /** Moves the current byte position indicator.
   *
   * Throws if the offset moves the position indicator to a negative position.
   * Derived classes may have different behaviour when the position is set
   * over the end of the file.
   * a value in the interval [0; byte_count] is always valid.
   *
   * \param offset the byte position indicator offset.
   *
   * \throws hou::cursor_error in case of an error.
   *
   * \return a reference to this stream.
   */
  virtual binary_stream& move_byte_pos(byte_offset offset) = 0;
};

}  // namespace hou

#endif
