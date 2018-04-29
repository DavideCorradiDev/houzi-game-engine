// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_stream.hpp"



namespace hou
{

audio_stream::audio_stream()
  : binary_stream()
  , m_format(audio_buffer_format::mono8)
  , m_sample_rate(0u)
{}



audio_stream::~audio_stream()
{}



audio_buffer_format audio_stream::get_format() const
{
  return m_format;
}



uint audio_stream::get_channel_count() const
{
  return get_audio_buffer_format_channel_count(m_format);
}



uint audio_stream::get_bytes_per_sample() const
{
  return get_audio_buffer_format_bytes_per_sample(m_format);
}



uint audio_stream::get_sample_rate() const
{
  return m_sample_rate;
}



void audio_stream::set_format(uint channels, uint bytesPerSample)
{
  m_format = get_audio_buffer_format_enum(channels, bytesPerSample);
}



void audio_stream::set_sample_rate(uint sampleRate)
{
  m_sample_rate = sampleRate;
}

}  // namespace hou
