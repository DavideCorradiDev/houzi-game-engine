// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_BUFFER_FORMAT_HPP
#define HOU_AL_AL_BUFFER_FORMAT_HPP

#include "hou/al/OpenAl.hpp"



namespace hou
{

namespace al
{

enum class BufferFormat : ALenum
{
  Unset = 0,
  Mono8 = AL_FORMAT_MONO8,
  Mono16 = AL_FORMAT_MONO16,
  Stereo8 = AL_FORMAT_STEREO8,
  Stereo16 = AL_FORMAT_STEREO16,
};

HOU_AL_API al::BufferFormat getBufferFormatEnum(ALint channels
  , ALint bytesPerSample);
HOU_AL_API ALint getBufferFormatChannels(BufferFormat format);
HOU_AL_API ALint getBufferFormatBytesPerSample(BufferFormat format);

}

}

#endif

