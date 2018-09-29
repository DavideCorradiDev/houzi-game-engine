// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/graphic_context.hpp"

#include "hou/gfx/graphics_state.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_texture_handle.hpp"



namespace hou
{

void graphic_context::set_current(graphic_context& ctx, window& wnd)
{
  gl::context::set_current(ctx.m_gl_context, wnd);
  if(!ctx.m_initialized)
  {
    ctx.initialize();
  }
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
  : m_gl_context(gl::context_settings::get_default(),
      window("HouziTempWindow", vec2u(1u, 1u)))
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

  // vsync.
  set_vsync_mode(vsync_mode::enabled);

  // Enable alpha blending.
  set_blending_enabled(true);
  set_source_blending_factor(blending_factor::src_alpha);
  set_destination_blending_factor(blending_factor::one_minus_src_alpha);
}

}  // namespace hou
