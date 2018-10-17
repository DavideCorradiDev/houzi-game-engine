// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_SOURCE_HPP
#define HOU_AUD_AUDIO_SOURCE_HPP

#include "hou/aud/audio_source.hpp"

#include "hou/aud/aud_config.hpp"



namespace hou
{

class audio_buffer;



/**
 * Represents an audio source with the buffer completely loaded in memory.
 *
 * Since the buffer must be completely loaded in memory, this class is not
 * suited to play long audio buffers.
 * Prefer using streaming_audio_source in that case.
 *
 * A memory_audio_source must be associated to an audio_buffer to play a sound.
 * Many memory_audio_source objects may share the same audio_buffer.
 *
 * A memory audio_source only stores a reference to an audio_buffer object and
 * will not own it.
 * It must be ensured that the audio_buffer associated to a memory_audio_source
 * is not destroyed while the memory_audio_source is still existing, failing to
 * do so will result in undefined behaviour.
 */
class HOU_AUD_API memory_audio_source final : public audio_source
{
public:
  /**
   * Buffer constructor.
   *
   * Creates a memory_audio_source with the given audio_buffer.
   *
   * \param buffer pointer to the audio_buffer.
   * If nullptr is passed, the audio_source will not play any sound.
   */
  explicit memory_audio_source(const audio_buffer* buffer = nullptr);

  /**
   * Sets the audio_buffer.
   *
   * \param buffer pointer to the audio_buffer.
   * If nullptr is passed, the audio_source will not play any sound.
   */
  void set_buffer(const audio_buffer* buffer);

  /**
   * Gets the audio_buffer.
   *
   * \return a pointer to the audio_buffer, or nullptr if no audio_buffer is
   * associated to the memory_audio_source.
   */
  const audio_buffer* get_buffer() const;

  // audio_source overrides.
  bool is_valid() const final;
  void set_looping(bool looping) final;
  bool is_looping() const final;

private:
  void on_set_sample_pos(uint pos) final;
  uint on_get_sample_pos() const final;

  // audio_source overrides.
  audio_buffer_format get_format_internal() const final;
  uint get_channel_count_internal() const final;
  uint get_bytes_per_sample_internal() const final;
  uint get_sample_rate_internal() const final;
  uint get_sample_count_internal() const final;

private:
  const audio_buffer* m_buffer_ref;
};

}  // namespace hou

#endif
