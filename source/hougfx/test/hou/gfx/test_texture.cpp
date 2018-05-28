// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.


#include "hou/test.hpp"
#include "hou/gfx/test_data.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/texture.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"

#include "hou/sys/image.hpp"

using namespace hou;
using namespace testing;



namespace
{

template <typename Tex>
class test_texture_base : public test_gfx_base
{
public:
  virtual ~test_texture_base();

  // The following functions are there to generate vectors and images consistent
  // with the concrete texture type being tested (Tex). Without these it would
  // not be possible to write generic tests.
  typename Tex::size_type generate_size();
  typename Tex::size_type compute_mipmap_size(
    const typename Tex::size_type& size, uint mipmap_level);
  typename Tex::template image<pixel_format::rgba> generate_image(
    const typename Tex::size_type& size);
  typename Tex::wrap_mode get_default_wrap_mode() const;
  typename Tex::wrap_mode get_alternative_wrap_mode() const;
};



template <typename Tex>
test_texture_base<Tex>::~test_texture_base()
{}



template <>
typename texture1::size_type test_texture_base<texture1>::generate_size()
{
  return vec1u{4u};
}



template <>
typename texture1_array::size_type
  test_texture_base<texture1_array>::generate_size()
{
  return vec2u{4u, 8u};
}



template <>
typename texture2::size_type test_texture_base<texture2>::generate_size()
{
  return vec2u{4u, 8u};
}



template <>
typename texture2_array::size_type
  test_texture_base<texture2_array>::generate_size()
{
  return vec3u{4u, 8u, 13u};
}



template <>
typename texture3::size_type test_texture_base<texture3>::generate_size()
{
  return vec3u{4u, 8u, 13u};
}



template <>
typename multisample_texture2::size_type
  test_texture_base<multisample_texture2>::generate_size()
{
  return vec2u{4u, 8u};
}



template <>
typename multisample_texture2_array::size_type
  test_texture_base<multisample_texture2_array>::generate_size()
{
  return vec3u{4u, 8u, 13u};
}



template <>
typename texture1::size_type test_texture_base<texture1>::compute_mipmap_size(
  const typename texture1::size_type& size, uint mipmap_level)
{
  return size / std::pow(2, mipmap_level);
}



template <>
typename texture1_array::size_type
  test_texture_base<texture1_array>::compute_mipmap_size(
    const typename texture1_array::size_type& size, uint mipmap_level)
{
  texture1_array::size_type retval = size / std::pow(2, mipmap_level);
  retval.y() = size.y();
  return retval;
}



template <>
typename texture2::size_type test_texture_base<texture2>::compute_mipmap_size(
  const typename texture2::size_type& size, uint mipmap_level)
{
  return size / std::pow(2, mipmap_level);
}



template <>
typename texture2_array::size_type
  test_texture_base<texture2_array>::compute_mipmap_size(
    const typename texture2_array::size_type& size, uint mipmap_level)
{
  texture2_array::size_type retval = size / std::pow(2, mipmap_level);
  retval.z() = size.z();
  return retval;
}



template <>
typename texture3::size_type test_texture_base<texture3>::compute_mipmap_size(
  const typename texture3::size_type& size, uint mipmap_level)
{
  return size / std::pow(2, mipmap_level);
}



template <typename Tex>
typename Tex::template image<pixel_format::rgba>
  test_texture_base<Tex>::generate_image(const typename Tex::size_type& size)
{
  using image = typename Tex::template image<pixel_format::rgba>;
  image im(size);
  typename image::pixel_collection pixels = im.get_pixels();
  for(size_t i = 0; i < pixels.size(); ++i)
  {
    pixels[i].set_r(static_cast<uint8_t>((i * 4) + 0));
    pixels[i].set_g(static_cast<uint8_t>((i * 4) + 1));
    pixels[i].set_b(static_cast<uint8_t>((i * 4) + 2));
    pixels[i].set_a(static_cast<uint8_t>((i * 4) + 3));
  }
  im.set_pixels(pixels);
  return im;
}



template <typename Tex>
typename Tex::wrap_mode test_texture_base<Tex>::get_default_wrap_mode() const
{
  typename Tex::wrap_mode retval;
  for(size_t i = 0; i < retval.size(); ++i)
  {
    retval[i] = texture_wrap_mode::repeat;
  }
  return retval;
}



template <typename Tex>
typename Tex::wrap_mode test_texture_base<Tex>::get_alternative_wrap_mode()
  const
{
  typename Tex::wrap_mode retval;

  std::vector<texture_wrap_mode> wrapModes{texture_wrap_mode::clamp_to_edge,
    texture_wrap_mode::clamp_to_border, texture_wrap_mode::mirrored_repeat};
  for(size_t i = 0; i < retval.size(); ++i)
  {
    retval[i] = wrapModes[i % wrapModes.size()];
  }
  return retval;
}



template <typename Tex>
class test_texture_common : public test_texture_base<Tex>
{};

template <typename Tex>
class test_texture_common_death_test : public test_texture_common<Tex>
{};

using texture_types_common = Types<texture1, texture1_array, texture2,
  texture2_array, texture3, multisample_texture2, multisample_texture2_array>;

template <typename Tex>
class test_texture_not_multisampled : public test_texture_base<Tex>
{};

template <typename Tex>
class test_texture_not_multisampled_death_test
  : public test_texture_not_multisampled<Tex>
{};

using texture_types_not_multisampled
  = Types<texture1, texture1_array, texture2, texture2_array, texture3>;

template <typename Tex>
class test_texture_multisampled : public test_texture_base<Tex>
{};

template <typename Tex>
class test_texture_multisampled_death_test
  : public test_texture_multisampled<Tex>
{};

using texture_types_multisampled
  = Types<multisample_texture2, multisample_texture2_array>;

}  // namespace



