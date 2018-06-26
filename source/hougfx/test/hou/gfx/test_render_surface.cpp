// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"
#include "hou/test.hpp"

#include "hou/gfx/render_surface.hpp"
#include "hou/gfx/texture.hpp"

#include "hou/sys/color.hpp"

#include <algorithm>

using namespace hou;



namespace
{

class test_render_surface : public test_gfx_base
{};

class test_render_surface_death_test : public test_render_surface
{};



image2_rgba generate_blit_result_image(const vec2u& dst_size,
  const recti& dst_rect, const color& dst_color, const color& src_color);



image2_rgba generate_blit_result_image(const vec2u& dst_size,
  const recti& dst_rect, const color& dst_color, const color& src_color)
{
  image2_rgba im_ref(dst_size);
  im_ref.clear(image2_rgba::pixel_type(dst_color.get_red(),
    dst_color.get_green(), dst_color.get_blue(), dst_color.get_alpha()));

  uint xMax = std::min(static_cast<uint>(dst_rect.r()), dst_size.x());
  uint yMax = std::min(static_cast<uint>(dst_rect.b()), dst_size.y());
  for(uint y = dst_rect.t(); y < yMax; ++y)
  {
    for(uint x = dst_rect.l(); x < xMax; ++x)
    {
      im_ref.set_pixel(vec2u(x, y),
        image2_rgba::pixel_type(src_color.get_red(), src_color.get_green(),
          src_color.get_blue(), src_color.get_alpha()));
    }
  }
  return im_ref;
}

}  // namespace



TEST_F(test_render_surface, constructor_single_sample)
{
  vec2u size(3u, 4u);
  uint samples = 1u;
  render_surface rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_FALSE(rs.is_multisampled());

  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, constructor_multisampled)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  render_surface rs(size, samples);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
  EXPECT_EQ(samples, rs.get_sample_count());
  EXPECT_TRUE(rs.is_multisampled());

  render_surface ssrs(size);
  blit(rs, rs.get_default_viewport(), ssrs, rs.get_default_viewport());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    ssrs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, constructor_lower_size_limit)
{
  render_surface rs(vec2u(1u, 1u));
  EXPECT_EQ(vec2u(1u, 1u), rs.get_size());
}



TEST_F(test_render_surface, constructor_upper_size_limit)
{
  vec2u max_size = render_surface::get_max_size();
  vec2u max_size_x(max_size.x(), 1u);
  vec2u max_size_y(1u, max_size.y());

  render_surface rs_x(max_size_x);
  EXPECT_EQ(max_size_x, rs_x.get_size());
  render_surface rs_y(max_size_y);
  EXPECT_EQ(max_size_y, rs_y.get_size());
}



TEST_F(test_render_surface_death_test, constructor_error_null_size)
{
  EXPECT_PRECOND_ERROR(render_surface rs(vec2u(0u, 1u)));
  EXPECT_PRECOND_ERROR(render_surface rs(vec2u(1u, 0u)));
  EXPECT_PRECOND_ERROR(render_surface rs(vec2u(0u, 0u)));
}



TEST_F(test_render_surface_death_test, constructor_error_size_too_large)
{
  vec2u max_size = render_surface::get_max_size();
  vec2u wrong_size_x(max_size.x() + 1u, 1u);
  vec2u wrong_size_y(1u, max_size.y() + 1u);
  vec2u wrong_size(max_size.x() + 1u, max_size.y() + 1u);
  EXPECT_PRECOND_ERROR(render_surface rs(wrong_size_x));
  EXPECT_PRECOND_ERROR(render_surface rs(wrong_size_y));
  EXPECT_PRECOND_ERROR(render_surface rs(wrong_size));
}



TEST_F(test_render_surface, constructor_lower_sample_count_limit)
{
  render_surface rs(vec2u(1u, 1u), 1u);
  EXPECT_EQ(1u, rs.get_sample_count());
}



TEST_F(test_render_surface, constructor_upper_sample_count_limit)
{
  render_surface rs(vec2u(1u, 1u), render_surface::get_max_sample_count());
  EXPECT_EQ(render_surface::get_max_sample_count(), rs.get_sample_count());
}



