// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/graphic_context.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_functions.hpp"



namespace hou
{

namespace
{

constexpr const char* default_window_name = "ContextWindow";

}  // namespace



void graphic_context::set_current(graphic_context& ctx, window& wnd)
{
  gl::context::set_current(ctx.m_gl_context, wnd);
  if(!ctx.m_initialized)
  {
    ctx.initialize();
  }
}



void graphic_context::set_current(graphic_context& ctx)
{
  set_current(ctx, ctx.m_default_window);
}



void graphic_context::set_current(window& wnd)
{
  HOU_PRECOND(gl::context::get_current() != nullptr);
  gl::context::set_current(*gl::context::get_current(), wnd);
}



void graphic_context::unset_current()
{
  gl::context::unset_current();
}



graphic_context::graphic_context()
  : m_default_window(default_window_name, vec2u(1u, 1u))
  , m_gl_context(gl::context_settings::get_default(), m_default_window)
  , m_initialized(false)
{}



bool graphic_context::is_current() const
{
  return m_gl_context.is_current();
}



const graphic_context::impl_type& graphic_context::get_impl() const noexcept
{
  return m_gl_context;
}



graphic_context::impl_type& graphic_context::get_impl() noexcept
{
  return m_gl_context;
}



void graphic_context::initialize()
{
  // Initializes some context variables when binding the context for the first
  // time. These variables should only be set the first time to provide a
  // consistent "clean state" for the context, but should not be set for
  // subsequent bindings to prevent resetting the state of the context.
  m_initialized = true;

  // Set texture pack and unpack alignment to 1 so that there is no padding.
  gl::set_unpack_alignment(1);
  gl::set_pack_alignment(1);

  // Enable alpha blending.
  gl::enable_blending();
  gl::set_blending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}  // namespace hou
