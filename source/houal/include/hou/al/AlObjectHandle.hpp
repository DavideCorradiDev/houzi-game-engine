// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_OBJECT_HANDLE_HPP
#define HOU_AL_AL_OBJECT_HANDLE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/cor/NonCopyable.hpp"

#include "hou/al/OpenAl.hpp"

#include "hou/cor/BasicTypes.hpp"



namespace hou
{

namespace al
{

class HOU_AL_API ObjectHandle
  : public NonCopyable
{
public:
  ObjectHandle(ALuint name);
  ObjectHandle(ObjectHandle&& other);
  virtual ~ObjectHandle() = 0;

  ALuint getName() const;

private:
  ALuint mName;
};



class HOU_AL_API DeviceOwnedObjectHandle
  : public ObjectHandle
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
  : public ObjectHandle
{
public:
  ContextOwnedObjectHandle(ALuint name);
  ContextOwnedObjectHandle(ContextOwnedObjectHandle&& other);
  virtual ~ContextOwnedObjectHandle() = 0;

  uint32_t getOwningContextUid() const;

private:
  uint32_t mOwningContextUid;
};

}

}

#endif

