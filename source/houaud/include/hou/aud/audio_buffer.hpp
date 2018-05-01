// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_BUFFER_HPP
#define HOU_AUD_AUDIO_BUFFER_HPP

#include "hou/aud/aud_export.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/aud/audio_buffer_format.hpp"
#include "hou/aud/audio_stream_in.hpp"

#include "hou/al/al_buffer_handle.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/span.hpp"

#include <vector>



namespace hou
{

/** Represents an audio buffer in memory.
 *
 * It is not possible to play a sound with an audio_buffer object alone.
 * It is necessary to create an audio_source object and assign a reference to an
 * audio_buffer to it.
 * Many audio_source objects can share the same audio_buffer objects, allowing
 * to save resources. An audio_buffer object loads the whole audio data into
 * memory. For large audio data this might be expensive. In that case, it is
 * suggested to use audio streams and a streaming_audio_source.
 */
class HOU_AUD_API audio_buffer : public non_copyable
{
public:
  /** Creates an empty audio_buffer.
   *
   * The buffer is created with one single sample set to 0, mono16 format, and
   * a frequency of 1 sample per second.
   */
  audio_buffer();

  /** Creates an audio_buffer object with the given parameters.
   *
   * \param data the data.
   *
   * \param format the audio format.
   *
   * \param smpRate the sample rate.
   */
  audio_buffer(
    const span<const uint8_t>& data, audio_buffer_format format, int smpRate);

  /** Creates an audio_buffer object with the given parameters, moving the data.
   *
   * \param data the data.
   *
   * \param format the audio format.
   *
   * \param smpRate the sample rate.
   */
  audio_buffer(
    std::vector<uint8_t>&& data, audio_buffer_format format, int smpRate);

  /** Creates an audio_buffer object with the data from the given ph_stream.
   *
   * \param audioStream the audioStream.
   */
  explicit audio_buffer(audio_stream_in& audioStream);

  /** Creates an audio_buffer object with the data from the given ph_stream.
   *
   * \param audioStream the audioStream.
   */
  explicit audio_buffer(audio_stream_in&& audioStream);

  /** Move constructor.
   *
   * \param other the other audio_buffer.
   */
  audio_buffer(audio_buffer&& other);

  /** Gets the OpenAL buffer handle.
   *
   * \return the OpenAL buffer handle.
   */
  const al::buffer_handle& get_handle() const;

  /** Gets the audio format of the buffer.
   *
   * \return the audio format of the buffer.
   */
  audio_buffer_format get_format() const;

  /** Gets the number of channels of the buffer, based on its audio format.
   *
   * \return 1 if the audio format is mono, 2 if the audio format is stereo.
   */
  uint get_channel_count() const;

  /** Gets the number of bytes per sample of the buffer, based on its audio
   * format.
   *
   * The number returned is the number of bytes per sample for a single
   * channel. \return 1 for 8-bit audio formats, 2 for 16-bit audio formats.
   */
  uint get_bytes_per_sample() const;

  /** Gets the number of samples per second.
   *
   * \return the sample rate in samples per second.
   */
  int get_sample_rate() const;

  /** Gets the number of bytes in the buffer.
   *
   * \return the number of bytes in the channel.
   */
  uint get_byte_count() const;

  /** Gets the number of samples in the buffer for a single channel.
   *
   * \return the number of samples in the buffer for a single channel.
   */
  uint get_sample_count() const;

  /** Sets the buffer data with the provided values.
   *
   * \param data the data.
   *
   * \param format the audio format.
   *
   * \param smlRate the sample rate.
   */
  void set_data(
    const span<const uint8_t>& data, audio_buffer_format format, int smlRate);

  /** Sets the buffer data with the provided values, moving the data.
   *
   * \param data the data.
   *
   * \param format the audio format.
   *
   * \param smlRate the sample rate.
   */
  void set_data(
    std::vector<uint8_t>&& data, audio_buffer_format format, int smlRate);

  /** Sets the buffer data by reading the provided audio_stream_in)
   *
   * \param audioStream the audio ph_stream.
   */
  void set_data(audio_stream_in& audioStream);

  /** Sets the buffer data by reading the provided audio_stream_in)
   *
   * \param audioStream the audio ph_stream.
   */
  void set_data(audio_stream_in&& audioStream);

private:
  al::buffer_handle m_handle;
};

}  // namespace hou

#endif
