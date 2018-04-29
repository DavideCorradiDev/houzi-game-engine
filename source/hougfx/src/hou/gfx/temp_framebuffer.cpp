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
  HOU_EXPECT(fb.is_complete());
  gl::bind_framebuffer(fb.get_handle(), GL_DRAW_FRAMEBUFFER);
}



void framebuffer::bind_read_target(const framebuffer& fb)
{
  HOU_EXPECT(fb.is_complete());
  gl::bind_framebuffer(fb.get_handle(), GL_READ_FRAMEBUFFER);
}



void framebuffer::bind(const framebuffer& fb)
{
  HOU_EXPECT(fb.is_complete());
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
  uint attachmentPoint, const texture& ph_texture, uint mipMapLevel)
{
  HOU_EXPECT(attachmentPoint < get_color_attachment_point_count());
  HOU_EXPECT(mipMapLevel < ph_texture.get_mipmap_level_count());
  HOU_EXPECT(ph_texture.get_format() == texture_format::rgba
    || ph_texture.get_format() == texture_format::rgb
    || ph_texture.get_format() == texture_format::rg
    || ph_texture.get_format() == texture_format::r);
  gl::set_framebuffer_color_texture(m_handle, static_cast<GLuint>(attachmentPoint),
    ph_texture.get_handle(), static_cast<GLint>(mipMapLevel));
  m_has_multisample_color_attachment = is_texture_type_multisampled(ph_texture.get_type());
}



void framebuffer::set_depth_attachment(const texture& ph_texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < ph_texture.get_mipmap_level_count());
  HOU_EXPECT(ph_texture.get_format() == texture_format::depth
    || ph_texture.get_format() == texture_format::depth_stencil);
  gl::set_framebuffer_depth_texture(m_handle, ph_texture.get_handle(), mipMapLevel);
  m_has_multisample_depth_attachment = is_texture_type_multisampled(ph_texture.get_type());
}



void framebuffer::set_stencil_attachment(const texture& ph_texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < ph_texture.get_mipmap_level_count());
  HOU_EXPECT(ph_texture.get_format() == texture_format::stencil
    || ph_texture.get_format() == texture_format::depth_stencil);
  gl::set_framebuffer_stencil_texture(m_handle, ph_texture.get_handle(), mipMapLevel);
  m_has_multisample_stencil_attachment
    = is_texture_type_multisampled(ph_texture.get_type());
}



void framebuffer::set_depth_stencil_attachment(
  const texture& ph_texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < ph_texture.get_mipmap_level_count());
  HOU_EXPECT(ph_texture.get_format() == texture_format::depth_stencil);
  gl::set_framebuffer_depth_stencil_texture(
    m_handle, ph_texture.get_handle(), mipMapLevel);
  m_has_multisample_depth_attachment = is_texture_type_multisampled(ph_texture.get_type());
  m_has_multisample_stencil_attachment
    = is_texture_type_multisampled(ph_texture.get_type());
}



bool framebuffer::hasMultisampleAttachment() const
{
  return m_has_multisample_color_attachment || m_has_multisample_depth_attachment
    || m_has_multisample_stencil_attachment;
}



void blit(const framebuffer& src, const recti& srcRect, framebuffer& dst,
  const recti& dstRect, framebuffer_blit_mask mask, framebuffer_blit_filter filter)
{
  HOU_EXPECT((filter == framebuffer_blit_filter::nearest
    || mask == framebuffer_blit_mask::none
    || mask == framebuffer_blit_mask::color));
  HOU_EXPECT(src.is_complete());
  HOU_EXPECT(dst.is_complete());
  HOU_EXPECT(
    (!src.hasMultisampleAttachment() && !dst.hasMultisampleAttachment())
    || (std::abs(srcRect.w()) == std::abs(dstRect.w())
         && std::abs(srcRect.h()) == std::abs(srcRect.h())));

  gl::blit_framebuffer(src.get_handle(), dst.get_handle(), srcRect.l(),
    srcRect.t(), srcRect.r(), srcRect.b(), dstRect.l(), dstRect.t(),
    dstRect.r(), dstRect.b(), static_cast<GLbitfield>(mask),
    static_cast<GLenum>(filter));
}



void blit(const framebuffer& src, const recti& srcRect, texture& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  framebuffer dstFrameBuffer;
  dstFrameBuffer.set_color_attachment(0u, dst);
  blit(
    src, srcRect, dstFrameBuffer, dstRect, framebuffer_blit_mask::color, filter);
}



void blit(const texture& src, const recti& srcRect, framebuffer& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  framebuffer srcFrameBuffer;
  srcFrameBuffer.set_color_attachment(0u, src);
  blit(
    srcFrameBuffer, srcRect, dst, dstRect, framebuffer_blit_mask::color, filter);
}



void blit(const texture& src, const recti& srcRect, texture& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  framebuffer srcFrameBuffer;
  srcFrameBuffer.set_color_attachment(0u, src);
  blit(srcFrameBuffer, srcRect, dst, dstRect, filter);
}

}  // namespace hou
