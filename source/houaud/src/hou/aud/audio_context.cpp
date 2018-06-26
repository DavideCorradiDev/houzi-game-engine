// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_context.hpp"



namespace hou
{

void audio_context::set_current(audio_context& ctx)
{
  al::context::set_current(ctx.m_al_context);
}



void audio_context::unset_current()
{
  al::context::unset_current();
}



std::vector<std::string> audio_context::get_device_names()
{
  return al::device::get_device_names();
}



audio_context::audio_context()
  : non_copyable()
  , m_al_device()
  , m_al_context(m_al_device)
{}



audio_context::audio_context(const std::string& dev_name)
  : non_copyable()
  , m_al_device(dev_name)
  , m_al_context(m_al_device)
{}



bool audio_context::is_current() const
{
  return m_al_context.is_current();
}



const audio_context::impl_type& audio_context::get_impl() const noexcept
{
  return m_al_context;
}



audio_context::impl_type& audio_context::get_impl() noexcept
{
  return m_al_context;
}



const audio_context::device_type& audio_context::get_device() const noexcept
{
  return m_al_device;
}



audio_context::device_type& audio_context::get_device() noexcept
{
  return m_al_device;
}

}  // namespace hou
