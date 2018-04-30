// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/render_surface.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/texture.hpp"

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



uint render_surface::get_max_sample_count()
{
  return multisample_attachment_type::get_max_sample_count();
}



render_surface::render_surface(const vec2u& size, uint sampleCount)
  : non_copyable()
  , m_framebuffer()
  , m_color_attachment(nullptr)
  , m_depth_stencil_attachment(nullptr)
  , m_sample_count(sampleCount)
  , m_viewport(recti(0, 0, size.x(), size.y()))
{
  build_framebuffer(size, sampleCount);
}



render_surface::render_surface(render_surface&& other)
  : non_copyable()
  , m_framebuffer(std::move(other.m_framebuffer))
  , m_color_attachment(std::move(other.m_color_attachment))
  , m_depth_stencil_attachment(std::move(other.m_depth_stencil_attachment))
  , m_sample_count(std::move(other.m_sample_count))
  , m_viewport(std::move(other.m_viewport))
{}



render_surface::~render_surface()
{}



recti render_surface::get_default_viewport() const
{
  return recti(vec2i(0, 0), get_size());
}



const recti& render_surface::get_viewport() const
{
  return m_viewport;
}



void render_surface::set_viewport(const recti& viewport)
{
  m_viewport = viewport;
}



vec2u render_surface::get_size() const
{
  HOU_EXPECT_DEV(m_color_attachment != nullptr);
  return m_color_attachment->get_size2();
}



bool render_surface::is_multisampled() const
{
  return m_sample_count > 1u;
}



uint render_surface::get_sample_count() const
{
  return m_sample_count;
}



void render_surface::clear(const color& color)
{
  set_current_render_target(*this);

  gl::set_clear_color(
    color.get_red_f(), color.get_green_f(), color.get_blue_f(), color.get_alpha_f());
  gl::set_clear_depth(1.f);
  gl::set_clear_stencil(0u);
  gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}



texture2 render_surface::to_texture() const
{
  texture2 tex(get_size());
  recti blitRect(vec2i::zero(), static_cast<vec2i>(get_size()));
  blit(m_framebuffer, blitRect, tex, blitRect, framebuffer_blit_filter::nearest);
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



void render_surface::build_framebuffer(const vec2u& size, uint sampleCount)
{
  HOU_ENSURE_DEV(graphic_context::get_rendering_color_byte_count() == 4u);
  HOU_ENSURE_DEV(graphic_context::get_rendering_depth_byte_count() == 3u);
  HOU_ENSURE_DEV(graphic_context::get_rendering_stencil_byte_count() == 1u);
  HOU_EXPECT(sampleCount > 0u);

  m_sample_count = sampleCount;
  if(sampleCount <= 1)
  {
    static constexpr uint mipMapLevelCount = 1u;
    m_color_attachment
      = std::make_unique<texture2>(size, texture_format::rgba, mipMapLevelCount);
    m_depth_stencil_attachment = std::make_unique<texture2>(
      size, texture_format::depth_stencil, mipMapLevelCount);
  }
  else
  {
    static constexpr bool fixedSampleLocations = true;
    m_color_attachment = std::make_unique<multisample_texture2>(
      size, texture_format::rgba, sampleCount, fixedSampleLocations);
    m_depth_stencil_attachment = std::make_unique<multisample_texture2>(
      size, texture_format::depth_stencil, sampleCount, fixedSampleLocations);
  }
  HOU_ENSURE_DEV(m_color_attachment != nullptr);
  HOU_ENSURE_DEV(m_depth_stencil_attachment != nullptr);

  static constexpr uint attachmentPoint = 0u;
  static constexpr uint mipMapLevel = 0u;
  m_framebuffer.set_color_attachment(
    attachmentPoint, *m_color_attachment, mipMapLevel);
  m_framebuffer.set_depth_stencil_attachment(*m_depth_stencil_attachment, mipMapLevel);

  HOU_ENSURE_DEV(m_framebuffer.is_complete());
}



void blit(const render_surface& src, const recti& srcRect, render_surface& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  blit(src.m_framebuffer, srcRect, dst.m_framebuffer, dstRect,
    framebuffer_blit_mask::all, filter);
}



void blit(const render_surface& src, const recti& srcRect, texture& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  blit(src.m_framebuffer, srcRect, dst, dstRect, filter);
}



void blit(const texture& src, const recti& srcRect, render_surface& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  blit(src, srcRect, dst.m_framebuffer, dstRect, filter);
}

}  // namespace hou
