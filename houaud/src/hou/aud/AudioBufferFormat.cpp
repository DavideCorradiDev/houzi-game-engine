// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioBufferFormat.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"

#define AUDIO_BUFFER_FORMAT_CASE(format, os) \
  case AudioBufferFormat::format:            \
    return (os) << #format



namespace hou
{

AudioBufferFormat getAudioBufferFormatEnum(uint channels, uint bytesPerSample)
{
  HOU_EXPECT((channels == 1u || channels == 2u)
    && (bytesPerSample == 1u || bytesPerSample == 2u));
  if(channels == 1u)
  {
    if(bytesPerSample == 1u)
    {
      return AudioBufferFormat::Mono8;
    }
    else if(bytesPerSample == 2u)
    {
      return AudioBufferFormat::Mono16;
    }
  }
  else if(channels == 2u)
  {
    if(bytesPerSample == 1u)
    {
      return AudioBufferFormat::Stereo8;
    }
    else if(bytesPerSample == 2u)
    {
      return AudioBufferFormat::Stereo16;
    }
  }
  return AudioBufferFormat::Mono16;
}



uint getAudioBufferFormatChannelCount(AudioBufferFormat format)
{
  switch(format)
  {
  case AudioBufferFormat::Mono8:
  case AudioBufferFormat::Mono16:
    return 1u;
  case AudioBufferFormat::Stereo8:
  case AudioBufferFormat::Stereo16:
    return 2u;
  default:
    HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
    return 1u;
  }
}



uint getAudioBufferFormatBytesPerSample(AudioBufferFormat format)
{
  switch(format)
  {
  case AudioBufferFormat::Mono8:
  case AudioBufferFormat::Stereo8:
    return 1u;
  case AudioBufferFormat::Stereo16:
  case AudioBufferFormat::Mono16:
    return 2u;
  default:
    HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
    return 0u;
  }
}



std::ostream& operator<<(std::ostream& os, AudioBufferFormat format)
{
  switch(format)
  {
    AUDIO_BUFFER_FORMAT_CASE(Mono8, os);
    AUDIO_BUFFER_FORMAT_CASE(Mono16, os);
    AUDIO_BUFFER_FORMAT_CASE(Stereo8, os);
    AUDIO_BUFFER_FORMAT_CASE(Stereo16, os);
  default:
    return os;
  }
}

}  // namespace hou
