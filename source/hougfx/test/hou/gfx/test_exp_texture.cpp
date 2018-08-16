// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/exp_texture.hpp"

#include "hou/gl/gl_functions.hpp"

using namespace hou;
using namespace hou::exp;
using namespace testing;

namespace
{

template <typename TexType>
class test_exp_texture : public test_gfx_base
{
public:
  static TexType make_texture(texture_format format = texture_format::rgba);

public:
  static const std::vector<texture_format> color_formats;
  static const std::vector<texture_format> all_formats;
  static const std::vector<texture_filter> all_filters;
  static const std::vector<texture_wrap_mode> all_wrap_modes;
};

template <typename TexType>
using test_exp_texture_death_test = test_exp_texture<TexType>;

using texture_types = Types<texture2, texture2_array, texture3,
  multisampled_texture2, multisampled_texture2_array>;

using test_exp_texture2 = test_exp_texture<texture2>;
using test_exp_texture2_death_test = test_exp_texture2;
using test_exp_multisampled_texture2 = test_exp_texture<multisampled_texture2>;
using test_exp_multisampled_texture2_death_test
  = test_exp_multisampled_texture2;
using test_exp_texture2_array = test_exp_texture<texture2_array>;
using test_exp_texture2_array_death_test = test_exp_texture2_array;
using test_exp_texture3 = test_exp_texture<texture3>;
using test_exp_texture3_death_test = test_exp_texture3;
using test_exp_multisampled_texture2_array
  = test_exp_texture<multisampled_texture2_array>;
using test_exp_multisampled_texture2_array_death_test
  = test_exp_multisampled_texture2_array;

template <>
texture2 test_exp_texture<texture2>::make_texture(texture_format format)
{
  return texture2(vec2u(1u, 1u), format);
}

template <>
multisampled_texture2 test_exp_texture<multisampled_texture2>::make_texture(
  texture_format format)
{
  return multisampled_texture2(vec2u(1u, 1u), format);
}

template <>
texture3 test_exp_texture<texture3>::make_texture(texture_format format)
{
  return texture3(vec3u(1u, 1u, 1u), format);
}

template <>
texture2_array test_exp_texture<texture2_array>::make_texture(
  texture_format format)
{
  return texture2_array(vec3u(1u, 1u, 1u), format);
}

template <>
multisampled_texture2_array
  test_exp_texture<multisampled_texture2_array>::make_texture(
    texture_format format)
{
  return multisampled_texture2_array(vec3u(1u, 1u, 1u), format);
}

template <typename TexType>
const std::vector<texture_format> test_exp_texture<TexType>::color_formats{
  texture_format::r,
  texture_format::rg,
  texture_format::rgb,
  texture_format::rgba,
};

template <typename TexType>
const std::vector<texture_format> test_exp_texture<TexType>::all_formats{
  texture_format::r,
  texture_format::rg,
  texture_format::rgb,
  texture_format::rgba,
  texture_format::depth_stencil,
};

template <typename TexType>
const std::vector<texture_filter> test_exp_texture<TexType>::all_filters{
  texture_filter::nearest,
  texture_filter::linear,
  texture_filter::bilinear,
  texture_filter::trilinear,
};

template <typename TexType>
const std::vector<texture_wrap_mode> test_exp_texture<TexType>::all_wrap_modes{
  texture_wrap_mode::repeat,
  texture_wrap_mode::mirrored_repeat,
  texture_wrap_mode::clamp_to_edge,
};

}  // namespace



TYPED_TEST_CASE(test_exp_texture, texture_types);
TYPED_TEST_CASE(test_exp_texture_death_test, texture_types);