TYPED_TEST_CASE(test_texture_common, texture_types_common);
TYPED_TEST_CASE(test_texture_common_death_test, texture_types_common);
TYPED_TEST_CASE(test_texture_not_multisampled, texture_types_not_multisampled);
TYPED_TEST_CASE(
  test_texture_not_multisampled_death_test, texture_types_not_multisampled);
TYPED_TEST_CASE(test_texture_multisampled, texture_types_multisampled);
TYPED_TEST_CASE(
  test_texture_multisampled_death_test, texture_types_multisampled);



TYPED_TEST(test_texture_common, binding)
{
  TypeParam t0(this->generate_size());
  TypeParam t1(this->generate_size());

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



TYPED_TEST(test_texture_common, binding_unit_limit)
{
  TypeParam t(this->generate_size());
  uint max_tex_unit = TypeParam::get_texture_unit_count() - 1u;

  EXPECT_FALSE(t.is_bound(max_tex_unit));
  TypeParam::bind(t, max_tex_unit);
  EXPECT_TRUE(t.is_bound(max_tex_unit));
  TypeParam::unbind(max_tex_unit);
  EXPECT_FALSE(t.is_bound(max_tex_unit));
}



TYPED_TEST(test_texture_common_death_test, binding_error_unit_too_large)
{
  TypeParam t(this->generate_size());
  EXPECT_PRECOND_ERROR(t.is_bound(TypeParam::get_texture_unit_count()));
  EXPECT_PRECOND_ERROR(TypeParam::bind(t, TypeParam::get_texture_unit_count()));
  EXPECT_PRECOND_ERROR(TypeParam::unbind(TypeParam::get_texture_unit_count()));
}



TYPED_TEST(test_texture_common, size_constructor)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  TypeParam tex(size_ref);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(texture_format::rgba, tex.get_format());
  EXPECT_EQ(1u, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(size_ref, tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
}



TYPED_TEST(test_texture_common, size_constructor_size_limits)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_one = size_ref;
    size_with_one(i) = 1u;
    TypeParam tex_with_one(size_with_one);
    EXPECT_EQ(size_with_one, tex_with_one.get_size());

    size_type size_with_max = size_ref;
    size_with_max(i) = max_size(i);
    TypeParam tex_with_max(size_with_max);
    EXPECT_EQ(size_with_max, tex_with_max.get_size());
  }
}



