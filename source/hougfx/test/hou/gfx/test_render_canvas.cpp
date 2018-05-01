// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/render_canvas.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/gl/gl_error.hpp"

#include "hou/sys/color.hpp"

#include <algorithm>

using namespace hou;



namespace
{

class test_render_canvas : public test_gfx_base
{};

class test_render_canvas_death_test : public test_render_canvas
{};



image2rgba generate_blit_result_image(const vec2u& dst_size,
  const recti& dst_rect, const color& dst_color, const color& src_color);



image2rgba generate_blit_result_image(const vec2u& dst_size,
  const recti& dst_rect, const color& dst_color, const color& src_color)
{
  image2rgba im_ref(dst_size);
  im_ref.clear(image2rgba::pixel(dst_color.get_red(), dst_color.get_green(),
    dst_color.get_blue(), dst_color.get_alpha()));

  uint xMax = std::min(static_cast<uint>(dst_rect.r()), dst_size.x());
  uint yMax = std::min(static_cast<uint>(dst_rect.b()), dst_size.y());
  for(uint y = dst_rect.t(); y < yMax; ++y)
  {
    for(uint x = dst_rect.l(); x < xMax; ++x)
    {
      im_ref.set_pixel(vec2u(x, y),
        image2rgba::pixel(src_color.get_red(), src_color.get_green(),
          src_color.get_blue(), src_color.get_alpha()));
    }
  }
  return im_ref;
}

}  // namespace



TEST_F(test_render_canvas, creation)
{
  vec2u size(3u, 4u);
  uint samples = 1u;
  render_canvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_FALSE(rs.is_multisampled());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, creation_error_zero_samples)
{
  vec2u size(3u, 4u);
  HOU_EXPECT_PRECONDITION(render_canvas rs(size, 0u));
}



TEST_F(test_render_canvas, creation_with_area_greater_than_max_texture_size)
{
  vec2u size(texture2::get_max_size().x(), 2u);
  uint samples = 1u;
  render_canvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_FALSE(rs.is_multisampled());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, creation_multisampled)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  render_canvas rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_TRUE(rs.is_multisampled());

  render_canvas ssrs(size);
  blit(rs, rs.get_default_viewport(), ssrs, rs.get_default_viewport());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    ssrs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas_death_test, creation_samples_too_large)
{
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(3u, 4u), 40000u));
}



TEST_F(test_render_canvas_death_test, creation_size_null)
{
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(0u, 0u), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(1u, 0u), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(0u, 1u), 1u));
}



TEST_F(test_render_canvas_death_test, creation_size_too_large)
{
  const uint size = gl::get_max_texture_size() + 1;
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(size, size), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(1u, size), 1u));
  HOU_EXPECT_PRECONDITION(render_canvas rs(vec2u(size, 1u), 1u));
}



