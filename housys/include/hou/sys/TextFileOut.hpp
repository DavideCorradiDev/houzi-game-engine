// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_TEXT_FILE_OUT_HPP
#define HOU_SYS_TEXT_FILE_OUT_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/TextStreamOut.hpp"

#include "hou/cor/NonCopyable.hpp"

#include "hou/sys/File.hpp"



namespace hou
{

/** Output text file stream.
 */
class HOU_SYS_API TextFileOut
  : public NonCopyable
  , public TextStreamOut
{
public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the file to be opened.
   */
  explicit TextFileOut(const std::string& path);

  /** Move constructor.
   *
   *  \param other the other object.
   */
  TextFileOut(TextFileOut&& other);

  /** Destructor.
   */
  virtual ~TextFileOut();

  // Stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t getByteCount() const final;

  // StreamOut overrides.
  size_t getWriteByteCount() const final;
  size_t getWriteElementCount() const final;

  // TextStream overrides.
  TextPosition getTextPos() const final;
  TextStream& setTextPos(TextPosition pos) final;

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

