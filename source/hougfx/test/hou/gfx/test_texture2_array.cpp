// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_texture_base.hpp"

#include "hou/gl/gl_functions.hpp"

using namespace hou;
using namespace testing;

namespace
{

using test_texture2_array = test_texture_base<texture2_array>;
using test_texture2_array_death_test = test_texture2_array;

}  // namespace



TEST_F(test_texture2_array, size_constructor)
{
  vec3u size_ref(4u, 8u, 3u);
  texture2_array t(size_ref);
  EXPECT_EQ(texture_type::texture2_array, t.get_type());
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(
    gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), size_ref.z(),
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(t.get_format()))),
    t.get_byte_count());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_mipmap_level_count());
  EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_pixels());
}



TEST_F(test_texture2_array, size_constructor_size_limits)
{
  vec3u min_size(1u, 1u, 1u);
  texture2_array t_min_size(min_size);
  EXPECT_EQ(min_size, t_min_size.get_size());

  vec3u max_size_x(texture2_array::get_max_size().x(), 1u, 1u);
  texture2_array t_max_size_x(max_size_x);
  EXPECT_EQ(max_size_x, t_max_size_x.get_size());

  vec3u max_size_y(1u, texture2_array::get_max_size().y(), 1u);
  texture2_array t_max_size_y(max_size_y);
  EXPECT_EQ(max_size_y, t_max_size_y.get_size());

  vec3u max_size_z(1u, 1u, texture2_array::get_max_size().z());
  texture2_array t_max_size_z(max_size_z);
  EXPECT_EQ(max_size_z, t_max_size_z.get_size());
}



TEST_F(test_texture2_array_death_test, size_constructor_invalid_size)
{
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(0u, 0u, 0u)));
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(1u, 0u, 0u)));
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(0u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(1u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(0u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(1u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(0u, 1u, 1u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(1u, 1u, 1u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(0u, 1u, 1u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(1u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(0u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(1u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(0u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(texture2_array::get_max_size() + vec3u(1u, 0u, 0u)));
}



TEST_F(test_texture2_array, full_size_constructor)
{
  vec3u size_ref(4u, 8u, 3u);
  uint mipmap_level_count_ref = 2u;
  for(auto tf : all_formats)
  {
    texture2_array t(size_ref, tf, mipmap_level_count_ref);
    EXPECT_EQ(size_ref, t.get_size());
    EXPECT_EQ(tf, t.get_format());
    EXPECT_EQ(mipmap_level_count_ref, t.get_mipmap_level_count());
    EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_pixels());
  }
}



TEST_F(test_texture2_array, full_size_constructor_mipmap_level_count_limits)
{
  vec3u size_ref(4u, 8u, 3u);

  uint min_mipmap_level_count = 1u;
  texture2_array t_min_level(
    size_ref, texture_format::rgba, min_mipmap_level_count);
  EXPECT_EQ(min_mipmap_level_count, t_min_level.get_mipmap_level_count());

  uint max_mipmap_level_count = 1u;
  texture2_array t_max_level(
    size_ref, texture_format::rgba, max_mipmap_level_count);
  EXPECT_EQ(max_mipmap_level_count, t_max_level.get_mipmap_level_count());
}



TEST_F(test_texture2_array_death_test, invalid_sample_count)
{
  EXPECT_PRECOND_ERROR(texture2_array(vec3u(1u, 1u, 1u), texture_format::rgba,
    texture2_array::get_max_mipmap_level_count(vec3u(1u, 1u, 1u)) + 1u));
}



TEST_F(test_texture2_array, image_constructor)
{
  std::vector<uint8_t> image_data{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u,
    11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u};

  std::vector<std::pair<texture_format, pixel_view3>> format_images{
    std::make_pair(
      texture_format::r, pixel_view3(image_data.data(), vec3u(3u, 4u, 2u), 1u)),
    std::make_pair(texture_format::rg,
      pixel_view3(image_data.data(), vec3u(3u, 2u, 2u), 2u)),
    std::make_pair(texture_format::rgb,
      pixel_view3(image_data.data(), vec3u(1u, 4u, 2u), 3u)),
    std::make_pair(texture_format::rgba,
      pixel_view3(image_data.data(), vec3u(3u, 1u, 2u), 4u)),
  };

  uint mipmap_level_count_ref = 2u;
  for(auto fi : format_images)
  {
    texture2_array t(fi.second, fi.first, mipmap_level_count_ref);
    EXPECT_EQ(fi.second.get_size(), t.get_size());
    EXPECT_EQ(fi.first, t.get_format());
    EXPECT_EQ(mipmap_level_count_ref, t.get_mipmap_level_count());
    EXPECT_EQ(image_data, t.get_pixels());
  }
}



TEST_F(test_texture2_array_death_test, image_constructor_invalid_size)
{
  std::vector<uint8_t> image_data{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u,
    11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u};

  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(0u, 0u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 0u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(0u, 1u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(0u, 0u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 0u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(0u, 1u, 1u), 4u)));

  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(1u, 1u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(0u, 1u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(1u, 0u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(0u, 0u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(1u, 1u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(0u, 1u, 0u), 4u)));
  EXPECT_PRECOND_ERROR(texture2_array(pixel_view3(image_data.data(),
    texture2_array::get_max_size() + vec3u(1u, 0u, 0u), 4u)));
}



TEST_F(test_texture2_array_death_test, image_constructor_invalid_byte_depth)
{
  std::vector<uint8_t> image_data{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u,
    11u, 12u, 13u, 14u, 15u, 16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u};

  EXPECT_PRECOND_ERROR(texture2_array(
    pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 2u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2_array(
    pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 3u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2_array(
    pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 4u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2_array(
    pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 1u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2_array(
    pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 3u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2_array(
    pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 4u), texture_format::rg));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 1u),
      texture_format::rgb));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 2u),
      texture_format::rgb));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 4u),
      texture_format::rgb));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 1u),
      texture_format::rgba));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 2u),
      texture_format::rgba));
  EXPECT_PRECOND_ERROR(
    texture2_array(pixel_view3(image_data.data(), vec3u(1u, 1u, 1u), 3u),
      texture_format::rgba));
}



