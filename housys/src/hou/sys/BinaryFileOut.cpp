// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/BinaryFileOut.hpp"



namespace hou
{

BinaryFileOut::BinaryFileOut(const std::string& path)
  : NonCopyable()
  , BinaryStreamOut()
  , mFile(path, FileOpenMode::Write, FileType::Binary)
  , mByteCount(0u)
  , mElementCount(0u)
{}



BinaryFileOut::BinaryFileOut(BinaryFileOut&& other)
  : BinaryStreamOut(std::move(other))
  , mFile(std::move(other.mFile))
  , mByteCount(std::move(other.mByteCount))
  , mElementCount(std::move(other.mElementCount))
{}



BinaryFileOut::~BinaryFileOut()
{}



bool BinaryFileOut::eof() const
{
  return mFile.eof();
}



bool BinaryFileOut::error() const
{
  return mFile.error();
}



size_t BinaryFileOut::getByteCount() const
{
  return mFile.getByteCount();
}



size_t BinaryFileOut::getWriteByteCount() const
{
  return mByteCount;
}



size_t BinaryFileOut::getWriteElementCount() const
{
  return mElementCount;
}



BinaryFileOut::BytePosition BinaryFileOut::getBytePos() const
{
  return mFile.tell();
}



BinaryStream& BinaryFileOut::setBytePos(BinaryFileOut::BytePosition pos)
{
  mFile.seekSet(pos);
  return *this;
}



BinaryStream& BinaryFileOut::moveBytePos(BinaryFileOut::ByteOffset offset)
{
  mFile.seekOffset(offset);
  return *this;
}



void BinaryFileOut::onWrite(const void* buf, size_t elementSize, size_t bufSize)
{
  mFile.write(buf, elementSize, bufSize);
  mElementCount = bufSize;
  mByteCount = elementSize * bufSize;
}

}

