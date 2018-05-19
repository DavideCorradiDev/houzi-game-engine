// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_OBJECT_HANDLE_HPP
#define HOU_AL_AL_OBJECT_HANDLE_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"



namespace hou
{

namespace al
{

class HOU_AL_API object_handle : public non_copyable
{
public:
  object_handle(ALuint name) noexcept;
  object_handle(object_handle&& other) noexcept;
  virtual ~object_handle() = 0;

  ALuint get_name() const noexcept;

private:
  ALuint m_name;
};



class HOU_AL_API device_owned_object_handle : public object_handle
{
public:
  device_owned_object_handle(ALuint name);
  device_owned_object_handle(device_owned_object_handle&& other) noexcept
    = default;
  virtual ~device_owned_object_handle() = 0;

  uint32_t get_owning_device_uid() const noexcept;

private:
  uint32_t m_owning_device_uid;
};



class HOU_AL_API context_owned_object_handle : public object_handle
{
public:
  context_owned_object_handle(ALuint name);
  context_owned_object_handle(context_owned_object_handle&& other) noexcept
    = default;
  virtual ~context_owned_object_handle() = 0;

  uint32_t get_owning_context_uid() const noexcept;

private:
  uint32_t m_owning_context_uid;
};

}  // namespace al

}  // namespace hou

#endif