TEST_F(test_render_canvas, move_constructor)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  render_canvas rs1(size, samples);
  render_canvas rs2(std::move(rs1));

  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.get_viewport());
  EXPECT_EQ(size, rs2.get_size());
  EXPECT_EQ(samples, rs2.get_sample_count());
  EXPECT_TRUE(rs2.is_multisampled());

  render_canvas ssrs(size);
  blit(rs2, rs2.get_default_viewport(), ssrs, rs2.get_default_viewport());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    ssrs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, viewport)
{
  vec2u size(3u, 4u);
  render_canvas rs(size);
  recti viewport(vec2i(1, 2), vec2i(3, 5));
  rs.set_viewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(viewport, rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(test_render_canvas, negative_size_viewport)
{
  vec2u size(3u, 4u);
  render_canvas rs(size);
  recti viewport(vec2i(1, -2), vec2i(-3, 5));
  rs.set_viewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(viewport, rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(test_render_canvas, is_multisampled)
{
  render_canvas rs1(vec2u(3u, 4u), 1u);
  render_canvas rs2(vec2u(3u, 4u), 2u);

  EXPECT_FALSE(rs1.is_multisampled());
  EXPECT_TRUE(rs2.is_multisampled());
}



TEST_F(test_render_canvas, clear)
{
  vec2u size(3u, 4u);
  render_canvas rs(size);
  color col(4, 6, 2, 78);

  rs.clear(col);

  image2rgba im_ref(size);
  im_ref.clear(image2rgba::pixel(
    col.get_red(), col.get_green(), col.get_blue(), col.get_alpha()));
  EXPECT_EQ(im_ref, rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_full_size)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti blit_rect = rs_src.get_default_viewport();
  rs_src.clear(color::red);
  blit(rs_src, blit_rect, rs_dst, blit_rect);

  EXPECT_EQ(rs_src.to_texture().get_image<pixel_format::rgba>(),
    rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_small_rect)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti blit_rect(vec2i(1, 2), vec2i(2, 1));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, blit_rect, rs_dst, blit_rect);

  image2rgba im_ref
    = generate_blit_result_image(size, blit_rect, color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_different_source_and_destination_rect)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti src_rect(vec2i(1, 2), vec2i(2, 1));
  recti dst_rect(vec2i(0, 1), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref
    = generate_blit_result_image(size, dst_rect, color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_over_flowing_source_rect)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti src_rect(vec2i(2, 2), vec2i(2, 3));
  recti dst_rect(vec2i(0, 0), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref = generate_blit_result_image(
    size, recti(0, 0, 1, 2), color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_over_flowing_destination_rect)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(2, 2), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref
    = generate_blit_result_image(size, dst_rect, color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_inverted_source_rect)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti src_rect(vec2i(0, 1), vec2i(2, -3));
  recti dst_rect(vec2i(0, 0), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref = generate_blit_result_image(
    size, recti(0, 0, 2, 1), color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_inverted_destination_rect)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size);
  render_canvas rs_dst(size);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 1), vec2i(2, -3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref = generate_blit_result_image(
    size, recti(0, 0, 2, 1), color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_different_sample_size_same_rect_size)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size, 2u);
  render_canvas rs_dst(size, 1u);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 0), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref
    = generate_blit_result_image(size, dst_rect, color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, blit_different_sample_size_same_rect_size_inverted)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size, 2u);
  render_canvas rs_dst(size, 1u);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 4), vec2i(2, -3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2rgba im_ref = generate_blit_result_image(
    size, recti(0, 1, 2, 3), color::transparent, blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}


TEST_F(test_render_canvas_death_test, blit_different_sample_size_different_rect_size)
{
  vec2u size(3u, 4u);
  render_canvas rs_src(size, 2u);
  render_canvas rs_dst(size, 1u);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 0), vec2i(1, 2));
  rs_src.clear(color::red);
  HOU_EXPECT_PRECONDITION(blit(rs_src, src_rect, rs_dst, dst_rect));
}



TEST_F(test_render_canvas, to_texture_multisampled)
{
  render_canvas rs(vec2u(3u, 4u), 2u);
  color col(3, 5, 8, 9);
  rs.clear(col);

  texture2 tex = rs.to_texture();
  image2rgba im_ref(tex.get_size(), pixelrgba(col));
  EXPECT_EQ(im_ref, tex.get_image<pixel_format::rgba>());
}



TEST_F(test_render_canvas, set_current_render_source)
{
  render_canvas rs1(vec2u(3u, 4u));
  render_canvas rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
  render_canvas::set_current_render_source(rs1);
  EXPECT_TRUE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
  render_canvas::set_current_render_source(rs2);
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_TRUE(rs2.is_current_render_source());
  render_canvas::set_default_render_source();
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
}



TEST_F(test_render_canvas, set_current_render_target)
{
  render_canvas rs1(vec2u(3u, 4u));
  render_canvas rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
  render_canvas::set_current_render_target(rs1);
  EXPECT_TRUE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
  render_canvas::set_current_render_target(rs2);
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_TRUE(rs2.is_current_render_target());
  render_canvas::set_default_render_target();
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
}
