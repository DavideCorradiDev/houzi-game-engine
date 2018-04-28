// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_EMPTY_AUDIO_STREAM_IN_HPP
#define HOU_AUD_EMPTY_AUDIO_STREAM_IN_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioStreamIn.hpp"



namespace hou
{

/** Class representing a dummy empty input audio ph_stream.
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

  // stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t get_byte_count() const final;

  // stream_in overrides.
  size_t get_read_byte_count() const final;
  size_t get_read_element_count() const final;

  // binary_stream overrides.
  byte_position get_byte_pos() const final;
  binary_stream& set_byte_pos(byte_position pos) final;
  binary_stream& move_byte_pos(byte_offset offset) final;

  // AudioStream overrides.
  size_t getSampleCount() const final;
  SamplePosition getSamplePos() const final;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative or greater than the number of bytes in the ph_stream.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this ph_stream.
   */
  AudioStreamIn& setSamplePos(SamplePosition pos) final;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position
   *  or to a position greater than the number of bytes in the ph_stream.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this ph_stream.
   */
  AudioStreamIn& moveSamplePos(SampleOffset offset) final;

private:
  void on_read(void* buf, size_t elementSize, size_t bufSize) final;
};

}

#endif

