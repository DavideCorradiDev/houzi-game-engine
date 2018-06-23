// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/render_surface.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

void render_surface::set_current_render_source(const render_surface& rs)
{
  framebuffer::bind_read_target(rs.m_framebuffer);
}



void render_surface::set_default_render_source()
{
  framebuffer::unbind_read_target();
}



void render_surface::set_current_render_target(const render_surface& rs)
{
  gl::set_viewport(
    rs.m_viewport.x(), rs.m_viewport.y(), rs.m_viewport.w(), rs.m_viewport.h());
  framebuffer::bind_draw_target(rs.m_framebuffer);
}



void render_surface::set_default_render_target()
{
  framebuffer::unbind_draw_target();
}



vec2u render_surface::get_max_size()
{
  return attachment_type::get_max_size();
}



positive<uint> render_surface::get_max_sample_count()
{
  return multisample_attachment_type::get_max_sample_count();
}



render_surface::render_surface(const vec2u& size, positive<uint> sample_count)
  : non_copyable()
  , m_framebuffer()
  , m_color_attachment(nullptr)
  , m_depth_stencil_attachment(nullptr)
  , m_sample_count(sample_count)
  , m_viewport(recti(0, 0, size.x(), size.y()))
{
  build_framebuffer(size, sample_count);
}



recti render_surface::get_default_viewport() const
{
  return recti(vec2i(0, 0), get_size());
}



const recti& render_surface::get_viewport() const noexcept
{
  return m_viewport;
}



void render_surface::set_viewport(const recti& viewport)
{
  m_viewport = viewport;
}



vec2u render_surface::get_size() const
{
  HOU_DEV_ASSERT(m_color_attachment != nullptr);
  return m_color_attachment->get_size2();
}



bool render_surface::is_multisampled() const noexcept
{
  return m_sample_count > 1u;
}



positive<uint> render_surface::get_sample_count() const noexcept
{
  return m_sample_count;
}



void render_surface::clear(const color& color)
{
  set_current_render_target(*this);

  gl::set_clear_color(color.get_red_f(), color.get_green_f(),
    color.get_blue_f(), color.get_alpha_f());
  gl::set_clear_depth(1.f);
  gl::set_clear_stencil(0u);
  gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}



texture2 render_surface::to_texture() const
{
  texture2 tex(get_size());
  recti blitRect(vec2i::zero(), narrow_cast<vec2i>(get_size()));
  blit(
    m_framebuffer, blitRect, tex, blitRect, framebuffer_blit_filter::nearest);
  return tex;
}



bool render_surface::is_current_render_source() const
{
  return m_framebuffer.is_bound_to_read_target();
}



bool render_surface::is_current_render_target() const
{
  return m_framebuffer.is_bound_to_draw_target();
}



void render_surface::build_framebuffer(
  const vec2u& size, positive<uint> sample_count)
{
  m_sample_count = sample_count;
  if(sample_count <= 1)
  {
    static constexpr uint mipmap_level_count = 1u;
    m_color_attachment = std::make_unique<texture2>(
      size, texture_format::rgba, mipmap_level_count);
    m_depth_stencil_attachment = std::make_unique<texture2>(
      size, texture_format::depth_stencil, mipmap_level_count);
  }
  else
  {
    static constexpr bool fixed_sample_locations = true;
    m_color_attachment = std::make_unique<multisample_texture2>(
      size, texture_format::rgba, sample_count, fixed_sample_locations);
    m_depth_stencil_attachment = std::make_unique<multisample_texture2>(size,
      texture_format::depth_stencil, sample_count, fixed_sample_locations);
  }
  HOU_DEV_ASSERT(m_color_attachment != nullptr);
  HOU_DEV_ASSERT(m_depth_stencil_attachment != nullptr);

  static constexpr uint attachment_point = 0u;
  static constexpr uint mipmap_level = 0u;
  m_framebuffer.set_color_attachment(
    attachment_point, *m_color_attachment, mipmap_level);
  m_framebuffer.set_depth_stencil_attachment(
    *m_depth_stencil_attachment, mipmap_level);

  HOU_DEV_ASSERT(m_framebuffer.is_complete());
}



void blit(const render_surface& src, const recti& src_rect, render_surface& dst,
  const recti& dst_rect, framebuffer_blit_filter filter)
{
  blit(src.m_framebuffer, src_rect, dst.m_framebuffer, dst_rect,
    framebuffer_blit_mask::all, filter);
}



void blit(const render_surface& src, const recti& src_rect, texture& dst,
  const recti& dst_rect, framebuffer_blit_filter filter)
{
  blit(src.m_framebuffer, src_rect, dst, dst_rect, filter);
}



void blit(const texture& src, const recti& src_rect, render_surface& dst,
  const recti& dst_rect, framebuffer_blit_filter filter)
{
  blit(src, src_rect, dst.m_framebuffer, dst_rect, filter);
}

}  // namespace hou
