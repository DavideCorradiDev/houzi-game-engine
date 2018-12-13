// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/automatic_stream_audio_source.hpp"

#include <functional>



namespace hou
{

automatic_stream_audio_source::automatic_stream_audio_source(
  std::unique_ptr<audio_stream_in> as)
  : stream_audio_source(std::move(as))
  , m_thread()
  , m_streaming_thread_end_requested(false)
  , m_stream_mutex()
  , m_processing_buffer_flag_mutex()
{
  m_thread = std::thread(
    std::bind(&automatic_stream_audio_source::thread_function, this));
}



automatic_stream_audio_source::~automatic_stream_audio_source()
{
  if(get_handle().get_name() != 0)
  {
    m_streaming_thread_end_requested = true;
    stop();
    m_thread.join();
  }
}



audio_source_state automatic_stream_audio_source::get_state() const
{
  std::lock_guard<std::mutex> lock(m_processing_buffer_flag_mutex);
  return stream_audio_source::get_state();
}



void automatic_stream_audio_source::set_stream(
  std::unique_ptr<audio_stream_in> as)
{
  std::lock_guard<std::mutex> lock(m_stream_mutex);
  stream_audio_source::set_stream(std::move(as));
}



void automatic_stream_audio_source::set_buffer_count(size_t buffer_count)
{
  std::lock_guard<std::mutex> lock(m_stream_mutex);
  stream_audio_source::set_buffer_count(buffer_count);
}



void automatic_stream_audio_source::set_buffer_sample_count(
  size_t buffer_sample_count)
{
  std::lock_guard<std::mutex> lock(m_stream_mutex);
  stream_audio_source::set_buffer_sample_count(buffer_sample_count);
}



void automatic_stream_audio_source::on_set_looping(bool looping)
{
  std::lock_guard<std::mutex> lock(m_stream_mutex);
  stream_audio_source::on_set_looping(looping);
}



void automatic_stream_audio_source::on_set_sample_pos(uint value)
{
  std::lock_guard<std::mutex> lock(m_stream_mutex);
  stream_audio_source::on_set_sample_pos(value);
}



uint automatic_stream_audio_source::on_get_sample_pos() const
{
  std::lock_guard<std::mutex> lock(m_stream_mutex);
  return stream_audio_source::on_get_sample_pos();
}



void automatic_stream_audio_source::on_play()
{
  std::lock_guard<std::mutex> lock(m_processing_buffer_flag_mutex);
  stream_audio_source::on_play();
}



void automatic_stream_audio_source::on_pause()
{
  std::lock_guard<std::mutex> lock(m_processing_buffer_flag_mutex);
  stream_audio_source::on_pause();
}



void automatic_stream_audio_source::thread_function()
{
  while(!m_streaming_thread_end_requested)
  {
    {
      std::lock_guard<std::mutex> stream_lock(m_stream_mutex);
      std::lock_guard<std::mutex> proc_lock(m_processing_buffer_flag_mutex);
      update_buffer_queue();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10u));
  }
}

}  // namespace hou
