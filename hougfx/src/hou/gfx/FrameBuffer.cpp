// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/FrameBuffer.hpp"

#include "hou/mth/Rectangle.hpp"

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
  : NonCopyable()
  , mHandle(gl::FramebufferHandle::create())
  , mHasMultisampleColorAttachment(false)
  , mHasMultisampleDepthAttachment(false)
  , mHasMultisampleStencilAttachment(false)
{}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
  : NonCopyable()
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
  uint attachmentPoint, Texture& texture, uint mipMapLevel)
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



void FrameBuffer::setDepthAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::Depth
    || texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferDepthTexture(mHandle, texture.getHandle(), mipMapLevel);
  mHasMultisampleDepthAttachment = isTextureTypeMultisampled(texture.getType());
}



void FrameBuffer::setStencilAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::Stencil
    || texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferStencilTexture(mHandle, texture.getHandle(), mipMapLevel);
  mHasMultisampleStencilAttachment
    = isTextureTypeMultisampled(texture.getType());
}



void FrameBuffer::setDepthStencilAttachment(Texture& texture, uint mipMapLevel)
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



void blit(const FrameBuffer& src, const Recti& srcRect, FrameBuffer& dst,
  const Recti& dstRect, FrameBufferBlitMask mask, FrameBufferBlitFilter filter)
{
  HOU_EXPECT((filter == FrameBufferBlitFilter::Nearest
               || mask == FrameBufferBlitMask::None
               || mask == FrameBufferBlitMask::Color)
    && src.isComplete() && dst.isComplete()
    && ((!src.hasMultisampleAttachment() && !dst.hasMultisampleAttachment())
         || (std::abs(srcRect.w()) == std::abs(dstRect.w())
              && std::abs(srcRect.h()) == std::abs(srcRect.h()))));

  gl::blitFramebuffer(src.getHandle(), dst.getHandle(), srcRect.l(),
    srcRect.t(), srcRect.r(), srcRect.b(), dstRect.l(), dstRect.t(),
    dstRect.r(), dstRect.b(), static_cast<GLbitfield>(mask),
    static_cast<GLenum>(filter));
}

}  // namespace hou
