// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_BUFFER_FORMAT_HPP
#define HOU_AUD_AUDIO_BUFFER_FORMAT_HPP

#include "hou/aud/aud_config.hpp"

#include "hou/al/open_al.hpp"

#include "hou/cor/narrow_cast.hpp"

#include <iostream>



namespace hou
{

/**
 * Enumeration class for audio formats.
 */
enum class audio_buffer_format : ALenum
{
  /**
   * 8-bit mono audio format.
   */
  mono8 = AL_FORMAT_MONO8,
  /**
   * 16-bit mono audio format.
   */
  mono16 = AL_FORMAT_MONO16,
  /**
   * 8-bit stereo audio format.
   */
  stereo8 = AL_FORMAT_STEREO8,
  /**
   * 16-bit stereo audio format.
   */
  stereo16 = AL_FORMAT_STEREO16,
};

/**
 * Gets the appropriate audio format given the number of channels and bytes per
 * sample.
 *
 * \param channels the number of channels. It must be 1 (single channel, mono
 * format) or 2 (double channel, stereo format).
 *
 * \param bytes_per_sample the number of bytes per sample. It must be 1 (8-bit
 * format) or 2 (16-bit format).
 *
 * \throws hou::precondition_violation if channels or bytes_per_sample have
 * a value different from 1 or 2.
 *
 * \return the audio format corresponding to the given number of channels and
 * bytes per sample.
 */
HOU_AUD_API audio_buffer_format get_audio_buffer_format_enum(
  uint channels, uint bytes_per_sample);

/**
 * Gets the number of channels associated to an audio format.
 *
 * \param format the audio format.
 *
 * \return the number of channels of the format, either 1 (single channel, mono
 * format) or 2 (double channel, stereo format).
 */
HOU_AUD_API uint get_audio_buffer_format_channel_count(
  audio_buffer_format format) noexcept;

/**
 * Gets the number of bytes per sample associated to an audio format.
 *
 * \param format the audio format.
 *
 * \return the number of bytes per sample of the format, either 1 (8-bit
 * format) or 2 (16-bit format).
 */
HOU_AUD_API uint get_audio_buffer_format_bytes_per_sample(
  audio_buffer_format format) noexcept;

/**
 * Writes a audio_buffer_format enum into a stream.
 *
 * \param os the stream.
 *
 * \param format the audio_buffer_format enum.
 *
 * \return a reference to the stream.
 */
HOU_AUD_API std::ostream& operator<<(
  std::ostream& os, audio_buffer_format format);

}  // namespace hou

#endif
