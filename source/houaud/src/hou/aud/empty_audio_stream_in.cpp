// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/empty_audio_stream_in.hpp"

#include "hou/sys/sys_error.hpp"



namespace hou
{

empty_audio_stream_in::empty_audio_stream_in()
  : audio_stream_in()
{
  set_format(1u, 1u);
  set_sample_rate(1u);
}



empty_audio_stream_in::~empty_audio_stream_in()
{}



bool empty_audio_stream_in::eof() const
{
  return true;
}



bool empty_audio_stream_in::error() const
{
  return false;
}



size_t empty_audio_stream_in::get_byte_count() const
{
  return 0u;
}



size_t empty_audio_stream_in::get_read_element_count() const
{
  return 0u;
}



empty_audio_stream_in::byte_position empty_audio_stream_in::get_byte_pos() const
{
  return 0u;
}



binary_stream& empty_audio_stream_in::set_byte_pos(byte_position pos)
{
  HOU_RUNTIME_CHECK(pos == 0, get_text(sys_error::file_seek));
  HOU_EXPECT(pos == 0);
  return *this;
}



binary_stream& empty_audio_stream_in::move_byte_pos(byte_offset offset)
{
  HOU_RUNTIME_CHECK(offset == 0, get_text(sys_error::file_seek));
  return *this;
}



size_t empty_audio_stream_in::get_sample_count() const
{
  return 0u;
}



empty_audio_stream_in::sample_position empty_audio_stream_in::get_sample_pos()
  const
{
  return 0u;
}



audio_stream_in& empty_audio_stream_in::set_sample_pos(sample_position pos)
{
  HOU_RUNTIME_CHECK(pos == 0, get_text(sys_error::file_seek));
  return *this;
}



audio_stream_in& empty_audio_stream_in::move_sample_pos(sample_offset offset)
{
  HOU_RUNTIME_CHECK(offset == 0, get_text(sys_error::file_seek));
  return *this;
}



size_t empty_audio_stream_in::get_read_byte_count() const
{
  return 0u;
}



void empty_audio_stream_in::on_read(void*, size_t, size_t)
{}

}  // namespace hou
