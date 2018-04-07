// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/aud/WavFileIn.hpp"

#include "hou/aud/AudError.hpp"

#include "hou/cor/Error.hpp"

#include "hou/sys/BinaryFileIn.hpp"
#include "hou/sys/SysError.hpp"



namespace hou
{

namespace
{
  constexpr size_t wavHeaderStringSize = 4u;

  struct WavSignature
  {
    char id[wavHeaderStringSize];
    uint32_t size;
    char form[wavHeaderStringSize];
  };

  struct WavChunkSignature
  {
    char id[wavHeaderStringSize];
    uint32_t size;
  };

  struct WavFormat
  {
    WavChunkSignature signature;
    uint16_t format;
    uint16_t channels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
  };
}



bool WavFileIn::check(const std::string& path)
{
  BinaryFileIn f(path);
  WavSignature signature;
  f.read(signature);

  return std::string(signature.id, wavHeaderStringSize) == u8"RIFF"
    && std::string(signature.form, wavHeaderStringSize) == u8"WAVE";
}



WavFileIn::WavFileIn(const std::string& path)
  : NonCopyable()
  , AudioStreamIn()
  , mFile(path, FileOpenMode::Read, FileType::Binary)
  , mDataOffset(0u)
  , mByteCount(0u)
  , mElementCount(0u)
{
  readMetadata(path);
}



WavFileIn::WavFileIn(WavFileIn&& other)
  : AudioStreamIn(std::move(other))
  , mFile(std::move(other.mFile))
  , mDataOffset(std::move(other.mDataOffset))
  , mByteCount(std::move(other.mByteCount))
  , mElementCount(std::move(other.mElementCount))
{}



WavFileIn::~WavFileIn()
{}



bool WavFileIn::eof() const
{
  return mFile.eof();
}



bool WavFileIn::error() const
{
  return mFile.error();
}



size_t WavFileIn::getByteCount() const
{
  return mFile.getByteCount() - mDataOffset;
}



size_t WavFileIn::getReadByteCount() const
{
  return mByteCount;
}



size_t WavFileIn::getReadElementCount() const
{
  return mElementCount;
}



WavFileIn::BytePosition WavFileIn::getBytePos() const
{
  return mFile.tell() - mDataOffset;
}



BinaryStream& WavFileIn::setBytePos(WavFileIn::BytePosition pos)
{
  // Audio streams have stricter requirements for cursor position, therefore
  // a check must be done here.
  HOU_EXPECT((pos % (getChannelCount() * getBytesPerSample())) == 0u);
  HOU_RUNTIME_CHECK(pos >= 0
    && pos <= static_cast<WavFileIn::BytePosition>(getByteCount())
    , getText(SysError::FileSeek));
  mFile.seekSet(pos + mDataOffset);
  return *this;
}



BinaryStream& WavFileIn::moveBytePos(WavFileIn::ByteOffset offset)
{
  BytePosition pos = getBytePos() + offset;
  return setBytePos(pos);
}



size_t WavFileIn::getSampleCount() const
{
  return getByteCount() / (getChannelCount() * getBytesPerSample());
}



WavFileIn::SamplePosition WavFileIn::getSamplePos() const
{
  return getBytePos() / (getChannelCount() * getBytesPerSample());
}



AudioStreamIn& WavFileIn::setSamplePos(WavFileIn::SamplePosition pos)
{
  setBytePos(pos * (getChannelCount() * getBytesPerSample()));
  return *this;
}



AudioStreamIn& WavFileIn::moveSamplePos(WavFileIn::SampleOffset offset)
{
  moveBytePos(offset * (getChannelCount() * getBytesPerSample()));
  return *this;
}



void WavFileIn::readMetadata(const std::string& path)
{

  // Read metadata from header.
  WavSignature signature;
  WavFormat format;
  read(signature);
  read(format);

  // Check if the read opeartion was performed correctly.
  HOU_RUNTIME_CHECK(!mFile.eof(), getText(AudError::WavInvalidHeader)
    , path.c_str());

  // Consistency checks.
  HOU_RUNTIME_CHECK(std::string(signature.id, wavHeaderStringSize) == u8"RIFF"
    , getText(AudError::WavInvalidHeader), path.c_str());
  HOU_RUNTIME_CHECK(std::string(signature.form, wavHeaderStringSize) == u8"WAVE"
    , getText(AudError::WavInvalidHeader), path.c_str());
  HOU_RUNTIME_CHECK(std::string(format.signature.id, wavHeaderStringSize)
    == u8"fmt ", getText(AudError::WavInvalidHeader), path.c_str());
  HOU_RUNTIME_CHECK(format.byteRate == (format.sampleRate * format.channels
    * format.bitsPerSample / 8), getText(AudError::WavInvalidHeader)
    , path.c_str());
  HOU_RUNTIME_CHECK(format.blockAlign == (format.channels * format.bitsPerSample
    / 8u), getText(AudError::WavInvalidHeader), path.c_str());

  // Look for the data subchunk.and set the data offset.
  WavChunkSignature chunkSignature;
  read(chunkSignature);
  while(std::string(chunkSignature.id, wavHeaderStringSize) != u8"data")
  {
    mFile.seekOffset(chunkSignature.size);
    read(chunkSignature);
    HOU_RUNTIME_CHECK(!eof(), getText(AudError::WavInvalidHeader)
      , path.c_str());
  }

  // Set data offset.
  mDataOffset = mFile.tell();
  HOU_ENSURE_DEV(getBytePos() == 0u);
  HOU_ENSURE_DEV(getByteCount() == chunkSignature.size);

  // Reset read counter (it is set to 1 by the metadata read operation);
  mByteCount = 0;
  mElementCount = 0;

  // Update internal metadata.
  setAudioFormat(format.channels, format.bitsPerSample / 8u);
  setSampleRate(format.sampleRate);
}



void WavFileIn::onRead(void* buf, size_t elementSize, size_t bufSize)
{
  HOU_EXPECT(((elementSize * bufSize) % (getChannelCount() * getBytesPerSample()))
    == 0u);
  mElementCount = mFile.read(buf, elementSize, bufSize);
  mByteCount = mElementCount * elementSize;
}

}

