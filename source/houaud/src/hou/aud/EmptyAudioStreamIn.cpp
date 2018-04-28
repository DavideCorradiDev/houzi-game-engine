// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/EmptyAudioStreamIn.hpp"

#include "hou/sys/SysError.hpp"



namespace hou
{

EmptyAudioStreamIn::EmptyAudioStreamIn()
  : AudioStreamIn()
{
  setFormat(1u, 1u);
  setSampleRate(1u);
}



EmptyAudioStreamIn::~EmptyAudioStreamIn()
{}



bool EmptyAudioStreamIn::eof() const
{
  return true;
}



bool EmptyAudioStreamIn::error() const
{
  return false;
}



size_t EmptyAudioStreamIn::getByteCount() const
{
  return 0u;
}



size_t EmptyAudioStreamIn::getReadElementCount() const
{
  return 0u;
}



EmptyAudioStreamIn::BytePosition EmptyAudioStreamIn::getBytePos() const
{
  return 0u;
}



BinaryStream& EmptyAudioStreamIn::setBytePos(BytePosition pos)
{
  HOU_RUNTIME_CHECK(pos == 0, get_text(SysError::FileSeek));
  HOU_EXPECT(pos == 0);
  return *this;
}



BinaryStream& EmptyAudioStreamIn::moveBytePos(ByteOffset offset)
{
  HOU_RUNTIME_CHECK(offset == 0, get_text(SysError::FileSeek));
  return *this;
}



size_t EmptyAudioStreamIn::getSampleCount() const
{
  return 0u;
}



EmptyAudioStreamIn::SamplePosition EmptyAudioStreamIn::getSamplePos() const
{
  return 0u;
}



AudioStreamIn& EmptyAudioStreamIn::setSamplePos(SamplePosition pos)
{
  HOU_RUNTIME_CHECK(pos == 0, get_text(SysError::FileSeek));
  return *this;
}



AudioStreamIn& EmptyAudioStreamIn::moveSamplePos(SampleOffset offset)
{
  HOU_RUNTIME_CHECK(offset == 0, get_text(SysError::FileSeek));
  return *this;
}



size_t EmptyAudioStreamIn::getReadByteCount() const
{
  return 0u;
}



void EmptyAudioStreamIn::onRead(void*, size_t, size_t)
{}

}

