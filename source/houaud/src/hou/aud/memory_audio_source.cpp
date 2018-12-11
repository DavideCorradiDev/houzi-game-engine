// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/memory_audio_source.hpp"

#include "hou/aud/audio_buffer.hpp"



namespace hou
{

memory_audio_source::memory_audio_source(std::shared_ptr<audio_buffer> buffer)
  : audio_source()
  , m_buffer_ref(nullptr)
{
  set_buffer(buffer);
}



memory_audio_source::~memory_audio_source()
{
  // ~memory_audio_source is called before ~audio_source.
  // Therefore, if this memory_audio_source is the sole owner of the buffer,
  // the al buffer will be destroyed before the al source.
  // OpenAL forbids destroying an al buffer which is currently in use by an al
  // source, therefore this will result in an error.
  // To avoid this, the buffer in the audio source must be explicitly reset.
  // It is also necessary to check if the current source handle is valid, in
  // case the object was moved and is not in a valid state anymore.
  if(get_handle().get_name() != 0)
  {
    stop();
    al::set_source_buffer(get_handle(), 0);
  }
}



void memory_audio_source::set_buffer(std::shared_ptr<audio_buffer> buffer)
{
  stop();
  if(buffer != nullptr)
  {
    al::set_source_buffer(get_handle(), buffer->get_handle().get_name());
  }
  else
  {
    al::set_source_buffer(get_handle(), 0);
  }
  m_buffer_ref = buffer;
}



const audio_buffer* memory_audio_source::get_buffer() const
{
  return m_buffer_ref.get();
}



audio_source_state memory_audio_source::get_state() const
{
  return audio_source::get_state();
}



bool memory_audio_source::is_valid() const
{
  return m_buffer_ref != nullptr;
}



bool memory_audio_source::is_looping() const
{
  return audio_source::is_looping();
}



void memory_audio_source::on_set_looping(bool looping)
{
  audio_source::on_set_looping(looping);
}



void memory_audio_source::on_set_sample_pos(uint pos)
{
  audio_source::on_set_sample_pos(pos);
}



uint memory_audio_source::on_get_sample_pos() const
{
  return audio_source::on_get_sample_pos();
}



void memory_audio_source::on_play()
{
  audio_source::on_play();
}



void memory_audio_source::on_pause()
{
  audio_source::on_pause();
}



audio_buffer_format memory_audio_source::get_format_internal() const
{
  HOU_INVARIANT(m_buffer_ref != nullptr);
  return m_buffer_ref->get_format();
}



uint memory_audio_source::get_channel_count_internal() const
{
  HOU_INVARIANT(m_buffer_ref != nullptr);
  return m_buffer_ref->get_channel_count();
}



uint memory_audio_source::get_bytes_per_sample_internal() const
{
  HOU_INVARIANT(m_buffer_ref != nullptr);
  return m_buffer_ref->get_bytes_per_sample();
}



uint memory_audio_source::get_sample_rate_internal() const
{
  HOU_INVARIANT(m_buffer_ref != nullptr);
  return m_buffer_ref->get_sample_rate();
}



uint memory_audio_source::get_sample_count_internal() const
{
  HOU_INVARIANT(m_buffer_ref != nullptr);
  return m_buffer_ref->get_sample_count();
}

}  // namespace hou
