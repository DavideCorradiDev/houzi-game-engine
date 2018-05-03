// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_context.hpp"

#include "hou/al/al_device.hpp"
#include "hou/al/al_error.hpp"

#include "hou/cor/deprecated_error.hpp"
#include "hou/cor/uid_generator.hpp"

#include <mutex>



namespace hou
{

namespace al
{

namespace
{

std::mutex g_current_context_mutex;
context* g_current_context;

uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}

}



void context::set_current(context& ctx)
{
  std::lock_guard<std::mutex> lock(g_current_context_mutex);
  DEPRECATED_HOU_RUNTIME_CHECK(alcMakeContextCurrent(ctx.m_handle) == AL_TRUE
    , get_text(al_error::context_make_current));
  g_current_context = &ctx;
}



void context::unset_current()
{
  std::lock_guard<std::mutex> lock(g_current_context_mutex);
  DEPRECATED_HOU_RUNTIME_CHECK(alcMakeContextCurrent(nullptr) == AL_TRUE
    , get_text(al_error::context_make_current));
  g_current_context = nullptr;
}



context* context::get_current()
{
  context* retval = nullptr;
  {
    std::lock_guard<std::mutex> lock(g_current_context_mutex);
    retval = g_current_context;
  }
  return retval;
}



context::context(device& dev)
  : non_copyable()
  , m_handle(alcCreateContext(dev.get_handle(), nullptr))
  , m_uid(generate_uid())
  , m_device_uid(dev.get_uid())
{
  DEPRECATED_HOU_RUNTIME_CHECK(m_handle != nullptr, get_text(al_error::context_create));
}



context::context(context&& other)
  : m_handle(std::move(other.m_handle))
  , m_uid(std::move(other.m_uid))
  , m_device_uid(std::move(other.m_device_uid))
{
  other.m_handle = nullptr;
  if(get_current() == &other)
  {
    g_current_context = this;
  }
}



context::~context()
{
  if(m_handle != nullptr)
  {
    if(is_current())
    {
      unset_current();
    }
    alcDestroyContext(m_handle);
  }
}



uint32_t context::get_uid() const
{
  return m_uid;
}



uint32_t context::get_device_uid() const
{
  return m_device_uid;
}



bool context::is_current() const
{
  // alcGetCurrentContext cannot fail.
  return alcGetCurrentContext() == m_handle;
}

}

}

