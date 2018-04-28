// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/BinaryFileIn.hpp"



namespace hou
{

BinaryFileIn::BinaryFileIn(const std::string& path)
  : non_copyable()
  , BinaryStreamIn()
  , mFile(path, FileOpenMode::Read, FileType::Binary)
  , mByteCount(0u)
  , mElementCount(0u)
{}



BinaryFileIn::BinaryFileIn(BinaryFileIn&& other)
  : BinaryStreamIn(std::move(other))
  , mFile(std::move(other.mFile))
  , mByteCount(std::move(other.mByteCount))
  , mElementCount(std::move(other.mElementCount))
{}



BinaryFileIn::~BinaryFileIn()
{}



bool BinaryFileIn::eof() const
{
  return mFile.eof();
}



bool BinaryFileIn::error() const
{
  return mFile.error();
}



size_t BinaryFileIn::getByteCount() const
{
  return mFile.getByteCount();
}



size_t BinaryFileIn::getReadByteCount() const
{
  return mByteCount;
}



size_t BinaryFileIn::getReadElementCount() const
{
  return mElementCount;
}



BinaryFileIn::BytePosition BinaryFileIn::getBytePos() const
{
  return mFile.tell();
}



BinaryStream& BinaryFileIn::setBytePos(BinaryFileIn::BytePosition pos)
{
  mFile.seekSet(pos);
  return *this;
}



BinaryStream& BinaryFileIn::moveBytePos(BinaryFileIn::ByteOffset offset)
{
  mFile.seekOffset(offset);
  return *this;
}



void BinaryFileIn::onRead(void* buf, size_t elementSize, size_t bufSize)
{
  mElementCount = mFile.read(buf, elementSize, bufSize);
  mByteCount = mElementCount * elementSize;
}

}

