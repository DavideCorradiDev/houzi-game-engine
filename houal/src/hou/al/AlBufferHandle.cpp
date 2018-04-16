// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlBufferHandle.hpp"

#include "hou/al/AlCheck.hpp"



namespace hou
{

namespace al
{


BufferHandle BufferHandle::generate()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALuint name;
  alGenBuffers(1u, &name);
  HOU_AL_CHECK_ERROR();
  return BufferHandle(name);
}



BufferHandle::BufferHandle(BufferHandle&& other)
  : DeviceOwnedObjectHandle(std::move(other))
{}



BufferHandle::~BufferHandle()
{
  if(getName() != 0u)
  {
    HOU_AL_CHECK_CONTEXT_EXISTENCE();
    ALuint name = getName();
    alDeleteBuffers(1u, &name);
    HOU_AL_CHECK_ERROR();
  }
}



BufferHandle::BufferHandle(ALuint name)
  : DeviceOwnedObjectHandle(name)
{}



void setBufferData(const BufferHandle& handle, ALenum format, ALvoid* data,
  ALsizei size, ALsizei freq)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  alBufferData(handle.getName(), format, data, size, freq);
  HOU_AL_CHECK_ERROR();
}



ALint getBufferFrequency(const BufferHandle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.getName(), AL_FREQUENCY, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getBufferBits(const BufferHandle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.getName(), AL_BITS, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getBufferChannels(const BufferHandle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.getName(), AL_CHANNELS, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getBufferSize(const BufferHandle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.getName(), AL_SIZE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}

}  // namespace al

}  // namespace hou
