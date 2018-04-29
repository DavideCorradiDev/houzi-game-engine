// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/RenderSurface.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/sys/color.hpp"



namespace hou
{

void RenderSurface::setCurrentRenderSource(const RenderSurface& rs)
{
  framebuffer::bind_read_target(rs.mFrameBuffer);
}



void RenderSurface::setDefaultRenderSource()
{
  framebuffer::unbind_read_target();
}



void RenderSurface::setCurrentRenderTarget(const RenderSurface& rs)
{
  gl::set_viewport(
    rs.mViewport.x(), rs.mViewport.y(), rs.mViewport.w(), rs.mViewport.h());
  framebuffer::bind_draw_target(rs.mFrameBuffer);
}



void RenderSurface::setDefaultRenderTarget()
{
  framebuffer::unbind_draw_target();
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
  , m_sample_count(sampleCount)
  , mViewport(recti(0, 0, size.x(), size.y()))
{
  buildFramebuffer(size, sampleCount);
}



RenderSurface::RenderSurface(RenderSurface&& other)
  : non_copyable()
  , mFrameBuffer(std::move(other.mFrameBuffer))
  , mColorAttachment(std::move(other.mColorAttachment))
  , mDepthStencilAttachment(std::move(other.mDepthStencilAttachment))
  , m_sample_count(std::move(other.m_sample_count))
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



void RenderSurface::set_viewport(const recti& viewport)
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
  return m_sample_count > 1u;
}



uint RenderSurface::get_sample_count() const
{
  return m_sample_count;
}



void RenderSurface::clear(const color& ph_color)
{
  setCurrentRenderTarget(*this);

  gl::set_clear_color(
    ph_color.get_red_f(), ph_color.get_green_f(), ph_color.get_blue_f(), ph_color.get_alpha_f());
  gl::set_clear_depth(1.f);
  gl::set_clear_stencil(0u);
  gl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}



Texture2 RenderSurface::toTexture() const
{
  Texture2 tex(get_size());
  recti blitRect(vec2i::zero(), static_cast<vec2i>(get_size()));
  blit(mFrameBuffer, blitRect, tex, blitRect, framebuffer_blit_filter::nearest);
  return tex;
}



bool RenderSurface::isCurrentRenderSource() const
{
  return mFrameBuffer.is_bound_to_read_target();
}



bool RenderSurface::isCurrentRenderTarget() const
{
  return mFrameBuffer.is_bound_to_draw_target();
}



void RenderSurface::buildFramebuffer(const vec2u& size, uint sampleCount)
{
  HOU_ENSURE_DEV(graphic_context::get_rendering_color_byte_count() == 4u);
  HOU_ENSURE_DEV(graphic_context::get_rendering_depth_byte_count() == 3u);
  HOU_ENSURE_DEV(graphic_context::get_rendering_stencil_byte_count() == 1u);
  HOU_EXPECT(sampleCount > 0u);

  m_sample_count = sampleCount;
  if(sampleCount <= 1)
  {
    static constexpr uint mipMapLevelCount = 1u;
    mColorAttachment
      = std::make_unique<Texture2>(size, TextureFormat::rgba, mipMapLevelCount);
    mDepthStencilAttachment = std::make_unique<Texture2>(
      size, TextureFormat::DepthStencil, mipMapLevelCount);
  }
  else
  {
    static constexpr bool fixedSampleLocations = true;
    mColorAttachment = std::make_unique<MultisampleTexture2>(
      size, TextureFormat::rgba, sampleCount, fixedSampleLocations);
    mDepthStencilAttachment = std::make_unique<MultisampleTexture2>(
      size, TextureFormat::DepthStencil, sampleCount, fixedSampleLocations);
  }
  HOU_ENSURE_DEV(mColorAttachment != nullptr);
  HOU_ENSURE_DEV(mDepthStencilAttachment != nullptr);

  static constexpr uint attachmentPoint = 0u;
  static constexpr uint mipMapLevel = 0u;
  mFrameBuffer.set_color_attachment(
    attachmentPoint, *mColorAttachment, mipMapLevel);
  mFrameBuffer.set_depth_stencil_attachment(*mDepthStencilAttachment, mipMapLevel);

  HOU_ENSURE_DEV(mFrameBuffer.is_complete());
}



void blit(const RenderSurface& src, const recti& srcRect, RenderSurface& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  blit(src.mFrameBuffer, srcRect, dst.mFrameBuffer, dstRect,
    framebuffer_blit_mask::all, filter);
}



void blit(const RenderSurface& src, const recti& srcRect, Texture& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  blit(src.mFrameBuffer, srcRect, dst, dstRect, filter);
}



void blit(const Texture& src, const recti& srcRect, RenderSurface& dst,
  const recti& dstRect, framebuffer_blit_filter filter)
{
  blit(src, srcRect, dst.mFrameBuffer, dstRect, filter);
}

}  // namespace hou