TYPED_TEST(test_texture_common_death_test, size_constructor_error_invalid_size)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_zero = size_ref;
    size_with_zero(i) = 0u;
    EXPECT_PRECOND_ERROR(TypeParam tex(size_with_zero));
    size_type size_too_large = size_ref;
    size_too_large(i) = max_size(i) + 1;
    EXPECT_PRECOND_ERROR(TypeParam tex(size_too_large));
  }
}



TYPED_TEST(test_texture_common, set_channel_mapping)
{
  TypeParam tex(this->generate_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  tex.setChannelMapping(texture_channel_mapping::alpha);
  EXPECT_EQ(texture_channel_mapping::alpha, tex.get_channel_mapping());
  tex.setChannelMapping(texture_channel_mapping::luminosity);
  EXPECT_EQ(texture_channel_mapping::luminosity, tex.get_channel_mapping());
}



TYPED_TEST(test_texture_common, get_single_size_elements)
{
  TypeParam tex(this->generate_size());
  vec3u size_ref(1u, 1u, 1u);
  for(size_t i = 0; i < tex.get_size().size(); ++i)
  {
    size_ref(i) = tex.get_size()(i);
  }

  EXPECT_EQ(tex.get_width(), size_ref.x());
  EXPECT_EQ(tex.get_height(), size_ref.y());
  EXPECT_EQ(tex.get_depth(), size_ref.z());
}



TYPED_TEST(test_texture_common, get_size1)
{
  TypeParam tex(this->generate_size());
  vec1u size_ref(1u);
  for(size_t i = 0; i < std::min(size_ref.size(), tex.get_size().size()); ++i)
  {
    size_ref(i) = tex.get_size()(i);
  }
  EXPECT_EQ(size_ref, tex.get_size1());
}



TYPED_TEST(test_texture_common, get_size2)
{
  TypeParam tex(this->generate_size());
  vec2u size_ref(1u, 1u);
  for(size_t i = 0; i < std::min(size_ref.size(), tex.get_size().size()); ++i)
  {
    size_ref(i) = tex.get_size()(i);
  }
  EXPECT_EQ(size_ref, tex.get_size2());
}



TYPED_TEST(test_texture_common, get_size3)
{
  TypeParam tex(this->generate_size());
  vec3u size_ref(1u, 1u, 1u);
  for(size_t i = 0; i < std::min(size_ref.size(), tex.get_size().size()); ++i)
  {
    size_ref(i) = tex.get_size()(i);
  }
  EXPECT_EQ(size_ref, tex.get_size3());
}



TYPED_TEST(test_texture_not_multisampled, mip_map_constructor)
{
  using image = typename TypeParam::template image<pixel_format::rgb>;
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  texture_format format_ref = texture_format::rgb;
  uint mipMapLevelCount_ref = 3u;
  TypeParam tex(size_ref, format_ref, mipMapLevelCount_ref);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(format_ref, tex.get_format());
  EXPECT_EQ(mipMapLevelCount_ref, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(size_ref, tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  EXPECT_EQ(this->get_default_wrap_mode(), tex.get_wrap_mode());
  EXPECT_EQ(image(tex.get_size()), tex.template get_image<pixel_format::rgb>());
}



TYPED_TEST(test_texture_not_multisampled, mip_map_constructor_size_limits)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_one = size_ref;
    size_with_one(i) = 1u;
    TypeParam tex_with_one(size_with_one, texture_format::rgba, 1u);
    EXPECT_EQ(size_with_one, tex_with_one.get_size());

    size_type size_with_max = size_ref;
    size_with_max(i) = max_size(i);
    TypeParam tex_with_max(size_with_max, texture_format::rgba, 1u);
    EXPECT_EQ(size_with_max, tex_with_max.get_size());
  }
}



TYPED_TEST(
  test_texture_not_multisampled, mip_map_constructor_mip_map_level_count_limits)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  TypeParam texWithMinMipMapLevelcount(size_ref, texture_format::rgba, 1u);
  EXPECT_EQ(1u, texWithMinMipMapLevelcount.get_mipmap_level_count());
  TypeParam texWithMaxMipMapLevelcount(size_ref, texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(size_ref));
  EXPECT_EQ(TypeParam::get_max_mipmap_level_count(size_ref),
    texWithMaxMipMapLevelcount.get_mipmap_level_count());
}



