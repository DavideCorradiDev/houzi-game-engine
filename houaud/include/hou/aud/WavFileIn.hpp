// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_WAV_FILE_IN_HPP
#define HOU_AUD_WAV_FILE_IN_HPP

#include "hou/aud/AudExport.hpp"
#include "hou/aud/AudioStreamIn.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/sys/File.hpp"



namespace hou
{

/** Input wav file stream.
 */
class HOU_AUD_API WavFileIn
  : public NonCopyable
  , public AudioStreamIn
{
public:
  /** Checks if the file corresponding to the given path is a wav file.
   *
   *  \param path the file path.
   *  \return true if the specified file is a wav file.
   */
  static bool check(const std::string& path);

public:
  /** Path constructor.
   *
   *  Throws if the provided path is not valid or does not correspond to a wav
   *  file.
   *
   *  \param path the path to the file to be opened.
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

  // Stream overrides.
  bool eof() const final;
  bool error() const final;
  size_t getByteCount() const final;

  // StreamIn overrides.
  size_t getReadByteCount() const final;
  size_t getReadElementCount() const final;

  // BinaryStream overrides.
  BytePosition getBytePos() const final;

  /** Sets the current byte position indicator.
   *
   *  Throws if pos is negative or greater than the number of bytes in the stream.
   *
   *  \param pos the byte position indicator value.
   *  \return a reference to this stream.
   */
  BinaryStream& setBytePos(BytePosition pos) final;

  /** Moves the current byte position indicator.
   *
   *  Throws if the offset moves the position indicator to a negative position
   *  or to a position greater than the number of bytes in the stream.
   *
   *  \param offset the byte position indicator offset.
   *  \return a reference to this stream.
   */
  BinaryStream& moveBytePos(ByteOffset offset) final;

  // AudioStream overrides.
  size_t getSampleCount() const final;
  SamplePosition getSamplePos() const final;
  AudioStreamIn& setSamplePos(SamplePosition pos) final;
  AudioStreamIn& moveSamplePos(SampleOffset offset) final;

private:
  void readMetadata(const std::string& path);
  void onRead(void* buf, size_t elementSize, size_t bufSize) final;

private:
  File mFile;
  size_t mDataOffset;
  size_t mByteCount;
  size_t mElementCount;
};

}

#endif

