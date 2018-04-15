// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_HPP
#define HOU_GFX_FRAME_BUFFER_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/NonCopyable.hpp"

#include "hou/mth/RectangleFwd.hpp"

#include "hou/gfx/FrameBufferBlitFilter.hpp"
#include "hou/gfx/FrameBufferBlitMask.hpp"
#include "hou/gfx/FrameBufferStatus.hpp"
#include "hou/gfx/FrameBufferTarget.hpp"

#include "hou/gl/GlFramebufferHandle.hpp"



namespace hou
{

class Texture;

class HOU_GFX_API FrameBuffer : public NonCopyable
{
public:
  // Safe
  // I could check completeness before binding for safety reasons (otherwise
  // some error would happen later...).
  static void bind(FrameBuffer& fb);
  static void unbind();
  static void bind(FrameBuffer& fb, FrameBufferTarget fbt);
  static void unbind(FrameBufferTarget fbt);
  // Safe
  static uint getColorAttachmentPointCount();

public:
  FrameBuffer();
  FrameBuffer(FrameBuffer&& other);

  const gl::FramebufferHandle& getHandle() const;
  bool isBound(FrameBufferTarget fbt) const;

  // Safe
  FrameBufferStatus getStatus() const;

  // must check the mipmapLevel.
  // must check the attachment point.
  void setColorAttachment(
    uint attachmentPoint, Texture& texture, uint mipMapLevel = 0u);
  void setDepthAttachment(Texture& texture, uint mipMapLevel = 0u);
  void setStencilAttachment(Texture& texture, uint mipMapLevel = 0u);
  void setDepthStencilAttachment(Texture& texture, uint mipMapLevel = 0u);

  bool hasMultisampleAttachment() const;

private:
  gl::FramebufferHandle mHandle;
  bool mHasMultisampleColorAttachment;
  bool mHasMultisampleDepthAttachment;
  bool mHasMultisampleStencilAttachment;
};

HOU_GFX_API void blit(const FrameBuffer& src, const Recti& srcRect,
  FrameBuffer& dst, const Recti& dstRect, FrameBufferBlitMask mask,
  FrameBufferBlitFilter filter);

}  // namespace hou

#endif
