// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/mesh2.hpp"
#include "hou/gfx/mesh2_shader_program.hpp"
#include "hou/gfx/render_surface.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"

using namespace hou;



namespace
{

class test_mesh2_shader_program : public test_gfx_base
{};

image2_rgba generate_result_image(const vec2u& dst_size, const recti& dst_rect,
  const color& dst_color, const color& src_color);



image2_rgba generate_result_image(const vec2u& dst_size, const recti& dst_rect,
  const color& dst_color, const color& src_color)
{
  image2_rgba im_ref(dst_size);
  im_ref.clear(image2_rgba::pixel_type(dst_color));

  uint x_max = std::min(static_cast<uint>(dst_rect.r()), dst_size.x());
  uint y_max = std::min(static_cast<uint>(dst_rect.b()), dst_size.y());
  for(uint y = dst_rect.t(); y < y_max; ++y)
  {
    for(uint x = dst_rect.l(); x < x_max; ++x)
    {
      im_ref.set_pixel(vec2u(x, y), image2_rgba::pixel_type(src_color));
    }
  }
  return im_ref;
}

}  // namespace



TEST_F(test_mesh2_shader_program, creation)
{
  mesh2_shader_program sp;
  SUCCEED();
}



TEST_F(test_mesh2_shader_program, move_constructor)
{
  mesh2_shader_program sp_dummy;
  mesh2_shader_program sp(std::move(sp_dummy));
  SUCCEED();
}



TEST_F(test_mesh2_shader_program, set_color)
{
  mesh2_shader_program sp;
  sp.set_color(color::red());
  SUCCEED();
}



TEST_F(test_mesh2_shader_program, set_texture_unit)
{
  mesh2_shader_program sp;
  sp.set_texture_unit(1u);
  SUCCEED();
}



TEST_F(test_mesh2_shader_program, set_transform)
{
  mesh2_shader_program sp;
  sp.set_transform(trans2f::translation(vec2f(2.f, 3.f)));
  SUCCEED();
}



TEST_F(test_mesh2_shader_program, draw_rectangle)
{
  FAIL();
  // mesh2_shader_program mr;
  // vec2u size(4u, 6u);
  // render_surface rt(size);
  // mesh2 rect = create_rectangle_mesh2(vec2f(2.f, 3.f));
  // color col(20u, 30u, 40u, 255u);
  // trans2f t
  //   = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
  //   * trans2f::translation(vec2f(1.f, 2.f));

  // mr.draw(rt, rect, col, t);

  // image2_rgba im_ref
  //   = generate_result_image(size, recti(1, 2, 2, 3), color::transparent(), col);
  // EXPECT_EQ(im_ref, rt.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_mesh2_shader_program, draw_textured_rectangle)
{
  FAIL();
  // mesh2_shader_program mr;
  // vec2u size(8u, 10u);
  // render_surface rt(size);
  // mesh2 rect = create_rectangle_mesh2(vec2f(3.f, 4.f));
  // image2_rgba im(vec2u(3u, 4u));
  // color col(20u, 30u, 40u, 255u);
  // im.clear(image2_rgba::pixel_type(col));
  // texture2 tex(im);
  // trans2f t
  //   = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
  //   * trans2f::translation(vec2f(1.f, 2.f));

  // mr.draw(rt, rect, tex, color::white(), t);

  // image2_rgba im_ref = generate_result_image(
  //   size, recti(1, 2, 3, 4), color::transparent(), col);
  // EXPECT_EQ(im_ref, rt.to_texture().get_image<pixel_format::rgba>());
}