TEST_F(test_texture2_array, get_byte_count)
{
  vec3u size_ref(4u, 8u, 3u);
  for(auto tf : all_formats)
  {
    texture2_array t(size_ref, tf);
    EXPECT_EQ(
      gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), size_ref.z(),
        gl::get_texture_external_format_for_internal_format(
          static_cast<GLenum>(t.get_format()))),
      t.get_byte_count());
  }
}



TEST_F(test_texture2_array, set_filter)
{
  texture2_array t(vec3u(1u, 1u, 1u));
  EXPECT_EQ(texture_filter::linear, t.get_filter());
  for(auto filter : all_filters)
  {
    t.set_filter(filter);
    EXPECT_EQ(filter, t.get_filter());
  }
}



TEST_F(test_texture2_array, set_wrap_mode)
{
  texture2_array t(vec3u(1u, 1u, 1u));
  EXPECT_EQ((texture2_array::wrap_mode{texture_wrap_mode::repeat,
              texture_wrap_mode::repeat, texture_wrap_mode::repeat}),
    t.get_wrap_mode());
  for(auto wmx : all_wrap_modes)
  {
    for(auto wmy : all_wrap_modes)
    {
      for(auto wmz : all_wrap_modes)
      {
        t.set_wrap_mode(texture2_array::wrap_mode{wmx, wmy, wmz});
        EXPECT_EQ(
          (texture2_array::wrap_mode{wmx, wmy, wmz}), t.get_wrap_mode());
      }
    }
  }
}



TEST_F(test_texture2_array_death_test, get_sub_pixels_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));

  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 6u, 7u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(4u, 7u, 7u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 7u, 7u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(4u, 6u, 7u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 7u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(4u, 7u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 6u, 2u)));

  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(1u, 1u, 1u), vec3u(4u, 6u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 1u, 1u), vec3u(4u, 6u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(1u, 0u, 1u), vec3u(4u, 6u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 0u, 1u), vec3u(4u, 6u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(1u, 1u, 0u), vec3u(4u, 6u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(0u, 1u, 0u), vec3u(4u, 6u, 2u)));
  EXPECT_PRECOND_ERROR(t.get_sub_pixels(vec3u(1u, 0u, 0u), vec3u(4u, 6u, 2u)));
}



TEST_F(test_texture2_array, set_pixels)
{
  texture2_array t(vec3u(2u, 3u, 2u));
  // clang-format off
  std::vector<uint8_t> image_data{
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    //
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,};
  // clang-format on
  t.set_pixels(image_data);
  EXPECT_EQ(image_data, t.get_pixels());
}



TEST_F(test_texture2_array, set_sub_pixels)
{
  texture2_array t(vec3u(4u, 6u, 2u));
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
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    //
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,};
  // clang-format on
  t.set_sub_pixels(vec3u(1u, 2u, 0u), vec3u(3u, 2u, 1u), sub_image_data);
  EXPECT_EQ(image_data, t.get_pixels());
  EXPECT_EQ(
    sub_image_data, t.get_sub_pixels(vec3u(1u, 2u, 0u), vec3u(3u, 2u, 1u)));
}



