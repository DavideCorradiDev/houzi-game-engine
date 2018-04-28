// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlContext.hpp"

#include "hou/al/AlDevice.hpp"
#include "hou/al/AlError.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/uid_generator.hpp"

#include <mutex>



namespace hou
{

namespace al
{

namespace
{

std::mutex gCurrentContextMutex;
Context* gCurrentContext;

uint32_t generateUid();



uint32_t generateUid()
{
  static uid_generator uidGenerator(1u);
  return uidGenerator.generate();
}

}



void Context::setCurrent(Context& context)
{
  std::lock_guard<std::mutex> lock(gCurrentContextMutex);
  HOU_RUNTIME_CHECK(alcMakeContextCurrent(context.m_handle) == AL_TRUE
    , get_text(AlError::ContextMakeCurrent));
  gCurrentContext = &context;
}



void Context::unsetCurrent()
{
  std::lock_guard<std::mutex> lock(gCurrentContextMutex);
  HOU_RUNTIME_CHECK(alcMakeContextCurrent(nullptr) == AL_TRUE
    , get_text(AlError::ContextMakeCurrent));
  gCurrentContext = nullptr;
}



Context* Context::getCurrent()
{
  Context* retval = nullptr;
  {
    std::lock_guard<std::mutex> lock(gCurrentContextMutex);
    retval = gCurrentContext;
  }
  return retval;
}



Context::Context(Device& device)
  : non_copyable()
  , m_handle(alcCreateContext(device.getHandle(), nullptr))
  , m_uid(generateUid())
  , mDeviceUid(device.get_uid())
{
  HOU_RUNTIME_CHECK(m_handle != nullptr, get_text(AlError::ContextCreate));
}



Context::Context(Context&& other)
  : m_handle(std::move(other.m_handle))
  , m_uid(std::move(other.m_uid))
  , mDeviceUid(std::move(other.mDeviceUid))
{
  other.m_handle = nullptr;
  if(getCurrent() == &other)
  {
    gCurrentContext = this;
  }
}



Context::~Context()
{
  if(m_handle != nullptr)
  {
    if(isCurrent())
    {
      unsetCurrent();
    }
    alcDestroyContext(m_handle);
  }
}



uint32_t Context::get_uid() const
{
  return m_uid;
}



uint32_t Context::getDeviceUid() const
{
  return mDeviceUid;
}



bool Context::isCurrent() const
{
  // alcGetCurrentContext cannot fail.
  return alcGetCurrentContext() == m_handle;
}

}

}

