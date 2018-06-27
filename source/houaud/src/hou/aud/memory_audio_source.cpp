// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/memory_audio_source.hpp"

#include "hou/aud/audio_buffer.hpp"



namespace hou
{

memory_audio_source::memory_audio_source(const audio_buffer* buffer)
  : audio_source()
  , m_buffer_ref(nullptr)
{
  set_buffer(buffer);
}



void memory_audio_source::set_buffer(const audio_buffer* buffer)
{
  stop();
  m_buffer_ref = buffer;
  if(buffer != nullptr)
  {
    al::set_source_buffer(get_handle(), buffer->get_handle().get_name());
  }
  else
  {
    al::set_source_buffer(get_handle(), 0);
  }
}



const audio_buffer* memory_audio_source::get_buffer() const
{
  return m_buffer_ref;
}



audio_buffer_format memory_audio_source::get_format() const
{
  return m_buffer_ref == nullptr ? audio_buffer_format::mono8
                                 : m_buffer_ref->get_format();
}



uint memory_audio_source::get_channel_count() const
{
  return m_buffer_ref == nullptr ? 1u : m_buffer_ref->get_channel_count();
}



uint memory_audio_source::get_bytes_per_sample() const
{
  return m_buffer_ref == nullptr ? 1u : m_buffer_ref->get_bytes_per_sample();
}



uint memory_audio_source::get_sample_rate() const
{
  return m_buffer_ref == nullptr ? 1u : m_buffer_ref->get_sample_rate();
}



uint memory_audio_source::get_sample_count() const
{
  return m_buffer_ref == nullptr ? 0u : m_buffer_ref->get_sample_count();
}



void memory_audio_source::set_looping(bool looping)
{
  audio_source::set_looping(looping);
}



bool memory_audio_source::is_looping() const
{
  return audio_source::is_looping();
}



void memory_audio_source::on_set_sample_pos(uint pos)
{
  audio_source::on_set_sample_pos(pos);
}



uint memory_audio_source::on_get_sample_pos() const
{
  return audio_source::on_get_sample_pos();
}

}  // namespace hou
