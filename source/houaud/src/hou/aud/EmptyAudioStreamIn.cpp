// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/EmptyAudioStreamIn.hpp"

#include "hou/sys/sys_error.hpp"



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



size_t EmptyAudioStreamIn::get_byte_count() const
{
  return 0u;
}



size_t EmptyAudioStreamIn::get_read_element_count() const
{
  return 0u;
}



EmptyAudioStreamIn::byte_position EmptyAudioStreamIn::get_byte_pos() const
{
  return 0u;
}



binary_stream& EmptyAudioStreamIn::set_byte_pos(byte_position pos)
{
  HOU_RUNTIME_CHECK(pos == 0, get_text(sys_error::file_seek));
  HOU_EXPECT(pos == 0);
  return *this;
}



binary_stream& EmptyAudioStreamIn::move_byte_pos(byte_offset offset)
{
  HOU_RUNTIME_CHECK(offset == 0, get_text(sys_error::file_seek));
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
  HOU_RUNTIME_CHECK(pos == 0, get_text(sys_error::file_seek));
  return *this;
}



AudioStreamIn& EmptyAudioStreamIn::moveSamplePos(SampleOffset offset)
{
  HOU_RUNTIME_CHECK(offset == 0, get_text(sys_error::file_seek));
  return *this;
}



size_t EmptyAudioStreamIn::get_read_byte_count() const
{
  return 0u;
}



void EmptyAudioStreamIn::on_read(void*, size_t, size_t)
{}

}

