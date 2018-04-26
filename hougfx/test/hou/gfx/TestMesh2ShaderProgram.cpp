// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/RenderCanvas.hpp"
#include "hou/gfx/Vertex2.hpp"

#include "hou/mth/Transform2.hpp"

#include "hou/sys/Color.hpp"

using namespace hou;



namespace
{

class TestMesh2ShaderProgram : public TestGfxBase
{};

Image2RGBA generateResultImage(const Vec2u& dstSize, const Recti& dstRect,
  const Color& dstColor, const Color& srcColor);



Image2RGBA generateResultImage(const Vec2u& dstSize, const Recti& dstRect,
  const Color& dstColor, const Color& srcColor)
{
  Image2RGBA imRef(dstSize);
  imRef.clear(Image2RGBA::Pixel(dstColor));

  uint xMax = std::min(static_cast<uint>(dstRect.r()), dstSize.x());
  uint yMax = std::min(static_cast<uint>(dstRect.b()), dstSize.y());
  for(uint y = dstRect.t(); y < yMax; ++y)
  {
    for(uint x = dstRect.l(); x < xMax; ++x)
    {
      imRef.setPixel(Vec2u(x, y), Image2RGBA::Pixel(srcColor));
    }
  }
  return imRef;
}

}  // namespace



TEST_F(TestMesh2ShaderProgram, Creation)
{
  Mesh2ShaderProgram sp;
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, MoveConstructor)
{
  Mesh2ShaderProgram spDummy;
  Mesh2ShaderProgram sp(std::move(spDummy));
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetColor)
{
  Mesh2ShaderProgram sp;
  sp.setColor(Color::Red);
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetTextureUnit)
{
  Mesh2ShaderProgram sp;
  sp.setTextureUnit(1u);
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetTransform)
{
  Mesh2ShaderProgram sp;
  sp.setTransform(Trans2f::translation(Vec2f(2.f, 3.f)));
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, DrawRectangle)
{
  Mesh2ShaderProgram mr;
  Vec2u size(4u, 6u);
  RenderCanvas rt(size);
  Mesh2 rect = createRectangleMesh2(Vec2f(2.f, 3.f));
  Color col(20u, 30u, 40u, 255u);
  Trans2f t
    = Trans2f::orthographicProjection(Rectf(0.f, 0.f, size.x(), size.y()))
    * Trans2f::translation(Vec2f(1.f, 2.f));

  mr.draw(rt, rect, col, t);

  Image2RGBA imRef
    = generateResultImage(size, Recti(1, 2, 2, 3), Color::Transparent, col);
  EXPECT_EQ(imRef, rt.toTexture().getImage<PixelFormat::RGBA>());
}



TEST_F(TestMesh2ShaderProgram, DrawTexturedRectangle)
{
  Mesh2ShaderProgram mr;
  Vec2u size(8u, 10u);
  RenderCanvas rt(size);
  Mesh2 rect = createRectangleMesh2(Vec2f(3.f, 4.f));
  Image2RGBA image(Vec2u(3u, 4u));
  Color col(20u, 30u, 40u, 255u);
  image.clear(Image2RGBA::Pixel(col));
  Texture2 tex(image);
  Trans2f t
    = Trans2f::orthographicProjection(Rectf(0.f, 0.f, size.x(), size.y()))
    * Trans2f::translation(Vec2f(1.f, 2.f));

  mr.draw(rt, rect, tex, Color::White, t);

  Image2RGBA imRef
    = generateResultImage(size, Recti(1, 2, 3, 4), Color::Transparent, col);
  EXPECT_EQ(imRef, rt.toTexture().getImage<PixelFormat::RGBA>());
}
