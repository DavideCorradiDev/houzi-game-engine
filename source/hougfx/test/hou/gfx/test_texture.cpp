// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_texture_base.hpp"

#include "hou/gl/gl_functions.hpp"

using namespace hou;
using namespace testing;

namespace
{

template <typename TexType>
using test_texture = test_texture_base<TexType>;
template <typename TexType>
using test_texture_death_test = test_texture<TexType>;

using texture_types = Types<texture2, texture2_array, texture3,
  multisampled_texture2, multisampled_texture2_array>;


}  // namespace



TYPED_TEST_CASE(test_texture, texture_types);
TYPED_TEST_CASE(test_texture_death_test, texture_types);



TYPED_TEST(test_texture, binding)
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



TYPED_TEST(test_texture, binding_unit_limit)
{
  TypeParam t = TestFixture::make_texture();
  uint max_tex_unit = TypeParam::get_texture_unit_count() - 1u;

  EXPECT_FALSE(t.is_bound(max_tex_unit));
  TypeParam::bind(t, max_tex_unit);
  EXPECT_TRUE(t.is_bound(max_tex_unit));
  TypeParam::unbind(max_tex_unit);
  EXPECT_FALSE(t.is_bound(max_tex_unit));
}



TYPED_TEST(test_texture_death_test, binding_error_unit_too_large)
{
  TypeParam t = TestFixture::make_texture();
  EXPECT_PRECOND_ERROR(t.is_bound(TypeParam::get_texture_unit_count()));
  EXPECT_PRECOND_ERROR(TypeParam::bind(t, TypeParam::get_texture_unit_count()));
  EXPECT_PRECOND_ERROR(TypeParam::unbind(TypeParam::get_texture_unit_count()));
}



TYPED_TEST(test_texture, get_handle)
{
  TypeParam t = TestFixture::make_texture();
  EXPECT_NE(0u, t.get_handle().get_name());
}



TYPED_TEST(test_texture, get_format)
{
  // Only test color formats as they are supported by all texture types.
  for(auto format : TestFixture::color_formats)
  {
    TypeParam t = TestFixture::make_texture(format);
    EXPECT_EQ(format, t.get_format()) << format;
  }
}



TYPED_TEST(test_texture, set_channel_mapping)
{
  TypeParam t = TestFixture::make_texture();
  EXPECT_EQ(texture_channel_mapping::standard, t.get_channel_mapping());
  t.set_channel_mapping(texture_channel_mapping::luminosity);
  EXPECT_EQ(texture_channel_mapping::luminosity, t.get_channel_mapping());
  t.set_channel_mapping(texture_channel_mapping::alpha);
  EXPECT_EQ(texture_channel_mapping::alpha, t.get_channel_mapping());
}

