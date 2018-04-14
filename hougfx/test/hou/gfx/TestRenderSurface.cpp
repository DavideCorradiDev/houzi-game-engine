// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/RenderSurface.hpp"
#include "hou/gfx/Texture.hpp"

#include "hou/gl/GlError.hpp"

#include "hou/sys/Color.hpp"

#include <algorithm>

using namespace hou;



namespace
{

class TestRenderSurface : public TestGfxBase {};

class TestRenderSurfaceDeathTest : public TestRenderSurface {};

class ConcreteRenderSurface
  : public RenderSurface
{
public:
  ConcreteRenderSurface(const Vec2u& size, uint samples);
  ConcreteRenderSurface(ConcreteRenderSurface&& other);
  virtual ~ConcreteRenderSurface();

  void setSize(const Vec2u& size) override;
  Texture2 toTexture() const override;
};



ConcreteRenderSurface::ConcreteRenderSurface(const Vec2u& size, uint samples)
  : RenderSurface(size, samples)
{}



ConcreteRenderSurface::ConcreteRenderSurface(ConcreteRenderSurface&& other)
  : RenderSurface(std::move(other))
{}



ConcreteRenderSurface::~ConcreteRenderSurface()
{}



void ConcreteRenderSurface::setSize(const Vec2u& size)
{
  RenderSurface::setSize(size);
}



Texture2 ConcreteRenderSurface::toTexture() const
{
  return RenderSurface::toTexture();
}



Image2RGBA generateBlitResultImage(const Vec2u& dstSize, const Recti& dstRect
  , const Color& dstColor, const Color& srcColor);



Image2RGBA generateBlitResultImage(const Vec2u& dstSize, const Recti& dstRect
  , const Color& dstColor, const Color& srcColor)
{
  Image2RGBA imRef(dstSize);
  imRef.clear(Image2RGBA::Pixel(dstColor.getRed(), dstColor.getGreen(), dstColor.getBlue(), dstColor.getAlpha()));

  uint xMax = std::min(static_cast<uint>(dstRect.r()), dstSize.x());
  uint yMax = std::min(static_cast<uint>(dstRect.b()), dstSize.y());
  for(uint y = dstRect.t(); y < yMax; ++y)
  {
    for(uint x = dstRect.l(); x < xMax; ++x)
    {
      imRef.setPixel(Vec2u(x, y), Image2RGBA::Pixel(srcColor.getRed(), srcColor.getGreen(), srcColor.getBlue(), srcColor.getAlpha()));
    }
  }
  return imRef;
}

}



TEST_F(TestRenderSurface, Creation)
{
  Vec2u size(3u, 4u);
  uint samples = 0u;
  ConcreteRenderSurface rs(size, samples);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_FALSE(rs.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, CreationWithAreaGreaterThanMaxTextureSize)
{
  Vec2u size(Texture2::getMaxSize().x(), 2u);
  uint samples = 0u;
  ConcreteRenderSurface rs(size, samples);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_FALSE(rs.isMultisampled());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, CreationMultisampled)
{
  Vec2u size(3u, 4u);
  uint samples = 2u;
  ConcreteRenderSurface rs(size, samples);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_TRUE(rs.isMultisampled());

  ConcreteRenderSurface ssrs(size, 0);
  rs.blit(ssrs, rs.getDefaultViewport(), rs.getDefaultViewport());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), ssrs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurfaceDeathTest, CreationSamplesTooLarge)
{
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(3u, 4u), 40000u));
}



TEST_F(TestRenderSurfaceDeathTest, CreationSizeNull)
{
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(0u, 0u), 0u));
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(1u, 0u), 0u));
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(0u, 1u), 0u));
}



TEST_F(TestRenderSurfaceDeathTest, CreationSizeTooLarge)
{
  const uint size = gl::getMaxTextureSize() + 1;
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(size, size), 0u));
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(1u, size), 0u));
  HOU_EXPECT_PRECONDITION(ConcreteRenderSurface rs(Vec2u(size, 1u), 0u));
}



