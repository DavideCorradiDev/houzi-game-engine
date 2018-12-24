// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_STREAM_AUDIO_SOURCE_HPP
#define HOU_AUD_STREAM_AUDIO_SOURCE_HPP

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
 * For short audio files, it is suggested to use a buffer_audio_source and an
 * audio_buffer, as performance is better and the audio_buffer can be shared
 * by multiple buffer_audio_source objects.
 *
 * A stream_audio_source must be given an audio_stream to play a sound.
 * The stream_audio_source will retain unique ownership of the
 * audio_stream and will automatically destroy it.
 *
 * The buffer queue is defined by the number of buffers and the size of
 * each buffer.
 * The default values should work well for most applications.
 * If necessary it is possible to modify these values with the associated
 * methods.
 * Higher number of buffers and higher buffer size will result in higher
 * memory consumption, but potentially better sound quality.
 */
class HOU_AUD_API stream_audio_source : public audio_source
{
public:
  /**
   * Stream constructor.
   *
   * Creates a stream_audio_source object with the given audio stream,
   * taking ownership of it.
   *
   * \param as the audio stream.
   */
  explicit stream_audio_source(std::unique_ptr<audio_stream_in> as = nullptr);

  /**
   * Move constructor.
   *
   * \param other the object to be moved.
   */
  stream_audio_source(stream_audio_source&&) = default;

  /**
   * Destructor.
   */
  virtual ~stream_audio_source();

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
   * associated to the stream_audio_source.
   */
  const audio_stream_in* get_stream() const;

  /**
   * Sets the number of buffers in the buffer queue.
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
  bool is_playing() const override = 0;
  bool has_audio() const final;
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
  void on_set_looping(bool looping) override = 0;
  void on_set_sample_pos(sample_position pos) override = 0;
  sample_position on_get_sample_pos() const override = 0;
  void on_play() override = 0;
  void on_pause() override;

private:
  std::vector<uint8_t> read_data_chunk(size_t chunk_size);
  void free_buffers();
  void fill_buffers();
  sample_position normalize_sample_pos(sample_position pos);
  void set_sample_pos_variable(sample_position pos);
  void set_stream_cursor(sample_position pos);
  void set_sample_pos_and_stream_cursor(sample_position pos);
  void set_buffers_to_queue_count(uint pos);

  // audio_source overrides.
  audio_buffer_format get_format_internal() const final;
  uint get_channel_count_internal() const final;
  uint get_bytes_per_sample_internal() const final;
  uint get_sample_rate_internal() const final;
  uint get_sample_count_internal() const final;

private:
  std::unique_ptr<audio_stream_in> m_audio_stream;
  buffer_queue m_buffer_queue;
  bool m_looping;
  bool m_processing_buffer_queue;
  int m_sample_pos;
  uint m_buffers_to_queue_count;
  size_t m_buffer_byte_count;
};

}  // namespace hou

#endif
