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
  static void bind(FrameBufferTarget fbt);
  static void unbind(FrameBufferTarget fbt);

  // Params:
  // Filter:
  //  - Nearest.
  //  - Linear.
  // Bitmask:
  //  - Color.
  //  - Depth.
  //  - Stencil.
  // Invalid configs
  // - Stencil or Depth + linear
  // - Stencil or Depth + inconsistent depth /stencil format between the two.
  // - There are some conditions concerning floating point / integers?
  // - samplex > 0 for both source and dst and rect are not identical...
  // - dst or src is not complete.
  static void blit(const Recti& srcRect, const Recti& dstRect,
    FrameBufferBlitMask mask, FrameBufferBlitFilter filter);
  static void blit(const FrameBuffer& src, const Recti& srcRect,
    FrameBuffer& dst, const Recti& dstRect, FrameBufferBlitMask mask,
    FrameBufferBlitFilter filter);


  // Safe
  static uint getMaxColorAttachmentCount();

public:
  FrameBuffer();

  bool isBound(FrameBufferTarget fbt) const;

  // Safe
  FrameBufferStatus getStatus() const;
  FrameBufferStatus getStatus(FrameBufferTarget) const;

  // must check the mipmapLevel.
  // must check the attachment point.
  void setColorAttachment(
    uint attachmentPoint, Texture& texture, uint mipMapLevel = 0u);
  void setDepthAttachment(Texture& texture, uint mipMapLevel = 0u);
  void setStencilAttachment(Texture& texture, uint mipMapLevel = 0u);
  void setDepthStencilAttachment(Texture& texture, uint mipMapLevel = 0u);
};

}  // namespace hou

#endif
