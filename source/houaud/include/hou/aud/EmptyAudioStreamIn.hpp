// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_EMPTY_AUDIO_STREAM_IN_HPP
#define HOU_AUD_EMPTY_AUDIO_STREAM_IN_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioStreamIn.hpp"



namespace hou
{

/** Class representing a dummy empty input audio stream.
 */
class HOU_AUD_API EmptyAudioStreamIn
  : public AudioStreamIn
{
public:
  /** Default constructor.
   */
  EmptyAudioStreamIn();

  /** Destructor.
   */
  virtual ~EmptyAudioStreamIn();

  // Stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t getByteCount() const final;

  // StreamIn overrides.
  size_t getReadByteCount() const final;
  size_t getReadElementCount() const final;

  // BinaryStream overrides.
  BytePosition getBytePos() const final;
  BinaryStream& setBytePos(BytePosition pos) final;
  BinaryStream& moveBytePos(ByteOffset offset) final;

  // AudioStream overrides.
  size_t getSampleCount() const final;
  SamplePosition getSamplePos() const final;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative or greater than the number of bytes in the stream.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this stream.
   */
  AudioStreamIn& setSamplePos(SamplePosition pos) final;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position
   *  or to a position greater than the number of bytes in the stream.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this stream.
   */
  AudioStreamIn& moveSamplePos(SampleOffset offset) final;

private:
  void onRead(void* buf, size_t elementSize, size_t bufSize) final;
};

}

#endif

