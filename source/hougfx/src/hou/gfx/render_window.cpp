// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/render_window.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/texture.hpp"



// Implementation note:
//
// Drawing is never performed on the default framebuffer of the window.
// When performing draw operations, they are performed on an off-screen render
// target. When calling swap_buffers(), the off-screen target is blit onto the
// default backbuffer. Afterwards, the front and back buffer are swapped.
//
// This is done for the following reasons:
//
// - Multisampling behaviour is more consistent. Multisampling on the default
// target depends on driver settings an a lot of other things, multisampling on
// offline targets is more consistent.
//
// - OpenGL has the origin on the lower left corner. In order to have an origin
// on the top left corner, everything has to be mirrored. With the current
// implementation, the mirroring happens during the blit operation, while the
// image on the off-screen target is not mirrored. No mirroring takes place
// until when the rendered image is displayed to the user. IF not doing this,
// each single draw operation would have to be mirrored. Also, blitting would
// not perform correctly as the textures might be flipped multiple times.



namespace hou
{

render_window::render_window(
  const std::string& title, const vec2u& size, uint sample_count)
  : window(title, size)
  , render_surface(size, sample_count)
  , m_vsync_mode(vsync_mode::enabled)
{}




vec2u render_window::get_window_size() const
{
  return window::get_size();
}



vec2u render_window::get_framebuffer_size() const
{
  return render_surface::get_size();
}



render_window::vsync_mode render_window::get_vsync_mode() const
{
  return m_vsync_mode;
}



void render_window::set_vsync_mode(vsync_mode mode)
{
  gl::bind_window(*this);
  set_default_render_target();
  gl::set_vsync_mode(mode);
  m_vsync_mode = mode;
}



void render_window::set_sample_count(uint sample_count)
{
  build_framebuffer(get_framebuffer_size(), sample_count);
}




void render_window::clear(const color& color)
{
  render_surface::clear(color);
  window::clear(color);
}



void render_window::swap_buffers()
{
  gl::bind_window(*this);
  set_current_render_source(*this);
  set_default_render_target();

  vec2u size = get_framebuffer_size();
  gl::blit_framebuffer(0, 0, size.x(), size.y(), 0, size.y(), size.x(), 0,
    GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    GL_NEAREST);

  window::swap_buffers();
}



void render_window::on_size_change(const vec2u& size)
{
  vec2u new_size;
  new_size.x() = size.x() == 0 ? 1u : size.x();
  new_size.y() = size.y() == 0 ? 1u : size.y();
  if(new_size != get_framebuffer_size())
  {
    build_framebuffer(new_size, get_sample_count());
  }
}

}  // namespace hou
