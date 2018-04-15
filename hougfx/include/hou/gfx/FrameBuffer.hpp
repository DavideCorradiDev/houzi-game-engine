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
#include "hou/gfx/FrameBufferTarget.hpp"

#include "hou/gl/GlFramebufferHandle.hpp"



namespace hou
{

class Texture;

class HOU_GFX_API FrameBuffer : public NonCopyable
{
public:
  static void bind(const FrameBuffer& fb);
  static void unbind();
  static void bind(const FrameBuffer& fb, FrameBufferTarget fbt);
  static void unbind(FrameBufferTarget fbt);

  static uint getColorAttachmentPointCount();

public:
  FrameBuffer();
  FrameBuffer(FrameBuffer&& other);

  const gl::FramebufferHandle& getHandle() const;
  bool isBound(FrameBufferTarget fbt) const;

  bool isComplete() const;

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
