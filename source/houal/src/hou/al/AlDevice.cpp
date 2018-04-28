// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlDevice.hpp"

#include "hou/al/AlCheck.hpp"
#include "hou/al/AlError.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/StdString.hpp"
#include "hou/cor/UidGenerator.hpp"

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
  static UidGenerator uidGenerator(1u);
  return uidGenerator.generate();
}

}



std::vector<std::string> Device::getDeviceNames()
{
  std::vector<std::string> deviceNames;
  if(alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT"))
  {
    std::string deviceNamesStr(alcGetString(nullptr, ALC_DEVICE_SPECIFIER));
    splitString(deviceNamesStr, ',', std::back_inserter(deviceNames));
  }
  return deviceNames;
}



Device::Device()
  : NonCopyable()
  , mDevice(alcOpenDevice(nullptr))
  , mUid(generateUid())
{
  HOU_RUNTIME_CHECK(mDevice != nullptr, getText(AlError::DeviceOpen)
    , u8"Default Device");
}



Device::Device(const std::string& deviceName)
  : NonCopyable()
  , mDevice(alcOpenDevice(deviceName.c_str()))
  , mUid(generateUid())
{
  HOU_RUNTIME_CHECK(mDevice != nullptr, getText(AlError::DeviceOpen)
    , deviceName.c_str());
}



Device::Device(Device&& other)
  : mDevice(std::move(other.mDevice))
  , mUid(std::move(other.mUid))
{
  other.mDevice = nullptr;
}



Device::~Device()
{
  if(mDevice != nullptr)
  {
    HOU_FATAL_CHECK(alcCloseDevice(mDevice) == AL_TRUE
      , getText(AlError::DeviceClose));
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



uint32_t Device::getUid() const
{
  return mUid;
}

}

}

