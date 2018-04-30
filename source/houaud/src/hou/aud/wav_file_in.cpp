// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/wav_file_in.hpp"

#include "hou/aud/aud_error.hpp"

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



bool wav_file_in::check(const std::string& path)
{
  binary_file_in f(path);
  WavSignature signature;
  f.read(signature);

  return std::string(signature.id, wavHeaderStringSize) == u8"RIFF"
    && std::string(signature.form, wavHeaderStringSize) == u8"WAVE";
}



wav_file_in::wav_file_in(const std::string& path)
  : non_copyable()
  , audio_stream_in()
  , m_file(path, file_open_mode::read, file_type::binary)
  , m_data_offset(0u)
  , m_byte_count(0u)
  , m_element_count(0u)
{
  read_metadata(path);
}



wav_file_in::wav_file_in(wav_file_in&& other)
  : audio_stream_in(std::move(other))
  , m_file(std::move(other.m_file))
  , m_data_offset(std::move(other.m_data_offset))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
{}



wav_file_in::~wav_file_in()
{}



bool wav_file_in::eof() const
{
  return m_file.eof();
}



bool wav_file_in::error() const
{
  return m_file.error();
}



size_t wav_file_in::get_byte_count() const
{
  return m_file.get_byte_count() - m_data_offset;
}



size_t wav_file_in::get_read_byte_count() const
{
  return m_byte_count;
}



size_t wav_file_in::get_read_element_count() const
{
  return m_element_count;
}



wav_file_in::byte_position wav_file_in::get_byte_pos() const
{
  return m_file.tell() - m_data_offset;
}



binary_stream& wav_file_in::set_byte_pos(wav_file_in::byte_position pos)
{
  // Audio streams have stricter requirements for cursor position, therefore
  // a check must be done here.
  HOU_EXPECT((pos % (get_channel_count() * get_bytes_per_sample())) == 0u);
  HOU_RUNTIME_CHECK(pos >= 0
    && pos <= static_cast<wav_file_in::byte_position>(get_byte_count())
    , get_text(sys_error::file_seek));
  m_file.seek_set(pos + m_data_offset);
  return *this;
}



binary_stream& wav_file_in::move_byte_pos(wav_file_in::byte_offset offset)
{
  byte_position pos = get_byte_pos() + offset;
  return set_byte_pos(pos);
}



size_t wav_file_in::get_sample_count() const
{
  return get_byte_count() / (get_channel_count() * get_bytes_per_sample());
}



wav_file_in::sample_position wav_file_in::get_sample_pos() const
{
  return get_byte_pos() / (get_channel_count() * get_bytes_per_sample());
}



audio_stream_in& wav_file_in::set_sample_pos(wav_file_in::sample_position pos)
{
  set_byte_pos(pos * (get_channel_count() * get_bytes_per_sample()));
  return *this;
}



audio_stream_in& wav_file_in::move_sample_pos(wav_file_in::sample_offset offset)
{
  move_byte_pos(offset * (get_channel_count() * get_bytes_per_sample()));
  return *this;
}



void wav_file_in::read_metadata(const std::string& path)
{

  // read metadata from header.
  WavSignature signature;
  WavFormat format;
  read(signature);
  read(format);

  // Check if the read opeartion was performed correctly.
  HOU_RUNTIME_CHECK(!m_file.eof(), get_text(aud_error::wav_invalid_header)
    , path.c_str());

  // Consistency checks.
  HOU_RUNTIME_CHECK(std::string(signature.id, wavHeaderStringSize) == u8"RIFF"
    , get_text(aud_error::wav_invalid_header), path.c_str());
  HOU_RUNTIME_CHECK(std::string(signature.form, wavHeaderStringSize) == u8"WAVE"
    , get_text(aud_error::wav_invalid_header), path.c_str());
  HOU_RUNTIME_CHECK(std::string(format.signature.id, wavHeaderStringSize)
    == u8"fmt ", get_text(aud_error::wav_invalid_header), path.c_str());
  HOU_RUNTIME_CHECK(format.byteRate == (format.sampleRate * format.channels
    * format.bitsPerSample / 8), get_text(aud_error::wav_invalid_header)
    , path.c_str());
  HOU_RUNTIME_CHECK(format.blockAlign == (format.channels * format.bitsPerSample
    / 8u), get_text(aud_error::wav_invalid_header), path.c_str());

  // Look for the data subchunk.and set the data offset.
  WavChunkSignature chunkSignature;
  read(chunkSignature);
  while(std::string(chunkSignature.id, wavHeaderStringSize) != u8"data")
  {
    m_file.seek_offset(chunkSignature.size);
    read(chunkSignature);
    HOU_RUNTIME_CHECK(!eof(), get_text(aud_error::wav_invalid_header)
      , path.c_str());
  }

  // Set data offset.
  m_data_offset = m_file.tell();
  HOU_ENSURE_DEV(get_byte_pos() == 0u);
  HOU_ENSURE_DEV(get_byte_count() == chunkSignature.size);

  // Reset read counter (it is set to 1 by the metadata read operation);
  m_byte_count = 0;
  m_element_count = 0;

  // Update internal metadata.
  set_format(format.channels, format.bitsPerSample / 8u);
  set_sample_rate(format.sampleRate);
}



void wav_file_in::on_read(void* buf, size_t element_size, size_t buf_size)
{
  HOU_EXPECT(((element_size * buf_size) % (get_channel_count() * get_bytes_per_sample()))
    == 0u);
  m_element_count = m_file.read(buf, element_size, buf_size);
  m_byte_count = m_element_count * element_size;
}

}