TYPED_TEST(test_texture_not_multisampled_death_test,
  mip_map_constructor_error_invalid_size)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_zero = size_ref;
    size_with_zero(i) = 0u;
    EXPECT_PRECOND_ERROR(
      TypeParam tex(size_with_zero, texture_format::rgba, 1u));
    size_type size_too_large = size_ref;
    size_too_large(i) = max_size(i) + 1;
    EXPECT_PRECOND_ERROR(
      TypeParam tex(size_too_large, texture_format::rgba, 1u));
  }
}



TYPED_TEST(test_texture_not_multisampled_death_test,
  mip_map_constructor_error_invalid_mip_map_level_count)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  EXPECT_PRECOND_ERROR(TypeParam tex(size_ref, texture_format::rgba, 0u));
  EXPECT_PRECOND_ERROR(TypeParam tex(size_ref, texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(size_ref) + 1));
}



TYPED_TEST(test_texture_not_multisampled, image_constructor)
{
  auto image_ref = this->generate_image(this->generate_size());
  texture_format format_ref = texture_format::rgba;
  uint mipMapLevelCount_ref = 3u;
  TypeParam tex(image_ref, texture_format::rgba, mipMapLevelCount_ref);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(format_ref, tex.get_format());
  EXPECT_EQ(mipMapLevelCount_ref, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(image_ref.get_size(), tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  EXPECT_EQ(this->get_default_wrap_mode(), tex.get_wrap_mode());
  EXPECT_EQ(image_ref, tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(test_texture_not_multisampled, image_constructor_default_arguments)
{
  auto image_ref = this->generate_image(this->generate_size());
  TypeParam tex(image_ref);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(texture_format::rgba, tex.get_format());
  EXPECT_EQ(1u, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(image_ref.get_size(), tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  EXPECT_EQ(this->get_default_wrap_mode(), tex.get_wrap_mode());
  EXPECT_EQ(image_ref, tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(test_texture_not_multisampled, image_constructor_size_limits)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_one = size_ref;
    size_with_one(i) = 1u;
    auto imageWithOne = this->generate_image(size_with_one);
    TypeParam tex_with_one(imageWithOne, texture_format::rgba, 1u);
    EXPECT_EQ(
      imageWithOne, tex_with_one.template get_image<pixel_format::rgba>());

    size_type size_with_max = size_ref;
    size_with_max(i) = max_size(i);
    auto imageWithMax = this->generate_image(size_with_max);
    TypeParam tex_with_max(imageWithMax, texture_format::rgba, 1u);
    EXPECT_EQ(
      imageWithMax, tex_with_max.template get_image<pixel_format::rgba>());
  }
}



TYPED_TEST(
  test_texture_not_multisampled, image_constructor_mip_map_level_count_limits)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  TypeParam texWithMinMipMapLevelcount(
    image(size_ref), texture_format::rgba, 1u);
  EXPECT_EQ(1u, texWithMinMipMapLevelcount.get_mipmap_level_count());
  TypeParam texWithMaxMipMapLevelcount(image(size_ref), texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(size_ref));
  EXPECT_EQ(TypeParam::get_max_mipmap_level_count(size_ref),
    texWithMaxMipMapLevelcount.get_mipmap_level_count());
}



TYPED_TEST(test_texture_not_multisampled_death_test,
  image_constructor_error_invalid_size)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_zero = size_ref;
    size_with_zero(i) = 0u;
    EXPECT_PRECOND_ERROR(
      TypeParam tex(image(size_with_zero), texture_format::rgba, 1u));
    size_type size_too_large = size_ref;
    size_too_large(i) = max_size(i) + 1;
    EXPECT_PRECOND_ERROR(
      TypeParam tex(image(size_too_large), texture_format::rgba, 1u));
  }
}



TYPED_TEST(test_texture_not_multisampled_death_test,
  image_constructor_error_invalid_mip_map_level_count)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  EXPECT_PRECOND_ERROR(
    TypeParam tex(image(size_ref), texture_format::rgba, 0u));
  EXPECT_PRECOND_ERROR(TypeParam tex(image(size_ref), texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(size_ref) + 1));
}



TYPED_TEST(test_texture_not_multisampled, set_filter)
{
  TypeParam tex(this->generate_size());
  std::vector<texture_filter> filters
    = {texture_filter::nearest, texture_filter::linear,
      texture_filter::bilinear, texture_filter::trilinear};
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  for(auto filter : filters)
  {
    tex.set_filter(filter);
    EXPECT_EQ(filter, tex.get_filter());
  }
}



TYPED_TEST(test_texture_not_multisampled, set_wrap_mode)
{
  TypeParam tex(this->generate_size());
  EXPECT_EQ(this->get_default_wrap_mode(), tex.get_wrap_mode());
  tex.set_wrap_mode(this->get_alternative_wrap_mode());
  EXPECT_EQ(this->get_alternative_wrap_mode(), tex.get_wrap_mode());
}



TYPED_TEST(test_texture_not_multisampled, set_image)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generate_size());
  EXPECT_EQ(
    image(tex.get_size()), tex.template get_image<pixel_format::rgba>());
  image image_ref = this->generate_image(tex.get_size());
  tex.set_image(image_ref);
  EXPECT_EQ(image_ref, tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(
  test_texture_not_multisampled_death_test, set_image_error_invalid_size)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generate_size());
  EXPECT_PRECOND_ERROR(tex.set_image(image(tex.get_size() * 2)));
}



