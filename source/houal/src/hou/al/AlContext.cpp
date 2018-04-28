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
  HOU_RUNTIME_CHECK(alcMakeContextCurrent(context.mHandle) == AL_TRUE
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
  , mHandle(alcCreateContext(device.getHandle(), nullptr))
  , mUid(generateUid())
  , mDeviceUid(device.getUid())
{
  HOU_RUNTIME_CHECK(mHandle != nullptr, get_text(AlError::ContextCreate));
}



Context::Context(Context&& other)
  : mHandle(std::move(other.mHandle))
  , mUid(std::move(other.mUid))
  , mDeviceUid(std::move(other.mDeviceUid))
{
  other.mHandle = nullptr;
  if(getCurrent() == &other)
  {
    gCurrentContext = this;
  }
}



Context::~Context()
{
  if(mHandle != nullptr)
  {
    if(isCurrent())
    {
      unsetCurrent();
    }
    alcDestroyContext(mHandle);
  }
}



uint32_t Context::getUid() const
{
  return mUid;
}



uint32_t Context::getDeviceUid() const
{
  return mDeviceUid;
}



bool Context::isCurrent() const
{
  // alcGetCurrentContext cannot fail.
  return alcGetCurrentContext() == mHandle;
}

}

}

