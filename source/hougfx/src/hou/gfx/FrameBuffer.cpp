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
  gl::bindFramebuffer(fb.getHandle(), GL_DRAW_FRAMEBUFFER);
}



void FrameBuffer::bindReadTarget(const FrameBuffer& fb)
{
  HOU_EXPECT(fb.isComplete());
  gl::bindFramebuffer(fb.getHandle(), GL_READ_FRAMEBUFFER);
}



void FrameBuffer::bind(const FrameBuffer& fb)
{
  HOU_EXPECT(fb.isComplete());
  gl::bindFramebuffer(fb.getHandle());
}



void FrameBuffer::unbindDrawTarget()
{
  gl::unbindFramebuffer(GL_DRAW_FRAMEBUFFER);
}



void FrameBuffer::unbindReadTarget()
{
  gl::unbindFramebuffer(GL_READ_FRAMEBUFFER);
}



void FrameBuffer::unbind()
{
  gl::unbindFramebuffer();
}



uint FrameBuffer::getColorAttachmentPointCount()
{
  return static_cast<uint>(gl::getMaxColorAttachments());
}



FrameBuffer::FrameBuffer()
  : non_copyable()
  , mHandle(gl::FramebufferHandle::create())
  , mHasMultisampleColorAttachment(false)
  , mHasMultisampleDepthAttachment(false)
  , mHasMultisampleStencilAttachment(false)
{}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
  : non_copyable()
  , mHandle(std::move(other.mHandle))
  , mHasMultisampleColorAttachment(
      std::move(other.mHasMultisampleColorAttachment))
  , mHasMultisampleDepthAttachment(
      std::move(other.mHasMultisampleDepthAttachment))
  , mHasMultisampleStencilAttachment(
      std::move(other.mHasMultisampleStencilAttachment))
{}



const gl::FramebufferHandle& FrameBuffer::getHandle() const
{
  return mHandle;
}



bool FrameBuffer::isBoundToDrawTarget() const
{
  return static_cast<bool>(
    gl::isFramebufferBound(mHandle, GL_DRAW_FRAMEBUFFER));
}



bool FrameBuffer::isBoundToReadTarget() const
{
  return static_cast<bool>(
    gl::isFramebufferBound(mHandle, GL_READ_FRAMEBUFFER));
}



bool FrameBuffer::isComplete() const
{
  return gl::getFramebufferStatus(mHandle) == GL_FRAMEBUFFER_COMPLETE;
}



void FrameBuffer::setColorAttachment(
  uint attachmentPoint, const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(attachmentPoint < getColorAttachmentPointCount());
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::RGBA
    || texture.getFormat() == TextureFormat::RGB
    || texture.getFormat() == TextureFormat::RG
    || texture.getFormat() == TextureFormat::R);
  gl::setFramebufferColorTexture(mHandle, static_cast<GLuint>(attachmentPoint),
    texture.getHandle(), static_cast<GLint>(mipMapLevel));
  mHasMultisampleColorAttachment = isTextureTypeMultisampled(texture.getType());
}



void FrameBuffer::setDepthAttachment(const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::Depth
    || texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferDepthTexture(mHandle, texture.getHandle(), mipMapLevel);
  mHasMultisampleDepthAttachment = isTextureTypeMultisampled(texture.getType());
}



void FrameBuffer::setStencilAttachment(const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::Stencil
    || texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferStencilTexture(mHandle, texture.getHandle(), mipMapLevel);
  mHasMultisampleStencilAttachment
    = isTextureTypeMultisampled(texture.getType());
}



void FrameBuffer::setDepthStencilAttachment(
  const Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferDepthStencilTexture(
    mHandle, texture.getHandle(), mipMapLevel);
  mHasMultisampleDepthAttachment = isTextureTypeMultisampled(texture.getType());
  mHasMultisampleStencilAttachment
    = isTextureTypeMultisampled(texture.getType());
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
    || mask == FrameBufferBlitMask::None
    || mask == FrameBufferBlitMask::Color));
  HOU_EXPECT(src.isComplete());
  HOU_EXPECT(dst.isComplete());
  HOU_EXPECT(
    (!src.hasMultisampleAttachment() && !dst.hasMultisampleAttachment())
    || (std::abs(srcRect.w()) == std::abs(dstRect.w())
         && std::abs(srcRect.h()) == std::abs(srcRect.h())));

  gl::blitFramebuffer(src.getHandle(), dst.getHandle(), srcRect.l(),
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
    src, srcRect, dstFrameBuffer, dstRect, FrameBufferBlitMask::Color, filter);
}



void blit(const Texture& src, const recti& srcRect, FrameBuffer& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  FrameBuffer srcFrameBuffer;
  srcFrameBuffer.setColorAttachment(0u, src);
  blit(
    srcFrameBuffer, srcRect, dst, dstRect, FrameBufferBlitMask::Color, filter);
}



void blit(const Texture& src, const recti& srcRect, Texture& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  FrameBuffer srcFrameBuffer;
  srcFrameBuffer.setColorAttachment(0u, src);
  blit(srcFrameBuffer, srcRect, dst, dstRect, filter);
}

}  // namespace hou
