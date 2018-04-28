// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/RenderCanvas.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/gl/GlError.hpp"

#include "hou/sys/Color.hpp"

#include <algorithm>

using namespace hou;



namespace
{

class TestRenderCanvas : public TestGfxBase
{};

class TestRenderCanvasDeathTest : public TestRenderCanvas
{};



Image2RGBA generateBlitResultImage(const vec2u& dstSize, const recti& dstRect,
  const Color& dstColor, const Color& srcColor);



Image2RGBA generateBlitResultImage(const vec2u& dstSize, const recti& dstRect,
  const Color& dstColor, const Color& srcColor)
{
  Image2RGBA imRef(dstSize);
  imRef.clear(Image2RGBA::Pixel(dstColor.getRed(), dstColor.getGreen(),
    dstColor.getBlue(), dstColor.getAlpha()));

  uint xMax = std::min(static_cast<uint>(dstRect.r()), dstSize.x());
  uint yMax = std::min(static_cast<uint>(dstRect.b()), dstSize.y());
  for(uint y = dstRect.t(); y < yMax; ++y)
  {
    for(uint x = dstRect.l(); x < xMax; ++x)
    {
      imRef.setPixel(vec2u(x, y),
        Image2RGBA::Pixel(srcColor.getRed(), srcColor.getGreen(),
          srcColor.getBlue(), srcColor.getAlpha()));
    }
  }
  return imRef;
}

}  // namespace



TEST_F(TestRenderCanvas, Creation)
{
  vec2u size(3u, 4u);
  uint samples = 1u;
  RenderCanvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_FALSE(rs.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(),
    rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, CreationErrorZeroSamples)
{
  vec2u size(3u, 4u);
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(size, 0u));
}



TEST_F(TestRenderCanvas, CreationWithAreaGreaterThanMaxTextureSize)
{
  vec2u size(Texture2::getMaxSize().x(), 2u);
  uint samples = 1u;
  RenderCanvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_FALSE(rs.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(),
    rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, CreationMultisampled)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  RenderCanvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_TRUE(rs.isMultisampled());

  RenderCanvas ssrs(size);
  blit(rs, rs.getDefaultViewport(), ssrs, rs.getDefaultViewport());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(),
    ssrs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvasDeathTest, CreationSamplesTooLarge)
{
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(3u, 4u), 40000u));
}



TEST_F(TestRenderCanvasDeathTest, CreationSizeNull)
{
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(0u, 0u), 1u));
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(1u, 0u), 1u));
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(0u, 1u), 1u));
}



TEST_F(TestRenderCanvasDeathTest, CreationSizeTooLarge)
{
  const uint size = gl::getMaxTextureSize() + 1;
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(size, size), 1u));
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(1u, size), 1u));
  HOU_EXPECT_PRECONDITION(RenderCanvas rs(vec2u(size, 1u), 1u));
}



