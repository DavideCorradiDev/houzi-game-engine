// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_FRAME_BUFFER_HPP
#define HOU_GFX_FRAME_BUFFER_HPP

#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/non_copyable.hpp"

#include "hou/mth/rectangle_fwd.hpp"

#include "hou/gfx/FrameBufferBlitFilter.hpp"
#include "hou/gfx/FrameBufferBlitMask.hpp"

#include "hou/gl/GlFramebufferHandle.hpp"



namespace hou
{

class Texture;

/** Represents a user defined framebuffer.
 */
class HOU_GFX_API FrameBuffer : public non_copyable
{
public:
  /** Binds a FrameBuffer as the target for drawing operations.
   *
   *  Throws if fb is not complete.
   *
   *  \param fb the FrameBuffer.
   */
  static void bindDrawTarget(const FrameBuffer& fb);

  /** Binds a FrameBuffer as the source FrameBuffer.
   *
   *  Throws if fb is not complete.
   *
   *  \param fb the FrameBuffer.
   */
  static void bindReadTarget(const FrameBuffer& fb);

  /** Binds a FrameBuffer as both target and source.
   *
   *  Throws if fb is not complete.
   *
   *  \param fb the FrameBuffer.
   */
  static void bind(const FrameBuffer& fb);

  /** Unbinds the current draw FrameBuffer.
   */
  static void unbindDrawTarget();

  /** Unbinds the current read FrameBuffer.
   */
  static void unbindReadTarget();

  /** Unbinds the current draw and read FrameBuffer objects.
   */
  static void unbind();

  /** Retrieves the number of available slots for color attachments in a
   *  FrameBuffer.
   *
   *  \return the number of available slots for color attachments.
   */
  static uint getColorAttachmentPointCount();

public:
  /** Default constructor.
   */
  FrameBuffer();

  /** Move constructor.
   *
   *  \param other the other FrameBuffer.
   */
  FrameBuffer(FrameBuffer&& other);

  /** Retrieves a reference to the OpenGL framebuffer handle.
   *
   *  \return a reference to the OpenGL framebuffer handle.
   */
  const gl::FramebufferHandle& getHandle() const;

  /** Checks if this FrameBuffer is currently bound as draw target.
   *
   *  \return the result of the check.
   */
  bool isBoundToDrawTarget() const;

  /** Checks if this FrameBuffer is currently bound as read target.
   *
   *  \return the result of the check.
   */
  bool isBoundToReadTarget() const;

  /** Checks if this FrameBuffer is complete.
   *
   *  Only complete FrameBuffer objects can be bound or used as source or
   *  destination for blit destination. Using an incomplete FrameBuffer will
   *  cause an exception to be thrown.
   *
   *  \return the result of the check.
   */
  bool isComplete() const;

  /** Sets a color attachment for this FrameBuffer.
   *
   *  \param attachmentPoint an index representing the desired attachment point.
   *  Its value must be lower than the maximum number of available attachment
   *  points.
   *  \param texture the texture to be attached. The format of the
   *  texture must be R, RG, RGB, or RGBA.
   *  \param mipMapLevel the mip map level
   *  to bind. It must be a valid mip map level of texture.
   */
  void setColorAttachment(
    uint attachmentPoint, const Texture& texture, uint mipMapLevel = 0u);

  /** Sets the depth attachment for this FrameBuffer.
   *
   *  \param texture the texture to be attached. The format of the texture must
   *  be Depth or DepthStencil.
   *  \param mipMapLevel the mip map level to bind. It must be a valid mip map
   *  level of texture.
   */
  void setDepthAttachment(const Texture& texture, uint mipMapLevel = 0u);

  /** Sets the stencil attachment for this FrameBuffer.
   *
   *  \param texture the texture to be attached. The format of the texture must
   *  be Stencil or DepthStencil.
   *  \param mipMapLevel the mip map level to bind. It must be a valid mip map
   *  level of texture.
   */
  void setStencilAttachment(const Texture& texture, uint mipMapLevel = 0u);

  /** Sets the depth and stencil attachment for this FrameBuffer.
   *
   *  \param texture the texture to be attached. The format of the texture must
   *  be DepthStencil.
   *  \param mipMapLevel the mip map level to bind. It must be a valid mip map
   *  level of texture.
   */
  void setDepthStencilAttachment(const Texture& texture, uint mipMapLevel = 0u);

  /** Checks if this FrameBuffer has a multisample attachment.
   *
   *  \return the result of the check.
   */
  bool hasMultisampleAttachment() const;

private:
  gl::FramebufferHandle mHandle;
  bool mHasMultisampleColorAttachment;
  bool mHasMultisampleDepthAttachment;
  bool mHasMultisampleStencilAttachment;
};

/** Copies a rectangular region of a FrameBuffer into another FrameBuffer.
 *
 * The following constraints must be observed, or an exception will be thrown:
 * * src and dst must be complete FrameBuffer objects.
 * * If src or dst are multisampled, srcRect and dstRect must have the same
 * size.
 * * If mask contains Depth or Stencil, filter must be set to Nearest.
 *
 * \param src the source FrameBuffer.
 * \param srcRect the source ph_rectangle.
 * \param dst the destination FrameBuffer.
 * \param dstRect the destination ph_rectangle.
 * \param mask a bitfield specifying what attachments to blit.
 * \param filter the filter to apply for this operation.
 */
HOU_GFX_API void blit(const FrameBuffer& src, const recti& srcRect,
  FrameBuffer& dst, const recti& dstRect, FrameBufferBlitMask mask,
  FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

/** Copies a rectangular region of a FrameBuffer into a texture.
 *
 * The following constraints must be observed, or an exception will be thrown:
 * * src must be complete FrameBuffer object.
 * * If src or dst are multisampled, srcRect and dstRect must have the same
 * size.
 *
 * \param src the source FrameBuffer.
 * \param srcRect the source ph_rectangle.
 * \param dst the destination texture.
 * \param dstRect the destination ph_rectangle.
 * \param filter the filter to apply for this operation.
 */
HOU_GFX_API void blit(const FrameBuffer& src, const recti& srcRect,
  Texture& dst, const recti& dstRect,
  FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

/** Copies a rectangular region of a texture into a FrameBuffer.
 *
 * The following constraints must be observed, or an exception will be thrown:
 * * dst must be complete FrameBuffer object.
 * * If src or dst are multisampled, srcRect and dstRect must have the same
 * size.
 *
 * \param src the source texture.
 * \param srcRect the source ph_rectangle.
 * \param dst the destination FrameBuffer.
 * \param dstRect the destination ph_rectangle.
 * \param filter the filter to apply for this operation.
 */
HOU_GFX_API void blit(const Texture& src, const recti& srcRect,
  FrameBuffer& dst, const recti& dstRect,
  FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

/** Copies a rectangular region of a texture into a FrameBuffer.
 *
 * The following constraints must be observed, or an exception will be thrown:
 * * dst must be complete FrameBuffer object.
 * * If src or dst are multisampled, srcRect and dstRect must have the same
 * size.
 *
 * \param src the source texture.
 * \param srcRect the source ph_rectangle.
 * \param dst the destination texture.
 * \param dstRect the destination ph_rectangle.
 * \param filter the filter to apply for this operation.
 */
HOU_GFX_API void blit(const Texture& src, const recti& srcRect, Texture& dst,
  const recti& dstRect,
  FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

}  // namespace hou

#endif
