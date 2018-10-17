// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_STREAMING_AUDIO_SOURCE_HPP
#define HOU_AUD_STREAMING_AUDIO_SOURCE_HPP

#include "hou/aud/audio_source.hpp"

#include "hou/aud/audio_buffer.hpp"

#include "hou/aud/aud_config.hpp"

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>



namespace hou
{

/**
 * Represents an audio source constantly streaming a buffer.
 *
 * This class is suited to play long audio buffers, as the buffer must not be
 * completely loaded in memory but is rather streamed concurrently in smaller
 * chunks.
 * For short audio files, it is suggested to use an memory_audio_source and an
 * audio_buffer, as performance is better and as the audio_buffer can be shared
 * by multiple memory_audio_source objects.
 *
 * Each streaming_audio_source object spawns a thread that takes care of
 * loading part of the audio into a queue of memory buffers.
 * The thread is destroyed when the streaming_audio_source is destroyed.
 *
 * A streaming_audio_source must be given an audio_stream to play a sound.
 * The streaming_audio_source will retain unique ownership of the audio_stream
 * and will automatically destroy it.
 *
 * The buffer queue is defined by the number of buffers and the size of
 * each buffer.
 * The default values are 3 buffers, each composed of 44100 bytes.
 * This configuration should work well for most applications.
 * If necessary it is possible to modify these values with the associated
 * methods.
 * Higher number of buffers and higher buffer size will result in higher
 * memory consumption, but potentially better sound quality.
 */
class HOU_AUD_API streaming_audio_source final : public audio_source
{
public:
  /**
   * Stream constructor.
   *
   * Creates a streaming_audio_source object with the given audio stream,
   * taking ownership of it.
   *
   * \param as the audio stream.
   */
  explicit streaming_audio_source(
    std::unique_ptr<audio_stream_in> as = nullptr);

  // It is not trivial to move the object because it internally spawns a thread
  // which uses a pointer to this object. Moving the object would invalidate
  // this pointer.
  streaming_audio_source(streaming_audio_source&&) = delete;

  /**
   * Destructor.
   */
  virtual ~streaming_audio_source();

  /**
   * Sets the stream and transfers ownership to this object.
   *
   * \param as the stream.
   */
  void set_stream(std::unique_ptr<audio_stream_in> as = nullptr);

  /**
   * Sets the number of buffers in the buffer queue.
   *
   * Throws if passed zero.
   *
   * \param buffer_count the number of buffers.
   */
  void set_buffer_count(size_t buffer_count);

  /**
   * Gets the number of buffers in the buffer queue.
   *
   * \return the number of buffers.
   */
  size_t get_buffer_count() const;

  /**
   * Sets the size in samples of each buffer in the buffer queue.
   *
   * \param buffer_sample_count the size in samples of each buffer.
   */
  void set_buffer_sample_count(size_t buffer_sample_count);

  /**
   * Gets the size in samples of each buffer in the buffer queue.
   *
   * \return the size in samples of each buffer.
   */
  size_t get_buffer_sample_count() const;

  // audio_source overrides.
  bool is_valid() const final;
  void set_looping(bool looping) final;
  bool is_looping() const final;

private:
  class buffer_queue
  {
  public:
    buffer_queue(size_t buffer_count);
    size_t free_buffers(size_t count);
    const audio_buffer& fill_buffer(const std::vector<uint8_t>& data,
      audio_buffer_format format, int sample_rate);
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
  void thread_function();
  std::vector<uint8_t> read_data_chunk(size_t chunk_size);
  void free_buffers();
  void fill_buffers();
  void set_sample_pos_variable(size_t pos);
  void set_sample_pos_and_stream_cursor(size_t pos);

  // audio_source overrides.
  void on_set_sample_pos(uint pos) final;
  uint on_get_sample_pos() const final;
  audio_buffer_format get_format_internal() const final;
  uint get_channel_count_internal() const final;
  uint get_bytes_per_sample_internal() const final;
  uint get_sample_rate_internal() const final;
  uint get_sample_count_internal() const final;

private:
  std::thread m_thread;
  std::mutex m_thread_mutex;
  std::unique_ptr<audio_stream_in> m_audio_stream;
  buffer_queue m_buffer_queue;
  std::atomic<bool> m_streaming_thread_end_requested;
  std::atomic<bool> m_looping;
  std::atomic<uint> m_sample_pos;
  size_t m_buffer_byte_count;
};

}  // namespace hou

#endif
