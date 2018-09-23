// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/framebuffer.hpp"
#include "hou/gfx/multisampled_texture2.hpp"
#include "hou/gfx/texture2.hpp"

#include "hou/gl/gl_functions.hpp"

#include "hou/sys/image.hpp"

using namespace hou;



namespace
{

class test_framebuffer : public test_gfx_base
{};

class test_framebuffer_death_test : public test_framebuffer
{};

template <typename SrcTexType, typename DstTexType>
void test_color_blit(texture_format src_format,
  const typename SrcTexType::size_type& src_size, const recti& src_rect,
  texture_format dst_format, const typename DstTexType::size_type& dst_size,
  const recti& dst_rect, framebuffer_blit_filter filter,
  bool test_error = false);

template <typename SrcTexType, typename DstTexType>
void test_color_blit(texture_format src_format,
  const typename SrcTexType::size_type& src_size, const recti& src_rect,
  texture_format dst_format, const typename DstTexType::size_type& dst_size,
  const recti& dst_rect, framebuffer_blit_filter filter, bool test_error)
{
  // Build the framebuffers.
  float src_value_f = 1.f;
  uint8_t src_value = 255u;

  framebuffer srf_fb;
  SrcTexType src_tex(src_size, src_format);
  srf_fb.set_color_attachment(0u, src_tex);

  framebuffer::bind(srf_fb);
  gl::set_clear_color(src_value_f, src_value_f, src_value_f, src_value_f);
  gl::clear(GL_COLOR_BUFFER_BIT);
  framebuffer::unbind();

  framebuffer dst_fb;
  DstTexType dst_tex(dst_size, dst_format);
  dst_fb.set_color_attachment(0u, dst_tex);

  if(test_error)
  {
    EXPECT_PRECOND_ERROR(blit(srf_fb, src_rect, dst_fb, dst_rect,
      framebuffer_blit_mask::color, filter));
  }
  else
  {
    // Blit.
    blit(
      srf_fb, src_rect, dst_fb, dst_rect, framebuffer_blit_mask::color, filter);

    // Compute the size of the area that was blit to.
    vec2u sub_image_size;
    int left = std::min(dst_rect.l(), dst_rect.r());
    int right = std::max(dst_rect.l(), dst_rect.r());
    int top = std::min(dst_rect.t(), dst_rect.b());
    int bottom = std::max(dst_rect.t(), dst_rect.b());
    sub_image_size.x() = static_cast<int>(dst_size.x()) >= right
      ? std::abs(dst_rect.w())
      : static_cast<int>(dst_size.x()) - left;
    sub_image_size.y() = static_cast<int>(dst_size.y()) >= bottom
      ? std::abs(dst_rect.h())
      : static_cast<int>(dst_size.y()) - top;

    DstTexType ref_tex(dst_tex.get_size(), dst_format);
    uint dst_bytes_per_pixel = get_bytes_per_pixel(dst_format);
    std::vector<uint8_t> sub_image_bits(
      sub_image_size.x() * sub_image_size.y() * dst_bytes_per_pixel, src_value);
    ref_tex.set_sub_image(vec2i(left, top),
      pixel_view2(sub_image_bits.data(), sub_image_size, dst_bytes_per_pixel));

    // Check if the blit was executed as expected
    EXPECT_EQ(ref_tex.get_pixels(), dst_tex.get_pixels());
  }
}

}  // namespace



TEST_F(test_framebuffer, binding)
{
  framebuffer fb1;
  texture2 tex1(vec2u(4u, 8u), texture_format::rgba);
  fb1.set_color_attachment(0u, tex1);
  EXPECT_TRUE(fb1.is_complete());

  framebuffer fb2;
  texture2 tex2(vec2u(4u, 8u), texture_format::rgba);
  fb2.set_color_attachment(0u, tex2);
  EXPECT_TRUE(fb2.is_complete());

  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind(fb1);
  EXPECT_TRUE(fb1.is_bound_to_draw_target());
  EXPECT_TRUE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind(fb2);
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_TRUE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::unbind();
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());
}



