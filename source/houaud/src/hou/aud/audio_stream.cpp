// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_stream.hpp"



namespace hou
{

audio_stream::audio_stream() noexcept
  : binary_stream()
  , m_format(audio_buffer_format::mono8)
  , m_sample_rate(0u)
{}



audio_buffer_format audio_stream::get_format() const noexcept
{
  return m_format;
}



uint audio_stream::get_channel_count() const noexcept
{
  return get_audio_buffer_format_channel_count(m_format);
}



uint audio_stream::get_bytes_per_sample() const noexcept
{
  return get_audio_buffer_format_bytes_per_sample(m_format);
}



uint audio_stream::get_sample_rate() const noexcept
{
  return m_sample_rate;
}



void audio_stream::set_format(uint channels, uint bytes_per_sample)
{
  m_format = get_audio_buffer_format_enum(channels, bytes_per_sample);
}



void audio_stream::set_sample_rate(uint sample_rate) noexcept
{
  m_sample_rate = sample_rate;
}

}  // namespace hou
