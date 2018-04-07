// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/al/AlObjectHandle.hpp"

#include "hou/al/AlCheck.hpp"
#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"

#include <utility>



namespace hou
{

namespace al
{

ObjectHandle::ObjectHandle(ALuint name)
  : NonCopyable()
  , mName(name)
{}



ObjectHandle::ObjectHandle(ObjectHandle&& other)
  : mName(std::move(other.mName))
{
  other.mName = 0u;
}



ObjectHandle::~ObjectHandle()
{}



ALuint ObjectHandle::getName() const
{
  return mName;
}



DeviceOwnedObjectHandle::DeviceOwnedObjectHandle(ALuint name)
  : ObjectHandle(name)
  , mOwningDeviceUid(0u)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  mOwningDeviceUid = al::Context::getCurrent()->getDeviceUid();
}



DeviceOwnedObjectHandle::DeviceOwnedObjectHandle
  (DeviceOwnedObjectHandle&& other)
  : ObjectHandle(std::move(other))
  , mOwningDeviceUid(std::move(other.mOwningDeviceUid))
{}



DeviceOwnedObjectHandle::~DeviceOwnedObjectHandle()
{}



uint32_t DeviceOwnedObjectHandle::getOwningDeviceUid() const
{
  return mOwningDeviceUid;
}



ContextOwnedObjectHandle::ContextOwnedObjectHandle(ALuint name)
  : ObjectHandle(name)
  , mOwningContextUid(0u)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  mOwningContextUid = al::Context::getCurrent()->getUid();
}



ContextOwnedObjectHandle::ContextOwnedObjectHandle
  (ContextOwnedObjectHandle&& other)
  : ObjectHandle(std::move(other))
  , mOwningContextUid(std::move(other.mOwningContextUid))
{}



ContextOwnedObjectHandle::~ContextOwnedObjectHandle()
{}



uint32_t ContextOwnedObjectHandle::getOwningContextUid() const
{
  return mOwningContextUid;
}

}

}

