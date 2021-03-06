// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/stream_audio_source.hpp"

#include "hou/aud/audio_stream_in.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

namespace
{

constexpr size_t g_default_buffer_count = 3u;
constexpr size_t g_default_buffer_byte_count = 44100u;

}  // namespace



stream_audio_source::stream_audio_source(std::unique_ptr<audio_stream_in> as)
  : audio_source()
  , m_audio_stream(std::move(as))
  , m_buffer_queue(g_default_buffer_count)
  , m_looping(false)
  , m_processing_buffer_queue(false)
  , m_sample_pos(0)
  , m_buffers_to_queue_count(0u)
  , m_buffer_byte_count(g_default_buffer_byte_count)
{
  set_sample_pos_and_stream_cursor(0);
}



stream_audio_source::~stream_audio_source()
{
  // The buffer queue will be deleted before the audio source, therefore
  // the buffers must be unqueued from the audio source to avoid an OpenAL
  // error. To unqueue all buffers, it is sufficient to stop the source first.
  // The handle is checked for validity for safety reasons.
  if(get_handle().get_name() != 0)
  {
    stop();
    free_buffers();
  }
}



void stream_audio_source::set_stream(std::unique_ptr<audio_stream_in> as)
{
  stop();
  m_audio_stream = std::move(as);
  set_sample_pos_and_stream_cursor(0);
}



const audio_stream_in* stream_audio_source::get_stream() const
{
  return m_audio_stream.get();
}



void stream_audio_source::set_buffer_count(size_t buffer_count)
{
  stop();
  free_buffers();
  m_buffer_queue = buffer_queue(buffer_count);
}



size_t stream_audio_source::get_buffer_count() const
{
  return m_buffer_queue.get_buffer_count();
}



void stream_audio_source::set_buffer_sample_count(size_t buffer_sample_count)
{
  stop();
  m_buffer_byte_count
    = buffer_sample_count * (get_channel_count() * get_bytes_per_sample());
}



size_t stream_audio_source::get_buffer_sample_count() const
{
  return m_buffer_byte_count / (get_channel_count() * get_bytes_per_sample());
}



bool stream_audio_source::is_playing() const
{
  return m_processing_buffer_queue || audio_source::is_playing();
}



bool stream_audio_source::has_audio() const
{
  return m_audio_stream != nullptr;
}



bool stream_audio_source::is_looping() const
{
  return m_looping;
}



void stream_audio_source::update_buffer_queue()
{
  if(m_processing_buffer_queue)
  {
    free_buffers();
    fill_buffers();

    // If the audio source is stopped at this point, it means that the buffer
    // queue was not updated fast enough and the audio source automatically
    // stopped. In this case force a restart of the audio source with the newly
    // added buffers.
    if(!audio_source::is_playing())
    {
      al::play_source(get_handle());
    }
  }
}



std::vector<uint8_t> stream_audio_source::read_data_chunk(size_t chunk_size)
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



void stream_audio_source::free_buffers()
{
  uint processed_buffers = al::get_source_processed_buffers(get_handle());
  if(processed_buffers > 0)
  {
    std::vector<ALuint> bufferNames(processed_buffers, 0);
    al::source_unqueue_buffers(get_handle(),
      narrow_cast<ALsizei>(bufferNames.size()), bufferNames.data());
    size_t processed_bytes = m_buffer_queue.free_buffers(processed_buffers);
    set_sample_pos_variable(normalize_sample_pos(m_sample_pos
      + processed_bytes / (get_channel_count() * get_bytes_per_sample())));
  }
}



