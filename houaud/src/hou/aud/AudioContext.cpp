// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/aud/AudioContext.hpp"



namespace hou
{

void AudioContext::setCurrent(AudioContext& context)
{
  al::Context::setCurrent(context.mAlContext);
}



std::vector<std::string> AudioContext::getDeviceNames()
{
  return al::Device::getDeviceNames();
}



AudioContext::AudioContext()
  : NonCopyable()
  , mAlDevice()
  , mAlContext(mAlDevice)
{
  initialize();
}



AudioContext::AudioContext(const std::string& deviceName)
  : NonCopyable()
  , mAlDevice(deviceName)
  , mAlContext(mAlDevice)
{
  initialize();
}



AudioContext::AudioContext(AudioContext&& other)
  : mAlDevice(std::move(other.mAlDevice))
  , mAlContext(std::move(other.mAlContext))
{}



bool AudioContext::isCurrent() const
{
  return mAlContext.isCurrent();
}



void AudioContext::initialize()
{
  alGetError();
  setCurrent(*this);
}

}

