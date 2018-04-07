// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_BINARY_STREAM_HPP
#define HOU_SYS_BINARY_STREAM_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/Stream.hpp"



namespace hou
{

/** Binary stream interface.
 */
class HOU_SYS_API BinaryStream
  : public Stream
{
public:
  /** Position indicator representing the number of bytes from the beginning
   *  of the file
   */
  using BytePosition = long;

  /** Offset of the byte position indicator in bytes.
   */
  using ByteOffset = long;

public:
  /** Destructor.
   */
  virtual ~BinaryStream() {};

  /** Gets the current byte position indicator.
   *
   *  \return the current byte position indicator.
   */
  virtual BytePosition getBytePos() const = 0;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative.
   *  Derived classes may have different behaviour when the position is set
   *  over the end of the file.
   *  A value in the interval [0; byteCount] is always valid.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this stream.
   */
  virtual BinaryStream& setBytePos(BytePosition pos) = 0;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position.
   *  Derived classes may have different behaviour when the position is set
   *  over the end of the file.
   *  A value in the interval [0; byteCount] is always valid.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this stream.
   */
  virtual BinaryStream& moveBytePos(ByteOffset offset) = 0;
};

}

#endif