TEST_F(test_render_surface_death_test, constructor_error_zero_samples)
{
  EXPECT_PRECOND_ERROR(render_surface rs(vec2u(1u, 1u), 0u));
}



TEST_F(test_render_surface_death_test, constructor_error_sample_count_too_large)
{
  EXPECT_PRECOND_ERROR(render_surface rs(
    vec2u(1u, 1u), render_surface::get_max_sample_count() + 1u));
}



TEST_F(test_render_surface, move_constructor)
{
  vec2u size(3u, 4u);
  uint samples = 2u;
  render_surface rs1(size, samples);
  render_surface rs2(std::move(rs1));

  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.get_default_viewport());
  EXPECT_EQ(recti(vec2i(0, 0), size), rs2.get_viewport());
  EXPECT_EQ(size, rs2.get_size());
  EXPECT_EQ(samples, rs2.get_sample_count());
  EXPECT_TRUE(rs2.is_multisampled());

  render_surface ssrs(size);
  blit(rs2, rs2.get_default_viewport(), ssrs, rs2.get_default_viewport());
  EXPECT_EQ(texture2(size).get_image<pixel_format::rgba>(),
    ssrs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, viewport)
{
  vec2u size(3u, 4u);
  render_surface rs(size);
  recti viewport(vec2i(1, 2), vec2i(3, 5));
  rs.set_viewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(viewport, rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(test_render_surface, negative_size_viewport)
{
  vec2u size(3u, 4u);
  render_surface rs(size);
  recti viewport(vec2i(1, -2), vec2i(-3, 5));
  rs.set_viewport(viewport);

  EXPECT_EQ(recti(vec2i(0, 0), size), rs.get_default_viewport());
  EXPECT_EQ(viewport, rs.get_viewport());
  EXPECT_EQ(size, rs.get_size());
}



TEST_F(test_render_surface, is_multisampled)
{
  render_surface rs1(vec2u(3u, 4u), 1u);
  render_surface rs2(vec2u(3u, 4u), 2u);

  EXPECT_FALSE(rs1.is_multisampled());
  EXPECT_TRUE(rs2.is_multisampled());
}



TEST_F(test_render_surface, clear)
{
  vec2u size(3u, 4u);
  render_surface rs(size);
  color col(4, 6, 2, 78);

  rs.clear(col);

  image2_rgba im_ref(size);
  im_ref.clear(image2_rgba::pixel_type(
    col.get_red(), col.get_green(), col.get_blue(), col.get_alpha()));
  EXPECT_EQ(im_ref, rs.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_full_size)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti blit_rect = rs_src.get_default_viewport();
  rs_src.clear(color::red());
  blit(rs_src, blit_rect, rs_dst, blit_rect);

  EXPECT_EQ(rs_src.to_texture().get_image<pixel_format::rgba>(),
    rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_small_rect)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti blit_rect(vec2i(1, 2), vec2i(2, 1));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, blit_rect, rs_dst, blit_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, blit_rect, color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_different_source_and_destination_rect)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti src_rect(vec2i(1, 2), vec2i(2, 1));
  recti dst_rect(vec2i(0, 1), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, dst_rect, color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_over_flowing_source_rect)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti src_rect(vec2i(2, 2), vec2i(2, 3));
  recti dst_rect(vec2i(0, 0), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, recti(0, 0, 1, 2), color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_over_flowing_destination_rect)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(2, 2), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, dst_rect, color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_inverted_source_rect)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti src_rect(vec2i(0, 1), vec2i(2, -3));
  recti dst_rect(vec2i(0, 0), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, recti(0, 0, 2, 1), color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_inverted_destination_rect)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size);
  render_surface rs_dst(size);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 1), vec2i(2, -3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, recti(0, 0, 2, 1), color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_different_sample_size_same_rect_size)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size, 2u);
  render_surface rs_dst(size, 1u);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 0), vec2i(2, 3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, dst_rect, color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, blit_different_sample_size_same_rect_size_inverted)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size, 2u);
  render_surface rs_dst(size, 1u);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 4), vec2i(2, -3));
  color blit_col(3, 5, 8, 9);
  rs_src.clear(blit_col);
  blit(rs_src, src_rect, rs_dst, dst_rect);

  image2_rgba im_ref = generate_blit_result_image(
    size, recti(0, 1, 2, 3), color::transparent(), blit_col);
  EXPECT_EQ(im_ref, rs_dst.to_texture().get_image<pixel_format::rgba>());
}


