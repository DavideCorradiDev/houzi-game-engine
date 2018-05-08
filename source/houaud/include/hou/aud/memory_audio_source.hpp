// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_SOURCE_HPP
#define HOU_AUD_AUDIO_SOURCE_HPP

#include "hou/aud/audio_source.hpp"

#include "hou/aud/aud_export.hpp"



namespace hou
{

class audio_buffer;



/** Represents an audio source with the buffer completely loaded in memory.
 *
 * Since the buffer must be completely loaded in memory, this class is not
 * suited to play long audio buffers.
 * Prefer using streaming_audio_source in that case.
 *
 * a memory_audio_source must be associated to an audio_buffer to play a sound.
 * Many memory_audio_source objects may share an audio_buffer.
 *
 * It must be ensured that the audio_buffer associated to a memory_audio_source
 * is not destroyed while the memory_audio_source is still existing, failing to
 * do so will result in undefined behaviour.
 */
class HOU_AUD_API memory_audio_source final : public audio_source
{
public:
  /** Buffer constructor.
   *
   * Creates a memory_audio_source with the given audio_buffer.
   * If passed nullptr, the memory_audio_source will not be associated to any
   * buffer and will not play any sound.
   *
   * \param buffer pointer to the audio_buffer.
   */
  explicit memory_audio_source(const audio_buffer* buffer = nullptr);

  /** Move constructor.
   *
   * \param other the other memory_audio_source.
   */
  memory_audio_source(memory_audio_source&& other) noexcept;

  /** Destructor.
   */
  virtual ~memory_audio_source();

  /** Sets the audio_buffer.
   *
   * If passed nullptr, the memory_audio_source will not be associated to any
   * buffer and will not play any sound.
   *
   * \param buffer pointer to the audio_buffer.
   */
  void set_buffer(const audio_buffer* buffer);

  /** Gets the audio_buffer.
   *
   * \return a pointer to the audio_buffer, or nullptr if no audio_buffer is
   * associated to the memory_audio_source.
   */
  const audio_buffer* get_buffer() const;

  // audio_source overrides.
  audio_buffer_format get_format() const final;
  uint get_channel_count() const final;
  uint get_bytes_per_sample() const final;
  uint get_sample_rate() const final;
  uint get_sample_count() const final;
  void set_looping(bool looping) final;
  bool is_looping() const final;

private:
  void on_set_sample_pos(uint pos) final;
  uint on_get_sample_pos() const final;

private:
  const audio_buffer* m_buffer_ref;
};

}  // namespace hou

#endif
