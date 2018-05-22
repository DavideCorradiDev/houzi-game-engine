// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_context.hpp"



namespace hou
{

void audio_context::set_current(audio_context& ctx)
{
  al::context::set_current(ctx.m_al_context);
  if(!ctx.m_initialized)
  {
    ctx.initialize();
  }
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
  , m_initialized(false)
{}



audio_context::audio_context(const std::string& dev_name)
  : non_copyable()
  , m_al_device(dev_name)
  , m_al_context(m_al_device)
  , m_initialized(false)
{}



bool audio_context::is_current() const
{
  return m_al_context.is_current();
}



void audio_context::initialize()
{
  m_initialized = true;
  alGetError();
}

}  // namespace hou
