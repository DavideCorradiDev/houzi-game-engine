// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_buffer.hpp"

#include "hou/aud/audio_stream_in.hpp"

#include "hou/cor/narrow_cast.hpp"



namespace hou
{

namespace
{
static constexpr uint bits_per_byte = 8u;
}



audio_buffer::audio_buffer()
  : audio_buffer(std::vector<uint8_t>(2u, 0u), audio_buffer_format::mono16, 1u)
{}



audio_buffer::audio_buffer(
  const span<const uint8_t>& data, audio_buffer_format format, int smlRate)
  : non_copyable()
  , m_handle(al::buffer_handle::generate())
{
  set_data(data, format, smlRate);
}



audio_buffer::audio_buffer(
  std::vector<uint8_t>&& data, audio_buffer_format format, int smp_rate)
  : audio_buffer(span<const uint8_t>(data), format, smp_rate)
{}



audio_buffer::audio_buffer(audio_stream_in& audio_stream)
  : non_copyable()
  , m_handle(al::buffer_handle::generate())
{
  set_data(audio_stream);
}



audio_buffer::audio_buffer(audio_stream_in&& audio_stream)
  : non_copyable()
  , m_handle(al::buffer_handle::generate())
{
  set_data(audio_stream);
}



const al::buffer_handle& audio_buffer::get_handle() const noexcept
{
  return m_handle;
}



audio_buffer_format audio_buffer::get_format() const
{
  return get_audio_buffer_format_enum(
    get_channel_count(), get_bytes_per_sample());
}



uint audio_buffer::get_bytes_per_sample() const
{
  return narrow_cast<uint>(al::get_buffer_bits(m_handle) / bits_per_byte);
}



uint audio_buffer::get_channel_count() const
{
  return narrow_cast<uint>(al::get_buffer_channels(m_handle));
}



int audio_buffer::get_sample_rate() const
{
  return narrow_cast<int>(al::get_buffer_frequency(m_handle));
}



uint audio_buffer::get_byte_count() const
{
  return narrow_cast<uint>(al::get_buffer_size(m_handle));
}



uint audio_buffer::get_sample_count() const
{
  HOU_DEV_ASSERT(get_bytes_per_sample() != 0u);
  HOU_DEV_ASSERT(
    get_byte_count() % (get_channel_count() * get_bytes_per_sample()) == 0);
  return get_byte_count() / (get_channel_count() * get_bytes_per_sample());
}



void audio_buffer::set_data(
  const span<const uint8_t>& data, audio_buffer_format format, int smlRate)
{
  HOU_DEV_ASSERT(sizeof(uint8_t) == 1u);
  al::set_buffer_data(m_handle, static_cast<ALenum>(format),
    reinterpret_cast<ALvoid*>(const_cast<uint8_t*>(data.data())),
    narrow_cast<ALsizei>(data.size()), narrow_cast<ALsizei>(smlRate));
}



void audio_buffer::set_data(
  std::vector<uint8_t>&& data, audio_buffer_format format, int smlRate)
{
  set_data(span<const uint8_t>(data), format, smlRate);
}



void audio_buffer::set_data(audio_stream_in& audio_stream)
{
  set_data(audio_stream.read_all<std::vector<uint8_t>>(),
    audio_stream.get_format(), audio_stream.get_sample_rate());
}



void audio_buffer::set_data(audio_stream_in&& audio_stream)
{
  set_data(audio_stream.read_all<std::vector<uint8_t>>(),
    audio_stream.get_format(), audio_stream.get_sample_rate());
}

}  // namespace hou