TEST_F(test_texture2_array_death_test, set_pixels_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));
  EXPECT_PRECOND_ERROR(
    t.set_pixels(std::vector<uint8_t>(t.get_byte_count() - 1u)));
  EXPECT_PRECOND_ERROR(
    t.set_pixels(std::vector<uint8_t>(t.get_byte_count() + 1u)));
}



TEST_F(test_texture2_array_death_test, set_sub_pixels_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));
  std::vector<uint8_t> image_data(5u * 7u * 3u * 4u, 0u);

  EXPECT_PRECOND_ERROR(t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(3u, 5u, 1u),
    std::vector<uint8_t>(4u * 6u * 2u * 4u + 1u, 0u)));

  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 7u, 3u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(4u, 7u, 3u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 6u, 3u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(4u, 6u, 3u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 7u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(4u, 7u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 0u), vec3u(5u, 6u, 2u), image_data));

  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(1u, 1u, 1u), vec3u(4u, 6u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 1u, 1u), vec3u(4u, 6u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(1u, 0u, 1u), vec3u(4u, 6u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 0u, 1u), vec3u(4u, 6u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(1u, 1u, 0u), vec3u(4u, 6u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(0u, 1u, 0u), vec3u(4u, 6u, 2u), image_data));
  EXPECT_PRECOND_ERROR(
    t.set_sub_pixels(vec3u(1u, 0u, 0u), vec3u(4u, 6u, 2u), image_data));
}



TEST_F(test_texture2_array, set_image_pixel_view)
{
  texture2_array t(vec3u(2u, 3u, 2u));
  // clang-format off
  std::vector<uint8_t> image_data{
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    //
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,};
  // clang-format on
  t.set_image(pixel_view3(image_data.data(), t.get_size(), 4u));
  EXPECT_EQ(image_data, t.get_pixels());
}



TEST_F(test_texture2_array, set_sub_image_pixel_view)
{
  texture2_array t(vec3u(4u, 6u, 2u));
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
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    //
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
    0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,};
  // clang-format on
  t.set_sub_image(vec3u(1u, 2u, 0u),
    pixel_view3(sub_image_data.data(), vec3u(3u, 2u, 1u), 4u));
  EXPECT_EQ(image_data, t.get_pixels());
  EXPECT_EQ(
    sub_image_data, t.get_sub_pixels(vec3u(1u, 2u, 0u), vec3u(3u, 2u, 1u)));
}



