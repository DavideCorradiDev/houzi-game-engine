// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Mesh.hpp"
#include "hou/gfx/Mesh2ShaderProgram.hpp"
#include "hou/gfx/RenderCanvas.hpp"
#include "hou/gfx/Vertex2.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"

using namespace hou;



namespace
{

class TestMesh2ShaderProgram : public TestGfxBase
{};

image2RGBA generateResultImage(const vec2u& dstSize, const recti& dstRect,
  const color& dstColor, const color& srcColor);



image2RGBA generateResultImage(const vec2u& dstSize, const recti& dstRect,
  const color& dstColor, const color& srcColor)
{
  image2RGBA imRef(dstSize);
  imRef.clear(image2RGBA::pixel(dstColor));

  uint xMax = std::min(static_cast<uint>(dstRect.r()), dstSize.x());
  uint yMax = std::min(static_cast<uint>(dstRect.b()), dstSize.y());
  for(uint y = dstRect.t(); y < yMax; ++y)
  {
    for(uint x = dstRect.l(); x < xMax; ++x)
    {
      imRef.set_pixel(vec2u(x, y), image2RGBA::pixel(srcColor));
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
  sp.set_color(color::red);
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
  sp.setTransform(trans2f::translation(vec2f(2.f, 3.f)));
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, DrawRectangle)
{
  Mesh2ShaderProgram mr;
  vec2u size(4u, 6u);
  RenderCanvas rt(size);
  Mesh2 rect = createRectangleMesh2(vec2f(2.f, 3.f));
  color col(20u, 30u, 40u, 255u);
  trans2f t
    = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
    * trans2f::translation(vec2f(1.f, 2.f));

  mr.draw(rt, rect, col, t);

  image2RGBA imRef
    = generateResultImage(size, recti(1, 2, 2, 3), color::transparent, col);
  EXPECT_EQ(imRef, rt.toTexture().get_image<pixel_format::rgba>());
}



TEST_F(TestMesh2ShaderProgram, DrawTexturedRectangle)
{
  Mesh2ShaderProgram mr;
  vec2u size(8u, 10u);
  RenderCanvas rt(size);
  Mesh2 rect = createRectangleMesh2(vec2f(3.f, 4.f));
  image2RGBA ph_image(vec2u(3u, 4u));
  color col(20u, 30u, 40u, 255u);
  ph_image.clear(image2RGBA::pixel(col));
  Texture2 tex(ph_image);
  trans2f t
    = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
    * trans2f::translation(vec2f(1.f, 2.f));

  mr.draw(rt, rect, tex, color::white, t);

  image2RGBA imRef
    = generateResultImage(size, recti(1, 2, 3, 4), color::transparent, col);
  EXPECT_EQ(imRef, rt.toTexture().get_image<pixel_format::rgba>());
}
