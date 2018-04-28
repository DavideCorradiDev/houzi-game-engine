// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/TextFileIn.hpp"

#include "hou/cor/error.hpp"



namespace hou
{

TextFileIn::TextFileIn(const std::string& path)
  : non_copyable()
  , TextStreamIn()
  , mFile(path, FileOpenMode::Read, FileType::Text)
  , mByteCount(0u)
  , mElementCount(0u)
{}



TextFileIn::TextFileIn(TextFileIn&& other)
  : TextStreamIn(std::move(other))
  , mFile(std::move(other.mFile))
  , mByteCount(std::move(other.mByteCount))
  , mElementCount(std::move(other.mElementCount))
{}



TextFileIn::~TextFileIn()
{}



bool TextFileIn::eof() const
{
  return mFile.eof();
}



bool TextFileIn::error() const
{
  return mFile.error();
}



size_t TextFileIn::getByteCount() const
{
  return mFile.getByteCount();
}



size_t TextFileIn::getReadByteCount() const
{
  return mByteCount;
}



size_t TextFileIn::getReadElementCount() const
{
  return mElementCount;
}



TextFileIn::TextPosition TextFileIn::getTextPos() const
{
  return createPositionObject(mFile.tell());
}



TextStream& TextFileIn::setTextPos(TextFileIn::TextPosition pos)
{
  mFile.seekSet(convertPositionObject(pos));
  return *this;
}



void TextFileIn::onRead(void* buf, size_t elementSize, size_t bufSize)
{
  mElementCount = mFile.read(buf, elementSize, bufSize);
  mByteCount = mElementCount * elementSize;
}

}

