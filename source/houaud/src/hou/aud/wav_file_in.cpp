// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/wav_file_in.hpp"

#include "hou/aud/aud_error.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/sys/binary_file_in.hpp"
#include "hou/sys/sys_error.hpp"



namespace hou
{

namespace
{

constexpr size_t g_wav_header_string_size = 4u;

HOU_PRAGMA_PACK_PUSH(1)
struct wav_signature
{
  char id[g_wav_header_string_size];
  uint32_t size;
  char form[g_wav_header_string_size];
};
HOU_PRAGMA_PACK_POP()

HOU_PRAGMA_PACK_PUSH(1)
struct wav_chunk_signature
{
  char id[g_wav_header_string_size];
  uint32_t size;
};
HOU_PRAGMA_PACK_POP()

HOU_PRAGMA_PACK_PUSH(1)
struct wav_format
{
  wav_chunk_signature signature;
  uint16_t format;
  uint16_t channels;
  uint32_t sample_rate;
  uint32_t byte_rate;
  uint16_t block_align;
  uint16_t bits_per_sample;
};
HOU_PRAGMA_PACK_POP()

}  // namespace



bool wav_file_in::check(const std::string& path)
{
  binary_file_in f(path);
  wav_signature signature;
  f.read(signature);

  return std::string(signature.id, g_wav_header_string_size) == u8"RIFF"
    && std::string(signature.form, g_wav_header_string_size) == u8"WAVE";
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
  HOU_PRECOND((pos % (get_channel_count() * get_bytes_per_sample())) == 0u);
  DEPRECATED_HOU_RUNTIME_CHECK(pos >= 0
      && pos <= static_cast<wav_file_in::byte_position>(get_byte_count()),
    get_text(sys_error::file_seek));
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
  wav_signature signature;
  wav_format format;
  read(signature);
  read(format);

  // Check if the read opeartion was performed correctly.
  DEPRECATED_HOU_RUNTIME_CHECK(
    !m_file.eof(), get_text(aud_error::wav_invalid_header), path.c_str());

  // Consistency checks.
  DEPRECATED_HOU_RUNTIME_CHECK(
    std::string(signature.id, g_wav_header_string_size) == u8"RIFF",
    get_text(aud_error::wav_invalid_header), path.c_str());
  DEPRECATED_HOU_RUNTIME_CHECK(
    std::string(signature.form, g_wav_header_string_size) == u8"WAVE",
    get_text(aud_error::wav_invalid_header), path.c_str());
  DEPRECATED_HOU_RUNTIME_CHECK(
    std::string(format.signature.id, g_wav_header_string_size) == u8"fmt ",
    get_text(aud_error::wav_invalid_header), path.c_str());
  DEPRECATED_HOU_RUNTIME_CHECK(format.byte_rate
      == (format.sample_rate * format.channels * format.bits_per_sample / 8),
    get_text(aud_error::wav_invalid_header), path.c_str());
  DEPRECATED_HOU_RUNTIME_CHECK(
    format.block_align == (format.channels * format.bits_per_sample / 8u),
    get_text(aud_error::wav_invalid_header), path.c_str());

  // Look for the data subchunk.and set the data offset.
  wav_chunk_signature chunk_signature;
  read(chunk_signature);
  while(std::string(chunk_signature.id, g_wav_header_string_size) != u8"data")
  {
    m_file.seek_offset(chunk_signature.size);
    read(chunk_signature);
    DEPRECATED_HOU_RUNTIME_CHECK(
      !eof(), get_text(aud_error::wav_invalid_header), path.c_str());
  }

  // Set data offset.
  m_data_offset = m_file.tell();
  HOU_DEV_POSTCOND(get_byte_pos() == 0u);
  HOU_DEV_POSTCOND(get_byte_count() == chunk_signature.size);

  // Reset read counter (it is set to 1 by the metadata read operation);
  m_byte_count = 0;
  m_element_count = 0;

  // Update internal metadata.
  set_format(format.channels, format.bits_per_sample / 8u);
  set_sample_rate(format.sample_rate);
}



void wav_file_in::on_read(void* buf, size_t element_size, size_t buf_size)
{
  HOU_PRECOND(
    ((element_size * buf_size) % (get_channel_count() * get_bytes_per_sample()))
    == 0u);
  m_element_count = m_file.read(buf, element_size, buf_size);
  m_byte_count = m_element_count * element_size;
}

}  // namespace hou
