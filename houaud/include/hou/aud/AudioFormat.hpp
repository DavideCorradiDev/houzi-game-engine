// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_FORMAT_HPP
#define HOU_AUD_AUDIO_FORMAT_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/al/AlBufferFormat.hpp"

#include "hou/cor/BasicTypes.hpp"

#include <iostream>



namespace hou
{

/** Enumeration class for audio formats.
 */
enum class AudioFormat
{
  /** 8-bit mono audio format. */
  Mono8,
  /** 16-bit mono audio format. */
  Mono16,
  /** 8-bit stereo audio format. */
  Stereo8,
  /** 16-bit stereo audio format. */
  Stereo16,
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
HOU_AUD_API AudioFormat getAudioFormatEnum(uint channels, uint bytesPerSample);

/** Gets the number of channels associated to an audio format.
 *
 *  \param format the audio format.
 *  \return the number of channels of the format, either 1 (single channel, mono
 *  format) or 2 (double channel, stereo format).
 */
HOU_AUD_API uint getAudioFormatChannelCount(AudioFormat format);

/** Gets the number of bytes per sample associated to an audio format.
 *
 *  \param format the audio format.
 *  \return the number of bytes per sample of the format, either 1 (8-bit
 *  format) or 2 (16-bit format).
 */
HOU_AUD_API uint getAudioFormatBytesPerSample(AudioFormat format);

/** Converts an AudioFormat enum into the corresponding OpenAL BufferFormat enum.
 *
 *  \param format the AudioFormat enum.
 *  \return the corresponding OpenAL BufferFormat enum.
 */
HOU_AUD_API al::BufferFormat audioBufferFormatToAlBufferFormat
  (AudioFormat format);

/** Converts an OpenAL BufferFormat enum into the corresponding AudioFormat enum.
 *
 *  \param format the OpenAL BufferFormat enum.
 *  \return the AudioFormat enum.
 */
HOU_AUD_API AudioFormat alBufferFormatToAudioFormat(al::BufferFormat format);


/** Writes a AudioFormat enum into a stream.
 *
 *  \param os the stream.
 *  \param format the AudioFormat enum.
 *  \return a reference to the stream.
 */
HOU_AUD_API std::ostream& operator<<(std::ostream& os, AudioFormat format);

}

#endif

