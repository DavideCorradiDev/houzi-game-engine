// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_BUFFER_FORMAT_HPP
#define HOU_AUD_AUDIO_BUFFER_FORMAT_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/al/open_al.hpp"

#include "hou/cor/basic_types.hpp"

#include <iostream>



namespace hou
{

/** Enumeration class for audio formats.
 */
enum class AudioBufferFormat : ALenum
{
  /** 8-bit mono audio format. */
  Mono8 = AL_FORMAT_MONO8,
  /** 16-bit mono audio format. */
  Mono16 = AL_FORMAT_MONO16,
  /** 8-bit stereo audio format. */
  Stereo8 = AL_FORMAT_STEREO8,
  /** 16-bit stereo audio format. */
  Stereo16 = AL_FORMAT_STEREO16,
};

/** Gets the appropriate audio format given the number of channels and bytes per
 *  sample.
 *
 *  Throws if the values of the arguments is invalid.
 *
 *  \param channels the number of channels. It must be 1 (single channel, mono
 *  format) or 2 (double channel, stereo format).
 *  \param bytesPerSample the number of bytes per sample. It must be 1 (8-bit
 *  format) or 2 (16-bit format).
 *  \return the audio format corresponding to the given number of channels and
 *  bytes per sample.
 */
HOU_AUD_API AudioBufferFormat getAudioBufferFormatEnum(
  uint channels, uint bytesPerSample);

/** Gets the number of channels associated to an audio format.
 *
 *  \param format the audio format.
 *  \return the number of channels of the format, either 1 (single channel, mono
 *  format) or 2 (double channel, stereo format).
 */
HOU_AUD_API uint getAudioBufferFormatChannelCount(AudioBufferFormat format);

/** Gets the number of bytes per sample associated to an audio format.
 *
 *  \param format the audio format.
 *  \return the number of bytes per sample of the format, either 1 (8-bit
 *  format) or 2 (16-bit format).
 */
HOU_AUD_API uint getAudioBufferFormatBytesPerSample(AudioBufferFormat format);

/** Writes a AudioBufferFormat enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param format the AudioBufferFormat enum.
 *  \return a reference to the ph_stream.
 */
HOU_AUD_API std::ostream& operator<<(
  std::ostream& os, AudioBufferFormat format);

}  // namespace hou

#endif
