// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"
#include "hou/test.hpp"

#include "hou/gfx/mesh2.hpp"
#include "hou/gfx/mesh2_renderer.hpp"
#include "hou/gfx/render_surface.hpp"

#include "hou/mth/transform2.hpp"

#include "hou/sys/color.hpp"

using namespace hou;



namespace
{

class test_mesh2_renderer : public test_gfx_base
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



TEST_F(test_mesh2_renderer, creation)
{
  mesh2_renderer sp;
  SUCCEED();
}



TEST_F(test_mesh2_renderer, move_constructor)
{
  mesh2_renderer sp_dummy;
  mesh2_renderer sp(std::move(sp_dummy));
  SUCCEED();
}



TEST_F(test_mesh2_renderer, set_color)
{
  mesh2_renderer sp;
  sp.set_color(color::red());
  SUCCEED();
}



TEST_F(test_mesh2_renderer, set_texture_unit)
{
  mesh2_renderer sp;
  sp.set_texture_unit(1u);
  SUCCEED();
}



TEST_F(test_mesh2_renderer, set_transform)
{
  mesh2_renderer sp;
  sp.set_transform(trans2f::translation(vec2f(2.f, 3.f)));
  SUCCEED();
}



TEST_F(test_mesh2_renderer, draw_rectangle)
{
  mesh2_renderer mr;
  vec2u size(4u, 6u);
  render_surface rt(size);
  mesh2 rect = rectangle_mesh2(vec2f(2.f, 3.f));
  color col(20u, 30u, 40u, 255u);
  trans2f t
    = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
    * trans2f::translation(vec2f(1.f, 2.f));

  mr.draw(rt, rect, col, t);

  image2_rgba im_ref
    = generate_result_image(size, recti(1, 2, 2, 3), color::transparent(), col);
  EXPECT_EQ(im_ref, rt.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_mesh2_renderer, draw_textured_rectangle)
{
  mesh2_renderer mr;
  vec2u size(8u, 10u);
  render_surface rt(size);
  mesh2 rect = rectangle_mesh2(vec2f(3.f, 4.f));
  image2_rgba im(vec2u(3u, 4u));
  color col(20u, 30u, 40u, 255u);
  im.clear(image2_rgba::pixel_type(col));
  texture2 tex(im);
  trans2f t
    = trans2f::orthographic_projection(rectf(0.f, 0.f, size.x(), size.y()))
    * trans2f::translation(vec2f(1.f, 2.f));

  mr.draw(rt, rect, tex, color::white(), t);

  image2_rgba im_ref
    = generate_result_image(size, recti(1, 2, 3, 4), color::transparent(), col);
  EXPECT_EQ(im_ref, rt.to_texture().get_image<pixel_format::rgba>());
}
