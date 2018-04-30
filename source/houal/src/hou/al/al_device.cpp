// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_device.hpp"

#include "hou/al/al_check.hpp"
#include "hou/al/al_error.hpp"

#include "hou/cor/error.hpp"
#include "hou/cor/std_string.hpp"
#include "hou/cor/uid_generator.hpp"

#include <AL/al.h>



namespace hou
{

namespace al
{

namespace
{

uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}

}



std::vector<std::string> device::get_device_names()
{
  std::vector<std::string> deviceNames;
  if(alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
  {
    std::string deviceNamesStr(alcGetString(nullptr, ALC_DEVICE_SPECIFIER));
    split_string(deviceNamesStr, ',', std::back_inserter(deviceNames));
  }
  return deviceNames;
}



device::device()
  : non_copyable()
  , m_device(alcOpenDevice(nullptr))
  , m_uid(generate_uid())
{
  HOU_RUNTIME_CHECK(m_device != nullptr, get_text(al_error::device_open)
    , u8"default device");
}



device::device(const std::string& deviceName)
  : non_copyable()
  , m_device(alcOpenDevice(deviceName.c_str()))
  , m_uid(generate_uid())
{
  HOU_RUNTIME_CHECK(m_device != nullptr, get_text(al_error::device_open)
    , deviceName.c_str());
}



device::device(device&& other)
  : m_device(std::move(other.m_device))
  , m_uid(std::move(other.m_uid))
{
  other.m_device = nullptr;
}



device::~device()
{
  if(m_device != nullptr)
  {
    HOU_FATAL_CHECK(alcCloseDevice(m_device) == AL_TRUE
      , get_text(al_error::device_close));
  }
}



const ALCdevice* device::get_handle() const
{
  return m_device;
}



ALCdevice* device::get_handle()
{
  return m_device;
}



uint32_t device::get_uid() const
{
  return m_uid;
}

}

}

