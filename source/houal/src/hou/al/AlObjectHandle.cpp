// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlObjectHandle.hpp"

#include "hou/al/AlCheck.hpp"
#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"

#include <utility>



namespace hou
{

namespace al
{

object_handle::object_handle(ALuint name)
  : non_copyable()
  , m_name(name)
{}



object_handle::object_handle(object_handle&& other)
  : m_name(std::move(other.m_name))
{
  other.m_name = 0u;
}



object_handle::~object_handle()
{}



ALuint object_handle::get_name() const
{
  return m_name;
}



DeviceOwnedObjectHandle::DeviceOwnedObjectHandle(ALuint name)
  : object_handle(name)
  , mOwningDeviceUid(0u)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  mOwningDeviceUid = al::context::getCurrent()->getDeviceUid();
}



DeviceOwnedObjectHandle::DeviceOwnedObjectHandle
  (DeviceOwnedObjectHandle&& other)
  : object_handle(std::move(other))
  , mOwningDeviceUid(std::move(other.mOwningDeviceUid))
{}



DeviceOwnedObjectHandle::~DeviceOwnedObjectHandle()
{}



uint32_t DeviceOwnedObjectHandle::getOwningDeviceUid() const
{
  return mOwningDeviceUid;
}



ContextOwnedObjectHandle::ContextOwnedObjectHandle(ALuint name)
  : object_handle(name)
  , m_owning_context_uid(0u)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  m_owning_context_uid = al::context::getCurrent()->get_uid();
}



ContextOwnedObjectHandle::ContextOwnedObjectHandle
  (ContextOwnedObjectHandle&& other)
  : object_handle(std::move(other))
  , m_owning_context_uid(std::move(other.m_owning_context_uid))
{}



ContextOwnedObjectHandle::~ContextOwnedObjectHandle()
{}



uint32_t ContextOwnedObjectHandle::get_owning_context_uid() const
{
  return m_owning_context_uid;
}

}

}

