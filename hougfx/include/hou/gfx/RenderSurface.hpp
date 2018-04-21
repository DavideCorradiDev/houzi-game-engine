// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_SURFACE_HPP
#define HOU_GFX_RENDER_SURFACE_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/gfx/FrameBuffer.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/mth/MatrixFwd.hpp"
#include "hou/mth/Rectangle.hpp"

#include <memory>



namespace hou
{

class Color;

/** Abstract base class for surfaces that can be rendered onto.
 */
class HOU_GFX_API RenderSurface : public NonCopyable
{
public:
  /** Makes this RenderSurface the current render source.
   *
   *  \param rs the render surface.
   */
  static void setCurrentRenderSource(const RenderSurface& rs);

  /** Sets the default render surface as the render source.
   *
   *  The default render source is that of the currently bound window.
   */
  static void setDefaultRenderSource();

  /** Makes this RenderSurface the current render target.
   *
   *  \param rs the render surface.
   */
  static void setCurrentRenderTarget(const RenderSurface& rs);

  /** Sets the default render surface as the render target.
   *
   *  The default render target is that of the currently bound window.
   */
  static void setDefaultRenderTarget();

  /** Retrieves the maximum allowed size for the render surface..
   *
   * \return a vector containing the maximum size on each dimension.
   */
  static Vec2u getMaxSize();

  /** Retrieves the maximum amount of samples per pixel.
   *
   * \return the maximum amount of samples per pixel.
   */
  static uint getMaxSampleCount();

public:
  /** Builds a RenderSurface with the given size and sample count.
   *
   *  Throws if the required sample count is larger than the maximum supported
   * or 0. Throws if the required area of the surface is 0. Throws if the
   * required area is larger than the maximum supported texture size.
   *
   *  \param size the size.
   *  \param sampleCount the sample count.
   */
  RenderSurface(const Vec2u& size, uint sampleCount = 1u);

  /** Move constructor.
   *
   *  \param other the other RenderSurface.
   */
  RenderSurface(RenderSurface&& other);

  /** Destructor.
   */
  virtual ~RenderSurface() = 0;

  /** Gets the default viewport rectangle.
   *
   *  The default viewport rectangle has the top left corner at the origin
   *  and side lengths equal to the size of the RenderSurface.
   *
   *  \return the default viewport rectangle.
   */
  Recti getDefaultViewport() const;

  /** Gets the current viewport rectangle.
   *
   *  The viewport rectangle represents the area of the RenderSurface which is
   *  drawn onto.
   *  For a newly created RenderSurface the viewport rectangle is the default
   *  viewport rectangle.
   *
   *  \return the current viewport rectangle.
   */
  const Recti& getViewport() const;

  /** Sets the current viewport rectangle.
   *
   *  \param viewport the desired viewport rectangle.
   */
  void setViewport(const Recti& viewport);

  /** Gets the size of the RenderSurface.
   *
   *  \return the size of the render surface.
   */
  Vec2u getSize() const;

  /** Checks if the RenderSurface is multisampled.
   *
   *  \return true if the number of samples of the RenderSurface is greater than
   *  one.
   */
  bool isMultisampled() const;

  /** Gets the number of samples of the RenderSurface.
   *
   *  \return the number of samples of the RenderSurface.
   */
  uint getSampleCount() const;

  /** Clears the RenderSurface to the desired color.
   *
   *  \param color the desired color.
   */
  void clear(const Color& color);

  /** Creates a Texture2 from this RenderSurface.
   *
   *  The generated Texture2 has RGBA format.
   *  Throws if the RenderSurface is multisampled. Only single sampled
   *  RenderSurface objects can be converted to textures.
   *
   *  \return the Texture2 create from this RenderSurface.
   */
  Texture2 toTexture() const;

  /** Checks if this RenderSurface is the current render source.
   *
   *  \return true if this is the current render source.
   */
  bool isCurrentRenderSource() const;

  /** Checks if this RenderSurface is the current render target.
   *
   *  \return true if this is the current render target.
   */
  bool isCurrentRenderTarget() const;

  /** Blits the RenderSurface onto another RenderSurface.
   *
   *  Throws if blitting is performed between two RenderSurface objects with
   *  different sample count and source and destination rectangles with
   *  different size.
   *  Blitting between two RenderSurface objects with different sample count
   *  but source and destination rectangle with the same size, or with
   *  source and destination rectangle with same size but different sample count
   *  is possible.
   *  If the size of the source and destination rectangle is the same but
   *  inverted, it counts as the same for the purpose of this check.
   *
   *  \param dst the destination RenderSurface.
   *  \param srcRect the source rectangle of the blit operation.
   *  \param dstRect the destination rectangle of the blit operation.
   */
  friend HOU_GFX_API void blit(const RenderSurface& src, const Recti& srcRect,
    RenderSurface& dst, const Recti& dstRect,
    FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

  friend HOU_GFX_API void blit(const RenderSurface& src, const Recti& srcRect,
    Texture& dst, const Recti& dstRect,
    FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

  friend HOU_GFX_API void blit(const Texture& src, const Recti& srcRect,
    RenderSurface& dst, const Recti& dstRect,
    FrameBufferBlitFilter filter = FrameBufferBlitFilter::Nearest);

protected:
  void buildFramebuffer(const Vec2u& size, uint sampleCount);

private:
  using AttachmentType = Texture2;
  using MultisampledAttachmentType = MultisampleTexture2;

private:
  FrameBuffer mFrameBuffer;
  std::unique_ptr<Texture> mColorAttachment;
  std::unique_ptr<Texture> mDepthStencilAttachment;
  uint mSampleCount;
  Recti mViewport;
};

}  // namespace hou

#endif
