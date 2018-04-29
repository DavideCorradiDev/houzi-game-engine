// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlBufferHandle.hpp"

#include "hou/al/AlCheck.hpp"



namespace hou
{

namespace al
{


buffer_handle buffer_handle::generate()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALuint name;
  alGenBuffers(1u, &name);
  HOU_AL_CHECK_ERROR();
  return buffer_handle(name);
}



buffer_handle::buffer_handle(buffer_handle&& other)
  : DeviceOwnedObjectHandle(std::move(other))
{}



buffer_handle::~buffer_handle()
{
  if(get_name() != 0u)
  {
    HOU_AL_CHECK_CONTEXT_EXISTENCE();
    HOU_AL_CHECK_CONTEXT_OWNERSHIP(*this);
    ALuint name = get_name();
    alDeleteBuffers(1u, &name);
    HOU_AL_CHECK_ERROR();
  }
}



buffer_handle::buffer_handle(ALuint name)
  : DeviceOwnedObjectHandle(name)
{}



void setBufferData(const buffer_handle& handle, ALenum format, ALvoid* data,
  ALsizei size, ALsizei freq)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  alBufferData(handle.get_name(), format, data, size, freq);
  HOU_AL_CHECK_ERROR();
}



ALint getBufferFrequency(const buffer_handle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.get_name(), AL_FREQUENCY, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getBufferBits(const buffer_handle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.get_name(), AL_BITS, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getBufferChannels(const buffer_handle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.get_name(), AL_CHANNELS, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint getBufferSize(const buffer_handle& handle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(handle);
  ALint value;
  alGetBufferi(handle.get_name(), AL_SIZE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}

}  // namespace al

}  // namespace hou