TEST_F(test_framebuffer, specific_binding)
{
  framebuffer fb1;
  texture2 tex1(vec2u(4u, 8u), texture_format::rgba);
  fb1.set_color_attachment(0u, tex1);
  EXPECT_TRUE(fb1.is_complete());

  framebuffer fb2;
  texture2 tex2(vec2u(4u, 8u), texture_format::rgba);
  fb2.set_color_attachment(0u, tex2);
  EXPECT_TRUE(fb2.is_complete());

  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind_draw_target(fb1);
  EXPECT_TRUE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());

  framebuffer::bind_read_target(fb2);
  EXPECT_TRUE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::bind_draw_target(fb2);
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_TRUE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::unbind_draw_target();
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_TRUE(fb2.is_bound_to_read_target());

  framebuffer::unbind_read_target();
  EXPECT_FALSE(fb1.is_bound_to_draw_target());
  EXPECT_FALSE(fb1.is_bound_to_read_target());
  EXPECT_FALSE(fb2.is_bound_to_draw_target());
  EXPECT_FALSE(fb2.is_bound_to_read_target());
}



TEST_F(test_framebuffer_death_test, binding_error_incomplete_frame_buffer)
{
  framebuffer fb;
  EXPECT_PRECOND_ERROR(framebuffer::bind(fb));
  EXPECT_PRECOND_ERROR(framebuffer::bind_draw_target(fb));
  EXPECT_PRECOND_ERROR(framebuffer::bind_read_target(fb));
}



TEST_F(test_framebuffer, default_constructor)
{
  framebuffer fb;

  EXPECT_NE(0u, fb.get_handle().get_name());
  EXPECT_FALSE(fb.is_bound_to_draw_target());
  EXPECT_FALSE(fb.is_bound_to_read_target());
  EXPECT_FALSE(fb.is_complete());
}



TEST_F(test_framebuffer, move_constructor)
{
  framebuffer fb_dummy;
  GLuint fbName = fb_dummy.get_handle().get_name();
  framebuffer fb(std::move(fb_dummy));

  EXPECT_EQ(0u, fb_dummy.get_handle().get_name());
  EXPECT_EQ(fbName, fb.get_handle().get_name());
  EXPECT_FALSE(fb.is_bound_to_draw_target());
  EXPECT_FALSE(fb.is_bound_to_read_target());
  EXPECT_FALSE(fb.is_complete());
}



TEST_F(test_framebuffer, set_color_attachment)
{
  framebuffer fb;
  texture2 tex(vec2u(4u, 8u), texture_format::rgba, 2u);

  fb.set_color_attachment(0u, tex);

  SUCCEED();
}



TEST_F(test_framebuffer, set_color_attachment_attachment_point_limit)
{
  framebuffer fb;
  texture2 tex(vec2u(4u, 8u), texture_format::rgba, 2u);

  fb.set_color_attachment(
    framebuffer::get_color_attachment_point_count() - 1u, tex);
  SUCCEED();
}



TEST_F(test_framebuffer_death_test,
  set_color_attachment_error_invalid_attachment_point)
{
  framebuffer fb;
  texture2 tex(vec2u(4u, 8u), texture_format::rgba, 2u);
  EXPECT_PRECOND_ERROR(fb.set_color_attachment(
    framebuffer::get_color_attachment_point_count(), tex));
}



TEST_F(test_framebuffer, set_color_attachment_mip_map_level_limit)
{
  framebuffer fb;
  uint mipmap_level_count = 3u;
  texture2 tex(vec2u(4u, 8u), texture_format::rgba, mipmap_level_count);

  for(uint i = 0; i < mipmap_level_count; ++i)
  {
    fb.set_color_attachment(0u, tex, i);
  }

  SUCCEED();
}



TEST_F(
  test_framebuffer_death_test, set_color_attachment_error_invalid_mip_map_level)
{
  framebuffer fb;
  uint mipmap_level_count = 3u;
  texture2 tex(vec2u(4u, 8u), texture_format::rgba, mipmap_level_count);
  EXPECT_PRECOND_ERROR(fb.set_color_attachment(0u, tex, mipmap_level_count));
}



