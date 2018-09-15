// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_texture_base.hpp"

#include "hou/gl/gl_functions.hpp"

using namespace hou;
using namespace testing;

namespace
{

using test_texture2 = test_texture_base<texture2>;
using test_texture2_death_test = test_texture2;

}  // namespace



TEST_F(test_texture2, size_constructor)
{
  vec2u size_ref(4u, 8u);
  texture2 t(size_ref);
  EXPECT_EQ(texture_type::texture2, t.get_type());
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_mipmap_level_count());
  EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_image());
}



TEST_F(test_texture2, size_constructor_size_limits)
{
  vec2u min_size(1u, 1u);
  texture2 t_min_size(min_size);
  EXPECT_EQ(min_size, t_min_size.get_size());

  vec2u max_size_x(texture2::get_max_size().x(), 1u);
  texture2 t_max_size_x(max_size_x);
  EXPECT_EQ(max_size_x, t_max_size_x.get_size());

  vec2u max_size_y(1u, texture2::get_max_size().y());
  texture2 t_max_size_y(max_size_y);
  EXPECT_EQ(max_size_y, t_max_size_y.get_size());
}



TEST_F(test_texture2_death_test, size_constructor_invalid_size)
{
  EXPECT_PRECOND_ERROR(texture2(vec2u(0u, 1u)));
  EXPECT_PRECOND_ERROR(texture2(vec2u(1u, 0u)));
  EXPECT_PRECOND_ERROR(texture2(vec2u(0u, 0u)));
  EXPECT_PRECOND_ERROR(texture2(texture2::get_max_size() + vec2u(1u, 1u)));
  EXPECT_PRECOND_ERROR(texture2(texture2::get_max_size() + vec2u(0u, 1u)));
  EXPECT_PRECOND_ERROR(texture2(texture2::get_max_size() + vec2u(1u, 0u)));
}



TEST_F(test_texture2, full_size_constructor)
{
  vec2u size_ref(4u, 8u);
  uint mipmap_level_count_ref = 2u;
  for(auto tf : all_formats)
  {
    texture2 t(size_ref, tf, mipmap_level_count_ref);
    EXPECT_EQ(size_ref, t.get_size());
    EXPECT_EQ(tf, t.get_format());
    EXPECT_EQ(mipmap_level_count_ref, t.get_mipmap_level_count());
    EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_image());
  }
}



TEST_F(test_texture2, full_size_constructor_mipmap_level_count_limits)
{
  vec2u size_ref(4u, 8u);

  uint min_mipmap_level_count = 1u;
  texture2 t_min_level(size_ref, texture_format::rgba, min_mipmap_level_count);
  EXPECT_EQ(min_mipmap_level_count, t_min_level.get_mipmap_level_count());

  uint max_mipmap_level_count = 1u;
  texture2 t_max_level(size_ref, texture_format::rgba, max_mipmap_level_count);
  EXPECT_EQ(max_mipmap_level_count, t_max_level.get_mipmap_level_count());
}



TEST_F(test_texture2_death_test, invalid_sample_count)
{
  EXPECT_PRECOND_ERROR(texture2(vec2u(1u, 1u), texture_format::rgba,
    texture2::get_max_mipmap_level_count(vec2u(1u, 1u)) + 1u));
}



TEST_F(test_texture2, image_constructor)
{
  std::vector<uint8_t> image_data{
    0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u};

  std::vector<std::pair<texture_format, pixel_view2>> format_images{
    std::make_pair(
      texture_format::r, pixel_view2(image_data.data(), vec2u(3u, 4u), 1u)),
    std::make_pair(
      texture_format::rg, pixel_view2(image_data.data(), vec2u(3u, 2u), 2u)),
    std::make_pair(
      texture_format::rgb, pixel_view2(image_data.data(), vec2u(1u, 4u), 3u)),
    std::make_pair(
      texture_format::rgba, pixel_view2(image_data.data(), vec2u(3u, 1u), 4u)),
    std::make_pair(texture_format::depth_stencil,
      pixel_view2(image_data.data(), vec2u(3u, 1u), 4u)),
  };

  uint mipmap_level_count_ref = 2u;
  for(auto fi : format_images)
  {
    texture2 t(fi.second, fi.first, mipmap_level_count_ref);
    EXPECT_EQ(fi.second.get_size(), t.get_size());
    EXPECT_EQ(fi.first, t.get_format());
    EXPECT_EQ(mipmap_level_count_ref, t.get_mipmap_level_count());
    EXPECT_EQ(image_data, t.get_image());
  }
}



TEST_F(test_texture2, image_constructor_with_image)
{
  image2_rgba im(vec2u(4u, 8u), pixel_rgba(color::red()));
  texture2 t(im);
  EXPECT_EQ(im.get_size(), t.get_size());
}



