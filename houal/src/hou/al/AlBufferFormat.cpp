// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlBufferFormat.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"



namespace hou
{

namespace al
{

al::BufferFormat getBufferFormatEnum(ALint channels, ALint bytesPerSample)
{
  if(channels == 1)
  {
    if(bytesPerSample == 1)
    {
      return al::BufferFormat::Mono8;
    }
    else if(bytesPerSample == 2)
    {
      return al::BufferFormat::Mono16;
    }
  }
  else if(channels == 2)
  {
    if(bytesPerSample == 1)
    {
      return al::BufferFormat::Stereo8;
    }
    else if(bytesPerSample == 2)
    {
      return al::BufferFormat::Stereo16;
    }
  }
  return al::BufferFormat::Unset;
}



ALint getBufferFormatChannels(BufferFormat format)
{
  switch(format)
  {
    case al::BufferFormat::Unset:
      return 0;
    case al::BufferFormat::Mono8:
    case al::BufferFormat::Mono16:
      return 1;
    case al::BufferFormat::Stereo8:
    case al::BufferFormat::Stereo16:
      return 2;
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
      return 0;
  }
}



ALint getBufferFormatBytesPerSample(BufferFormat format)
{
  switch(format)
  {
    case al::BufferFormat::Unset:
      return 0;
    case al::BufferFormat::Mono8:
    case al::BufferFormat::Stereo8:
      return 1;
    case al::BufferFormat::Stereo16:
    case al::BufferFormat::Mono16:
      return 2;
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(format));
      return 0;
  }
}

}

}

