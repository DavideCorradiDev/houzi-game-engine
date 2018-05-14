// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_BUFFER_HANDLE_HPP
#define HOU_AL_AL_BUFFER_HANDLE_HPP

#include "hou/al/al_object_handle.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace al
{

class HOU_AL_API buffer_handle : public device_owned_object_handle
{
public:
  static buffer_handle generate();

  buffer_handle(buffer_handle&& other) noexcept = default;
  virtual ~buffer_handle();

private:
  buffer_handle(ALuint name);
};

HOU_AL_API void set_buffer_data(const buffer_handle& handle, ALenum format,
  ALvoid* data, ALsizei size, ALsizei freq);
HOU_AL_API ALint get_buffer_frequency(const buffer_handle& handle);
HOU_AL_API ALint get_buffer_bits(const buffer_handle& handle);
HOU_AL_API ALint get_buffer_channels(const buffer_handle& handle);
HOU_AL_API ALint get_buffer_size(const buffer_handle& handle);

}  // namespace al

}  // namespace hou

#endif