TEST_F(test_texture2_death_test, image_constructor_invalid_size)
{
  std::vector<uint8_t> image_data{
    0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u};
  EXPECT_PRECOND_ERROR(
    texture2(pixel_view2(image_data.data(), vec2u(0u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2(pixel_view2(image_data.data(), vec2u(1u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2(pixel_view2(image_data.data(), vec2u(0u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(texture2(pixel_view2(
    image_data.data(), texture2::get_max_size() + vec2u(1u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2(pixel_view2(
    image_data.data(), texture2::get_max_size() + vec2u(0u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2(pixel_view2(
    image_data.data(), texture2::get_max_size() + vec2u(1u, 0u), 4u)));
}



TEST_F(test_texture2_death_test, image_constructor_invalid_byte_depth)
{
  std::vector<uint8_t> image_data{
    0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u};
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 2u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 3u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 4u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 1u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 3u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 4u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 1u), texture_format::rgb));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 2u), texture_format::rgb));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 4u), texture_format::rgb));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 1u), texture_format::rgba));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 2u), texture_format::rgba));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(1u, 1u), 3u), texture_format::rgba));
  EXPECT_PRECOND_ERROR(
    texture2(pixel_view2(image_data.data(), vec2u(0u, 1u), 1u),
      texture_format::depth_stencil));
  EXPECT_PRECOND_ERROR(
    texture2(pixel_view2(image_data.data(), vec2u(0u, 1u), 2u),
      texture_format::depth_stencil));
  EXPECT_PRECOND_ERROR(
    texture2(pixel_view2(image_data.data(), vec2u(0u, 1u), 3u),
      texture_format::depth_stencil));
}



TEST_F(test_texture2, get_byte_count)
{
  vec2u size_ref(4u, 8u);
  for(auto tf : all_formats)
  {
    texture2 t(size_ref, tf);
    EXPECT_EQ(gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), 1u,
                gl::get_texture_external_format_for_internal_format(
                  static_cast<GLenum>(t.get_format()))),
      t.get_byte_count());
  }
}



TEST_F(test_texture2, set_filter)
{
  texture2 t(vec2u(1u, 1u));
  EXPECT_EQ(texture_filter::linear, t.get_filter());
  for(auto filter : all_filters)
  {
    t.set_filter(filter);
    EXPECT_EQ(filter, t.get_filter());
  }
}



TEST_F(test_texture2, set_wrap_mode)
{
  texture2 t(vec2u(1u, 1u));
  EXPECT_EQ(
    (texture2::wrap_mode{texture_wrap_mode::repeat, texture_wrap_mode::repeat}),
    t.get_wrap_mode());
  for(auto wmx : all_wrap_modes)
  {
    for(auto wmy : all_wrap_modes)
    {
      t.set_wrap_mode(texture2::wrap_mode{wmx, wmy});
      EXPECT_EQ((texture2::wrap_mode{wmx, wmy}), t.get_wrap_mode());
    }
  }
}



TEST_F(test_texture2, set_image)
{
  texture2 t(vec2u(2u, 3u));
  // clang-format off
  std::vector<uint8_t> image_data{
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,};
  // clang-format on
  t.set_image(pixel_view2(image_data.data(), t.get_size(), 4u));
  EXPECT_EQ(image_data, t.get_image());
}



TEST_F(test_texture2, set_sub_image)
{
  texture2 t(vec2u(4u, 6u));
  // clang-format off
  std::vector<uint8_t> sub_image_data{
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,};
  std::vector<uint8_t> image_data{
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    0u, 0u, 0u, 0u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,};
  // clang-format on
  t.set_sub_image(
    vec2u(1u, 2u), pixel_view2(sub_image_data.data(), vec2u(3u, 2u), 4u));
  EXPECT_EQ(image_data, t.get_image());
  EXPECT_EQ(sub_image_data, t.get_sub_image(vec2u(1u, 2u), vec2u(3u, 2u)));
}



TEST_F(test_texture2_death_test, get_sub_image_invalid_params)
{
  texture2 t(vec2u(4u, 6u));
  EXPECT_PRECOND_ERROR(t.get_sub_image(vec2u(0u, 0u), vec2u(5u, 6u)));
  EXPECT_PRECOND_ERROR(t.get_sub_image(vec2u(0u, 0u), vec2u(4u, 7u)));
  EXPECT_PRECOND_ERROR(t.get_sub_image(vec2u(0u, 0u), vec2u(5u, 7u)));
  EXPECT_PRECOND_ERROR(t.get_sub_image(vec2u(1u, 0u), vec2u(4u, 6u)));
  EXPECT_PRECOND_ERROR(t.get_sub_image(vec2u(0u, 1u), vec2u(4u, 6u)));
  EXPECT_PRECOND_ERROR(t.get_sub_image(vec2u(1u, 1u), vec2u(4u, 6u)));
}



TEST_F(test_texture2_death_test, set_sub_image_invalid_params)
{
  texture2 t(vec2u(4u, 6u));
  std::vector<uint8_t> image_data(5u * 7u * 4u, 0u);
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec2u(0u, 0u), pixel_view2(image_data.data(), vec2u(5u, 6u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec2u(0u, 0u), pixel_view2(image_data.data(), vec2u(4u, 7u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec2u(0u, 0u), pixel_view2(image_data.data(), vec2u(5u, 7u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec2u(1u, 0u), pixel_view2(image_data.data(), vec2u(4u, 6u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec2u(0u, 1u), pixel_view2(image_data.data(), vec2u(4u, 6u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec2u(1u, 1u), pixel_view2(image_data.data(), vec2u(4u, 6u), 4u)));
}



TEST_F(test_texture2, clear)
{
  // clang-format off
  std::vector<uint8_t> image_data{
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,};
  // clang-format on
  texture2 t(pixel_view2(image_data.data(), vec2u(2u, 3u), 4u));
  t.clear();
  EXPECT_EQ(std::vector<uint8_t>(image_data.size(), 0u), t.get_image());
}

