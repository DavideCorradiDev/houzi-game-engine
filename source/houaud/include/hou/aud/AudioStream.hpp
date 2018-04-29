// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_STREAM_HPP
#define HOU_AUD_AUDIO_STREAM_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/sys/binary_stream.hpp"

#include "hou/aud/AudioBufferFormat.hpp"



namespace hou
{

/** Specialization of a binary_stream representing an audio ph_stream.
 *
 *  Setting or moving the position indicator throws when moving it to the middle
 *  of the data of a single sample.
 *
 */
class HOU_AUD_API AudioStream : public binary_stream
{
public:
  /** Position indicator representing the number of samples from the beginning
   *  of the ph_file
   */
  using SamplePosition = long;

  /** Offset of the sample position indicator in bytes.
   */
  using SampleOffset = long;

public:
  /** default constructor.
   */
  AudioStream();

  /** Destructor.
   */
  virtual ~AudioStream() = 0;

  /** Gets the audio format of the ph_stream.
   *
   *  \return the audio format of the ph_stream.
   */
  AudioBufferFormat get_format() const;

  /** Gets the number of channels of the ph_stream, based on its audio format.
   *
   *  \return 1 if the audio format is mono, 2 if the audio format is stereo.
   */
  uint getChannelCount() const;

  /** Gets the number of bytes per sample of the ph_stream, based on its audio
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
  uint getSampleRate() const;

  /** Gets the number of samples in the ph_stream for a single channel.
   *
   *  \return the number of samples in the ph_stream for a single channel.
   */
  virtual size_t get_sample_count() const = 0;

  /** Gets the current sample position indicator.
   *
   *  \return the current sample position indicator.
   */
  virtual SamplePosition getSamplePos() const = 0;

  /** Sets the current sample position indicator.
   *
   *  Throws if pos is negative or higher than the number of samples in the
   *  ph_stream.
   *
   *  \param pos the sample position indicator value.
   *  \return a reference to this ph_stream.
   */
  virtual AudioStream& setSamplePos(SamplePosition pos) = 0;

  /** Moves the current sample position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position
   *  or to a position higher than the number of samples in the ph_stream.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this ph_stream.
   */
  virtual AudioStream& moveSamplePos(SampleOffset offset) = 0;

protected:
  /** Sets the audio format of the ph_stream.
   *
   *  \param channels the number of channels.
   *  \param bytesPerSample the number of bytes per sample per channel.
   */
  void setFormat(uint channels, uint bytesPerSample);

  /** Sets the sample rate of the ph_stream.
   *
   *  \param sampleRate the sample rate in samples per second.
   */
  void setSampleRate(uint sampleRate);

private:
  AudioBufferFormat mFormat;
  uint mSampleRate;
};

}  // namespace hou

#endif
