// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/RenderSurface.hpp"

#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/gl/GlFunctions.hpp"

#include "hou/sys/Color.hpp"



namespace hou
{

void RenderSurface::setCurrentRenderSource(const RenderSurface& rs)
{
  FrameBuffer::bindReadTarget(rs.mFrameBuffer);
}



void RenderSurface::setDefaultRenderSource()
{
  FrameBuffer::unbindReadTarget();
}



void RenderSurface::setCurrentRenderTarget(const RenderSurface& rs)
{
  gl::setViewport(
    rs.mViewport.x(), rs.mViewport.y(), rs.mViewport.w(), rs.mViewport.h());
  FrameBuffer::bindDrawTarget(rs.mFrameBuffer);
}



void RenderSurface::setDefaultRenderTarget()
{
  FrameBuffer::unbindDrawTarget();
}



vec2u RenderSurface::getMaxSize()
{
  return AttachmentType::getMaxSize();
}



uint RenderSurface::getMaxSampleCount()
{
  return MultisampledAttachmentType::getMaxSampleCount();
}



RenderSurface::RenderSurface(const vec2u& size, uint sampleCount)
  : non_copyable()
  , mFrameBuffer()
  , mColorAttachment(nullptr)
  , mDepthStencilAttachment(nullptr)
  , mSampleCount(sampleCount)
  , mViewport(recti(0, 0, size.x(), size.y()))
{
  buildFramebuffer(size, sampleCount);
}



RenderSurface::RenderSurface(RenderSurface&& other)
  : non_copyable()
  , mFrameBuffer(std::move(other.mFrameBuffer))
  , mColorAttachment(std::move(other.mColorAttachment))
  , mDepthStencilAttachment(std::move(other.mDepthStencilAttachment))
  , mSampleCount(std::move(other.mSampleCount))
  , mViewport(std::move(other.mViewport))
{}



RenderSurface::~RenderSurface()
{}



recti RenderSurface::getDefaultViewport() const
{
  return recti(vec2i(0, 0), get_size());
}



const recti& RenderSurface::getViewport() const
{
  return mViewport;
}



void RenderSurface::setViewport(const recti& viewport)
{
  mViewport = viewport;
}



vec2u RenderSurface::get_size() const
{
  HOU_EXPECT_DEV(mColorAttachment != nullptr);
  return mColorAttachment->getSize2();
}



bool RenderSurface::isMultisampled() const
{
  return mSampleCount > 1u;
}



uint RenderSurface::getSampleCount() const
{
  return mSampleCount;
}



void RenderSurface::clear(const Color& color)
{
  setCurrentRenderTarget(*this);

  gl::setClearColor(
    color.getRedf(), color.getGreenf(), color.getBluef(), color.getAlphaf());
  gl::setClearDepth(1.f);
  gl::setClearStencil(0u);
  gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}



Texture2 RenderSurface::toTexture() const
{
  Texture2 tex(get_size());
  recti blitRect(vec2i::zero(), static_cast<vec2i>(get_size()));
  blit(mFrameBuffer, blitRect, tex, blitRect, FrameBufferBlitFilter::Nearest);
  return tex;
}



bool RenderSurface::isCurrentRenderSource() const
{
  return mFrameBuffer.isBoundToReadTarget();
}



bool RenderSurface::isCurrentRenderTarget() const
{
  return mFrameBuffer.isBoundToDrawTarget();
}



void RenderSurface::buildFramebuffer(const vec2u& size, uint sampleCount)
{
  HOU_ENSURE_DEV(GraphicContext::getRenderingColorByteCount() == 4u);
  HOU_ENSURE_DEV(GraphicContext::getRenderingDepthByteCount() == 3u);
  HOU_ENSURE_DEV(GraphicContext::getRenderingStencilByteCount() == 1u);
  HOU_EXPECT(sampleCount > 0u);

  mSampleCount = sampleCount;
  if(sampleCount <= 1)
  {
    static constexpr uint mipMapLevelCount = 1u;
    mColorAttachment
      = std::make_unique<Texture2>(size, TextureFormat::RGBA, mipMapLevelCount);
    mDepthStencilAttachment = std::make_unique<Texture2>(
      size, TextureFormat::DepthStencil, mipMapLevelCount);
  }
  else
  {
    static constexpr bool fixedSampleLocations = true;
    mColorAttachment = std::make_unique<MultisampleTexture2>(
      size, TextureFormat::RGBA, sampleCount, fixedSampleLocations);
    mDepthStencilAttachment = std::make_unique<MultisampleTexture2>(
      size, TextureFormat::DepthStencil, sampleCount, fixedSampleLocations);
  }
  HOU_ENSURE_DEV(mColorAttachment != nullptr);
  HOU_ENSURE_DEV(mDepthStencilAttachment != nullptr);

  static constexpr uint attachmentPoint = 0u;
  static constexpr uint mipMapLevel = 0u;
  mFrameBuffer.setColorAttachment(
    attachmentPoint, *mColorAttachment, mipMapLevel);
  mFrameBuffer.setDepthStencilAttachment(*mDepthStencilAttachment, mipMapLevel);

  HOU_ENSURE_DEV(mFrameBuffer.isComplete());
}



void blit(const RenderSurface& src, const recti& srcRect, RenderSurface& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  blit(src.mFrameBuffer, srcRect, dst.mFrameBuffer, dstRect,
    FrameBufferBlitMask::All, filter);
}



void blit(const RenderSurface& src, const recti& srcRect, Texture& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  blit(src.mFrameBuffer, srcRect, dst, dstRect, filter);
}



void blit(const Texture& src, const recti& srcRect, RenderSurface& dst,
  const recti& dstRect, FrameBufferBlitFilter filter)
{
  blit(src, srcRect, dst.mFrameBuffer, dstRect, filter);
}

}  // namespace hou
