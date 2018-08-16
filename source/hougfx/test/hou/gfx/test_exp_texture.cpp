// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/exp_texture.hpp"

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
  texture_format::depth,
  texture_format::depth_stencil,
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



TEST_F(test_exp_texture2, size_constructor)
{
  vec2u size_ref(4u, 8u);
  texture2 t(size_ref);
  EXPECT_EQ(size_ref, t.get_size());
  EXPECT_EQ(texture_format::rgba, t.get_format());
  EXPECT_EQ(1u, t.get_mipmap_level_count());
  EXPECT_EQ(texture_filter::bilinear, t.get_filter());
  EXPECT_EQ(
    (texture2::wrap_mode{texture_wrap_mode::repeat, texture_wrap_mode::repeat}),
    t.get_wrap_mode());
}
