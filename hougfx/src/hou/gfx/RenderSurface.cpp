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



RenderSurface::RenderSurface(const Vec2u& size, uint sampleCount)
  : NonCopyable()
  , mFrameBuffer()
  , mColorAttachment(nullptr)
  , mDepthStencilAttachment(nullptr)
  , mSampleCount(sampleCount)
  , mViewport(Recti(0, 0, size.x(), size.y()))
{
  buildFramebuffer(size, sampleCount);
}



RenderSurface::RenderSurface(RenderSurface&& other)
  : NonCopyable()
  , mFrameBuffer(std::move(other.mFrameBuffer))
  , mColorAttachment(std::move(other.mColorAttachment))
  , mDepthStencilAttachment(std::move(other.mDepthStencilAttachment))
  , mSampleCount(std::move(other.mSampleCount))
  , mViewport(std::move(other.mViewport))
{}



RenderSurface::~RenderSurface()
{}



Recti RenderSurface::getDefaultViewport() const
{
  return Recti(Vec2i(0, 0), getSize());
}



const Recti& RenderSurface::getViewport() const
{
  return mViewport;
}



void RenderSurface::setViewport(const Recti& viewport)
{
  mViewport = viewport;
}



Vec2u RenderSurface::getSize() const
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



void RenderSurface::setSampleCount(uint sampleCount)
{
  buildFramebuffer(getSize(), sampleCount);
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
  Texture2 tex(getSize());
  Recti blitRect(Vec2i::zero(), static_cast<Vec2i>(getSize()));
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



void RenderSurface::buildFramebuffer(const Vec2u& size, uint sampleCount)
{
  HOU_ENSURE_DEV(GraphicContext::getRenderingColorByteCount() == 4u);
  HOU_ENSURE_DEV(GraphicContext::getRenderingDepthByteCount() == 3u);
  HOU_ENSURE_DEV(GraphicContext::getRenderingStencilByteCount() == 1u);

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



void blit(const RenderSurface& src, const Recti& srcRect, RenderSurface& dst,
  const Recti& dstRect)
{
  blit(src.mFrameBuffer, srcRect, dst.mFrameBuffer, dstRect,
    FrameBufferBlitMask::All, FrameBufferBlitFilter::Nearest);
}

}  // namespace hou
