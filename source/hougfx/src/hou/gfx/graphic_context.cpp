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

constexpr const char* default_window_name = "HouziHiddenWindow";

}  // namespace



void graphic_context::set_current(graphic_context& ctx)
{
  gl::context::set_current(ctx.gl_context, ctx.m_default_window);
  if(!ctx.m_initialized)
  {
    ctx.initialize();
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



// clang-format off
graphic_context::graphic_context()
  : m_extension_initializer()
  , m_default_window(default_window_name,
      video_mode(vec2u::zero(), get_rendering_color_byte_count()),
      window_style::windowed)
  , gl_context(
      gl::context_settings(
        gl::version(4u, 5u),
        gl::context_profile::core,
        get_rendering_depth_byte_count(),
        get_rendering_stencil_byte_count(),
        0u),
      m_default_window)
  , m_initialized(false)
{}
// clang-format on



graphic_context::graphic_context(graphic_context&& other)
  : m_extension_initializer()
  , m_default_window(std::move(other.m_default_window))
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

  // Set texture pack and unpack alignment to 1 so that there is no padding.
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
