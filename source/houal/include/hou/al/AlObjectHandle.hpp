// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_OBJECT_HANDLE_HPP
#define HOU_AL_AL_OBJECT_HANDLE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/cor/non_copyable.hpp"

#include "hou/al/OpenAl.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

namespace al
{

class HOU_AL_API object_handle
  : public non_copyable
{
public:
  object_handle(ALuint name);
  object_handle(object_handle&& other);
  virtual ~object_handle() = 0;

  ALuint get_name() const;

private:
  ALuint m_name;
};



class HOU_AL_API DeviceOwnedObjectHandle
  : public object_handle
{
public:
  DeviceOwnedObjectHandle(ALuint name);
  DeviceOwnedObjectHandle(DeviceOwnedObjectHandle&& other);
  virtual ~DeviceOwnedObjectHandle() = 0;

  uint32_t getOwningDeviceUid() const;

private:
  uint32_t mOwningDeviceUid;
};



class HOU_AL_API ContextOwnedObjectHandle
  : public object_handle
{
public:
  ContextOwnedObjectHandle(ALuint name);
  ContextOwnedObjectHandle(ContextOwnedObjectHandle&& other);
  virtual ~ContextOwnedObjectHandle() = 0;

  uint32_t get_owning_context_uid() const;

private:
  uint32_t m_owning_context_uid;
};

}

}

#endif