TEST_F(test_framebuffer, set_color_attachment_valid_formats)
{
  framebuffer fb;
  texture2 tex_r(vec2u(4u, 8u), texture_format::r);
  texture2 tex_rg(vec2u(4u, 8u), texture_format::rg);
  texture2 tex_rgb(vec2u(4u, 8u), texture_format::rgb);
  texture2 tex_rgba(vec2u(4u, 8u), texture_format::rgba);
  fb.set_color_attachment(0u, tex_r);
  fb.set_color_attachment(0u, tex_rg);
  fb.set_color_attachment(0u, tex_rgb);
  fb.set_color_attachment(0u, tex_rgba);
  SUCCEED();
}



TEST_F(test_framebuffer_death_test, set_color_attachment_invalid_formats)
{
  framebuffer fb;
  texture2 tex_depth_stencil(vec2u(4u, 8u), texture_format::depth_stencil);
  EXPECT_PRECOND_ERROR(fb.set_color_attachment(0u, tex_depth_stencil));
}



TEST_F(test_framebuffer, set_depth_stencil_attachment)
{
  framebuffer fb;
  texture2 tex(vec2u(4u, 8u), texture_format::depth_stencil);

  fb.set_depth_stencil_attachment(tex);

  SUCCEED();
}



TEST_F(test_framebuffer, set_depth_stencil_attachment_mip_map_level_limit)
{
  framebuffer fb;
  uint mipmap_level_count = 3u;
  texture2 tex(
    vec2u(4u, 8u), texture_format::depth_stencil, mipmap_level_count);

  for(uint i = 0; i < mipmap_level_count; ++i)
  {
    fb.set_depth_stencil_attachment(tex, i);
  }

  SUCCEED();
}



TEST_F(
  test_framebuffer_death_test, set_depth_stencil_attachment_error_invalid_mip_map_level)
{
  framebuffer fb;
  uint mipmap_level_count = 3u;
  texture2 tex(
    vec2u(4u, 8u), texture_format::depth_stencil, mipmap_level_count);
  EXPECT_PRECOND_ERROR(
    fb.set_depth_stencil_attachment(tex, mipmap_level_count));
}



TEST_F(test_framebuffer, set_depth_stencil_attachment_valid_formats)
{
  framebuffer fb;
  texture2 tex_depth_stencil(vec2u(4u, 8u), texture_format::depth_stencil);
  fb.set_depth_stencil_attachment(tex_depth_stencil);
  SUCCEED();
}



TEST_F(
  test_framebuffer_death_test, set_depth_stencil_attachment_invalid_formats)
{
  framebuffer fb;
  texture2 tex_r(vec2u(4u, 8u), texture_format::r);
  texture2 tex_rg(vec2u(4u, 8u), texture_format::rg);
  texture2 tex_rgb(vec2u(4u, 8u), texture_format::rgb);
  texture2 tex_rgba(vec2u(4u, 8u), texture_format::rgba);
  EXPECT_PRECOND_ERROR(fb.set_depth_stencil_attachment(tex_r));
  EXPECT_PRECOND_ERROR(fb.set_depth_stencil_attachment(tex_rg));
  EXPECT_PRECOND_ERROR(fb.set_depth_stencil_attachment(tex_rgb));
  EXPECT_PRECOND_ERROR(fb.set_depth_stencil_attachment(tex_rgba));
}



