// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/FrameBuffer.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/gfx/Texture.hpp"



namespace hou
{

void FrameBuffer::bindDrawTarget(const FrameBuffer& fb)
{
  HOU_EXPECT(fb.isComplete());
  gl::bind_framebuffer(fb.getHandle(), GL_DRAW_FRAMEBUFFER);
}



void FrameBuffer::bindReadTarget(const FrameBuffer& fb)
{
  HOU_EXPECT(fb.isComplete());
  gl::bind_framebuffer(fb.getHandle(), GL_READ_FRAMEBUFFER);
}



void FrameBuffer::bind(const FrameBuffer& fb)
{
  HOU_EXPECT(fb.isComplete());
  gl::bind_framebuffer(fb.getHandle());
}



void FrameBuffer::unbindDrawTarget()
{
  gl::unbind_framebuffer(GL_DRAW_FRAMEBUFFER);
}



void FrameBuffer::unbindReadTarget()
{
  gl::unbind_framebuffer(GL_READ_FRAMEBUFFER);
}



void FrameBuffer::unbind()
{
  gl::unbind_framebuffer();
}



uint FrameBuffer::getColorAttachmentPointCount()
{
  return static_cast<uint>(gl::get_max_color_attachments());
}



FrameBuffer::FrameBuffer()
  : non_copyable()
  , m_handle(gl::framebuffer_handle::create())
  , mHasMultisampleColorAttachment(false)
  , mHasMultisampleDepthAttachment(false)
  , mHasMultisampleStencilAttachment(false)
{}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
  , mHasMultisampleColorAttachment(
      std::move(other.mHasMultisampleColorAttachment))
  , mHasMultisampleDepthAttachment(
      std::move(other.mHasMultisampleDepthAttachment))
  , mHasMultisampleStencilAttachment(
      std::move(other.mHasMultisampleStencilAttachment))
{}



const gl::framebuffer_handle& FrameBuffer::getHandle() const
{
  return m_handle;
}



bool FrameBuffer::isBoundToDrawTarget() const
{
  return static_cast<bool>(
    gl::is_framebuffer_bound(m_handle, GL_DRAW_FRAMEBUFFER));
}



bool FrameBuffer::isBoundToReadTarget() const
{
  return static_cast<bool>(
    gl::is_framebuffer_bound(m_handle, GL_READ_FRAMEBUFFER));
}



bool FrameBuffer::isComplete() const
{
  return gl::get_framebuffer_status(m_handle) == GL_FRAMEBUFFER_COMPLETE;
}



void FrameBuffer::setColorAttachment(
  uint attachmentPoint, const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(attachmentPoint < getColorAttachmentPointCount());
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.get_format() == TextureFormat::rgba
    || texture.get_format() == TextureFormat::rgb
    || texture.get_format() == TextureFormat::rg
    || texture.get_format() == TextureFormat::r);
  gl::set_framebuffer_color_texture(m_handle, static_cast<GLuint>(attachmentPoint),
    texture.getHandle(), static_cast<GLint>(mipMapLevel));
  mHasMultisampleColorAttachment = isTextureTypeMultisampled(texture.get_type());
}



void FrameBuffer::setDepthAttachment(const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.get_format() == TextureFormat::Depth
    || texture.get_format() == TextureFormat::DepthStencil);
  gl::set_framebuffer_depth_texture(m_handle, texture.getHandle(), mipMapLevel);
  mHasMultisampleDepthAttachment = isTextureTypeMultisampled(texture.get_type());
}



void FrameBuffer::setStencilAttachment(const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.get_format() == TextureFormat::Stencil
    || texture.get_format() == TextureFormat::DepthStencil);
  gl::set_framebuffer_stencil_texture(m_handle, texture.getHandle(), mipMapLevel);
  mHasMultisampleStencilAttachment
    = isTextureTypeMultisampled(texture.get_type());
}



void FrameBuffer::setDepthStencilAttachment(
  const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.get_format() == TextureFormat::DepthStencil);
  gl::set_framebuffer_depth_stencil_texture(
    m_handle, texture.getHandle(), mipMapLevel);
  mHasMultisampleDepthAttachment = isTextureTypeMultisampled(texture.get_type());
  mHasMultisampleStencilAttachment
    = isTextureTypeMultisampled(texture.get_type());
}



bool FrameBuffer::hasMultisampleAttachment() const
{
  return mHasMultisampleColorAttachment || mHasMultisampleDepthAttachment
    || mHasMultisampleStencilAttachment;
}



void blit(const FrameBuffer& src, const recti& srcRect, FrameBuffer& dst,
  const recti& dstRect, FrameBufferBlitMask mask, FrameBufferBlitFilter filter)
{
  HOU_EXPECT((filter == FrameBufferBlitFilter::Nearest
    || mask == FrameBufferBlitMask::none
    || mask == FrameBufferBlitMask::color));
  HOU_EXPECT(src.isComplete());
  HOU_EXPECT(dst.isComplete());
  HOU_EXPECT(
    (!src.hasMultisampleAttachment() && !dst.hasMultisampleAttachment())
    || (std::abs(srcRect.w()) == std::abs(dstRect.w())
         && std::abs(srcRect.h()) == std::abs(srcRect.h())));

  gl::blit_framebuffer(src.getHandle(), dst.getHandle(), srcRect.l(),
    srcRect.t(), srcRect.r(), srcRect.b(), dstRect.l(), dstRect.t(),
    dstRect.r(), dstRect.b(), static_cast<GLbitfield>(mask),
    static_cast<GLenum>(filter));
}



void blit(const FrameBuffer& src, const recti& srcRect, Texture& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  FrameBuffer dstFrameBuffer;
  dstFrameBuffer.setColorAttachment(0u, dst);
  blit(
    src, srcRect, dstFrameBuffer, dstRect, FrameBufferBlitMask::color, filter);
}



void blit(const Texture& src, const recti& srcRect, FrameBuffer& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  FrameBuffer srcFrameBuffer;
  srcFrameBuffer.setColorAttachment(0u, src);
  blit(
    srcFrameBuffer, srcRect, dst, dstRect, FrameBufferBlitMask::color, filter);
}



void blit(const Texture& src, const recti& srcRect, Texture& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  FrameBuffer srcFrameBuffer;
  srcFrameBuffer.setColorAttachment(0u, src);
  blit(srcFrameBuffer, srcRect, dst, dstRect, filter);
}

}  // namespace hou
