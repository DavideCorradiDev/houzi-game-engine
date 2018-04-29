// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/graphic_context.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/video_mode.hpp"



namespace hou
{

namespace
{

constexpr const char* defaultWindowName = "HouziHiddenWindow";

}  // namespace



void graphic_context::set_current(graphic_context& ph_context)
{
  gl::context::set_current(ph_context.gl_context, ph_context.mDefaultWindow);
  if(!ph_context.m_initialized)
  {
    ph_context.initialize();
  }
}



void graphic_context::unset_current()
{
  gl::context::unset_current();
}



uint graphic_context::get_rendering_color_byte_count()
{
  return 4u;
}



uint graphic_context::get_rendering_depth_byte_count()
{
  return 3u;
}



uint graphic_context::get_rendering_stencil_byte_count()
{
  return 1u;
}



graphic_context::graphic_context()
  : mExtensionInitializer()
  , mDefaultWindow(defaultWindowName,
      video_mode(vec2u::zero(), get_rendering_color_byte_count()),
      window_style::windowed)
  , gl_context(
      gl::context_settings(gl::version(4u, 5u), gl::context_profile::core,
        get_rendering_depth_byte_count(), get_rendering_stencil_byte_count(), 0u),
      mDefaultWindow)
  , m_initialized(false)
{}



graphic_context::graphic_context(graphic_context&& other)
  : mExtensionInitializer()
  , mDefaultWindow(std::move(other.mDefaultWindow))
  , gl_context(std::move(other.gl_context))
  , m_initialized(std::move(other.m_initialized))
{}



bool graphic_context::is_current() const
{
  return gl_context.is_current();
}



void graphic_context::initialize()
{
  m_initialized = true;

  // Set ph_texture pack and unpack alignment to 1 so that there is no padding.
  gl::set_unpack_alignment(1);
  gl::set_pack_alignment(1);

  // Multisampled default framebuffer is never used.
  gl::disable_multisampling();

  // Enable alpha blending.
  gl::enable_blending();
  gl::set_blending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



graphic_context::extension_initializer::extension_initializer()
{
  gl::init_extensions();
}

}  // namespace hou
