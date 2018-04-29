// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_BUFFER_HANDLE_HPP
#define HOU_AL_AL_BUFFER_HANDLE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/al/AlObjectHandle.hpp"



namespace hou
{

namespace al
{

class HOU_AL_API buffer_handle : public DeviceOwnedObjectHandle
{
public:
  static buffer_handle generate();

  buffer_handle(buffer_handle&& other);
  virtual ~buffer_handle();

private:
  buffer_handle(ALuint name);
};

HOU_AL_API void setBufferData(const buffer_handle& handle, ALenum format,
  ALvoid* data, ALsizei size, ALsizei freq);
HOU_AL_API ALint getBufferFrequency(const buffer_handle& handle);
HOU_AL_API ALint getBufferBits(const buffer_handle& handle);
HOU_AL_API ALint getBufferChannels(const buffer_handle& handle);
HOU_AL_API ALint getBufferSize(const buffer_handle& handle);

}  // namespace al

}  // namespace hou

#endif
