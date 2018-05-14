// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_CONTEXT_HPP
#define HOU_AL_AL_CONTEXT_HPP

#include "hou/al/open_al.hpp"

#include "hou/al/al_config.hpp"

#include "hou/cor/non_copyable.hpp"



namespace hou
{

namespace al
{

class device;

class HOU_AL_API context : public non_copyable
{
public:
  static void set_current(context& ctx);
  static void unset_current();
  static context* get_current();

public:
  context(device& dev);
  context(context&& other) noexcept;
  ~context();

  uint32_t get_uid() const noexcept;
  uint32_t get_device_uid() const noexcept;

  bool is_current() const;

private:
  ALCcontext* m_handle;
  uint32_t m_uid;
  uint32_t m_device_uid;
};

}  // namespace al

}  // namespace hou

#endif
