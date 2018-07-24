// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/streaming_audio_source.hpp"

#include "hou/aud/audio_stream_in.hpp"
#include "hou/aud/empty_audio_stream_in.hpp"

#include "hou/cor/narrow_cast.hpp"

#include <functional>



namespace hou
{

namespace
{

constexpr size_t g_default_buffer_count = 3u;
constexpr size_t g_default_buffer_byte_count = 44100u;

}  // namespace



streaming_audio_source::streaming_audio_source()
  : streaming_audio_source(std::make_unique<empty_audio_stream_in>())
{}



streaming_audio_source::streaming_audio_source(
  not_null<std::unique_ptr<audio_stream_in>> as)
  : audio_source()
  , m_thread()
  , m_thread_mutex()
  , m_audio_stream(std::move(as))
  , m_buffer_queue(g_default_buffer_count)
  , m_streaming_thread_end_requested(false)
  , m_looping(false)
  , m_sample_pos(0u)
  , m_buffer_byte_count(g_default_buffer_byte_count)
{
  m_audio_stream->set_sample_pos(0u);
  m_thread
    = std::thread(std::bind(&streaming_audio_source::thread_function, this));
}



streaming_audio_source::~streaming_audio_source()
{
  stop();
  m_streaming_thread_end_requested = true;
  m_thread.join();
  free_buffers();
}



void streaming_audio_source::set_stream(
  not_null<std::unique_ptr<audio_stream_in>> as)
{
  stop();
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  m_audio_stream = std::move(as);
  set_sample_pos_and_stream_cursor(0u);
}



void streaming_audio_source::set_buffer_count(size_t buffer_count)
{
  HOU_PRECOND(buffer_count > 0u);
  stop();
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  free_buffers();
  m_buffer_queue = buffer_queue(buffer_count);
}



size_t streaming_audio_source::get_buffer_count() const
{
  return m_buffer_queue.get_buffer_count();
}



void streaming_audio_source::set_buffer_sample_count(size_t buffer_sample_count)
{
  HOU_PRECOND(buffer_sample_count > 0u);
  stop();
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  m_buffer_byte_count = buffer_sample_count
    * (m_audio_stream->get_channel_count()
        * m_audio_stream->get_bytes_per_sample());
}



size_t streaming_audio_source::get_buffer_sample_count() const
{
  return m_buffer_byte_count
    / (m_audio_stream->get_channel_count()
        * m_audio_stream->get_bytes_per_sample());
}



audio_buffer_format streaming_audio_source::get_format() const
{
  return m_audio_stream->get_format();
}



uint streaming_audio_source::get_channel_count() const
{
  return m_audio_stream->get_channel_count();
}



uint streaming_audio_source::get_bytes_per_sample() const
{
  return m_audio_stream->get_bytes_per_sample();
}



uint streaming_audio_source::get_sample_rate() const
{
  return m_audio_stream->get_sample_rate();
}



uint streaming_audio_source::get_sample_count() const
{
  return narrow_cast<uint>(m_audio_stream->get_sample_count());
}



void streaming_audio_source::set_looping(bool looping)
{
  m_looping = looping;
}



bool streaming_audio_source::is_looping() const
{
  return m_looping;
}



void streaming_audio_source::on_set_sample_pos(uint value)
{
  std::lock_guard<std::mutex> lock(m_thread_mutex);
  free_buffers();
  set_sample_pos_and_stream_cursor(value);
  fill_buffers();
}



uint streaming_audio_source::on_get_sample_pos() const
{
  uint sample_count = get_sample_count();
  return sample_count == 0u
    ? 0u
    : (m_sample_pos + audio_source::on_get_sample_pos()) % get_sample_count();
}



void streaming_audio_source::thread_function()
{
  while(!m_streaming_thread_end_requested)
  {
    std::lock_guard<std::mutex> lock(m_thread_mutex);
    free_buffers();
    if(get_state() == audio_source_state::playing)
    {
      fill_buffers();
    }
  }
}



std::vector<uint8_t> streaming_audio_source::read_data_chunk(size_t chunk_size)
{
  std::vector<uint8_t> data(chunk_size);
  m_audio_stream->read(data);
  data.resize(m_audio_stream->get_read_byte_count());
  return data;
}



void streaming_audio_source::free_buffers()
{
  uint processed_buffers = al::get_source_processed_buffers(get_handle());
  std::vector<ALuint> bufferNames(processed_buffers, 0);
  al::source_unqueue_buffers(
    get_handle(), narrow_cast<ALsizei>(bufferNames.size()), bufferNames.data());
  size_t processed_bytes = m_buffer_queue.free_buffers(processed_buffers);
  set_sample_pos_variable(m_sample_pos
    + processed_bytes
      / (m_audio_stream->get_channel_count()
          * m_audio_stream->get_bytes_per_sample()));
}



void streaming_audio_source::fill_buffers()
{
  while(get_sample_count() > 0 && m_buffer_queue.get_free_buffer_count() > 0)
  {
    std::vector<uint8_t> data = read_data_chunk(m_buffer_byte_count);
    if(data.empty())
    {
      if(m_looping)
      {
        m_audio_stream->set_sample_pos(0u);
      }
      else
      {
        return;
      }
    }
    else
    {
      const audio_buffer& buf = m_buffer_queue.fill_buffer(
        data, m_audio_stream->get_format(), m_audio_stream->get_sample_rate());
      ALuint buf_name = buf.get_handle().get_name();
      al::source_queue_buffers(get_handle(), 1u, &buf_name);
    }
  }
}



void streaming_audio_source::set_sample_pos_variable(size_t pos)
{
  uint sample_count = get_sample_count();
  m_sample_pos = sample_count == 0u ? 0u : pos % get_sample_count();
}



void streaming_audio_source::set_sample_pos_and_stream_cursor(size_t pos)
{
  set_sample_pos_variable(pos);
  m_audio_stream->set_sample_pos(
    narrow_cast<audio_stream::sample_position>(pos));
}



streaming_audio_source::buffer_queue::buffer_queue(size_t buffer_count)
  : m_buffers(buffer_count)
  , m_buffer_sample_counts()
  , m_free_buffer_count(buffer_count)
  , m_current_index(0u)
{}



size_t streaming_audio_source::buffer_queue::free_buffers(size_t count)
{
  m_free_buffer_count += count;
  HOU_DEV_ASSERT(m_free_buffer_count <= m_buffers.size());
  size_t freed_bytes = 0u;
  for(uint i = 0; i < count; ++i)
  {
    freed_bytes += m_buffer_sample_counts.front();
    m_buffer_sample_counts.pop();
  }
  return freed_bytes;
}



const audio_buffer& streaming_audio_source::buffer_queue::fill_buffer(
  const std::vector<uint8_t>& data, audio_buffer_format format, int sample_rate)
{
  HOU_DEV_ASSERT(m_free_buffer_count > 0);
  audio_buffer& buffer = m_buffers[m_current_index];
  buffer.set_data(data, format, sample_rate);
  m_current_index = (m_current_index + 1) % m_buffers.size();
  --m_free_buffer_count;
  m_buffer_sample_counts.push(data.size());
  return buffer;
}



size_t streaming_audio_source::buffer_queue::get_free_buffer_count() const
{
  return m_free_buffer_count;
}



size_t streaming_audio_source::buffer_queue::get_used_buffer_count() const
{
  return m_buffers.size() - m_free_buffer_count;
}



size_t streaming_audio_source::buffer_queue::get_buffer_count() const
{
  return m_buffers.size();
}

}  // namespace hou
