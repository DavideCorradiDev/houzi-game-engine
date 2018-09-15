// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_texture_base.hpp"

#include "hou/gl/gl_functions.hpp"

using namespace hou;
using namespace testing;

namespace
{

using test_multisampled_texture2_array
  = test_texture_base<multisampled_texture2_array>;
using test_multisampled_texture2_array_death_test
  = test_multisampled_texture2_array;

}  // namespace



TEST_F(test_multisampled_texture2_array, size_constructor)
{
  vec3u size_ref(4u, 8u, 3u);
  multisampled_texture2_array t(size_ref);
  EXPECT_EQ(texture_type::multisampled_texture2_array, t.get_type());
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(
    gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), size_ref.z(),
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(t.get_format()))),
    t.get_byte_count());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_sample_count());
  EXPECT_TRUE(t.has_fixed_sample_locations());
}



TEST_F(test_multisampled_texture2_array, size_constructor_size_limits)
{
  vec3u min_size(1u, 1u, 1u);
  multisampled_texture2_array t_min_size(min_size);
  EXPECT_EQ(min_size, t_min_size.get_size());

  vec3u max_size_x(multisampled_texture2_array::get_max_size().x(), 1u, 1u);
  multisampled_texture2_array t_max_size_x(max_size_x);
  EXPECT_EQ(max_size_x, t_max_size_x.get_size());

  vec3u max_size_y(1u, multisampled_texture2_array::get_max_size().y(), 1u);
  multisampled_texture2_array t_max_size_y(max_size_y);
  EXPECT_EQ(max_size_y, t_max_size_y.get_size());

  vec3u max_size_z(1u, 1u, multisampled_texture2_array::get_max_size().z());
  multisampled_texture2_array t_max_size_z(max_size_z);
  EXPECT_EQ(max_size_z, t_max_size_z.get_size());
}



TEST_F(
  test_multisampled_texture2_array_death_test, size_constructor_invalid_size)
{
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(0u, 0u, 0u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(1u, 0u, 0u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(0u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(1u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(0u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(1u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(vec3u(0u, 1u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(1u, 1u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(0u, 1u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(1u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(0u, 0u, 1u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(1u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(0u, 1u, 0u)));
  EXPECT_PRECOND_ERROR(multisampled_texture2_array(
    multisampled_texture2_array::get_max_size() + vec3u(1u, 0u, 0u)));
}



TEST_F(test_multisampled_texture2_array, full_size_constructor)
{
  vec3u size_ref(4u, 8u, 2u);
  uint sample_count_ref = 2u;
  for(auto tf : all_formats)
  {
    multisampled_texture2_array t(size_ref, tf, sample_count_ref);
    EXPECT_EQ(size_ref, t.get_size());
    EXPECT_EQ(tf, t.get_format());
    EXPECT_EQ(sample_count_ref, t.get_sample_count());
    EXPECT_TRUE(t.has_fixed_sample_locations());
  }
}



TEST_F(
  test_multisampled_texture2_array, full_size_constructor_sample_count_limits)
{
  vec3u size_ref(4u, 8u, 2u);

  uint min_sample_count = 1u;
  multisampled_texture2_array t_min_sample(
    size_ref, texture_format::rgba, min_sample_count);
  EXPECT_EQ(min_sample_count, t_min_sample.get_sample_count());

  uint max_sample_count = multisampled_texture2_array::get_max_sample_count();
  multisampled_texture2_array t_max_sample(
    size_ref, texture_format::rgba, max_sample_count);
  EXPECT_EQ(max_sample_count, t_max_sample.get_sample_count());
}



TEST_F(test_multisampled_texture2_array,
  full_size_constructor_fixed_sample_locations)
{
  vec3u size_ref(4u, 8u, 2u);
  texture_format format_ref = texture_format::rgba;
  uint sample_count_ref = 2u;
  std::vector<bool> has_fixed_sample_locations_values = {false, true};
  for(auto fsl : has_fixed_sample_locations_values)
  {
    multisampled_texture2_array t(size_ref, format_ref, sample_count_ref, fsl);
    EXPECT_EQ(size_ref, t.get_size());
    EXPECT_EQ(format_ref, t.get_format());
    EXPECT_EQ(sample_count_ref, t.get_sample_count());
    EXPECT_EQ(fsl, t.has_fixed_sample_locations());
  }
}



TEST_F(test_multisampled_texture2_array_death_test, invalid_sample_count)
{
  EXPECT_PRECOND_ERROR(
    multisampled_texture2_array(vec3u(1u, 1u, 1u), texture_format::rgba,
      multisampled_texture2_array::get_max_sample_count() + 1u));
}



TEST_F(test_multisampled_texture2_array, get_byte_count)
{
  vec3u size_ref(4u, 8u, 2u);
  for(auto tf : all_formats)
  {
    multisampled_texture2_array t(size_ref, tf);
    EXPECT_EQ(
      gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), size_ref.z(),
        gl::get_texture_external_format_for_internal_format(
          static_cast<GLenum>(t.get_format()))),
      t.get_byte_count());
  }
}