TYPED_TEST(test_exp_texture, binding)
{
  TypeParam t0 = TestFixture::make_texture();
  TypeParam t1 = TestFixture::make_texture();

  EXPECT_FALSE(t0.is_bound(0u));
  EXPECT_FALSE(t0.is_bound(1u));
  EXPECT_FALSE(t1.is_bound(0u));
  EXPECT_FALSE(t1.is_bound(1u));

  TypeParam::bind(t0, 1u);
  EXPECT_FALSE(t0.is_bound(0u));
  EXPECT_TRUE(t0.is_bound(1u));
  EXPECT_FALSE(t1.is_bound(0u));
  EXPECT_FALSE(t1.is_bound(1u));

  TypeParam::bind(t0, 0u);
  EXPECT_TRUE(t0.is_bound(0u));
  EXPECT_TRUE(t0.is_bound(1u));
  EXPECT_FALSE(t1.is_bound(0u));
  EXPECT_FALSE(t1.is_bound(1u));

  TypeParam::bind(t1, 1u);
  EXPECT_TRUE(t0.is_bound(0u));
  EXPECT_FALSE(t0.is_bound(1u));
  EXPECT_FALSE(t1.is_bound(0u));
  EXPECT_TRUE(t1.is_bound(1u));

  TypeParam::unbind(0u);
  EXPECT_FALSE(t0.is_bound(0u));
  EXPECT_FALSE(t0.is_bound(1u));
  EXPECT_FALSE(t1.is_bound(0u));
  EXPECT_TRUE(t1.is_bound(1u));

  TypeParam::unbind(1u);
  EXPECT_FALSE(t0.is_bound(0u));
  EXPECT_FALSE(t0.is_bound(1u));
  EXPECT_FALSE(t1.is_bound(0u));
  EXPECT_FALSE(t1.is_bound(1u));
}



TYPED_TEST(test_exp_texture, binding_unit_limit)
{
  TypeParam t = TestFixture::make_texture();
  uint max_tex_unit = TypeParam::get_texture_unit_count() - 1u;

  EXPECT_FALSE(t.is_bound(max_tex_unit));
  TypeParam::bind(t, max_tex_unit);
  EXPECT_TRUE(t.is_bound(max_tex_unit));
  TypeParam::unbind(max_tex_unit);
  EXPECT_FALSE(t.is_bound(max_tex_unit));
}



TYPED_TEST(test_exp_texture_death_test, binding_error_unit_too_large)
{
  TypeParam t = TestFixture::make_texture();
  EXPECT_PRECOND_ERROR(t.is_bound(TypeParam::get_texture_unit_count()));
  EXPECT_PRECOND_ERROR(TypeParam::bind(t, TypeParam::get_texture_unit_count()));
  EXPECT_PRECOND_ERROR(TypeParam::unbind(TypeParam::get_texture_unit_count()));
}



TYPED_TEST(test_exp_texture, get_handle)
{
  TypeParam t = TestFixture::make_texture();
  EXPECT_NE(0u, t.get_handle().get_name());
}



TYPED_TEST(test_exp_texture, get_format)
{
  // Only test color formats as they are supported by all texture types.
  for(auto format : TestFixture::color_formats)
  {
    TypeParam t = TestFixture::make_texture(format);
    EXPECT_EQ(format, t.get_format()) << format;
  }
}



TYPED_TEST(test_exp_texture, set_channel_mapping)
{
  TypeParam t = TestFixture::make_texture();
  EXPECT_EQ(texture_channel_mapping::standard, t.get_channel_mapping());
  t.set_channel_mapping(texture_channel_mapping::luminosity);
  EXPECT_EQ(texture_channel_mapping::luminosity, t.get_channel_mapping());
  t.set_channel_mapping(texture_channel_mapping::alpha);
  EXPECT_EQ(texture_channel_mapping::alpha, t.get_channel_mapping());
}



TEST_F(test_exp_texture2, size_constructor)
{
  vec2u size_ref(4u, 8u);
  texture2 t(size_ref);
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_mipmap_level_count());
  EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_image());
}



TEST_F(test_exp_texture2, size_constructor_size_limits)
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



TEST_F(test_exp_texture2_death_test, size_constructor_invalid_size)
{
  EXPECT_PRECOND_ERROR(texture2(vec2u(0u, 1u)));
  EXPECT_PRECOND_ERROR(texture2(vec2u(1u, 0u)));
  EXPECT_PRECOND_ERROR(texture2(vec2u(0u, 0u)));
  EXPECT_PRECOND_ERROR(texture2(vec2u(texture2::get_max_size().x() + 1u, 1u)));
  EXPECT_PRECOND_ERROR(texture2(vec2u(1u, texture2::get_max_size().y() + 1u)));
  EXPECT_PRECOND_ERROR(texture2(texture2::get_max_size() + vec2u(1u, 1u)));
}



TEST_F(test_exp_texture2, full_size_constructor)
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