TYPED_TEST(test_texture_not_multisampled, get_sub_image)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type tex_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < tex_size.size(); ++i)
  {
    tex_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_size(i) = static_cast<uint>((i + 1) * 2);
    sub_image_offset(i) = static_cast<uint>(i + 1);
  }

  image image_ref = this->generate_image(tex_size);
  image sub_image_ref
    = image_ref.get_sub_image(sub_image_offset, sub_image_size);
  TypeParam tex(image_ref);

  // Note MSVC can't deduce the template params, so they must be given
  // explicitly.
  EXPECT_EQ(sub_image_ref,
    (tex.template get_sub_image<image::format, TypeParam::type, void>(
      sub_image_offset, sub_image_size)));
}



TYPED_TEST(
  test_texture_not_multisampled_death_test, get_sub_image_error_overflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type tex_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < tex_size.size(); ++i)
  {
    tex_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_offset(i) = static_cast<uint>(i + 1);
    sub_image_size(i)
      = static_cast<uint>((i + 1) * 4 - sub_image_offset(i) + 1u);
  }
  TypeParam tex(this->generate_image(tex_size));

  // Note MSVC can't deduce the template params, so they must be given
  // explicitly.
  EXPECT_PRECOND_ERROR(
    (tex.template get_sub_image<pixel_format::rgba, TypeParam::type, void>(
      sub_image_offset, sub_image_size)));
}



TYPED_TEST(test_texture_not_multisampled, set_sub_image)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type tex_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < tex_size.size(); ++i)
  {
    tex_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_size(i) = static_cast<uint>((i + 1) * 2);
    sub_image_offset(i) = static_cast<uint>(i + 1);
  }

  typename image::pixel pixel_ref(1u, 2u, 3u, 4u);
  image sub_image_ref(sub_image_size, pixel_ref);
  image image_ref(tex_size);
  image_ref.set_sub_image(sub_image_offset, sub_image_ref);
  TypeParam tex(tex_size);
  tex.template set_sub_image<image::format, TypeParam::type, void>(
    sub_image_offset, sub_image_ref);

  EXPECT_EQ(image_ref,
    (tex.template get_image<image::format, TypeParam::type, void>()));
  EXPECT_EQ(sub_image_ref,
    (tex.template get_sub_image<image::format, TypeParam::type, void>(
      sub_image_offset, sub_image_size)));
}



