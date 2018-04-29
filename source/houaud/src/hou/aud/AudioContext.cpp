// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioContext.hpp"



namespace hou
{

void AudioContext::set_current(AudioContext& ph_context)
{
  al::context::set_current(ph_context.mAlContext);
}



void AudioContext::unset_current()
{
  al::context::unset_current();
}



std::vector<std::string> AudioContext::getDeviceNames()
{
  return al::Device::getDeviceNames();
}



AudioContext::AudioContext()
  : non_copyable()
  , mAlDevice()
  , mAlContext(mAlDevice)
{
  alGetError();
}



AudioContext::AudioContext(const std::string& deviceName)
  : non_copyable()
  , mAlDevice(deviceName)
  , mAlContext(mAlDevice)
{
  alGetError();
}



AudioContext::AudioContext(AudioContext&& other)
  : mAlDevice(std::move(other.mAlDevice))
  , mAlContext(std::move(other.mAlContext))
{}



bool AudioContext::is_current() const
{
  return mAlContext.is_current();
}

}

