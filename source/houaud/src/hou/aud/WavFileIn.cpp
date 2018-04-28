// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/WavFileIn.hpp"

#include "hou/aud/AudError.hpp"

#include "hou/cor/error.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/sys_error.hpp"



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
  binary_file_in f(path);
  WavSignature signature;
  f.read(signature);

  return std::string(signature.id, wavHeaderStringSize) == u8"RIFF"
    && std::string(signature.form, wavHeaderStringSize) == u8"WAVE";
}



WavFileIn::WavFileIn(const std::string& path)
  : non_copyable()
  , AudioStreamIn()
  , m_file(path, file_open_mode::read, file_type::binary)
  , mDataOffset(0u)
  , m_byte_count(0u)
  , m_element_count(0u)
{
  readMetadata(path);
}



WavFileIn::WavFileIn(WavFileIn&& other)
  : AudioStreamIn(std::move(other))
  , m_file(std::move(other.m_file))
  , mDataOffset(std::move(other.mDataOffset))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
{}



WavFileIn::~WavFileIn()
{}



bool WavFileIn::eof() const
{
  return m_file.eof();
}



bool WavFileIn::error() const
{
  return m_file.error();
}



size_t WavFileIn::get_byte_count() const
{
  return m_file.get_byte_count() - mDataOffset;
}



size_t WavFileIn::get_read_byte_count() const
{
  return m_byte_count;
}



size_t WavFileIn::get_read_element_count() const
{
  return m_element_count;
}



WavFileIn::byte_position WavFileIn::get_byte_pos() const
{
  return m_file.tell() - mDataOffset;
}



binary_stream& WavFileIn::set_byte_pos(WavFileIn::byte_position pos)
{
  // Audio streams have stricter requirements for cursor position, therefore
  // a check must be done here.
  HOU_EXPECT((pos % (getChannelCount() * getBytesPerSample())) == 0u);
  HOU_RUNTIME_CHECK(pos >= 0
    && pos <= static_cast<WavFileIn::byte_position>(get_byte_count())
    , get_text(sys_error::file_seek));
  m_file.seek_set(pos + mDataOffset);
  return *this;
}



binary_stream& WavFileIn::move_byte_pos(WavFileIn::byte_offset offset)
{
  byte_position pos = get_byte_pos() + offset;
  return set_byte_pos(pos);
}



size_t WavFileIn::getSampleCount() const
{
  return get_byte_count() / (getChannelCount() * getBytesPerSample());
}



WavFileIn::SamplePosition WavFileIn::getSamplePos() const
{
  return get_byte_pos() / (getChannelCount() * getBytesPerSample());
}



AudioStreamIn& WavFileIn::setSamplePos(WavFileIn::SamplePosition pos)
{
  set_byte_pos(pos * (getChannelCount() * getBytesPerSample()));
  return *this;
}



AudioStreamIn& WavFileIn::moveSamplePos(WavFileIn::SampleOffset offset)
{
  move_byte_pos(offset * (getChannelCount() * getBytesPerSample()));
  return *this;
}



void WavFileIn::readMetadata(const std::string& path)
{

  // read metadata from header.
  WavSignature signature;
  WavFormat format;
  read(signature);
  read(format);

  // Check if the read opeartion was performed correctly.
  HOU_RUNTIME_CHECK(!m_file.eof(), get_text(AudError::WavInvalidHeader)
    , path.c_str());

  // Consistency checks.
  HOU_RUNTIME_CHECK(std::string(signature.id, wavHeaderStringSize) == u8"RIFF"
    , get_text(AudError::WavInvalidHeader), path.c_str());
  HOU_RUNTIME_CHECK(std::string(signature.form, wavHeaderStringSize) == u8"WAVE"
    , get_text(AudError::WavInvalidHeader), path.c_str());
  HOU_RUNTIME_CHECK(std::string(format.signature.id, wavHeaderStringSize)
    == u8"fmt ", get_text(AudError::WavInvalidHeader), path.c_str());
  HOU_RUNTIME_CHECK(format.byteRate == (format.sampleRate * format.channels
    * format.bitsPerSample / 8), get_text(AudError::WavInvalidHeader)
    , path.c_str());
  HOU_RUNTIME_CHECK(format.blockAlign == (format.channels * format.bitsPerSample
    / 8u), get_text(AudError::WavInvalidHeader), path.c_str());

  // Look for the data subchunk.and set the data offset.
  WavChunkSignature chunkSignature;
  read(chunkSignature);
  while(std::string(chunkSignature.id, wavHeaderStringSize) != u8"data")
  {
    m_file.seek_offset(chunkSignature.size);
    read(chunkSignature);
    HOU_RUNTIME_CHECK(!eof(), get_text(AudError::WavInvalidHeader)
      , path.c_str());
  }

  // Set data offset.
  mDataOffset = m_file.tell();
  HOU_ENSURE_DEV(get_byte_pos() == 0u);
  HOU_ENSURE_DEV(get_byte_count() == chunkSignature.size);

  // Reset read counter (it is set to 1 by the metadata read operation);
  m_byte_count = 0;
  m_element_count = 0;

  // Update internal metadata.
  setFormat(format.channels, format.bitsPerSample / 8u);
  setSampleRate(format.sampleRate);
}



void WavFileIn::on_read(void* buf, size_t elementSize, size_t bufSize)
{
  HOU_EXPECT(((elementSize * bufSize) % (getChannelCount() * getBytesPerSample()))
    == 0u);
  m_element_count = m_file.read(buf, elementSize, bufSize);
  m_byte_count = m_element_count * elementSize;
}

}