TEST_F(test_framebuffer, status_color_attachment)
{
  framebuffer fb;
  texture2 tex_rgba(vec2u(4u, 8u), texture_format::rgba);

  fb.set_color_attachment(0u, tex_rgba);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(test_framebuffer, status_depth_stencil_attachment)
{
  framebuffer fb;
  texture2 tex_depth_stencil(vec2u(4u, 8u), texture_format::depth_stencil);

  fb.set_depth_stencil_attachment(tex_depth_stencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(test_framebuffer, status_color_depth_stencil_attachment)
{
  framebuffer fb;
  texture2 tex_rgba(vec2u(4u, 8u), texture_format::rgba);
  texture2 tex_depth_stencil(vec2u(4u, 8u), texture_format::depth_stencil);

  fb.set_color_attachment(0u, tex_rgba);
  fb.set_depth_stencil_attachment(tex_depth_stencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(test_framebuffer, status_multisampled_color_depth_stencil_attachment)
{
  framebuffer fb;
  uint sample_count
    = std::min(multisampled_texture2::get_max_sample_count().get(), 4u);
  multisampled_texture2 tex_rgba(
    vec2u(4u, 8u), texture_format::rgba, sample_count);
  texture2 tex_depth_stencil(vec2u(4u, 8u), texture_format::depth_stencil);

  fb.set_color_attachment(0u, tex_rgba);
  fb.set_depth_stencil_attachment(tex_depth_stencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(test_framebuffer,
  status_multisampled_color_multisampled_depth_stencil_attachment)
{
  framebuffer fb;
  uint sample_count
    = std::min(multisampled_texture2::get_max_sample_count().get(), 4u);
  multisampled_texture2 tex_rgba(
    vec2u(4u, 8u), texture_format::rgba, sample_count);
  multisampled_texture2 tex_depth_stencil(
    vec2u(4u, 8u), texture_format::depth_stencil, sample_count);

  fb.set_color_attachment(0u, tex_rgba);
  fb.set_depth_stencil_attachment(tex_depth_stencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(test_framebuffer,
  status_multisampled_color_multisampled_depth_stencil_attachment_different_samples)
{
  framebuffer fb;
  uint sample_count
    = std::min(multisampled_texture2::get_max_sample_count().get(), 4u);
  multisampled_texture2 tex_rgba(
    vec2u(4u, 8u), texture_format::rgba, sample_count);
  multisampled_texture2 tex_depth_stencil(
    vec2u(4u, 8u), texture_format::depth_stencil, 1u);

  fb.set_color_attachment(0u, tex_rgba);
  fb.set_depth_stencil_attachment(tex_depth_stencil);
  EXPECT_TRUE(fb.is_complete());
}



TEST_F(test_framebuffer, has_multisample_attachment)
{
  vec2u size(4u, 8u);
  framebuffer fb;
  texture2 tex_color_ss(size, texture_format::rgba);
  texture2 tex_ds_ss(size, texture_format::depth_stencil);
  multisampled_texture2 tex_color_ms(size, texture_format::rgba);
  multisampled_texture2 tex_ds_ms(size, texture_format::depth_stencil);

  EXPECT_FALSE(fb.has_multisample_attachment());
  fb.set_color_attachment(0u, tex_color_ss);
  EXPECT_FALSE(fb.has_multisample_attachment());
  fb.set_depth_stencil_attachment(tex_ds_ss);
  EXPECT_FALSE(fb.has_multisample_attachment());
  fb.set_color_attachment(0u, tex_color_ms);
  EXPECT_TRUE(fb.has_multisample_attachment());
  fb.set_color_attachment(0u, tex_color_ss);
  EXPECT_FALSE(fb.has_multisample_attachment());
  fb.set_depth_stencil_attachment(tex_ds_ms);
  EXPECT_TRUE(fb.has_multisample_attachment());
  fb.set_depth_stencil_attachment(tex_ds_ss);
  EXPECT_FALSE(fb.has_multisample_attachment());
  fb.set_color_attachment(0u, tex_color_ms);
  fb.set_depth_stencil_attachment(tex_ds_ms);
  EXPECT_TRUE(fb.has_multisample_attachment());
}



TEST_F(test_framebuffer, blit_color_full_image)
{
  vec2u size(4u, 8u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size,
    recti(vec2u(), size), texture_format::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_same_rect)
{
  vec2u size(8u, 16u);
  recti rect(1u, 2u, 3u, 4u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size, rect,
    texture_format::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_different_texture_sizes)
{
  vec2u size1(4u, 8u);
  vec2u size2(8u, 16u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size1,
    recti(vec2u(), size1), texture_format::rgba, size2, recti(vec2u(), size1),
    framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_different_rects)
{
  vec2u size(8u, 16u);
  recti src_rect(1u, 2u, 3u, 4u);
  recti dst_rect(2u, 1u, 4u, 6u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size, src_rect,
    texture_format::rgba, size, dst_rect, framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_overflowing_rect)
{
  vec2u size(8u, 16u);
  recti rect(4u, 6u, 6u, 16u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size, rect,
    texture_format::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_inverted_rect)
{
  vec2u size(8u, 16u);
  recti src_rect(1u, 2u, 3u, 4u);
  recti dst_rect(src_rect.r(), src_rect.b(), -src_rect.w(), -src_rect.h());
  test_color_blit<texture2, texture2>(texture_format::rgba, size, src_rect,
    texture_format::rgba, size, dst_rect, framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_linear_filter)
{
  vec2u size(4u, 8u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size,
    recti(vec2u(), size), texture_format::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::linear);
}



TEST_F(test_framebuffer, blit_color_different_format)
{
  vec2u size(4u, 8u);
  test_color_blit<texture2, texture2>(texture_format::rgba, size,
    recti(vec2u(), size), texture_format::rgb, size, recti(vec2u(), size),
    framebuffer_blit_filter::linear);
}



TEST_F(test_framebuffer, blit_color_full_image_multisample)
{
  vec2u size(4u, 8u);
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size,
    recti(vec2u(), size), texture_format::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_same_rect_multisample)
{
  vec2u size(8u, 16u);
  recti rect(1u, 2u, 3u, 4u);
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size,
    rect, texture_format::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_different_texture_sizes_multisample)
{
  vec2u size1(4u, 8u);
  vec2u size2(8u, 16u);
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size1,
    recti(vec2u(), size1), texture_format::rgba, size2, recti(vec2u(), size1),
    framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_overflowing_rect_multisample)
{
  vec2u size(8u, 16u);
  recti rect(4u, 6u, 6u, 16u);
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size,
    rect, texture_format::rgba, size, rect, framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_inverted_rect_multisample)
{
  vec2u size(8u, 16u);
  recti src_rect(1u, 2u, 3u, 4u);
  recti dst_rect(src_rect.r(), src_rect.b(), -src_rect.w(), -src_rect.h());
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size,
    src_rect, texture_format::rgba, size, dst_rect,
    framebuffer_blit_filter::nearest);
}



TEST_F(test_framebuffer, blit_color_linear_filter_multisample)
{
  vec2u size(4u, 8u);
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size,
    recti(vec2u(), size), texture_format::rgba, size, recti(vec2u(), size),
    framebuffer_blit_filter::linear);
}



TEST_F(
  test_framebuffer_death_test, blit_error_color_different_rects_multisample)
{
  vec2u size(8u, 16u);
  recti src_rect(1u, 2u, 3u, 4u);
  recti dst_rect(2u, 1u, 4u, 6u);
  test_color_blit<multisampled_texture2, texture2>(texture_format::rgba, size,
    src_rect, texture_format::rgba, size, dst_rect,
    framebuffer_blit_filter::nearest, true);
}



TEST_F(test_framebuffer_death_test, blit_error_incomplete_source_buffer)
{
  framebuffer src;
  framebuffer dst;
  texture2 dst_tex(vec2u(4u, 8u));
  dst.set_color_attachment(0u, dst_tex);

  EXPECT_FALSE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());
  EXPECT_PRECOND_ERROR(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::color, framebuffer_blit_filter::nearest));
}



TEST_F(test_framebuffer_death_test, blit_error_incomplete_destination_buffer)
{
  framebuffer src;
  texture2 src_tex(vec2u(4u, 8u));
  src.set_color_attachment(0u, src_tex);
  framebuffer dst;

  EXPECT_TRUE(src.is_complete());
  EXPECT_FALSE(dst.is_complete());
  EXPECT_PRECOND_ERROR(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::color, framebuffer_blit_filter::nearest));
}



TEST_F(test_framebuffer, blit_no_attachment_specified)
{
  framebuffer src;
  texture2 src_tex_color(vec2u(4u, 8u));
  texture2 src_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  src.set_color_attachment(0u, src_tex_color);
  src.set_depth_stencil_attachment(src_tex_ds);

  framebuffer dst;
  texture2 dst_tex_color(vec2u(4u, 8u));
  texture2 dst_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  dst.set_color_attachment(0u, dst_tex_color);
  dst.set_depth_stencil_attachment(dst_tex_ds);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::none, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(test_framebuffer, blit_source_missing_color)
{
  framebuffer src;
  texture2 src_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  src.set_depth_stencil_attachment(src_tex_ds);

  framebuffer dst;
  texture2 dst_tex_color(vec2u(4u, 8u));
  texture2 dst_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  dst.set_color_attachment(0u, dst_tex_color);
  dst.set_depth_stencil_attachment(dst_tex_ds);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::color, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(test_framebuffer, blit_source_missing_depth_stencil)
{
  framebuffer src;
  texture2 src_tex_color(vec2u(4u, 8u));
  src.set_color_attachment(0u, src_tex_color);

  framebuffer dst;
  texture2 dst_tex_color(vec2u(4u, 8u));
  texture2 dst_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  dst.set_color_attachment(0u, dst_tex_color);
  dst.set_depth_stencil_attachment(dst_tex_ds);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::depth, framebuffer_blit_filter::nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::stencil, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(test_framebuffer, blit_destination_missing_color)
{
  framebuffer src;
  texture2 src_tex_color(vec2u(4u, 8u));
  texture2 src_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  src.set_color_attachment(0u, src_tex_color);
  src.set_depth_stencil_attachment(src_tex_ds);

  framebuffer dst;
  texture2 dst_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  dst.set_depth_stencil_attachment(dst_tex_ds);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::color, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(test_framebuffer, blit_destination_missing_depth_stencil)
{
  framebuffer src;
  texture2 src_tex_color(vec2u(4u, 8u));
  texture2 src_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  src.set_color_attachment(0u, src_tex_color);
  src.set_depth_stencil_attachment(src_tex_ds);

  framebuffer dst;
  texture2 dst_tex_color(vec2u(4u, 8u));
  dst.set_color_attachment(0u, dst_tex_color);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::depth, framebuffer_blit_filter::nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::stencil, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(test_framebuffer, blit_missing_color)
{
  framebuffer src;
  texture2 src_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  src.set_depth_stencil_attachment(src_tex_ds);

  framebuffer dst;
  texture2 dst_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  dst.set_depth_stencil_attachment(dst_tex_ds);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::color, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(test_framebuffer, blit_missing_depth_stencil)
{
  framebuffer src;
  texture2 src_tex_color(vec2u(4u, 8u));
  src.set_color_attachment(0u, src_tex_color);

  framebuffer dst;
  texture2 dst_tex_color(vec2u(4u, 8u));
  dst.set_color_attachment(0u, dst_tex_color);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::depth, framebuffer_blit_filter::nearest);
  blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
    framebuffer_blit_mask::stencil, framebuffer_blit_filter::nearest);
  SUCCEED();
}



TEST_F(
  test_framebuffer_death_test, blit_error_linear_filter_with_depth_stencil_mask)
{
  framebuffer src;
  texture2 src_tex_color(vec2u(4u, 8u));
  texture2 src_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  src.set_color_attachment(0u, src_tex_color);
  src.set_depth_stencil_attachment(src_tex_ds);

  framebuffer dst;
  texture2 dst_tex_color(vec2u(4u, 8u));
  texture2 dst_tex_ds(vec2u(4u, 8u), texture_format::depth_stencil);
  dst.set_color_attachment(0u, dst_tex_color);
  dst.set_depth_stencil_attachment(dst_tex_ds);

  EXPECT_TRUE(src.is_complete());
  EXPECT_TRUE(dst.is_complete());

  EXPECT_PRECOND_ERROR(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::depth, framebuffer_blit_filter::linear));
  EXPECT_PRECOND_ERROR(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::stencil, framebuffer_blit_filter::linear));
  EXPECT_PRECOND_ERROR(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::depth | framebuffer_blit_mask::stencil,
      framebuffer_blit_filter::linear));
  EXPECT_PRECOND_ERROR(
    blit(src, recti(1u, 1u, 1u, 1u), dst, recti(1u, 1u, 1u, 1u),
      framebuffer_blit_mask::all, framebuffer_blit_filter::linear));
}
