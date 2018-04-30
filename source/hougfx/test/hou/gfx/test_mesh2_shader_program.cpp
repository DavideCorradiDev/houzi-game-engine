// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/render_canvas.hpp"
#include "hou/gfx/vertex2.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"

using namespace hou;



namespace
{

class TestMesh2ShaderProgram : public test_gfx_base
{};

image2RGBA generateResultImage(const vec2u& dstSize, const recti& dstRect,
  const color& dstColor, const color& srcColor);



image2RGBA generateResultImage(const vec2u& dstSize, const recti& dstRect,
  const color& dstColor, const color& srcColor)
{
  image2RGBA im_ref(dstSize);
  im_ref.clear(image2RGBA::pixel(dstColor));

  uint xMax = std::min(static_cast<uint>(dstRect.r()), dstSize.x());
  uint yMax = std::min(static_cast<uint>(dstRect.b()), dstSize.y());
  for(uint y = dstRect.t(); y < yMax; ++y)
  {
    for(uint x = dstRect.l(); x < xMax; ++x)
    {
      im_ref.set_pixel(vec2u(x, y), image2RGBA::pixel(srcColor));
    }
  }
  return im_ref;
}

}  // namespace



TEST_F(TestMesh2ShaderProgram, Creation)
{
  mesh2_shader_program sp;
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, MoveConstructor)
{
  mesh2_shader_program sp_dummy;
  mesh2_shader_program sp(std::move(sp_dummy));
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetColor)
{
  mesh2_shader_program sp;
  sp.set_color(color::red);
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetTextureUnit)
{
  mesh2_shader_program sp;
  sp.set_texture_unit(1u);
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, SetTransform)
{
  mesh2_shader_program sp;
  sp.set_transform(trans2f::translation(vec2f(2.f, 3.f)));
  SUCCEED();
}



TEST_F(TestMesh2ShaderProgram, DrawRectangle)
{
  mesh2_shader_program mr;
  vec2u size(4u, 6u);
  render_canvas rt(size);
  mesh2 rect = create_rectangle_mesh2(vec2f(2.f, 3.f));
  color col(20u, 30u, 40u, 255u);
  trans2f t
    = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
    * trans2f::translation(vec2f(1.f, 2.f));

  mr.draw(rt, rect, col, t);

  image2RGBA im_ref
    = generateResultImage(size, recti(1, 2, 2, 3), color::transparent, col);
  EXPECT_EQ(im_ref, rt.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(TestMesh2ShaderProgram, DrawTexturedRectangle)
{
  mesh2_shader_program mr;
  vec2u size(8u, 10u);
  render_canvas rt(size);
  mesh2 rect = create_rectangle_mesh2(vec2f(3.f, 4.f));
  image2RGBA ph_image(vec2u(3u, 4u));
  color col(20u, 30u, 40u, 255u);
  ph_image.clear(image2RGBA::pixel(col));
  texture2 tex(ph_image);
  trans2f t
    = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
    * trans2f::translation(vec2f(1.f, 2.f));

  mr.draw(rt, rect, tex, color::white, t);

  image2RGBA im_ref
    = generateResultImage(size, recti(1, 2, 3, 4), color::transparent, col);
  EXPECT_EQ(im_ref, rt.to_texture().get_image<pixel_format::rgba>());
}
