// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_context.hpp"

#include "hou/al/al_device.hpp"
#include "hou/al/al_exceptions.hpp"

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

}  // namespace



void context::set_current(context& ctx)
{
  std::lock_guard<std::mutex> lock(g_current_context_mutex);
  HOU_CHECK_0(
    alcMakeContextCurrent(ctx.m_handle) == AL_TRUE, context_switch_error);
  g_current_context = &ctx;
}



void context::unset_current()
{
  std::lock_guard<std::mutex> lock(g_current_context_mutex);
  HOU_CHECK_0(alcMakeContextCurrent(nullptr) == AL_TRUE, context_switch_error);
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
  HOU_CHECK_0(m_handle != nullptr, context_creation_error);
}



context::context(context&& other) noexcept
  : non_copyable()
  , m_handle(std::move(other.m_handle))
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



uint32_t context::get_uid() const noexcept
{
  return m_uid;
}



uint32_t context::get_device_uid() const noexcept
{
  return m_device_uid;
}



bool context::is_current() const
{
  // alcGetCurrentContext cannot fail.
  return alcGetCurrentContext() == m_handle;
}

}  // namespace al

}  // namespace hou
