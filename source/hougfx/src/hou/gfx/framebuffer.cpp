// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/framebuffer.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/gfx/texture.hpp"



namespace hou
{

void framebuffer::bind_draw_target(const framebuffer& fb)
{
  DEPRECATED_HOU_EXPECT(fb.is_complete());
  gl::bind_framebuffer(fb.get_handle(), GL_DRAW_FRAMEBUFFER);
}



void framebuffer::bind_read_target(const framebuffer& fb)
{
  DEPRECATED_HOU_EXPECT(fb.is_complete());
  gl::bind_framebuffer(fb.get_handle(), GL_READ_FRAMEBUFFER);
}



void framebuffer::bind(const framebuffer& fb)
{
  DEPRECATED_HOU_EXPECT(fb.is_complete());
  gl::bind_framebuffer(fb.get_handle());
}



void framebuffer::unbind_draw_target()
{
  gl::unbind_framebuffer(GL_DRAW_FRAMEBUFFER);
}



void framebuffer::unbind_read_target()
{
  gl::unbind_framebuffer(GL_READ_FRAMEBUFFER);
}



void framebuffer::unbind()
{
  gl::unbind_framebuffer();
}



uint framebuffer::get_color_attachment_point_count()
{
  return static_cast<uint>(gl::get_max_color_attachments());
}



framebuffer::framebuffer()
  : non_copyable()
  , m_handle(gl::framebuffer_handle::create())
  , m_has_multisample_color_attachment(false)
  , m_has_multisample_depth_attachment(false)
  , m_has_multisample_stencil_attachment(false)
{}



framebuffer::framebuffer(framebuffer&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
  , m_has_multisample_color_attachment(
      std::move(other.m_has_multisample_color_attachment))
  , m_has_multisample_depth_attachment(
      std::move(other.m_has_multisample_depth_attachment))
  , m_has_multisample_stencil_attachment(
      std::move(other.m_has_multisample_stencil_attachment))
{}



const gl::framebuffer_handle& framebuffer::get_handle() const
{
  return m_handle;
}



bool framebuffer::is_bound_to_draw_target() const
{
  return static_cast<bool>(
    gl::is_framebuffer_bound(m_handle, GL_DRAW_FRAMEBUFFER));
}



bool framebuffer::is_bound_to_read_target() const
{
  return static_cast<bool>(
    gl::is_framebuffer_bound(m_handle, GL_READ_FRAMEBUFFER));
}



bool framebuffer::is_complete() const
{
  return gl::get_framebuffer_status(m_handle) == GL_FRAMEBUFFER_COMPLETE;
}



void framebuffer::set_color_attachment(
  uint attachmentPoint, const texture& tex, uint mipmap_level)
{
  DEPRECATED_HOU_EXPECT(attachmentPoint < get_color_attachment_point_count());
  DEPRECATED_HOU_EXPECT(mipmap_level < tex.get_mipmap_level_count());
  DEPRECATED_HOU_EXPECT(tex.get_format() == texture_format::rgba
    || tex.get_format() == texture_format::rgb
    || tex.get_format() == texture_format::rg
    || tex.get_format() == texture_format::r);
  gl::set_framebuffer_color_texture(m_handle,
    static_cast<GLuint>(attachmentPoint), tex.get_handle(),
    static_cast<GLint>(mipmap_level));
  m_has_multisample_color_attachment
    = is_texture_type_multisampled(tex.get_type());
}



void framebuffer::set_depth_attachment(const texture& tex, uint mipmap_level)
{
  DEPRECATED_HOU_EXPECT(mipmap_level < tex.get_mipmap_level_count());
  DEPRECATED_HOU_EXPECT(tex.get_format() == texture_format::depth
    || tex.get_format() == texture_format::depth_stencil);
  gl::set_framebuffer_depth_texture(m_handle, tex.get_handle(), mipmap_level);
  m_has_multisample_depth_attachment
    = is_texture_type_multisampled(tex.get_type());
}



void framebuffer::set_stencil_attachment(const texture& tex, uint mipmap_level)
{
  DEPRECATED_HOU_EXPECT(mipmap_level < tex.get_mipmap_level_count());
  DEPRECATED_HOU_EXPECT(tex.get_format() == texture_format::stencil
    || tex.get_format() == texture_format::depth_stencil);
  gl::set_framebuffer_stencil_texture(m_handle, tex.get_handle(), mipmap_level);
  m_has_multisample_stencil_attachment
    = is_texture_type_multisampled(tex.get_type());
}



void framebuffer::set_depth_stencil_attachment(
  const texture& tex, uint mipmap_level)
{
  DEPRECATED_HOU_EXPECT(mipmap_level < tex.get_mipmap_level_count());
  DEPRECATED_HOU_EXPECT(tex.get_format() == texture_format::depth_stencil);
  gl::set_framebuffer_depth_stencil_texture(
    m_handle, tex.get_handle(), mipmap_level);
  m_has_multisample_depth_attachment
    = is_texture_type_multisampled(tex.get_type());
  m_has_multisample_stencil_attachment
    = is_texture_type_multisampled(tex.get_type());
}



bool framebuffer::has_multisample_attachment() const
{
  return m_has_multisample_color_attachment
    || m_has_multisample_depth_attachment
    || m_has_multisample_stencil_attachment;
}



void blit(const framebuffer& src, const recti& src_rect, framebuffer& dst,
  const recti& dst_rect, framebuffer_blit_mask mask,
  framebuffer_blit_filter filter)
{
  DEPRECATED_HOU_EXPECT((filter == framebuffer_blit_filter::nearest
    || mask == framebuffer_blit_mask::none
    || mask == framebuffer_blit_mask::color));
  DEPRECATED_HOU_EXPECT(src.is_complete());
  DEPRECATED_HOU_EXPECT(dst.is_complete());
  DEPRECATED_HOU_EXPECT(
    (!src.has_multisample_attachment() && !dst.has_multisample_attachment())
    || (std::abs(src_rect.w()) == std::abs(dst_rect.w())
         && std::abs(src_rect.h()) == std::abs(src_rect.h())));

  gl::blit_framebuffer(src.get_handle(), dst.get_handle(), src_rect.l(),
    src_rect.t(), src_rect.r(), src_rect.b(), dst_rect.l(), dst_rect.t(),
    dst_rect.r(), dst_rect.b(), static_cast<GLbitfield>(mask),
    static_cast<GLenum>(filter));
}



void blit(const framebuffer& src, const recti& src_rect, texture& dst,
  const recti& dst_rect, framebuffer_blit_filter filter)
{
  framebuffer dst_frame_buffer;
  dst_frame_buffer.set_color_attachment(0u, dst);
  blit(src, src_rect, dst_frame_buffer, dst_rect, framebuffer_blit_mask::color,
    filter);
}



void blit(const texture& src, const recti& src_rect, framebuffer& dst,
  const recti& dst_rect, framebuffer_blit_filter filter)
{
  framebuffer src_frame_buffer;
  src_frame_buffer.set_color_attachment(0u, src);
  blit(src_frame_buffer, src_rect, dst, dst_rect, framebuffer_blit_mask::color,
    filter);
}



void blit(const texture& src, const recti& src_rect, texture& dst,
  const recti& dst_rect, framebuffer_blit_filter filter)
{
  framebuffer src_frame_buffer;
  src_frame_buffer.set_color_attachment(0u, src);
  blit(src_frame_buffer, src_rect, dst, dst_rect, filter);
}

}  // namespace hou
