// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/ogg_file_in.hpp"

#include "hou/aud/aud_error.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/pragmas.hpp"

#include "hou/sys/sys_error.hpp"

// clang-format off
HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(-Wunused-variable)
#include <vorbis/vorbisfile.h>
HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
// clang-format on



namespace hou
{

namespace
{

// It is possible to decide whether to decode data in 8 or 16 bits format.
// We just set 16 bits by default.
static constexpr size_t bytes_per_sample = 2u;

}  // namespace



bool ogg_file_in::check(const std::string& path)
{
  FILE* file = open_file(path, "rb");
  HOU_RUNTIME_CHECK(
    file != nullptr, get_text(sys_error::file_open), path.c_str());

  OggVorbis_File vorbis_file;
  if(ov_test(file, &vorbis_file, nullptr, 0) != 0)
  {
    fclose(file);
    return false;
  }
  else
  {
    ov_clear(&vorbis_file);
    return true;
  }
}



ogg_file_in::ogg_file_in(const std::string& path)
  : non_copyable()
  , audio_stream_in()
  , m_vorbis_file(std::make_unique<OggVorbis_File>())
  , m_logical_bit_stream(0u)
  , m_pcm_size(0u)
  , m_byte_count(0u)
  , m_element_count(0u)
  , m_eof(false)
  , m_error(false)
{
  FILE* file = open_file(path, "rb");
  HOU_RUNTIME_CHECK(
    file != nullptr, get_text(sys_error::file_open), path.c_str());

  // The last two parameters are used to point to initial data.
  // They are irrelevant in this case.
  if(ov_open(file, m_vorbis_file.get(), nullptr, 0) != 0)
  {
    fclose(file);
    HOU_RUNTIME_ERROR(get_text(aud_error::ogg_invalid_header), path.c_str());
  }

  read_metadata();
}



ogg_file_in::ogg_file_in::ogg_file_in(ogg_file_in&& other)
  : audio_stream_in(std::move(other))
  , m_vorbis_file(std::move(other.m_vorbis_file))
  , m_logical_bit_stream(std::move(other.m_logical_bit_stream))
  , m_pcm_size(std::move(other.m_pcm_size))
  , m_byte_count(std::move(other.m_byte_count))
  , m_element_count(std::move(other.m_element_count))
  , m_eof(std::move(other.m_eof))
  , m_error(std::move(other.m_error))
{
  other.m_vorbis_file.reset(nullptr);
}



ogg_file_in::~ogg_file_in()
{
  if(m_vorbis_file != nullptr)
  {
    HOU_FATAL_CHECK(
      ov_clear(m_vorbis_file.get()) == 0, get_text(sys_error::file_close));
  }
}



bool ogg_file_in::eof() const
{
  return m_eof;
}



bool ogg_file_in::error() const
{
  return m_error;
}



size_t ogg_file_in::get_byte_count() const
{
  return get_sample_count() * (get_channel_count() * get_bytes_per_sample());
}



size_t ogg_file_in::get_read_byte_count() const
{
  return m_byte_count;
}



size_t ogg_file_in::get_read_element_count() const
{
  return m_element_count;
}



ogg_file_in::byte_position ogg_file_in::get_byte_pos() const
{
  return get_sample_pos() * (get_channel_count() * get_bytes_per_sample());
}



binary_stream& ogg_file_in::set_byte_pos(ogg_file_in::byte_position pos)
{
  HOU_EXPECT((pos % (get_channel_count() * get_bytes_per_sample())) == 0u);
  set_sample_pos(pos / (get_channel_count() * get_bytes_per_sample()));
  return *this;
}



binary_stream& ogg_file_in::move_byte_pos(ogg_file_in::byte_offset offset)
{
  set_byte_pos(static_cast<byte_position>(
    static_cast<byte_offset>(get_byte_pos()) + offset));
  return *this;
}



size_t ogg_file_in::get_sample_count() const
{
  return m_pcm_size;
}



ogg_file_in::sample_position ogg_file_in::get_sample_pos() const
{
  return static_cast<sample_position>(
    ov_pcm_tell(const_cast<OggVorbis_File*>(m_vorbis_file.get())));
}



audio_stream_in& ogg_file_in::set_sample_pos(ogg_file_in::sample_position pos)
{
  m_eof = false;
  HOU_RUNTIME_CHECK(
    ov_pcm_seek(m_vorbis_file.get(), static_cast<ogg_int64_t>(pos)) == 0,
    get_text(sys_error::file_seek));
  return *this;
}



audio_stream_in& ogg_file_in::move_sample_pos(ogg_file_in::sample_offset offset)
{
  m_eof = false;
  HOU_RUNTIME_CHECK(
    ov_pcm_seek(m_vorbis_file.get(),
      static_cast<ogg_int64_t>(
        static_cast<ogg_file_in::sample_offset>(get_sample_pos()) + offset))
      == 0,
    get_text(sys_error::file_seek));
  return *this;
}



void ogg_file_in::read_metadata()
{
  vorbis_info* info = ov_info(m_vorbis_file.get(), -1);
  HOU_EXPECT(info != nullptr);
  set_format(info->channels, bytes_per_sample);
  set_sample_rate(info->rate);
  m_pcm_size = ov_pcm_total(m_vorbis_file.get(), -1);
}



void ogg_file_in::on_read(void* buf, size_t element_size, size_t buf_size)
{
  // Constant read parameters.
  static constexpr int big_endian_data = 0;
  static constexpr int signed_data = 1;

  HOU_EXPECT_DEV(get_bytes_per_sample() == bytes_per_sample);

  // ov_read reads one packet at most, so it has to be called repeatedly.
  // This is done by the following loop.
  size_t sizeBytes = element_size * buf_size;
  HOU_EXPECT(
    (sizeBytes % (get_channel_count() * get_bytes_per_sample())) == 0u);
  size_t countBytes = 0u;
  m_eof = false;
  while(countBytes < sizeBytes)
  {
    // If there is still room in the buffer, perform a read.
    long bytesRead = ov_read(m_vorbis_file.get(),
      reinterpret_cast<char*>(buf) + countBytes, sizeBytes - countBytes,
      big_endian_data, bytes_per_sample, signed_data, &m_logical_bit_stream);

    // No bytes read: end of file.
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
  HOU_RUNTIME_CHECK(
    countBytes == sizeBytes || !error(), get_text(sys_error::file_read));
  HOU_ENSURE_DEV(countBytes % element_size == 0u);
  m_byte_count = countBytes;
  m_element_count = countBytes / element_size;
}

}  // namespace hou
