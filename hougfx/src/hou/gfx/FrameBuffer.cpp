// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/FrameBuffer.hpp"

#include "hou/mth/Rectangle.hpp"

#include "hou/gfx/Texture.hpp"



namespace hou
{

void FrameBuffer::bind(FrameBuffer& fb)
{
  HOU_EXPECT(fb.getStatus() == FrameBufferStatus::Complete);
  gl::bindFramebuffer(fb.getHandle());
}



void FrameBuffer::unbind()
{
  gl::unbindFramebuffer();
}



void FrameBuffer::bind(FrameBuffer& fb, FrameBufferTarget fbt)
{
  HOU_EXPECT(fb.getStatus(fbt) == FrameBufferStatus::Complete);
  gl::bindFramebuffer(fb.getHandle(), static_cast<GLenum>(fbt));
}



void FrameBuffer::unbind(FrameBufferTarget fbt)
{
  gl::unbindFramebuffer(static_cast<GLenum>(fbt));
}



void FrameBuffer::blit(const Recti& srcRect, const Recti& dstRect,
  FrameBufferBlitMask mask, FrameBufferBlitFilter filter)
{
  HOU_EXPECT(false);
}



void FrameBuffer::blit(const FrameBuffer& src, const Recti& srcRect,
  FrameBuffer& dst, const Recti& dstRect, FrameBufferBlitMask mask,
  FrameBufferBlitFilter filter)
{
  HOU_EXPECT(false);
}



uint FrameBuffer::getColorAttachmentPointCount()
{
  return static_cast<uint>(gl::getMaxColorAttachments());
}



FrameBuffer::FrameBuffer()
  : NonCopyable()
  , mHandle(gl::FramebufferHandle::create())
{}



FrameBuffer::FrameBuffer(FrameBuffer&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
{}



const gl::FramebufferHandle& FrameBuffer::getHandle() const
{
  return mHandle;
}



bool FrameBuffer::isBound(FrameBufferTarget fbt) const
{
  return static_cast<bool>(
    gl::isFramebufferBound(mHandle, static_cast<GLenum>(fbt)));
}



FrameBufferStatus FrameBuffer::getStatus() const
{
  return FrameBufferStatus(gl::getFramebufferStatus(mHandle));
}



FrameBufferStatus FrameBuffer::getStatus(FrameBufferTarget fbt) const
{
  return FrameBufferStatus(
    gl::getFramebufferStatus(mHandle, static_cast<GLenum>(fbt)));
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
}



void FrameBuffer::setDepthAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::Depth
    || texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferDepthTexture(mHandle, texture.getHandle(), mipMapLevel);
}



void FrameBuffer::setStencilAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::Stencil
    || texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferStencilTexture(mHandle, texture.getHandle(), mipMapLevel);
}



void FrameBuffer::setDepthStencilAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(mipMapLevel < texture.getMipMapLevelCount());
  HOU_EXPECT(texture.getFormat() == TextureFormat::DepthStencil);
  gl::setFramebufferDepthStencilTexture(
    mHandle, texture.getHandle(), mipMapLevel);
}

}  // namespace hou