TEST_F(test_exp_texture2, full_size_constructor_sample_count_limits)
{
  vec2u size_ref(4u, 8u);

  uint min_mipmap_level_count = 1u;
  texture2 t_min_level(size_ref, texture_format::rgba, min_mipmap_level_count);
  EXPECT_EQ(min_mipmap_level_count, t_min_level.get_mipmap_level_count());

  uint max_mipmap_level_count = 1u;
  texture2 t_max_level(size_ref, texture_format::rgba, max_mipmap_level_count);
  EXPECT_EQ(max_mipmap_level_count, t_max_level.get_mipmap_level_count());
}



TEST_F(test_exp_texture2_death_test, invalid_sample_count)
{
  EXPECT_PRECOND_ERROR(texture2(vec2u(1u, 1u), texture_format::rgba,
    texture2::get_max_mipmap_level_count(vec2u(1u, 1u)) + 1u));
}



TEST_F(test_exp_texture2, image_constructor)
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



TEST_F(test_exp_texture2, image_constructor_with_image)
{
  image2_rgba im(vec2u(4u, 8u), pixel_rgba(color::red()));
  texture2 t(im);
  EXPECT_EQ(im.get_size(), t.get_size());
}



TEST_F(test_exp_texture2_death_test, image_constructor_invalid_size)
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
    image_data.data(), vec2u(texture2::get_max_size().x() + 1u, 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2(pixel_view2(
    image_data.data(), vec2u(1u, texture2::get_max_size().y() + 1u), 4u)));
  EXPECT_PRECOND_ERROR(texture2(pixel_view2(
    image_data.data(), texture2::get_max_size() + vec2u(1u, 1u), 4u)));
}



TEST_F(test_exp_texture2_death_test, image_constructor_invalid_byte_depth)
{
  std::vector<uint8_t> image_data{
    0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u, 10u, 11u};
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 2u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 3u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 4u), texture_format::r));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 1u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 3u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 4u), texture_format::rg));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 1u), texture_format::rgb));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 2u), texture_format::rgb));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 4u), texture_format::rgb));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 1u), texture_format::rgba));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 2u), texture_format::rgba));
  EXPECT_PRECOND_ERROR(texture2(
    pixel_view2(image_data.data(), vec2u(0u, 1u), 3u), texture_format::rgba));
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



TEST_F(test_exp_texture2, get_byte_count)
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



TEST_F(test_exp_texture2, set_filter)
{
  texture2 t(vec2u(1u, 1u));
  EXPECT_EQ(texture_filter::linear, t.get_filter());
  for(auto filter : all_filters)
  {
    t.set_filter(filter);
    EXPECT_EQ(filter, t.get_filter());
  }
}



TEST_F(test_exp_texture2, set_wrap_mode)
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



// get / set image + wrong args.
// get / set sub image + wrong args.
// clear
// set channel mapping



TEST_F(test_exp_multisampled_texture2, size_constructor)
{
  vec2u size_ref(4u, 8u);
  multisampled_texture2 t(size_ref);
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), 1u,
              gl::get_texture_external_format_for_internal_format(
                static_cast<GLenum>(t.get_format()))),
    t.get_byte_count());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_sample_count());
  EXPECT_TRUE(t.has_fixed_sample_locations());
}



TEST_F(test_exp_texture3, size_constructor)
{
  vec3u size_ref(4u, 8u, 3u);
  texture3 t(size_ref);
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(
    gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), size_ref.z(),
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(t.get_format()))),
    t.get_byte_count());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_mipmap_level_count());
  EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_image());
}



TEST_F(test_exp_texture2_array, size_constructor)
{
  vec3u size_ref(4u, 8u, 3u);
  texture2_array t(size_ref);
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(
    gl::compute_texture_size_bytes(size_ref.x(), size_ref.y(), size_ref.z(),
      gl::get_texture_external_format_for_internal_format(
        static_cast<GLenum>(t.get_format()))),
    t.get_byte_count());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_mipmap_level_count());
  EXPECT_EQ(std::vector<uint8_t>(t.get_byte_count(), 0u), t.get_image());
}



TEST_F(test_exp_multisampled_texture2_array, size_constructor)
{
  vec3u size_ref(4u, 8u, 3u);
  multisampled_texture2_array t(size_ref);
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