TEST_F(
  test_render_surface_death_test, blit_different_sample_size_different_rect_size)
{
  vec2u size(3u, 4u);
  render_surface rs_src(size, 2u);
  render_surface rs_dst(size, 1u);

  recti src_rect(vec2i(0, 0), vec2i(2, 3));
  recti dst_rect(vec2i(0, 0), vec2i(1, 2));
  rs_src.clear(color::red());
  EXPECT_PRECOND_ERROR(blit(rs_src, src_rect, rs_dst, dst_rect));
}



TEST_F(test_render_surface, to_texture_multisampled)
{
  render_surface rs(vec2u(3u, 4u), 2u);
  color col(3, 5, 8, 9);
  rs.clear(col);

  texture2 tex = rs.to_texture();
  image2_rgba im_ref(tex.get_size(), pixel_rgba(col));
  EXPECT_EQ(im_ref, tex.get_image<pixel_format::rgba>());
}



TEST_F(test_render_surface, set_current_render_source)
{
  render_surface rs1(vec2u(3u, 4u));
  render_surface rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
  render_surface::set_current_render_source(rs1);
  EXPECT_TRUE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
  render_surface::set_current_render_source(rs2);
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_TRUE(rs2.is_current_render_source());
  render_surface::set_default_render_source();
  EXPECT_FALSE(rs1.is_current_render_source());
  EXPECT_FALSE(rs2.is_current_render_source());
}



TEST_F(test_render_surface, set_current_render_target)
{
  render_surface rs1(vec2u(3u, 4u));
  render_surface rs2(vec2u(3u, 4u));
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
  render_surface::set_current_render_target(rs1);
  EXPECT_TRUE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
  render_surface::set_current_render_target(rs2);
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_TRUE(rs2.is_current_render_target());
  render_surface::set_default_render_target();
  EXPECT_FALSE(rs1.is_current_render_target());
  EXPECT_FALSE(rs2.is_current_render_target());
}



TEST_F(test_render_surface, blit_to_window_same_size)
{
  window wnd("TestWindow", vec2u(4u, 4u));
  graphic_context::set_current(wnd);

  render_surface rs_out(wnd.get_size());
  EXPECT_NO_ERROR(rs_out.display());

  graphic_context::set_current(get_default_window());
}



TEST_F(test_render_surface, blit_to_window_different_size)
{
  window wnd("TestWindow", vec2u(4u, 4u));
  graphic_context::set_current(wnd);

  render_surface rs_out(vec2u(2u, 1u));
  EXPECT_NO_ERROR(rs_out.display());

  graphic_context::set_current(get_default_window());
}



TEST_F(test_render_surface, blit_to_window_multisampled_same_size)
{
  window wnd("TestWindow", vec2u(4u, 4u));
  graphic_context::set_current(wnd);

  render_surface rs_out(wnd.get_size(), 2u);
  EXPECT_NO_ERROR(rs_out.display());

  graphic_context::set_current(get_default_window());
}



TEST_F(
  test_render_surface_death_test, blit_to_window_multisampled_different_size)
{
  window wnd("TestWindow", vec2u(4u, 4u));
  graphic_context::set_current(wnd);

  render_surface rs1(vec2u(2u, 1u), 2u);
  EXPECT_PRECOND_ERROR(rs1.display());

  render_surface rs2(vec2u(6u, 6u), 2u);
  EXPECT_PRECOND_ERROR(rs2.display());

  graphic_context::set_current(get_default_window());
}
