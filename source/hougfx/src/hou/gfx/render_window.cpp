// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/render_window.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/sys/video_mode.hpp"



// Implementation note:
//
// Drawing is never performed on the default framebuffer of the window.
// When performing draw operations, they are performed on an off-screen render
// target. When calling display(), the off-screen target is blit onto the
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

render_window::render_window(const std::string& title, const vec2u& size,
  window_style style, uint sample_count)
  : window(title,
      video_mode(size, graphic_context::get_rendering_color_byte_count()),
      style)
  , render_surface(size, sample_count)
{}



render_window::render_window(render_window&& other)
  : window(std::move(other))
  , render_surface(std::move(other))
{}



render_window::~render_window()
{}



void render_window::display()
{
  gl::bind_window(*this);
  set_current_render_source(*this);
  set_default_render_target();

  vec2u size = get_size();
  gl::blit_framebuffer(0, 0, size.x(), size.y(), 0, size.y(), size.x(), 0,
    GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
    GL_NEAREST);

  swap_buffers();
}



void render_window::set_vertical_sync_mode(vertical_sync_mode mode)
{
  gl::bind_window(*this);
  set_default_render_target();
  gl::set_vertical_sync_mode(gl::vertical_sync_mode(static_cast<int>(mode)));
}



void render_window::set_sample_count(uint sample_count)
{
  build_framebuffer(get_size(), sample_count);
}



void render_window::set_frame_rect(const vec2i& pos, const vec2u& size)
{
  window::set_frame_rect(pos, size);
  rebuild_framebuffer_if_necessary();
}



void render_window::set_client_rect(const vec2i& pos, const vec2u& size)
{
  window::set_client_rect(pos, size);
  rebuild_framebuffer_if_necessary();
}



void render_window::rebuild_framebuffer_if_necessary()
{
  vec2u new_size = get_client_size();
  if(new_size.x() == 0u)
  {
    new_size.x() = 1u;
  }
  if(new_size.y() == 0u)
  {
    new_size.y() = 1u;
  }
  if(get_size() != new_size)
  {
    build_framebuffer(new_size, get_sample_count());
  }
}

}  // namespace hou
