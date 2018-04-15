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
  HOU_EXPECT(false);
}



void FrameBuffer::unbind()
{
  HOU_EXPECT(false);
}



void FrameBuffer::bind(FrameBufferTarget fbt)
{
  HOU_EXPECT(false);
}



void FrameBuffer::unbind(FrameBufferTarget fbt)
{
  HOU_EXPECT(false);
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



uint FrameBuffer::getMaxColorAttachmentCount()
{
  HOU_EXPECT(false);
  return 42u;
}



FrameBuffer::FrameBuffer()
{
  HOU_EXPECT(false);
}



bool FrameBuffer::isBound(FrameBufferTarget fbt) const
{
  HOU_EXPECT(false);
  return false;
}



FrameBufferStatus FrameBuffer::getStatus() const
{
  HOU_EXPECT(false);
  return FrameBufferStatus::Undefined;
}



FrameBufferStatus FrameBuffer::getStatus(FrameBufferTarget) const
{
  HOU_EXPECT(false);
  return FrameBufferStatus::Undefined;
}



void FrameBuffer::setColorAttachment(
  uint attachmentPoint, Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(false);
}



void FrameBuffer::setDepthAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(false);
}



void FrameBuffer::setStencilAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(false);
}



void FrameBuffer::setDepthStencilAttachment(Texture& texture, uint mipMapLevel)
{
  HOU_EXPECT(false);
}

}  // namespace hou
