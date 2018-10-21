// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_STREAMING_AUDIO_SOURCE_BASE_HPP
#define HOU_AUD_STREAMING_AUDIO_SOURCE_BASE_HPP

#include "hou/aud/audio_source.hpp"

#include "hou/aud/audio_buffer.hpp"

#include "hou/aud/aud_config.hpp"

#include "hou/cor/std_string.hpp"
#include "hou/cor/std_vector.hpp"

#include <memory>
#include <queue>



namespace hou
{

/**
 * Represents an audio source streaming audio data from an audio stream.
 *
 * This class is suited to play long audio buffers, as the buffer must not be
 * completely loaded in memory but is rather streamed concurrently in smaller
 * chunks.
 * For short audio files, it is suggested to use an memory_audio_source and an
 * audio_buffer, as performance is better and as the audio_buffer can be shared
 * by multiple memory_audio_source objects.
 *
 * A streaming_audio_source_base must be given an audio_stream to play a sound.
 * The streaming_audio_source_base will retain unique ownership of the
 * audio_stream and will automatically destroy it.
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
class HOU_AUD_API streaming_audio_source_base : public audio_source
{
public:
  /**
   * Stream constructor.
   *
   * Creates a streaming_audio_source_base object with the given audio stream,
   * taking ownership of it.
   *
   * \param as the audio stream.
   */
  explicit streaming_audio_source_base(
    std::unique_ptr<audio_stream_in> as = nullptr);

  /**
   * Move constructor.
   *
   * \param other the object to be moved.
   */
  streaming_audio_source_base(streaming_audio_source_base&&) = default;

  /**
   * Destructor.
   */
  virtual ~streaming_audio_source_base();

  /**
   * Sets the stream and transfers ownership to this object.
   *
   * \param as the stream.
   */
  virtual void set_stream(std::unique_ptr<audio_stream_in> as = nullptr) = 0;

  /**
   * Gets the audio stream.
   *
   * \return a pointer to the audio stream, or nullptr if no audio stream is
   * associated to the streaming_audio_source_base.
   */
  const audio_stream_in* get_stream() const;

  /**
   * Sets the number of buffers in the buffer queue.
   *
   * Throws if passed zero.
   *
   * \param buffer_count the number of buffers.
   */
  virtual void set_buffer_count(size_t buffer_count) = 0;

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
  virtual void set_buffer_sample_count(size_t buffer_sample_count) = 0;

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

protected:
  /**
   * Updates the internal buffer queue.
   */
  void update_buffer_queue();

  // audio_source overrides.
  // Changed access to protected to allow derived classes to call ths
  // implementation.
  void on_set_sample_pos(uint pos) override = 0;

private:
  std::vector<uint8_t> read_data_chunk(size_t chunk_size);
  void free_buffers();
  void fill_buffers();
  void set_sample_pos_variable(size_t pos);
  void set_sample_pos_and_stream_cursor(size_t pos);

  uint on_get_sample_pos() const final;
  audio_buffer_format get_format_internal() const final;
  uint get_channel_count_internal() const final;
  uint get_bytes_per_sample_internal() const final;
  uint get_sample_rate_internal() const final;
  uint get_sample_count_internal() const final;

private:
  std::unique_ptr<audio_stream_in> m_audio_stream;
  buffer_queue m_buffer_queue;
  bool m_looping;
  uint m_sample_pos;
  size_t m_buffer_byte_count;
};

}  // namespace hou

#endif
