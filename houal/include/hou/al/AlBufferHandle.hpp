// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_BUFFER_HANDLE_HPP
#define HOU_AL_AL_BUFFER_HANDLE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/al/AlObjectHandle.hpp"

#include "hou/al/AlBufferFormat.hpp"



namespace hou
{

namespace al
{

class HOU_AL_API BufferHandle
  : public DeviceOwnedObjectHandle
{
public:
  static BufferHandle generate();

  BufferHandle(BufferHandle&& other);
  virtual ~BufferHandle();

private:
  BufferHandle(ALuint name);
};

HOU_AL_API void setBufferData(const BufferHandle& handle, BufferFormat format
  , ALvoid* data, ALsizei size, ALsizei freq);
HOU_AL_API ALint getBufferFrequency(const BufferHandle& handle);
HOU_AL_API ALint getBufferBits(const BufferHandle& handle);
HOU_AL_API ALint getBufferChannels(const BufferHandle& handle);
HOU_AL_API ALint getBufferSize(const BufferHandle& handle);

}

}

#endif

