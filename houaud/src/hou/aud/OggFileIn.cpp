// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/OggFileIn.hpp"

#include "hou/aud/AudError.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/Pragmas.hpp"

#include "hou/sys/SysError.hpp"

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
  FILE* file = openFile(path, "rb");
  HOU_RUNTIME_CHECK(file != nullptr, getText(SysError::FileOpen)
    , path.c_str());

  OggVorbis_File vorbisFile;
  if(ov_test(file, &vorbisFile, nullptr, 0) != 0)
  {
    fclose(file);
    return false;
  }
  else
  {
    ov_clear(&vorbisFile);
    return true;
  }
}



OggFileIn::OggFileIn(const std::string& path)
  : NonCopyable()
  , AudioStreamIn()
  , mVorbisFile(std::make_unique<OggVorbis_File>())
  , mLogicalBitStream(0u)
  , mPcmSize(0u)
  , mByteCount(0u)
  , mElementCount(0u)
  , mEof(false)
  , mError(false)
{
  FILE* file = openFile(path, "rb");
  HOU_RUNTIME_CHECK(file != nullptr, getText(SysError::FileOpen)
    , path.c_str());

  // The last two parameters are used to point to initial data.
  // They are irrelevant in this case.
  if(ov_open(file, mVorbisFile.get(), nullptr, 0) != 0)
  {
    fclose(file);
    HOU_RUNTIME_ERROR(getText(AudError::OggInvalidHeader), path.c_str());
  }

  readMetadata();
}



OggFileIn::OggFileIn::OggFileIn(OggFileIn&& other)
  : AudioStreamIn(std::move(other))
  , mVorbisFile(std::move(other.mVorbisFile))
  , mLogicalBitStream(std::move(other.mLogicalBitStream))
  , mPcmSize(std::move(other.mPcmSize))
  , mByteCount(std::move(other.mByteCount))
  , mElementCount(std::move(other.mElementCount))
  , mEof(std::move(other.mEof))
  , mError(std::move(other.mError))
{
  other.mVorbisFile.reset(nullptr);
}



OggFileIn::~OggFileIn()
{
  if(mVorbisFile != nullptr)
  {
    HOU_FATAL_CHECK(ov_clear(mVorbisFile.get()) == 0, getText(SysError::FileClose));
  }
}



bool OggFileIn::eof() const
{
  return mEof;
}



bool OggFileIn::error() const
{
  return mError;
}



size_t OggFileIn::getByteCount() const
{
  return getSampleCount() * (getChannelCount() * getBytesPerSample());
}



size_t OggFileIn::getReadByteCount() const
{
  return mByteCount;
}



size_t OggFileIn::getReadElementCount() const
{
  return mElementCount;
}



OggFileIn::BytePosition OggFileIn::getBytePos() const
{
  return getSamplePos() * (getChannelCount() * getBytesPerSample());
}



BinaryStream& OggFileIn::setBytePos(OggFileIn::BytePosition pos)
{
  HOU_EXPECT((pos % (getChannelCount() * getBytesPerSample())) == 0u);
  setSamplePos(pos / (getChannelCount() * getBytesPerSample()));
  return *this;
}



BinaryStream& OggFileIn::moveBytePos(OggFileIn::ByteOffset offset)
{
  setBytePos(static_cast<BytePosition>(static_cast<ByteOffset>
    (getBytePos()) + offset));
  return *this;
}



size_t OggFileIn::getSampleCount() const
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
  mEof = false;
  HOU_RUNTIME_CHECK(ov_pcm_seek(mVorbisFile.get()
    , static_cast<ogg_int64_t>(pos)) == 0, getText(SysError::FileSeek));
  return *this;
}



AudioStreamIn& OggFileIn::moveSamplePos(OggFileIn::SampleOffset offset)
{
  mEof = false;
  HOU_RUNTIME_CHECK(ov_pcm_seek(mVorbisFile.get(), static_cast<ogg_int64_t>
    (static_cast<OggFileIn::SampleOffset>(getSamplePos()) + offset)) == 0
    , getText(SysError::FileSeek));
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



void OggFileIn::onRead(void* buf, size_t elementSize, size_t bufSize)
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
  mEof = false;
  while(countBytes < sizeBytes)
  {
    // If there is still room in the buffer, perform a read.
    long bytesRead = ov_read(mVorbisFile.get()
    , reinterpret_cast<char*>(buf) + countBytes, sizeBytes - countBytes
    , bigEndianData, bytesPerSample, signedData, &mLogicalBitStream);

    // No bytes read: end of file.
    if(bytesRead == 0)
    {
      mEof = true;
      break;
    }
    // Negative value: error.
    else if(bytesRead < 0)
    {
      mError = true;
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
    , getText(SysError::FileRead));
  HOU_ENSURE_DEV(countBytes % elementSize == 0u);
  mByteCount = countBytes;
  mElementCount = countBytes / elementSize;
}

}