TEST_F(test_texture2_array_death_test, set_image_pixel_view_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));
  std::vector<uint8_t> image_data(5u * 7u * 3u * 4u, 0u);

  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(3u, 5u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(3u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(4u, 5u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(4u, 6u, 1u), 4u)));

  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(3u, 5u, 1u), 5u)));

  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(5u, 7u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(4u, 7u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(5u, 6u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(4u, 6u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(5u, 7u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(4u, 7u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(
    t.set_image(pixel_view3(image_data.data(), vec3u(5u, 6u, 2u), 4u)));
}



TEST_F(test_texture2_array_death_test, set_sub_image_pixel_view_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));
  std::vector<uint8_t> image_data(5u * 7u * 3u * 4u, 0u);

  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(3u, 5u, 1u), 5u)));

  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(5u, 7u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(4u, 7u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(5u, 6u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(4u, 6u, 3u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(5u, 7u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(4u, 7u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 0u), pixel_view3(image_data.data(), vec3u(5u, 6u, 2u), 4u)));

  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(1u, 1u, 1u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 1u, 1u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(1u, 0u, 1u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 0u, 1u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(1u, 1u, 0u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(0u, 1u, 0u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
  EXPECT_PRECOND_ERROR(t.set_sub_image(
    vec3u(1u, 0u, 0u), pixel_view3(image_data.data(), vec3u(4u, 6u, 2u), 4u)));
}



TEST_F(test_texture2_array, set_image)
{
  texture2_array t(vec3u(2u, 3u, 4u));
  pixel_rgba pixel_ref(1u, 2u, 3u, 4u);

  image3_rgba img_rgba_ref(t.get_size(), pixel_ref);
  t.set_image(img_rgba_ref);
  EXPECT_EQ(img_rgba_ref, t.get_image<pixel_format::rgba>());
  EXPECT_EQ(image3_rgb(img_rgba_ref), t.get_image<pixel_format::rgb>());
  EXPECT_EQ(image3_rg(img_rgba_ref), t.get_image<pixel_format::rg>());
  EXPECT_EQ(image3_r(img_rgba_ref), t.get_image<pixel_format::r>());

  image3_rgb img_rgb_ref(img_rgba_ref);
  t.set_image(img_rgb_ref);
  EXPECT_EQ(image3_rgba(img_rgb_ref), t.get_image<pixel_format::rgba>());
  EXPECT_EQ(
    image3_rgb(image3_rgba(img_rgb_ref)), t.get_image<pixel_format::rgb>());
  EXPECT_EQ(
    image3_rg(image3_rgba(img_rgb_ref)), t.get_image<pixel_format::rg>());
  EXPECT_EQ(image3_r(image3_rgba(img_rgb_ref)), t.get_image<pixel_format::r>());

  image3_rg img_rg_ref(img_rgba_ref);
  t.set_image(img_rg_ref);
  EXPECT_EQ(image3_rgba(img_rg_ref), t.get_image<pixel_format::rgba>());
  EXPECT_EQ(
    image3_rgb(image3_rgba(img_rg_ref)), t.get_image<pixel_format::rgb>());
  EXPECT_EQ(
    image3_rg(image3_rgba(img_rg_ref)), t.get_image<pixel_format::rg>());
  EXPECT_EQ(image3_r(image3_rgba(img_rg_ref)), t.get_image<pixel_format::r>());

  image3_r img_r_ref(img_rgba_ref);
  t.set_image(img_r_ref);
  EXPECT_EQ(image3_rgba(img_r_ref), t.get_image<pixel_format::rgba>());
  EXPECT_EQ(
    image3_rgb(image3_rgba(img_r_ref)), t.get_image<pixel_format::rgb>());
  EXPECT_EQ(image3_rg(image3_rgba(img_r_ref)), t.get_image<pixel_format::rg>());
  EXPECT_EQ(image3_r(image3_rgba(img_r_ref)), t.get_image<pixel_format::r>());
}



TEST_F(test_texture2_array, set_sub_image)
{
  texture2_array t(vec3u(4u, 6u, 7u));
  pixel_rgba pixel_ref(1u, 2u, 3u, 4u);
  image3_rgba img_ref(t.get_size());
  image3_rgba sub_img_ref(vec3u(3u, 2u, 2u), pixel_ref);
  img_ref.set_sub_image(vec3u(1u, 2u, 3u), sub_img_ref);
  t.set_sub_image(vec3u(1u, 2u, 3u), sub_img_ref);
  EXPECT_EQ(img_ref, t.get_image<pixel_format::rgba>());
  EXPECT_EQ(sub_img_ref,
    t.get_sub_image<pixel_format::rgba>(vec3u(1u, 2u, 3u), vec3u(3u, 2u, 2u)));
}



TEST_F(test_texture2_array_death_test, set_image_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(3u, 5u, 1u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(3u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(4u, 5u, 2u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(4u, 6u, 1u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(5u, 7u, 3u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(4u, 7u, 3u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(5u, 6u, 3u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(4u, 6u, 3u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(5u, 7u, 2u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(4u, 7u, 2u))));
  EXPECT_PRECOND_ERROR(t.set_image(image3_rgba(vec3u(5u, 6u, 2u))));
}



TEST_F(test_texture2_array_death_test, set_sub_image_invalid_params)
{
  texture2_array t(vec3u(4u, 6u, 2u));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(5u, 7u, 3u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(4u, 7u, 3u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(5u, 6u, 3u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(4u, 6u, 3u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(5u, 7u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(4u, 7u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 0u), image3_rgba(vec3u(5u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(1u, 1u, 1u), image3_rgba(vec3u(4u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 1u, 1u), image3_rgba(vec3u(4u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(1u, 0u, 1u), image3_rgba(vec3u(4u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 0u, 1u), image3_rgba(vec3u(4u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(1u, 1u, 0u), image3_rgba(vec3u(4u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(0u, 1u, 0u), image3_rgba(vec3u(4u, 6u, 2u))));
  EXPECT_PRECOND_ERROR(
    t.set_sub_image(vec3u(1u, 0u, 0u), image3_rgba(vec3u(4u, 6u, 2u))));
}



TEST_F(test_texture2_array, clear)
{
  // clang-format off
  std::vector<uint8_t> image_data{
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    //
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,
    1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u,};
  // clang-format on
  texture2_array t(pixel_view3(image_data.data(), vec3u(2u, 3u, 2u), 4u));
  t.clear();
  EXPECT_EQ(std::vector<uint8_t>(image_data.size(), 0u), t.get_pixels());
}
