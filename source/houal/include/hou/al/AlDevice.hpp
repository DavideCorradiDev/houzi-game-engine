// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_DEVICE_HPP
#define HOU_AL_AL_DEVICE_HPP

#include "hou/al/AlExport.hpp"

#include "hou/al/OpenAl.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/non_copyable.hpp"

#include <string>
#include <vector>



namespace hou
{

namespace al
{

class HOU_AL_API Device
  : public non_copyable
{
public:
  static std::vector<std::string> getDeviceNames();

public:
  Device();
  Device(const std::string& deviceName);
  Device(Device&& other);
  ~Device();

  const ALCdevice* getHandle() const;
  ALCdevice* getHandle();
  uint32_t getUid() const;

private:
  ALCdevice* mDevice;
  uint32_t mUid;
};

}

}

#endif

