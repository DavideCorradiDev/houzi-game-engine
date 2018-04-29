// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_STREAMING_AUDIO_SOURCE_HPP
#define HOU_AUD_STREAMING_AUDIO_SOURCE_HPP

#include "hou/aud/aud_export.hpp"
#include "hou/aud/audio_source.hpp"

#include "hou/aud/audio_buffer.hpp"

#include "hou/cor/not_null.hpp"

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>



namespace hou
{

/** Represents an audio source constantly streaming a buffer.
 *
 *  This class is suited to play long audio buffers, as the buffer must not be
 *  completely loaded in memory but is rather streamed concurrently in smaller
 *  chunks.
 *  For short audio files, it is suggested to use an memory_audio_source and an
 *  audio_buffer, as performance is better and as the audio_buffer can be shared
 *  by multiple AudioSources.
 *  Each streaming_audio_source object spawns a thread that takes care of loading
 *  part of the audio into a queue of memory buffers.
 *  The thread is destroyed when the streaming_audio_source is destroyed.
 *  a streaming_audio_source must be given an audio_stream to play a sound.
 *  The streaming_audio_source will retain unique ownership of the audio_stream and
 *  will automatically destroy it when necessary.
 *
 *  The buffer queue is defined by the number of buffers and the size of
 *  each buffer.
 *  The default values are 3 buffers, each composed of 44100 bytes.
 *  If necessary it is possible to modify these values with the associated
 *  methods.
 *  Higher number of buffers and higher buffer size will result in higher
 *  memory consumption, but better sound quality.
 */
class HOU_AUD_API streaming_audio_source : public audio_source
{
public:
  /** default constructor.
   *
   *  Creates a streaming_audio_source object with an EmptyStream.
   */
  streaming_audio_source();

  /** stream constructor.
   *
   *  Creates a streaming_audio_source object with the given audio ph_stream, taking
   *  ownership of it.
   *
   *  \param audioStream the audio ph_stream.
   */
  explicit streaming_audio_source(
    not_null<std::unique_ptr<audio_stream_in>> audioStream);

  /** Destructor.
   */
  virtual ~streaming_audio_source();
  // Note: no move constructor is implemented at the moment because of
  // difficulty with the streaming thread. The thread should be stopped before
  // copying data around.

  /** Sets the ph_stream and transfers ownership to this object.
   *
   *  \param audioStream the ph_stream.
   */
  void set_stream(not_null<std::unique_ptr<audio_stream_in>> audioStream);

  /** Sets the number of buffers in the buffer queue.
   *
   *  Throws if passed zero.
   *
   *  \param bufferCount the number of buffers.
   */
  void set_buffer_count(size_t bufferCount);

  /** Gets the number of buffers in the buffer queue.
   *
   *  \return the number of buffers.
   */
  size_t get_buffer_count() const;

  /** Sets the size in samples of each buffer in the buffer queue.
   *
   *  \param bufferSampleCount the size in samples of each buffer.
   */
  void set_buffer_sample_count(size_t bufferSampleCount);

  /** Gets the size in samples of each buffer in the buffer queue.
   *
   *  \return the size in samples of each buffer.
   */
  size_t get_buffer_sample_count() const;

  // audio_source overrides.
  audio_buffer_format get_format() const final;
  uint get_channel_count() const final;
  uint get_bytes_per_sample() const final;
  uint get_sample_rate() const final;
  uint get_sample_count() const final;
  void set_looping(bool looping) final;
  bool is_looping() const final;

private:
  class buffer_queue
  {
  public:
    buffer_queue(size_t bufferCount);
    size_t free_buffers(size_t count);
    const audio_buffer& fill_buffer(const std::vector<uint8_t>& data,
      audio_buffer_format format, int sampleRate);
    size_t get_free_buffer_count() const;
    size_t get_used_buffer_count() const;
    size_t get_buffer_count() const;

  private:
    std::vector<audio_buffer> m_buffers;
    std::queue<size_t> m_buffer_sample_counts;
    size_t m_free_buffer_count;
    size_t m_current_index;
  };

private:
  void on_set_sample_pos(uint pos) final;
  uint on_get_sample_pos() const final;

  void thread_function();
  std::vector<uint8_t> read_data_chunk(size_t chunkSize);
  void free_buffers();
  void fill_buffers();
  void set_sample_pos_variable(size_t pos);
  void set_sample_pos_and_stream_cursor(size_t pos);

private:
  std::thread m_thread;
  std::mutex m_thread_mutex;
  not_null<std::unique_ptr<audio_stream_in>> m_audio_stream;
  buffer_queue m_buffer_queue;
  std::atomic<bool> m_streaming_thread_end_requested;
  std::atomic<bool> m_looping;
  std::atomic<uint> m_sample_pos;
  size_t m_buffer_byte_count;
};

}  // namespace hou

#endif
