// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_device.hpp"

#include "hou/al/al_context_exceptions.hpp"

#include "hou/cor/assertions.hpp"
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

}  // namespace



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
  HOU_CHECK_N(m_device != nullptr, device_open_error, u8"default device");
}



device::device(const std::string& dev_name)
  : non_copyable()
  , m_device(alcOpenDevice(dev_name.c_str()))
  , m_uid(generate_uid())
{
  HOU_CHECK_N(m_device != nullptr, device_open_error, dev_name);
}



device::device(device&& other) noexcept
  : m_device(std::move(other.m_device))
  , m_uid(std::move(other.m_uid))
{
  other.m_device = nullptr;
  other.m_uid = 0u;
}



device::~device()
{
  if(m_device != nullptr)
  {
    HOU_CHECK_0(alcCloseDevice(m_device) == AL_TRUE, device_close_error);
  }
}



const device::impl_type* device::get_impl() const
{
  return m_device;
}



device::impl_type* device::get_impl()
{
  return m_device;
}



device::uid_type device::get_uid() const noexcept
{
  return m_uid;
}

}  // namespace al

}  // namespace hou
