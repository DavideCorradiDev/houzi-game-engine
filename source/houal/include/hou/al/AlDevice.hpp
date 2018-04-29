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

  const ALCdevice* get_handle() const;
  ALCdevice* get_handle();
  uint32_t get_uid() const;

private:
  ALCdevice* mDevice;
  uint32_t m_uid;
};

}

}

#endif

