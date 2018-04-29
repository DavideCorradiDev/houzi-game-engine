// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_buffer_format.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"

#define AUDIO_BUFFER_FORMAT_CASE(format, os) \
  case audio_buffer_format::format:            \
    return (os) << #format



namespace hou
{

audio_buffer_format get_audio_buffer_format_enum(uint channels, uint bytesPerSample)
{
  HOU_EXPECT((channels == 1u || channels == 2u)
    && (bytesPerSample == 1u || bytesPerSample == 2u));
  if(channels == 1u)
  {
    if(bytesPerSample == 1u)
    {
      return audio_buffer_format::mono8;
    }
    else if(bytesPerSample == 2u)
    {
      return audio_buffer_format::mono16;
    }
  }
  else if(channels == 2u)
  {
    if(bytesPerSample == 1u)
    {
      return audio_buffer_format::stereo8;
    }
    else if(bytesPerSample == 2u)
    {
      return audio_buffer_format::stereo16;
    }
  }
  return audio_buffer_format::mono16;
}



uint get_audio_buffer_format_channel_count(audio_buffer_format format)
{
  switch(format)
  {
  case audio_buffer_format::mono8:
  case audio_buffer_format::mono16:
    return 1u;
  case audio_buffer_format::stereo8:
  case audio_buffer_format::stereo16:
    return 2u;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(format));
    return 1u;
  }
}



uint get_audio_buffer_format_bytes_per_sample(audio_buffer_format format)
{
  switch(format)
  {
  case audio_buffer_format::mono8:
  case audio_buffer_format::stereo8:
    return 1u;
  case audio_buffer_format::stereo16:
  case audio_buffer_format::mono16:
    return 2u;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(format));
    return 0u;
  }
}



std::ostream& operator<<(std::ostream& os, audio_buffer_format format)
{
  switch(format)
  {
    AUDIO_BUFFER_FORMAT_CASE(mono8, os);
    AUDIO_BUFFER_FORMAT_CASE(mono16, os);
    AUDIO_BUFFER_FORMAT_CASE(stereo8, os);
    AUDIO_BUFFER_FORMAT_CASE(stereo16, os);
  default:
    return os;
  }
}

}  // namespace hou
