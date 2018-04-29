// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlDevice.hpp"

#include "hou/al/AlCheck.hpp"
#include "hou/al/AlError.hpp"

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

uint32_t generateUid();



uint32_t generateUid()
{
  static uid_generator uidGenerator(1u);
  return uidGenerator.generate();
}

}



std::vector<std::string> Device::getDeviceNames()
{
  std::vector<std::string> deviceNames;
  if(alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
  {
    std::string deviceNamesStr(alcGetString(nullptr, ALC_DEVICE_SPECIFIER));
    split_string(deviceNamesStr, ',', std::back_inserter(deviceNames));
  }
  return deviceNames;
}



Device::Device()
  : non_copyable()
  , mDevice(alcOpenDevice(nullptr))
  , m_uid(generateUid())
{
  HOU_RUNTIME_CHECK(mDevice != nullptr, get_text(AlError::DeviceOpen)
    , u8"default Device");
}



Device::Device(const std::string& deviceName)
  : non_copyable()
  , mDevice(alcOpenDevice(deviceName.c_str()))
  , m_uid(generateUid())
{
  HOU_RUNTIME_CHECK(mDevice != nullptr, get_text(AlError::DeviceOpen)
    , deviceName.c_str());
}



Device::Device(Device&& other)
  : mDevice(std::move(other.mDevice))
  , m_uid(std::move(other.m_uid))
{
  other.mDevice = nullptr;
}



Device::~Device()
{
  if(mDevice != nullptr)
  {
    HOU_FATAL_CHECK(alcCloseDevice(mDevice) == AL_TRUE
      , get_text(AlError::DeviceClose));
  }
}



const ALCdevice* Device::getHandle() const
{
  return mDevice;
}



ALCdevice* Device::getHandle()
{
  return mDevice;
}



uint32_t Device::get_uid() const
{
  return m_uid;
}

}

}

