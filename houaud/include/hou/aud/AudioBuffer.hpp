// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_BUFFER_HPP
#define HOU_AUD_AUDIO_BUFFER_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/aud/AudioFormat.hpp"
#include "hou/aud/AudioStreamIn.hpp"

#include "hou/al/AlBufferHandle.hpp"

#include "hou/cor/BasicTypes.hpp"
#include "hou/cor/NotNull.hpp"

#include <memory>
#include <vector>



namespace hou
{

/** Represents an audio buffer in memory.
 *
 *  It is not possible to play a sound with an AudioBuffer object alone.
 *  It is necessary to create an AudioSource object and assign a reference to an
 *  AudioBuffer to it.
 *  Many AudioSource objects can share the same AudioBuffer objects, allowing to
 *  save resources.
 *  An AudioBuffer object loads the whole audio data into memory.
 *  For large audio data this might be expensive.
 *  In that case, it is suggested to use audio streams and a
 * StreamingAudioSource.
 */
class HOU_AUD_API AudioBuffer : public NonCopyable
{
public:
  /** Creates an empty AudioBuffer.
   *
   *  The buffer is created with one single sample set to 0, Mono16 format, and a
   *  frequency of 1 sample per second.
   */
  AudioBuffer();

  /** Creates an AudioBuffer object with the given parameters.
   *
   *  \param data the data.
   *  \param format the audio format.
   *  \param smpRate the sample rate.
   */
  AudioBuffer(
    const std::vector<uint8_t>& data, AudioFormat format, int smpRate);

  /** Creates an AudioBuffer object with the data from the given stream.
   *
   *  \param audioStream the audioStream.
   */
  explicit AudioBuffer(NotNull<std::unique_ptr<AudioStreamIn>> audioStream);

  /** Move constructor.
   *
   *  \param other the other AudioBuffer.
   */
  AudioBuffer(AudioBuffer&& other);

  /** Gets the OpenAL buffer handle.
   *
   *  \return the OpenAL buffer handle.
   */
  const al::BufferHandle& getHandle() const;

  /** Gets the audio format of the buffer.
   *
   *  \return the audio format of the buffer.
   */
  AudioFormat getAudioFormat() const;

  /** Gets the number of channels of the buffer, based on its audio format.
   *
   *  \return 1 if the audio format is mono, 2 if the audio format is stereo.
   */
  uint getChannelCount() const;

  /** Gets the number of bytes per sample of the buffer, based on its audio
   * format.
   *
   *  The number returned is the number of bytes per sample for a single
   * channel. \return 1 for 8-bit audio formats, 2 for 16-bit audio formats.
   */
  uint getBytesPerSample() const;

  /** Gets the number of samples per second.
   *
   *  \return the sample rate in samples per second.
   */
  int getSampleRate() const;

  /** Gets the number of bytes in the buffer.
   *
   *  \return the number of bytes in the channel.
   */
  uint getByteCount() const;

  /** Gets the number of samples in the buffer for a single channel.
   *
   *  \return the number of samples in the buffer for a single channel.
   */
  uint getSampleCount() const;

  /** Sets the buffer data with the provided values.
   *
   *  \param data the data.
   *  \param format the audio format.
   *  \param smlRate the sample rate.
   */
  void setData(
    const std::vector<uint8_t>& data, AudioFormat format, int smlRate);

  /** Sets the buffer data by reading the provided AudioStreamIn)
   *
   *  \param audioStream the audio stream.
   */
  void setData(NotNull<std::unique_ptr<AudioStreamIn>> audioStream);

private:
  al::BufferHandle mHandle;
};

}  // namespace hou

#endif