TEST_F(TestRenderCanvas, MoveConstructor)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  RenderCanvas rs1(size, samples);
  RenderCanvas rs2(std::move(rs1));

  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.getDefaultViewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.getViewport());
  EXPECT_EQ(size, rs2.get_size());
  EXPECT_EQ(samples, rs2.getSampleCount());
  EXPECT_TRUE(rs2.isMultisampled());

  RenderCanvas ssrs(size);
  blit(rs2, rs2.getDefaultViewport(), ssrs, rs2.getDefaultViewport());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(),
    ssrs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, Viewport)
{
  vec2u size(3u, 4u);
  RenderCanvas rs(size);
  recti viewport(vec2i(1, 2), vec2i(3, 5));
  rs.setViewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(viewport, rs.getViewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(TestRenderCanvas, NegativeSizeViewport)
{
  vec2u size(3u, 4u);
  RenderCanvas rs(size);
  recti viewport(vec2i(1, -2), vec2i(-3, 5));
  rs.setViewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(viewport, rs.getViewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(TestRenderCanvas, IsMultisampled)
{
  RenderCanvas rs1(vec2u(3u, 4u), 1u);
  RenderCanvas rs2(vec2u(3u, 4u), 2u);

  EXPECT_FALSE(rs1.isMultisampled());
  EXPECT_TRUE(rs2.isMultisampled());
}



TEST_F(TestRenderCanvas, Clear)
{
  vec2u size(3u, 4u);
  RenderCanvas rs(size);
  Color col(4, 6, 2, 78);

  rs.clear(col);

  Image2RGBA imRef(size);
  imRef.clear(Image2RGBA::Pixel(
    col.getRed(), col.getGreen(), col.getBlue(), col.getAlpha()));
  EXPECT_EQ(imRef, rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitFullSize)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti blitRect = rsSrc.getDefaultViewport();
  rsSrc.clear(Color::Red);
  blit(rsSrc, blitRect, rsDst, blitRect);

  EXPECT_EQ(rsSrc.toTexture().getImage<PixelFormat::RGBA>(),
    rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitSmallRect)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti blitRect(vec2i(1, 2), vec2i(2, 1));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, blitRect, rsDst, blitRect);

  Image2RGBA imRef
    = generateBlitResultImage(size, blitRect, Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitDifferentSourceAndDestinationRect)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti srcRect(vec2i(1, 2), vec2i(2, 1));
  recti dstRect(vec2i(0, 1), vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef
    = generateBlitResultImage(size, dstRect, Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitOverFlowingSourceRect)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti srcRect(vec2i(2, 2), vec2i(2, 3));
  recti dstRect(vec2i(0, 0), vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 0, 1, 2), Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitOverFlowingDestinationRect)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(2, 2), vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef
    = generateBlitResultImage(size, dstRect, Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitInvertedSourceRect)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti srcRect(vec2i(0, 1), vec2i(2, -3));
  recti dstRect(vec2i(0, 0), vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 0, 2, 1), Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitInvertedDestinationRect)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size);
  RenderCanvas rsDst(size);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 1), vec2i(2, -3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 0, 2, 1), Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitDifferentSampleSizeSameRectSize)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size, 2u);
  RenderCanvas rsDst(size, 1u);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 0), vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef
    = generateBlitResultImage(size, dstRect, Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, BlitDifferentSampleSizeSameRectSizeInverted)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size, 2u);
  RenderCanvas rsDst(size, 1u);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 4), vec2i(2, -3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  blit(rsSrc, srcRect, rsDst, dstRect);

  Image2RGBA imRef = generateBlitResultImage(
    size, recti(0, 1, 2, 3), Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}


TEST_F(TestRenderCanvasDeathTest, BlitDifferentSampleSizeDifferentRectSize)
{
  vec2u size(3u, 4u);
  RenderCanvas rsSrc(size, 2u);
  RenderCanvas rsDst(size, 1u);

  recti srcRect(vec2i(0, 0), vec2i(2, 3));
  recti dstRect(vec2i(0, 0), vec2i(1, 2));
  rsSrc.clear(Color::Red);
  HOU_EXPECT_PRECONDITION(blit(rsSrc, srcRect, rsDst, dstRect));
}



TEST_F(TestRenderCanvas, ToTextureMultisampled)
{
  RenderCanvas rs(vec2u(3u, 4u), 2u);
  Color col(3, 5, 8, 9);
  rs.clear(col);

  Texture2 tex = rs.toTexture();
  Image2RGBA imRef(tex.get_size(), PixelRGBA(col));
  EXPECT_EQ(imRef, tex.getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderCanvas, SetCurrentRenderSource)
{
  RenderCanvas rs1(vec2u(3u, 4u));
  RenderCanvas rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.isCurrentRenderSource());
  EXPECT_FALSE(rs2.isCurrentRenderSource());
  RenderCanvas::setCurrentRenderSource(rs1);
  EXPECT_TRUE(rs1.isCurrentRenderSource());
  EXPECT_FALSE(rs2.isCurrentRenderSource());
  RenderCanvas::setCurrentRenderSource(rs2);
  EXPECT_FALSE(rs1.isCurrentRenderSource());
  EXPECT_TRUE(rs2.isCurrentRenderSource());
  RenderCanvas::setDefaultRenderSource();
  EXPECT_FALSE(rs1.isCurrentRenderSource());
  EXPECT_FALSE(rs2.isCurrentRenderSource());
}



TEST_F(TestRenderCanvas, SetCurrentRenderTarget)
{
  RenderCanvas rs1(vec2u(3u, 4u));
  RenderCanvas rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.isCurrentRenderTarget());
  EXPECT_FALSE(rs2.isCurrentRenderTarget());
  RenderCanvas::setCurrentRenderTarget(rs1);
  EXPECT_TRUE(rs1.isCurrentRenderTarget());
  EXPECT_FALSE(rs2.isCurrentRenderTarget());
  RenderCanvas::setCurrentRenderTarget(rs2);
  EXPECT_FALSE(rs1.isCurrentRenderTarget());
  EXPECT_TRUE(rs2.isCurrentRenderTarget());
  RenderCanvas::setDefaultRenderTarget();
  EXPECT_FALSE(rs1.isCurrentRenderTarget());
  EXPECT_FALSE(rs2.isCurrentRenderTarget());
}