TEST_F(TestRenderSurface, MoveConstructor)
{
  Vec2u size(3u, 4u);
  uint samples = 2u;
  ConcreteRenderSurface rs1(size, samples);
  ConcreteRenderSurface rs2(std::move(rs1));

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs2.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs2.getViewport());
  EXPECT_EQ(size, rs2.getSize());
  EXPECT_EQ(samples, rs2.getSampleCount());
  EXPECT_TRUE(rs2.isMultisampled());

  ConcreteRenderSurface ssrs(size, 0);
  rs2.blit(ssrs, rs2.getDefaultViewport(), rs2.getDefaultViewport());
  EXPECT_EQ(Texture2(size).getImage<PixelFormat::RGBA>(), ssrs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, Viewport)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rs(size, 0u);
  Recti viewport(Vec2i(1, 2), Vec2i(3, 5));
  rs.setViewport(viewport);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(viewport, rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
}



TEST_F(TestRenderSurface, NegativeSizeViewport)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rs(size, 0u);
  Recti viewport(Vec2i(1, -2), Vec2i(-3, 5));
  rs.setViewport(viewport);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(viewport, rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
}



TEST_F(TestRenderSurface, Size)
{
  Vec2u originalSize(3u, 4u);
  ConcreteRenderSurface rs(originalSize, 0u);
  Vec2u size(5u, 2u);
  rs.setSize(size);

  EXPECT_EQ(Recti(Vec2i(0, 0), size), rs.getDefaultViewport());
  EXPECT_EQ(Recti(Vec2i(0, 0), originalSize), rs.getViewport());
  EXPECT_EQ(size, rs.getSize());
}



TEST_F(TestRenderSurfaceDeathTest, SetSizeNull)
{
  ConcreteRenderSurface rs(Vec2u(3u, 4u), 0u);
  HOU_EXPECT_PRECONDITION(rs.setSize(Vec2u(0u, 0u)));
  HOU_EXPECT_PRECONDITION(rs.setSize(Vec2u(1u, 0u)));
  HOU_EXPECT_PRECONDITION(rs.setSize(Vec2u(0u, 1u)));
}



TEST_F(TestRenderSurfaceDeathTest, SetSizeTooLarge)
{
  const uint size = gl::getMaxTextureSize() + 1;
  ConcreteRenderSurface rs(Vec2u(3u, 4u), 0u);
  HOU_EXPECT_PRECONDITION(rs.setSize(Vec2u(size, size)));
  HOU_EXPECT_PRECONDITION(rs.setSize(Vec2u(1u, size)));
  HOU_EXPECT_PRECONDITION(rs.setSize(Vec2u(size, 1u)));
}



TEST_F(TestRenderSurface, IsMultisampled)
{
  ConcreteRenderSurface rs(Vec2u(3u, 4u), 0u);

  EXPECT_FALSE(rs.isMultisampled());

  rs.setSampleCount(1u);
  EXPECT_FALSE(rs.isMultisampled());

  rs.setSampleCount(2u);
  EXPECT_TRUE(rs.isMultisampled());
}



TEST_F(TestRenderSurface, SetSamples)
{
  ConcreteRenderSurface rs(Vec2u(3u, 4u), 0u);
  uint samples = 5u;
  rs.setSampleCount(samples);

  EXPECT_EQ(samples, rs.getSampleCount());
  EXPECT_TRUE(rs.isMultisampled());
}



TEST_F(TestRenderSurfaceDeathTest, SetSamplesTooLarge)
{
  ConcreteRenderSurface rs(Vec2u(3u, 4u), 0u);
  HOU_EXPECT_PRECONDITION(rs.setSampleCount(40000));
}