void stream_audio_source::fill_buffers()
{
  while(
    m_buffers_to_queue_count > 0u && m_buffer_queue.get_free_buffer_count() > 0)
  {
    std::vector<uint8_t> data = read_data_chunk(m_buffer_byte_count);
    HOU_DEV_ASSERT(!data.empty());

    const audio_buffer& buf
      = m_buffer_queue.fill_buffer(data, get_format(), get_sample_rate());
    ALuint buf_name = buf.get_handle().get_name();
    al::source_queue_buffers(get_handle(), 1u, &buf_name);

    HOU_DEV_ASSERT(m_buffers_to_queue_count > 0u);
    --m_buffers_to_queue_count;

    // If looping, reset the stream to the beginning and the number of buffers
    // to queue, so that the buffer queueing will continue from the beginning of
    // the stream.
    if(m_looping && m_buffers_to_queue_count == 0u)
    {
      HOU_DEV_ASSERT(m_audio_stream != nullptr);
      m_audio_stream->set_sample_pos(
        narrow_cast<audio_stream::sample_position>(0));
      set_buffers_to_queue_count(0u);
      // m_sample_pos shouldn't be updated here, it is updated in free_buffers.
    }
  }

  // If the loop ended and the number of buffers to queue is 0, it means that
  // the buffer queu processing was ended.
  if(m_buffers_to_queue_count == 0u)
  {
    m_processing_buffer_queue = false;
  }
}



stream_audio_source::sample_position stream_audio_source::normalize_sample_pos(
  sample_position pos)
{
  uint sample_count = get_sample_count();
  return sample_count == 0 ? 0 : pos % sample_count;
}



void stream_audio_source::set_sample_pos_variable(sample_position pos)
{
  m_sample_pos = pos;
}



void stream_audio_source::set_stream_cursor(sample_position pos)
{
  if(m_audio_stream != nullptr)
  {
    m_audio_stream->set_sample_pos(
      narrow_cast<audio_stream::sample_position>(pos));
  }
}



void stream_audio_source::set_sample_pos_and_stream_cursor(sample_position pos)
{
  pos = normalize_sample_pos(pos);
  set_sample_pos_variable(pos);
  set_stream_cursor(pos);
}



void stream_audio_source::set_buffers_to_queue_count(uint pos)
{
  uint samples_to_end = get_sample_count() - pos;
  uint buffer_sample_count = get_buffer_sample_count();
  m_buffers_to_queue_count = (samples_to_end > 0u && buffer_sample_count > 0)
    ? 1u + (samples_to_end - 1u) / buffer_sample_count
    : 0u;
}



void stream_audio_source::on_set_looping(bool looping)
{
  m_looping = looping;
}



void stream_audio_source::on_set_sample_pos(sample_position value)
{
  free_buffers();
  set_sample_pos_and_stream_cursor(value);
  set_buffers_to_queue_count(m_sample_pos);
  fill_buffers();
}



stream_audio_source::sample_position stream_audio_source::on_get_sample_pos()
  const
{
  uint sample_count = get_sample_count();
  return sample_count == 0
    ? 0
    : (m_sample_pos + audio_source::on_get_sample_pos()) % get_sample_count();
}



void stream_audio_source::on_play()
{
  m_processing_buffer_queue = true;
}



void stream_audio_source::on_pause()
{
  m_processing_buffer_queue = false;
}



audio_buffer_format stream_audio_source::get_format_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_format();
}



uint stream_audio_source::get_channel_count_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_channel_count();
}



uint stream_audio_source::get_bytes_per_sample_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_bytes_per_sample();
}



uint stream_audio_source::get_sample_rate_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return m_audio_stream->get_sample_rate();
}



uint stream_audio_source::get_sample_count_internal() const
{
  HOU_INVARIANT(m_audio_stream != nullptr);
  return narrow_cast<uint>(m_audio_stream->get_sample_count());
}



stream_audio_source::buffer_queue::buffer_queue(size_t buffer_count)
  : m_buffers(buffer_count)
  , m_buffer_sample_counts()
  , m_free_buffer_count(buffer_count)
  , m_current_index(0u)
{}



size_t stream_audio_source::buffer_queue::free_buffers(size_t count)
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



const audio_buffer& stream_audio_source::buffer_queue::fill_buffer(
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



size_t stream_audio_source::buffer_queue::get_free_buffer_count() const
{
  return m_free_buffer_count;
}



size_t stream_audio_source::buffer_queue::get_used_buffer_count() const
{
  return m_buffers.size() - m_free_buffer_count;
}



size_t stream_audio_source::buffer_queue::get_buffer_count() const
{
  return m_buffers.size();
}

}  // namespace hou

