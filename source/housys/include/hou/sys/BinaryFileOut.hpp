// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_BINARY_FILE_OUT_HPP
#define HOU_SYS_BINARY_FILE_OUT_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/BinaryStreamOut.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/File.hpp"



namespace hou
{

/** Output binary file stream.
 */
class HOU_SYS_API BinaryFileOut
  : public non_copyable
  , public BinaryStreamOut
{
public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the file to be opened.
   */
  explicit BinaryFileOut(const std::string& path);

  /** Move constructor.
   *
   *  \param other the other object.
   */
  BinaryFileOut(BinaryFileOut&& other);

  /** Destructor.
   */
  virtual ~BinaryFileOut();

  // Stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t getByteCount() const final;

  // StreamOut overrides.
  size_t getWriteByteCount() const final;
  size_t getWriteElementCount() const final;

  // BinaryStream overrides.
  BytePosition getBytePos() const final;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative.
   *  The position may be over the end of the file.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this stream.
   */
  BinaryStream& setBytePos(BytePosition pos) final;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position.
   *  The position may be over the end of the file.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this stream.
   */
  BinaryStream& moveBytePos(ByteOffset offset) final;

protected:
  // StreamOut overrides.
  void onWrite(const void* buf, size_t elementSize, size_t bufSize) final;

private:
  File mFile;
  size_t mByteCount;
  size_t mElementCount;
};

}

#endif