TYPED_TEST(
  test_texture_not_multisampled_death_test, set_sub_image_error_overflow)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type tex_size;
  size_type sub_image_size;
  offset_type sub_image_offset;
  for(size_t i = 0; i < tex_size.size(); ++i)
  {
    tex_size(i) = static_cast<uint>((i + 1) * 4);
    sub_image_offset(i) = static_cast<uint>(i + 1);
    sub_image_size(i)
      = static_cast<uint>((i + 1) * 4 - sub_image_offset(i) + 1u);
  }

  TypeParam tex(tex_size);
  image sub_image_ref(sub_image_size);
  EXPECT_PRECOND_ERROR(
    (tex.template set_sub_image<image::format, TypeParam::type, void>(
      sub_image_offset, sub_image_ref)));
}



TYPED_TEST(test_texture_not_multisampled, clear)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generate_size());
  EXPECT_EQ(
    image(tex.get_size()), tex.template get_image<pixel_format::rgba>());
  pixel_rgba pixel_ref(1u, 2u, 3u, 4u);
  tex.clear(pixel_ref);
  EXPECT_EQ(image(tex.get_size(), pixel_ref),
    tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(test_texture_not_multisampled, get_mip_map_size)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  TypeParam tex(size_ref, texture_format::rgba, 3u);

  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(this->compute_mipmap_size(size_ref, i), tex.get_mipmap_size(i));
  }
}



TYPED_TEST(test_texture_not_multisampled_death_test,
  get_mip_map_size_error_invalid_mip_map_level)
{
  TypeParam tex(this->generate_size(), texture_format::rgba, 3u);
  EXPECT_PRECOND_ERROR(tex.get_mipmap_size(tex.get_mipmap_level_count() + 1u));
}



TYPED_TEST(test_texture_not_multisampled, mip_map_constructor_get_mip_map_image)
{
  using image = typename TypeParam::template image<pixel_format::rgb>;

  TypeParam tex(this->generate_size(), texture_format::rgba, 3u);

  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(image(tex.get_mipmap_size(i)),
      tex.template get_mipmap_image<pixel_format::rgb>(i));
  }
}



TYPED_TEST(test_texture_not_multisampled, image_constructor_get_mip_map_image)
{
  using image = typename TypeParam::template image<pixel_format::rgb>;

  TypeParam tex(image(this->generate_size()), texture_format::rgba, 3u);

  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(image(tex.get_mipmap_size(i)),
      tex.template get_mipmap_image<pixel_format::rgb>(i));
  }
}



TYPED_TEST(test_texture_not_multisampled, set_image_get_mip_map_image)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type tex_size;
  size_type sub_image_offset;
  size_type sub_image_size;
  for(uint i = 0; i < tex_size.size(); ++i)
  {
    tex_size(i) = (i + 1) * 16;
    sub_image_offset(i) = (i + 1) * 4;
    sub_image_size(i) = (i + 1) * 8;
  }

  TypeParam tex(tex_size, texture_format::rgba, 3u);

  std::vector<image> imageRefs;
  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    imageRefs.push_back(image(tex.get_mipmap_size(i)));
    imageRefs.back().set_sub_image(
      this->compute_mipmap_size(sub_image_offset, i),
      image(this->compute_mipmap_size(sub_image_size, i),
        typename image::pixel(2u, 3u, 5u, 7u)));
  }

  tex.set_image(imageRefs.front());
  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(
      imageRefs[i], tex.template get_mipmap_image<pixel_format::rgba>(i));
  }
}



