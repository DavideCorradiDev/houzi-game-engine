// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/TextFileOut.hpp"



namespace hou
{

TextFileOut::TextFileOut(const std::string& path)
  : NonCopyable()
  , TextStreamOut()
  , mFile(path, FileOpenMode::Write, FileType::Binary)
  , mByteCount(0u)
  , mElementCount(0u)
{}



TextFileOut::TextFileOut(TextFileOut&& other)
  : TextStreamOut(std::move(other))
  , mFile(std::move(other.mFile))
  , mByteCount(std::move(other.mByteCount))
  , mElementCount(std::move(other.mElementCount))
{}



TextFileOut::~TextFileOut()
{}



bool TextFileOut::eof() const
{
  return mFile.eof();
}



bool TextFileOut::error() const
{
  return mFile.error();
}



size_t TextFileOut::getByteCount() const
{
  return mFile.getByteCount();
}



size_t TextFileOut::getWriteByteCount() const
{
  return mByteCount;
}



size_t TextFileOut::getWriteElementCount() const
{
  return mElementCount;
}



TextFileOut::TextPosition TextFileOut::getTextPos() const
{
  return createPositionObject(mFile.tell());
}



TextStream& TextFileOut::setTextPos(TextFileOut::TextPosition pos)
{
  mFile.seekSet(convertPositionObject(pos));
  return *this;
}



void TextFileOut::onWrite(const void* buf, size_t elementSize, size_t bufSize)
{
  mFile.write(buf, elementSize, bufSize);
  mElementCount = bufSize;
  mByteCount = elementSize * bufSize;
}

}

