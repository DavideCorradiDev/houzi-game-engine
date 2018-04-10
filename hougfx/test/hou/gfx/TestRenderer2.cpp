// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/mth/Transform2.hpp"

#include "hou/gfx/Mesh2.hpp"
#include "hou/gfx/Renderer2.hpp"
#include "hou/gfx/RenderTexture.hpp"

#include "hou/sys/Color.hpp"

using namespace hou;



namespace
{

class TestRenderer2 : public TestGfxBase {};

Image2RGBA generateResultImage(const Vec2u& dstSize, const Recti& dstRect
  , const Color& dstColor, const Color& srcColor);



Image2RGBA generateResultImage(const Vec2u& dstSize, const Recti& dstRect
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



TEST_F(TestRenderer2, Creation)
{
  Renderer2 mr;

  SUCCEED();
}



TEST_F(TestRenderer2, MoveConstructor)
{
  Renderer2 mrDummy;
  Renderer2 mr(std::move(mrDummy));

  SUCCEED();
}



TEST_F(TestRenderer2, DrawRectangle)
{
  Renderer2 mr;
  Vec2u size(4u, 6u);
  RenderTexture rt(size, 0u);
  Mesh2 rect = createRectangleMesh2(Vec2f(2.f, 3.f));
  Color col(20u, 30u, 40u, 255u);
  Trans2f t = Trans2f::orthographicProjection(Rectf(0.f, 0.f, size.x(), size.y()))
    * Trans2f::translation(Vec2f(1.f, 2.f));

  mr.draw(rt, rect, col, t);

  Image2RGBA imRef = generateResultImage(size, Recti(1, 2, 2, 3), Color::Transparent
    , col);
  EXPECT_EQ(imRef, rt.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestRenderer2, DrawTexturedRectangle)
{
  Renderer2 mr;
  Vec2u size(8u, 10u);
  RenderTexture rt(size, 0u);
  Mesh2 rect = createRectangleMesh2(Vec2f(3.f, 4.f));
  Image2RGBA image(Vec2u(3u, 4u));
  Color col(20u, 30u, 40u, 255u);
  image.clear(Image2RGBA::Pixel(col.getRed(), col.getGreen(), col.getBlue(), col.getAlpha()));
  Texture2 tex(image);
  Trans2f t = Trans2f::orthographicProjection(Rectf(0.f, 0.f, size.x(), size.y()))
    * Trans2f::translation(Vec2f(1.f, 2.f));

  mr.draw(rt, rect, tex, Color::White, t);

  Image2RGBA imRef = generateResultImage(size, Recti(1, 2, 3, 4), Color::Transparent
    , col);
  EXPECT_EQ(imRef, rt.toTexture().getImage<PixelFormat::RGBA>());
}

