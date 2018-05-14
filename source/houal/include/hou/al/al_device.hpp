// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_DEVICE_HPP
#define HOU_AL_AL_DEVICE_HPP

#include "hou/al/open_al.hpp"

#include "hou/al/al_export.hpp"

#include "hou/cor/non_copyable.hpp"

#include <string>
#include <vector>



namespace hou
{

namespace al
{

class HOU_AL_API device : public non_copyable
{
public:
  static std::vector<std::string> get_device_names();

public:
  device();
  device(const std::string& dev_name);
  device(device&& other) noexcept;
  ~device();

  const ALCdevice* get_handle() const noexcept;
  ALCdevice* get_handle() noexcept;
  uint32_t get_uid() const noexcept;

private:
  ALCdevice* m_device;
  uint32_t m_uid;
};

}  // namespace al

}  // namespace hou

#endif
