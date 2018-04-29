// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_WAV_FILE_IN_HPP
#define HOU_AUD_WAV_FILE_IN_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioStreamIn.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/sys/file.hpp"



namespace hou
{

/** Input wav ph_file ph_stream.
 */
class HOU_AUD_API WavFileIn
  : public non_copyable
  , public AudioStreamIn
{
public:
  /** Checks if the ph_file corresponding to the given path is a wav ph_file.
   *
   *  \param path the ph_file path.
   *  \return true if the specified ph_file is a wav ph_file.
   */
  static bool check(const std::string& path);

public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid or does not correspond to a wav
   *  ph_file.
   *
   *  \param path the path to the ph_file to be opened.
   */
  explicit WavFileIn(const std::string& path);

  /** Move constructor.
   *
   *  \param other the other object.
   */
  WavFileIn(WavFileIn&& other);

  /** Destructor.
   */
  virtual ~WavFileIn();

  // stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t get_byte_count() const final;

  // stream_in overrides.
  size_t get_read_byte_count() const final;
  size_t get_read_element_count() const final;

  // binary_stream overrides.
  byte_position get_byte_pos() const final;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative or greater than the number of bytes in the ph_stream.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this ph_stream.
   */
  binary_stream& set_byte_pos(byte_position pos) final;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position
   *  or to a position greater than the number of bytes in the ph_stream.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this ph_stream.
   */
  binary_stream& move_byte_pos(byte_offset offset) final;

  // AudioStream overrides.
  size_t get_sample_count() const final;
  SamplePosition getSamplePos() const final;
  AudioStreamIn& setSamplePos(SamplePosition pos) final;
  AudioStreamIn& moveSamplePos(SampleOffset offset) final;

private:
  void readMetadata(const std::string& path);
  void on_read(void* buf, size_t elementSize, size_t bufSize) final;

private:
  file m_file;
  size_t mDataOffset;
  size_t m_byte_count;
  size_t m_element_count;
};

}

#endif

