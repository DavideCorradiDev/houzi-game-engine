// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_TEXT_FILE_IN_HPP
#define HOU_SYS_TEXT_FILE_IN_HPP

#include "hou/sys/SysExport.hpp"
#include "hou/sys/TextStreamIn.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/File.hpp"



namespace hou
{

/** Input text file stream.
 */
class HOU_SYS_API TextFileIn
  : public non_copyable
  , public TextStreamIn
{
public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid.
   *
   *  \param path the path to the file to be opened.
   */
  explicit TextFileIn(const std::string& path);

  /** Move constructor.
   *
   *  \param other the other object.
   */
  TextFileIn(TextFileIn&& other);

  /** Destructor.
   */
  virtual ~TextFileIn();

  // Stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t getByteCount() const final;

  // StreamIn overrides.
  size_t getReadByteCount() const final;
  size_t getReadElementCount() const final;

  // TextStream overrides.
  TextPosition getTextPos() const final;
  TextStream& setTextPos(TextPosition pos) final;

protected:
  // StreamIn overrides.
  void onRead(void* buf, size_t elementSize, size_t bufSize) final;

private:
  File mFile;
  size_t mByteCount;
  size_t mElementCount;
};

}

#endif

