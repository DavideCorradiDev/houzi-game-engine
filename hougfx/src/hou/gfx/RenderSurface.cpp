// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/RenderSurface.hpp"

#include "hou/gfx/GraphicContext.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/gl/GlUtils.hpp"

#include "hou/sys/Color.hpp"



namespace hou
{

void RenderSurface::setCurrentRenderSource(const RenderSurface& rs)
{
  FrameBuffer::bind(rs.mFrameBuffer, FrameBufferTarget::Read);
}



void RenderSurface::setDefaultRenderSource()
{
  FrameBuffer::unbind(FrameBufferTarget::Read);
}



void RenderSurface::setCurrentRenderTarget(const RenderSurface& rs)
{
  gl::setViewport(
    rs.mViewport.x(), rs.mViewport.y(), rs.mViewport.w(), rs.mViewport.h());
  FrameBuffer::bind(rs.mFrameBuffer, FrameBufferTarget::Draw);
}



void RenderSurface::setDefaultRenderTarget()
{
  FrameBuffer::unbind(FrameBufferTarget::Draw);
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



void RenderSurface::setSize(const Vec2u& size)
{
  buildFramebuffer(size, mSampleCount);
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
  HOU_EXPECT(!isMultisampled());
  setCurrentRenderSource(*this);
  Vec2u size = getSize();
  Texture2 tex(size);
  gl::copyTextureSubImage2d(tex.getHandle(), 0, 0, 0, 0, 0, size.x(), size.y());
  return tex;
}



bool RenderSurface::isCurrentRenderSource() const
{
  return mFrameBuffer.isBound(FrameBufferTarget::Read);
}



bool RenderSurface::isCurrentRenderTarget() const
{
  return mFrameBuffer.isBound(FrameBufferTarget::Draw);
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
