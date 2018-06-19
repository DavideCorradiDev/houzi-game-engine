// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_object_handle.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_exceptions.hpp"

#include <utility>



namespace hou
{

namespace al
{

object_handle::object_handle(ALuint name) noexcept
  : non_copyable()
  , m_name(name)
{}



object_handle::object_handle(object_handle&& other) noexcept
  : m_name(std::move(other.m_name))
{
  other.m_name = 0u;
}



object_handle::~object_handle()
{}



ALuint object_handle::get_name() const noexcept
{
  return m_name;
}



device_owned_object_handle::device_owned_object_handle(ALuint name)
  : object_handle(name)
  , m_owning_device_uid(0u)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  m_owning_device_uid = al::context::get_current()->get_device_uid();
}



uint32_t device_owned_object_handle::get_owning_device_uid() const noexcept
{
  return m_owning_device_uid;
}



context_owned_object_handle::context_owned_object_handle(ALuint name)
  : object_handle(name)
  , m_owning_context_uid(0u)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  m_owning_context_uid = al::context::get_current()->get_uid();
}



uint32_t context_owned_object_handle::get_owning_context_uid() const noexcept
{
  return m_owning_context_uid;
}

}  // namespace al

}  // namespace hou