TYPED_TEST(test_texture_not_multisampled, clear_get_mip_map_image)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generate_size(), texture_format::rgba, 3u);
  pixel_rgba pixel_ref(2u, 3u, 5u, 7u);
  tex.clear(pixel_ref);
  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(image(tex.get_mipmap_size(i), pixel_ref),
      tex.template get_mipmap_image<pixel_format::rgba>(i));
  }
}



TYPED_TEST(test_texture_not_multisampled_death_test,
  get_mip_map_image_error_invalid_mip_map_level)
{
  TypeParam tex(this->generate_size(), texture_format::rgba, 3u);
  EXPECT_PRECOND_ERROR(tex.template get_mipmap_image<pixel_format::rgba>(
    tex.get_mipmap_level_count() + 1u));
}



TYPED_TEST(test_texture_multisampled, multisample_constructor)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  texture_format format_ref = texture_format::rgb;
  uint sample_count_ref = 3u;
  TypeParam tex(size_ref, format_ref, sample_count_ref, false);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(format_ref, tex.get_format());
  EXPECT_EQ(1u, tex.get_mipmap_level_count());
  EXPECT_EQ(sample_count_ref, tex.get_sample_count());
  EXPECT_FALSE(tex.has_fixed_sample_locations());
  EXPECT_EQ(size_ref, tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
}



TYPED_TEST(test_texture_multisampled, multisample_constructor_size_limits)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_one = size_ref;
    size_with_one(i) = 1u;
    TypeParam tex_with_one(size_with_one, texture_format::rgba, 1u, true);
    EXPECT_EQ(size_with_one, tex_with_one.get_size());

    size_type size_with_max = size_ref;
    size_with_max(i) = max_size(i);
    TypeParam tex_with_max(size_with_max, texture_format::rgba, 1u, true);
    EXPECT_EQ(size_with_max, tex_with_max.get_size());
  }
}



TYPED_TEST(
  test_texture_multisampled, multisample_constructor_sample_count_limits)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  TypeParam tex_with_min_sample_count(size_ref, texture_format::rgba, 1u, true);
  EXPECT_EQ(1u, tex_with_min_sample_count.get_sample_count());
  TypeParam tex_with_max_sample_count(
    size_ref, texture_format::rgba, TypeParam::get_max_sample_count(), true);
  EXPECT_EQ(TypeParam::get_max_sample_count(),
    tex_with_max_sample_count.get_sample_count());
}



TYPED_TEST(
  test_texture_multisampled, multisample_constructor_sample_position_values)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  TypeParam texTrue(size_ref, texture_format::rgba, 1u, true);
  EXPECT_TRUE(texTrue.has_fixed_sample_locations());
  TypeParam texFalse(size_ref, texture_format::rgba, 1u, false);
  EXPECT_FALSE(texFalse.has_fixed_sample_locations());
}



TYPED_TEST(test_texture_multisampled_death_test,
  multisample_constructor_error_invalid_size)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  size_type max_size = TypeParam::get_max_size();
  for(size_t i = 0u; i < size_ref.size(); ++i)
  {
    size_type size_with_zero = size_ref;
    size_with_zero(i) = 0u;
    EXPECT_PRECOND_ERROR(
      TypeParam tex(size_with_zero, texture_format::rgba, 1u, true));
    size_type size_too_large = size_ref;
    size_too_large(i) = max_size(i) + 1;
    EXPECT_PRECOND_ERROR(
      TypeParam tex(size_too_large, texture_format::rgba, 1u, true));
  }
}



TYPED_TEST(test_texture_multisampled_death_test,
  multisample_constructor_error_invalid_mip_map)
{
  using size_type = typename TypeParam::size_type;

  size_type size_ref = this->generate_size();
  EXPECT_PRECOND_ERROR(TypeParam tex(size_ref, texture_format::rgba, 0u, true));
  EXPECT_PRECOND_ERROR(TypeParam tex(size_ref, texture_format::rgba,
    TypeParam::get_max_sample_count() + 1, true));
}
