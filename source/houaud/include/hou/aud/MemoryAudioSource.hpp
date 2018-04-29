// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_SOURCE_HPP
#define HOU_AUD_AUDIO_SOURCE_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioSource.hpp"



namespace hou
{

class AudioBuffer;



/** Represents an audio source with the buffer completely loaded in memory.
 *
 * Since the buffer must be completely loaded in memory, this class is not
 * suited to play long audio buffers.
 * Prefer using StreamingAudioSource in that case.
 *
 * A MemoryAudioSource must be associated to an AudioBuffer to play a sound.
 * Many MemoryAudioSource objects may share an AudioBuffer.
 *
 * It must be ensured that the AudioBuffer associated to a MemoryAudioSource is
 * not destroyed while the MemoryAudioSource is still existing, failing to do so
 * will result in undefined behaviour.
 */
class HOU_AUD_API MemoryAudioSource : public AudioSource
{
public:
  /** Buffer constructor.
   *
   * Creates a MemoryAudioSource with the given AudioBuffer.
   * If passed nullptr, the MemoryAudioSource will not be associated to any
   * buffer and will not play any sound.
   *
   * \param buffer pointer to the AudioBuffer.
   */
  explicit MemoryAudioSource(const AudioBuffer* buffer = nullptr);

  /** Move constructor.
   *
   * \param other the other MemoryAudioSource.
   */
  MemoryAudioSource(MemoryAudioSource&& other);

  /** Destructor.
   */
  virtual ~MemoryAudioSource();

  /** Sets the AudioBuffer.
   *
   * If passed nullptr, the MemoryAudioSource will not be associated to any
   * buffer and will not play any sound.
   *
   * \param buffer pointer to the AudioBuffer.
   */
  void setBuffer(const AudioBuffer* buffer);

  /** Gets the AudioBuffer.
   *
   * \return a pointer to the AudioBuffer, or nullptr if no AudioBuffer is
   * associated to the MemoryAudioSource.
   */
  const AudioBuffer* getBuffer() const;

  // AudioSource overrides.
  AudioBufferFormat get_format() const final;
  uint getChannelCount() const final;
  uint getBytesPerSample() const final;
  uint getSampleRate() const final;
  uint get_sample_count() const final;
  void setLooping(bool looping) final;
  bool isLooping() const final;

private:
  void onSetSamplePos(uint pos) final;
  uint onGetSamplePos() const final;

private:
  const AudioBuffer* mBufferRef;
};

}  // namespace hou

#endif
