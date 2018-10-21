// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/threaded_audio_source.hpp"

#include "hou/aud/audio_stream_in.hpp"

#include "hou/cor/narrow_cast.hpp"

#include <functional>



namespace hou
{

threaded_audio_source::threaded_audio_source(
  std::unique_ptr<audio_stream_in> as)
  : streaming_audio_source_base(std::move(as))
  , m_thread()
  , m_thread_mutex()
  , m_streaming_thread_end_requested(false)
{
  m_thread
    = std::thread(std::bind(&threaded_audio_source::thread_function, this));
}



threaded_audio_source::~threaded_audio_source()
{
  m_streaming_thread_end_requested = true;
  stop();
  m_thread.join();
}



void threaded_audio_source::set_stream(std::unique_ptr<audio_stream_in> as)
{
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  streaming_audio_source_base::set_stream(std::move(as));
}



void threaded_audio_source::set_buffer_count(size_t buffer_count)
{
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  streaming_audio_source_base::set_buffer_count(buffer_count);
}



void threaded_audio_source::set_buffer_sample_count(size_t buffer_sample_count)
{
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  streaming_audio_source_base::set_buffer_sample_count(buffer_sample_count);
}



void threaded_audio_source::thread_function()
{
  while(!m_streaming_thread_end_requested)
  {
    std::lock_guard<std::mutex> lock(m_thread_mutex);
    update_buffer_queue();
  }
}



void threaded_audio_source::on_set_sample_pos(uint value)
{
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  streaming_audio_source_base::on_set_sample_pos(value);
}

}  // namespace hou
