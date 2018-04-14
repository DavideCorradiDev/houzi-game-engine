// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioFormat.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"

#define AUDIO_FORMAT_CASE(format, os) \
  case AudioFormat::format: return (os) << #format



namespace hou
{

al::BufferFormat audioBufferFormatToAlBufferFormat(AudioFormat format)
{
  switch(format)
  {
    case AudioFormat::Mono8:
      return al::BufferFormat::Mono8;
    case AudioFormat::Mono16:
      return al::BufferFormat::Mono16;
    case AudioFormat::Stereo8:
      return al::BufferFormat::Stereo8;
    case AudioFormat::Stereo16:
      return al::BufferFormat::Stereo16;
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
      return al::BufferFormat::Unset;
  }
}

AudioFormat alBufferFormatToAudioFormat(al::BufferFormat format)
{
  switch(format)
  {
    case al::BufferFormat::Mono8:
      return AudioFormat::Mono8;
    case al::BufferFormat::Mono16:
      return AudioFormat::Mono16;
    case al::BufferFormat::Stereo8:
      return AudioFormat::Stereo8;
    case al::BufferFormat::Stereo16:
      return AudioFormat::Stereo16;
    case al::BufferFormat::Unset:
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
      return AudioFormat::Mono8;
  }
}



AudioFormat getAudioFormatEnum(uint channels, uint bytsPerSample)
{
  return alBufferFormatToAudioFormat
    (al::getBufferFormatEnum(static_cast<ALint>(channels)
    , static_cast<ALint>(bytsPerSample)));
}



uint getAudioFormatChannelCount(AudioFormat format)
{
  return static_cast<uint>(al::getBufferFormatChannels
    (audioBufferFormatToAlBufferFormat(format)));
}



uint getAudioFormatBytesPerSample(AudioFormat format)
{
  return static_cast<uint>(al::getBufferFormatBytesPerSample
    (audioBufferFormatToAlBufferFormat(format)));
}



std::ostream& operator<<(std::ostream& os, AudioFormat format)
{
  switch(format)
  {
    AUDIO_FORMAT_CASE(Mono8, os);
    AUDIO_FORMAT_CASE(Mono16, os);
    AUDIO_FORMAT_CASE(Stereo8, os);
    AUDIO_FORMAT_CASE(Stereo16, os);
    default: return os;
  }
}

}