TEST_F(TestRenderSurface, Clear)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rs(size, 0u);
  Color col(4, 6, 2, 78);

  rs.clear(col);

  Image2RGBA imRef(size);
  imRef.clear(Image2RGBA::Pixel(col.getRed(), col.getGreen(), col.getBlue(), col.getAlpha()));
  EXPECT_EQ(imRef, rs.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitFullSize)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti blitRect = rsSrc.getDefaultViewport();
  rsSrc.clear(Color::Red);
  rsSrc.blit(rsDst, blitRect, blitRect);

  EXPECT_EQ(rsSrc.toTexture().getImage<PixelFormat::RGBA>(), rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitSmallRect)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti blitRect(Vec2i(1, 2), Vec2i(2, 1));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, blitRect, blitRect);

  Image2RGBA imRef = generateBlitResultImage(size, blitRect, Color::Transparent
    , blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitDifferentSourceAndDestinationRect)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(1, 2), Vec2i(2, 1));
  Recti dstRect(Vec2i(0, 1), Vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, dstRect, Color::Transparent
    , blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitOverFlowingSourceRect)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(2, 2), Vec2i(2, 3));
  Recti dstRect(Vec2i(0, 0), Vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, Recti(0, 0, 1, 2)
    , Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitOverFlowingDestinationRect)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(0, 0), Vec2i(2, 3));
  Recti dstRect(Vec2i(2, 2), Vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, dstRect, Color::Transparent
    , blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitInvertedSourceRect)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(0, 1), Vec2i(2, -3));
  Recti dstRect(Vec2i(0, 0), Vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, Recti(0, 0, 2, 1)
    , Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitInvertedDestinationRect)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 0u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(0, 0), Vec2i(2, 3));
  Recti dstRect(Vec2i(0, 1), Vec2i(2, -3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, Recti(0, 0, 2, 1)
    , Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitDifferentSampleSizeSameRectSize)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 2u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(0, 0), Vec2i(2, 3));
  Recti dstRect(Vec2i(0, 0), Vec2i(2, 3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, dstRect, Color::Transparent
    , blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderSurface, BlitDifferentSampleSizeSameRectSizeInverted)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 2u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(0, 0), Vec2i(2, 3));
  Recti dstRect(Vec2i(0, 4), Vec2i(2, -3));
  Color blitCol(3, 5, 8, 9);
  rsSrc.clear(blitCol);
  rsSrc.blit(rsDst, srcRect, dstRect);

  Image2RGBA imRef = generateBlitResultImage(size, Recti(0, 1, 2, 3)
    , Color::Transparent, blitCol);
  EXPECT_EQ(imRef, rsDst.toTexture().getImage<PixelFormat::RGBA>());
}


TEST_F(TestRenderSurfaceDeathTest, BlitDifferentSampleSizeDifferentRectSize)
{
  Vec2u size(3u, 4u);
  ConcreteRenderSurface rsSrc(size, 2u);
  ConcreteRenderSurface rsDst(size, 0u);

  Recti srcRect(Vec2i(0, 0), Vec2i(2, 3));
  Recti dstRect(Vec2i(0, 0), Vec2i(1, 2));
  rsSrc.clear(Color::Red);
  HOU_EXPECT_PRECONDITION(rsSrc.blit(rsDst, srcRect, dstRect));
}



TEST_F(TestRenderSurfaceDeathTest, ToTextureMultisampled)
{
  ConcreteRenderSurface rs(Vec2u(3u, 4u), 2u);
  HOU_EXPECT_ERROR(rs.toTexture(), std::logic_error
    , getText(CorError::Precondition));
}



TEST_F(TestRenderSurface, SetCurrentRenderSource)
{
  ConcreteRenderSurface rs1(Vec2u(3u, 4u), 0u);
  ConcreteRenderSurface rs2(Vec2u(3u, 4u), 0u);
  EXPECT_FALSE(rs1.isCurrentRenderSource());
  EXPECT_FALSE(rs2.isCurrentRenderSource());
  RenderSurface::setCurrentRenderSource(rs1);
  EXPECT_TRUE(rs1.isCurrentRenderSource());
  EXPECT_FALSE(rs2.isCurrentRenderSource());
  RenderSurface::setCurrentRenderSource(rs2);
  EXPECT_FALSE(rs1.isCurrentRenderSource());
  EXPECT_TRUE(rs2.isCurrentRenderSource());
  RenderSurface::setDefaultRenderSource();
  EXPECT_FALSE(rs1.isCurrentRenderSource());
  EXPECT_FALSE(rs2.isCurrentRenderSource());
}



TEST_F(TestRenderSurface, SetCurrentRenderTarget)
{
  ConcreteRenderSurface rs1(Vec2u(3u, 4u), 0u);
  ConcreteRenderSurface rs2(Vec2u(3u, 4u), 0u);
  EXPECT_FALSE(rs1.isCurrentRenderTarget());
  EXPECT_FALSE(rs2.isCurrentRenderTarget());
  RenderSurface::setCurrentRenderTarget(rs1);
  EXPECT_TRUE(rs1.isCurrentRenderTarget());
  EXPECT_FALSE(rs2.isCurrentRenderTarget());
  RenderSurface::setCurrentRenderTarget(rs2);
  EXPECT_FALSE(rs1.isCurrentRenderTarget());
  EXPECT_TRUE(rs2.isCurrentRenderTarget());
  RenderSurface::setDefaultRenderTarget();
  EXPECT_FALSE(rs1.isCurrentRenderTarget());
  EXPECT_FALSE(rs2.isCurrentRenderTarget());
}

