// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/streaming_audio_source_base.hpp"

#include "hou/aud/audio_stream_in.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

namespace
{

constexpr size_t g_default_buffer_count = 3u;
constexpr size_t g_default_buffer_byte_count = 44100u;

}  // namespace



streaming_audio_source_base::streaming_audio_source_base(
  std::unique_ptr<audio_stream_in> as)
  : audio_source()
  , m_audio_stream(std::move(as))
  , m_buffer_queue(g_default_buffer_count)
  , m_looping(false)
  , m_sample_pos(0u)
  , m_buffer_byte_count(g_default_buffer_byte_count)
{
  if(m_audio_stream != nullptr)
  {
    m_audio_stream->set_sample_pos(0u);
  }
}



streaming_audio_source_base::~streaming_audio_source_base()
{
  if(get_handle().get_name() != 0)
  {
    stop();
    free_buffers();
  }
}



void streaming_audio_source_base::set_stream(
  std::unique_ptr<audio_stream_in> as)
{
  stop();
  m_audio_stream = std::move(as);
  set_sample_pos_and_stream_cursor(0u);
}



const audio_stream_in* streaming_audio_source_base::get_stream() const
{
  return m_audio_stream.get();
}



void streaming_audio_source_base::set_buffer_count(size_t buffer_count)
{
  HOU_PRECOND(buffer_count > 0u);
  stop();
  free_buffers();
  m_buffer_queue = buffer_queue(buffer_count);
}



size_t streaming_audio_source_base::get_buffer_count() const
{
  return m_buffer_queue.get_buffer_count();
}



void streaming_audio_source_base::set_buffer_sample_count(
  size_t buffer_sample_count)
{
  HOU_PRECOND(buffer_sample_count > 0u);
  stop();
  m_buffer_byte_count
    = buffer_sample_count * (get_channel_count() * get_bytes_per_sample());
}



size_t streaming_audio_source_base::get_buffer_sample_count() const
{
  return m_buffer_byte_count / (get_channel_count() * get_bytes_per_sample());
}



bool streaming_audio_source_base::is_valid() const
{
  return m_audio_stream != nullptr;
}



void streaming_audio_source_base::set_looping(bool looping)
{
  m_looping = looping;
}



bool streaming_audio_source_base::is_looping() const
{
  return m_looping;
}



void streaming_audio_source_base::update_buffer_queue()
{
  free_buffers();
  if(get_state() == audio_source_state::playing)
  {
    fill_buffers();
  }
}



std::vector<uint8_t> streaming_audio_source_base::read_data_chunk(
  size_t chunk_size)
{
  std::vector<uint8_t> data;
  if(m_audio_stream != nullptr)
  {
    data.resize(chunk_size);
    m_audio_stream->read(data);
    data.resize(m_audio_stream->get_read_byte_count());
  }
  return data;
}



void streaming_audio_source_base::free_buffers()
{
  uint processed_buffers = al::get_source_processed_buffers(get_handle());
  std::vector<ALuint> bufferNames(processed_buffers, 0);
  al::source_unqueue_buffers(
    get_handle(), narrow_cast<ALsizei>(bufferNames.size()), bufferNames.data());
  size_t processed_bytes = m_buffer_queue.free_buffers(processed_buffers);
  set_sample_pos_variable(m_sample_pos
    + processed_bytes / (get_channel_count() * get_bytes_per_sample()));
}



void streaming_audio_source_base::fill_buffers()
{
  if(m_audio_stream == nullptr)
  {
    return;
  }

  while(get_sample_count() > 0 && m_buffer_queue.get_free_buffer_count() > 0)
  {
    std::vector<uint8_t> data = read_data_chunk(m_buffer_byte_count);
    if(data.empty())
    {
      if(m_looping)
      {
        HOU_DEV_ASSERT(m_audio_stream != nullptr);
        m_audio_stream->set_sample_pos(0u);
      }
      else
      {
        return;
      }
    }
    else
    {
      const audio_buffer& buf
        = m_buffer_queue.fill_buffer(data, get_format(), get_sample_rate());
      ALuint buf_name = buf.get_handle().get_name();
      al::source_queue_buffers(get_handle(), 1u, &buf_name);
    }
  }
}



void streaming_audio_source_base::set_sample_pos_variable(size_t pos)
{
  uint sample_count = get_sample_count();
  m_sample_pos = sample_count == 0u ? 0u : pos % get_sample_count();
}



void streaming_audio_source_base::set_sample_pos_and_stream_cursor(size_t pos)
{
  set_sample_pos_variable(pos);
  if(m_audio_stream != nullptr)
  {
    m_audio_stream->set_sample_pos(
      narrow_cast<audio_stream::sample_position>(pos));
  }
}



void streaming_audio_source_base::on_set_sample_pos(uint value)
{
  free_buffers();
  set_sample_pos_and_stream_cursor(value);
  fill_buffers();
}



uint streaming_audio_source_base::on_get_sample_pos() const
{
  uint sample_count = get_sample_count();
  return sample_count == 0u
    ? 0u
    : (m_sample_pos + audio_source::on_get_sample_pos()) % get_sample_count();
}



audio_buffer_format streaming_audio_source_base::get_format_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_format();
}



uint streaming_audio_source_base::get_channel_count_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_channel_count();
}



uint streaming_audio_source_base::get_bytes_per_sample_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_bytes_per_sample();
}



uint streaming_audio_source_base::get_sample_rate_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_sample_rate();
}



uint streaming_audio_source_base::get_sample_count_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return narrow_cast<uint>(m_audio_stream->get_sample_count());
}



streaming_audio_source_base::buffer_queue::buffer_queue(size_t buffer_count)
  : m_buffers(buffer_count)
  , m_buffer_sample_counts()
  , m_free_buffer_count(buffer_count)
  , m_current_index(0u)
{}



size_t streaming_audio_source_base::buffer_queue::free_buffers(size_t count)
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



const audio_buffer& streaming_audio_source_base::buffer_queue::fill_buffer(
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



size_t streaming_audio_source_base::buffer_queue::get_free_buffer_count() const
{
  return m_free_buffer_count;
}



size_t streaming_audio_source_base::buffer_queue::get_used_buffer_count() const
{
  return m_buffers.size() - m_free_buffer_count;
}



size_t streaming_audio_source_base::buffer_queue::get_buffer_count() const
{
  return m_buffers.size();
}

}  // namespace hou

