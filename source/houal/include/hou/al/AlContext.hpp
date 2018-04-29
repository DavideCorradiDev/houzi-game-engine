// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_CONTEXT_HPP
#define HOU_AL_AL_CONTEXT_HPP

#include "hou/al/al_export.hpp"

#include "hou/al/open_al.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/non_copyable.hpp"



namespace hou
{

namespace al
{

class device;

class HOU_AL_API context
  : public non_copyable
{
public:
  static void set_current(context& ph_context);
  static void unset_current();
  static context* getCurrent();

public:
  context(device& ph_device);
  context(context&& other);
  ~context();

  uint32_t get_uid() const;
  uint32_t get_device_uid() const;

  bool is_current() const;

private:
  ALCcontext* m_handle;
  uint32_t m_uid;
  uint32_t m_device_uid;
};

}

}

#endif

