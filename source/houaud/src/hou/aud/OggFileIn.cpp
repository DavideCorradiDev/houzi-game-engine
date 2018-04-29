// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/OggFileIn.hpp"

#include "hou/aud/AudError.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/sys/sys_error.hpp"

HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wunused-variable)
#include <vorbis/vorbisfile.h>
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()


namespace hou
{

namespace
{

// It is possible to decide whether to decode data in 8 or 16 bits format.
// We just set 16 bits by default.
static constexpr size_t bytesPerSample = 2u;

}



bool OggFileIn::check(const std::string& path)
{
  FILE* ph_file = open_file(path, "rb");
  HOU_RUNTIME_CHECK(ph_file != nullptr, get_text(sys_error::file_open)
    , path.c_str());

  OggVorbis_File vorbisFile;
  if(ov_test(ph_file, &vorbisFile, nullptr, 0) != 0)
  {
    fclose(ph_file);
    return false;
  }
  else
  {
    ov_clear(&vorbisFile);
    return true;
  }
}



OggFileIn::OggFileIn(const std::string& path)
  : non_copyable()
  , AudioStreamIn()
  , mVorbisFile(std::make_unique<OggVorbis_File>())
  , mLogicalBitStream(0u)
  , mPcmSize(0u)
  , m_byte_count(0u)
  , m_element_count(0u)
  , m_eof(false)
  , m_error(false)
{
  FILE* ph_file = open_file(path, "rb");
  HOU_RUNTIME_CHECK(ph_file != nullptr, get_text(sys_error::file_open)
    , path.c_str());

  // The last two parameters are used to point to initial data.
  // They are irrelevant in this case.
  if(ov_open(ph_file, mVorbisFile.get(), nullptr, 0) != 0)
  {
    fclose(ph_file);
    HOU_RUNTIME_ERROR(get_text(AudError::OggInvalidHeader), path.c_str());
  }

  readMetadata();
}



OggFileIn::OggFileIn::OggFileIn(OggFileIn&& other)
  : AudioStreamIn(std::move(other))
  , mVorbisFile(std::move(other.mVorbisFile))
  , mLogicalBitStream(std::move(other.mLogicalBitStream))
  , mPcmSize(std::move(other.mPcmSize))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
  , m_eof(std::move(other.m_eof))
  , m_error(std::move(other.m_error))
{
  other.mVorbisFile.reset(nullptr);
}



OggFileIn::~OggFileIn()
{
  if(mVorbisFile != nullptr)
  {
    HOU_FATAL_CHECK(ov_clear(mVorbisFile.get()) == 0, get_text(sys_error::file_close));
  }
}



bool OggFileIn::eof() const
{
  return m_eof;
}



bool OggFileIn::error() const
{
  return m_error;
}



size_t OggFileIn::get_byte_count() const
{
  return get_sample_count() * (getChannelCount() * getBytesPerSample());
}



size_t OggFileIn::get_read_byte_count() const
{
  return m_byte_count;
}



size_t OggFileIn::get_read_element_count() const
{
  return m_element_count;
}



OggFileIn::byte_position OggFileIn::get_byte_pos() const
{
  return getSamplePos() * (getChannelCount() * getBytesPerSample());
}



binary_stream& OggFileIn::set_byte_pos(OggFileIn::byte_position pos)
{
  HOU_EXPECT((pos % (getChannelCount() * getBytesPerSample())) == 0u);
  setSamplePos(pos / (getChannelCount() * getBytesPerSample()));
  return *this;
}



binary_stream& OggFileIn::move_byte_pos(OggFileIn::byte_offset offset)
{
  set_byte_pos(static_cast<byte_position>(static_cast<byte_offset>
    (get_byte_pos()) + offset));
  return *this;
}



size_t OggFileIn::get_sample_count() const
{
  return mPcmSize;
}



OggFileIn::SamplePosition OggFileIn::getSamplePos() const
{
  return static_cast<SamplePosition>(ov_pcm_tell
    (const_cast<OggVorbis_File*>(mVorbisFile.get())));
}



AudioStreamIn& OggFileIn::setSamplePos(OggFileIn::SamplePosition pos)
{
  m_eof = false;
  HOU_RUNTIME_CHECK(ov_pcm_seek(mVorbisFile.get()
    , static_cast<ogg_int64_t>(pos)) == 0, get_text(sys_error::file_seek));
  return *this;
}



AudioStreamIn& OggFileIn::moveSamplePos(OggFileIn::SampleOffset offset)
{
  m_eof = false;
  HOU_RUNTIME_CHECK(ov_pcm_seek(mVorbisFile.get(), static_cast<ogg_int64_t>
    (static_cast<OggFileIn::SampleOffset>(getSamplePos()) + offset)) == 0
    , get_text(sys_error::file_seek));
  return *this;
}



void OggFileIn::readMetadata()
{
  vorbis_info* info = ov_info(mVorbisFile.get(), -1);
  HOU_EXPECT(info != nullptr);
  setFormat(info->channels, bytesPerSample);
  setSampleRate(info->rate);
  mPcmSize = ov_pcm_total(mVorbisFile.get(), -1);
}



void OggFileIn::on_read(void* buf, size_t elementSize, size_t bufSize)
{
  // Constant read parameters.
  static constexpr int bigEndianData = 0;
  static constexpr int signedData = 1;

  HOU_EXPECT_DEV(getBytesPerSample() == bytesPerSample);

  // ov_read reads one packet at most, so it has to be called repeatedly.
  // This is done by the following loop.
  size_t sizeBytes = elementSize * bufSize;
  HOU_EXPECT((sizeBytes % (getChannelCount() * getBytesPerSample())) == 0u);
  size_t countBytes = 0u;
  m_eof = false;
  while(countBytes < sizeBytes)
  {
    // If there is still room in the buffer, perform a read.
    long bytesRead = ov_read(mVorbisFile.get()
    , reinterpret_cast<char*>(buf) + countBytes, sizeBytes - countBytes
    , bigEndianData, bytesPerSample, signedData, &mLogicalBitStream);

    // No bytes read: end of ph_file.
    if(bytesRead == 0)
    {
      m_eof = true;
      break;
    }
    // Negative value: error.
    else if(bytesRead < 0)
    {
      m_error = true;
      break;
    }
    // Bytes read, increment counter and go to next loop iteration.
    else
    {
      countBytes += bytesRead;
      HOU_ENSURE_DEV(countBytes <= sizeBytes);
    }
  }
  // Check that no error happened during the read operation.
  HOU_RUNTIME_CHECK(countBytes == sizeBytes || !error()
    , get_text(sys_error::file_read));
  HOU_ENSURE_DEV(countBytes % elementSize == 0u);
  m_byte_count = countBytes;
  m_element_count = countBytes / elementSize;
}

}

