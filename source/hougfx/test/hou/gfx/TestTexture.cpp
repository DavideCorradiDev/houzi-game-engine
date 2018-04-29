// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.


#include "hou/Test.hpp"
#include "hou/gfx/TestData.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/texture.hpp"
#include "hou/gfx/texture_channel_mapping.hpp"

#include "hou/gl/gl_error.hpp"

#include "hou/sys/image.hpp"

using namespace hou;
using namespace testing;



namespace
{

template <typename Tex>
class TestTextureBase : public TestGfxBase
{
public:
  virtual ~TestTextureBase();

  // The following functions are there to generate vectors and images consistent
  // with the concrete texture type being tested (Tex). Without these it would
  // not be possible to write generic tests.
  typename Tex::size_type generateSize();
  typename Tex::size_type computeMipMapSize(
    const typename Tex::size_type& size, uint mipMapLevel);
  typename Tex::template image<pixel_format::rgba> generateImage(
    const typename Tex::size_type& size);
  typename Tex::wrap_mode getDefaultWrapMode() const;
  typename Tex::wrap_mode getAlternativeWrapMode() const;
};



template <typename Tex>
TestTextureBase<Tex>::~TestTextureBase()
{}



template <>
typename texture1::size_type TestTextureBase<texture1>::generateSize()
{
  return vec1u{4u};
}



template <>
typename texture1_array::size_type TestTextureBase<texture1_array>::generateSize()
{
  return vec2u{4u, 8u};
}



template <>
typename texture2::size_type TestTextureBase<texture2>::generateSize()
{
  return vec2u{4u, 8u};
}



template <>
typename texture2_array::size_type TestTextureBase<texture2_array>::generateSize()
{
  return vec3u{4u, 8u, 13u};
}



template <>
typename texture3::size_type TestTextureBase<texture3>::generateSize()
{
  return vec3u{4u, 8u, 13u};
}



template <>
typename multisample_texture2::size_type
  TestTextureBase<multisample_texture2>::generateSize()
{
  return vec2u{4u, 8u};
}



template <>
typename multisample_texture2_array::size_type
  TestTextureBase<multisample_texture2_array>::generateSize()
{
  return vec3u{4u, 8u, 13u};
}



template <>
typename texture1::size_type TestTextureBase<texture1>::computeMipMapSize(
  const typename texture1::size_type& size, uint mipMapLevel)
{
  return size / std::pow(2, mipMapLevel);
}



template <>
typename texture1_array::size_type TestTextureBase<texture1_array>::computeMipMapSize(
  const typename texture1_array::size_type& size, uint mipMapLevel)
{
  texture1_array::size_type retval = size / std::pow(2, mipMapLevel);
  retval.y() = size.y();
  return retval;
}



template <>
typename texture2::size_type TestTextureBase<texture2>::computeMipMapSize(
  const typename texture2::size_type& size, uint mipMapLevel)
{
  return size / std::pow(2, mipMapLevel);
}



template <>
typename texture2_array::size_type TestTextureBase<texture2_array>::computeMipMapSize(
  const typename texture2_array::size_type& size, uint mipMapLevel)
{
  texture2_array::size_type retval = size / std::pow(2, mipMapLevel);
  retval.z() = size.z();
  return retval;
}



template <>
typename texture3::size_type TestTextureBase<texture3>::computeMipMapSize(
  const typename texture3::size_type& size, uint mipMapLevel)
{
  return size / std::pow(2, mipMapLevel);
}



template <typename Tex>
typename Tex::template image<pixel_format::rgba>
  TestTextureBase<Tex>::generateImage(const typename Tex::size_type& size)
{
  using image = typename Tex::template image<pixel_format::rgba>;
  image im(size);
  typename image::pixel_collection pixels = im.get_pixels();
  for(size_t i = 0; i < pixels.size(); ++i)
  {
    pixels[i].set_r((i * 4) + 0);
    pixels[i].set_g((i * 4) + 1);
    pixels[i].set_b((i * 4) + 2);
    pixels[i].set_a((i * 4) + 3);
  }
  im.set_pixels(pixels);
  return im;
}



template <typename Tex>
typename Tex::wrap_mode TestTextureBase<Tex>::getDefaultWrapMode() const
{
  typename Tex::wrap_mode retval;
  for(size_t i = 0; i < retval.size(); ++i)
  {
    retval[i] = texture_wrap_mode::repeat;
  }
  return retval;
}



template <typename Tex>
typename Tex::wrap_mode TestTextureBase<Tex>::getAlternativeWrapMode() const
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
class TestTextureCommon : public TestTextureBase<Tex>
{};

template <typename Tex>
class TestTextureCommonDeathTest : public TestTextureCommon<Tex>
{};

using TextureTypesCommon = Types<texture1, texture1_array, texture2,
  texture2_array, texture3, multisample_texture2, multisample_texture2_array>;

template <typename Tex>
class TestTextureNotMultisampled : public TestTextureBase<Tex>
{};

template <typename Tex>
class TestTextureNotMultisampledDeathTest
  : public TestTextureNotMultisampled<Tex>
{};

using TextureTypesNotMultisampled
  = Types<texture1, texture1_array, texture2, texture2_array, texture3>;

template <typename Tex>
class TestTextureMultisampled : public TestTextureBase<Tex>
{};

template <typename Tex>
class TestTextureMultisampledDeathTest : public TestTextureMultisampled<Tex>
{};

using TextureTypesMultisampled
  = Types<multisample_texture2, multisample_texture2_array>;

}  // namespace



TYPED_TEST_CASE(TestTextureCommon, TextureTypesCommon);
TYPED_TEST_CASE(TestTextureCommonDeathTest, TextureTypesCommon);
TYPED_TEST_CASE(TestTextureNotMultisampled, TextureTypesNotMultisampled);
TYPED_TEST_CASE(
  TestTextureNotMultisampledDeathTest, TextureTypesNotMultisampled);
TYPED_TEST_CASE(TestTextureMultisampled, TextureTypesMultisampled);
TYPED_TEST_CASE(TestTextureMultisampledDeathTest, TextureTypesMultisampled);



TYPED_TEST(TestTextureCommon, Binding)
{
  TypeParam t0(this->generateSize());
  TypeParam t1(this->generateSize());

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



TYPED_TEST(TestTextureCommon, BindingUnitLimit)
{
  TypeParam t(this->generateSize());
  uint maxTexUnit = TypeParam::get_texture_unit_count() - 1u;

  EXPECT_FALSE(t.is_bound(maxTexUnit));
  TypeParam::bind(t, maxTexUnit);
  EXPECT_TRUE(t.is_bound(maxTexUnit));
  TypeParam::unbind(maxTexUnit);
  EXPECT_FALSE(t.is_bound(maxTexUnit));
}



TYPED_TEST(TestTextureCommonDeathTest, BindingErrorUnitTooLarge)
{
  TypeParam t(this->generateSize());
  HOU_EXPECT_PRECONDITION(t.is_bound(TypeParam::get_texture_unit_count()));
  HOU_EXPECT_PRECONDITION(TypeParam::bind(t, TypeParam::get_texture_unit_count()));
  HOU_EXPECT_PRECONDITION(TypeParam::unbind(TypeParam::get_texture_unit_count()));
}



TYPED_TEST(TestTextureCommon, SizeConstructor)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  TypeParam tex(sizeRef);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(texture_format::rgba, tex.get_format());
  EXPECT_EQ(1u, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(sizeRef, tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
}



TYPED_TEST(TestTextureCommon, SizeConstructorSizeLimits)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    TypeParam texWithOne(sizeWithOne);
    EXPECT_EQ(sizeWithOne, texWithOne.get_size());

    size_type sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    TypeParam texWithMax(sizeWithMax);
    EXPECT_EQ(sizeWithMax, texWithMax.get_size());
  }
}



TYPED_TEST(TestTextureCommonDeathTest, SizeConstructorErrorInvalidSize)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(TypeParam tex(sizeWithNull));
    size_type sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(TypeParam tex(sizeTooBig));
  }
}



TYPED_TEST(TestTextureCommon, SetChannelMapping)
{
  TypeParam tex(this->generateSize());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  tex.setChannelMapping(texture_channel_mapping::alpha);
  EXPECT_EQ(texture_channel_mapping::alpha, tex.get_channel_mapping());
  tex.setChannelMapping(texture_channel_mapping::luminosity);
  EXPECT_EQ(texture_channel_mapping::luminosity, tex.get_channel_mapping());
}



TYPED_TEST(TestTextureCommon, GetSingleSizeElements)
{
  TypeParam tex(this->generateSize());
  vec3u sizeRef(1u, 1u, 1u);
  for(size_t i = 0; i < tex.get_size().get_size(); ++i)
  {
    sizeRef(i) = tex.get_size()(i);
  }

  EXPECT_EQ(tex.get_width(), sizeRef.x());
  EXPECT_EQ(tex.get_height(), sizeRef.y());
  EXPECT_EQ(tex.get_depth(), sizeRef.z());
}



TYPED_TEST(TestTextureCommon, GetSize1)
{
  TypeParam tex(this->generateSize());
  vec1u sizeRef(1u);
  for(size_t i = 0; i < std::min(sizeRef.get_size(), tex.get_size().get_size());
      ++i)
  {
    sizeRef(i) = tex.get_size()(i);
  }
  EXPECT_EQ(sizeRef, tex.get_size1());
}



TYPED_TEST(TestTextureCommon, GetSize2)
{
  TypeParam tex(this->generateSize());
  vec2u sizeRef(1u, 1u);
  for(size_t i = 0; i < std::min(sizeRef.get_size(), tex.get_size().get_size());
      ++i)
  {
    sizeRef(i) = tex.get_size()(i);
  }
  EXPECT_EQ(sizeRef, tex.get_size2());
}



TYPED_TEST(TestTextureCommon, GetSize3)
{
  TypeParam tex(this->generateSize());
  vec3u sizeRef(1u, 1u, 1u);
  for(size_t i = 0; i < std::min(sizeRef.get_size(), tex.get_size().get_size());
      ++i)
  {
    sizeRef(i) = tex.get_size()(i);
  }
  EXPECT_EQ(sizeRef, tex.get_size3());
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructor)
{
  using image = typename TypeParam::template image<pixel_format::rgb>;
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  texture_format formatRef = texture_format::rgb;
  uint mipMapLevelCountRef = 3u;
  TypeParam tex(sizeRef, formatRef, mipMapLevelCountRef);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(formatRef, tex.get_format());
  EXPECT_EQ(mipMapLevelCountRef, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(sizeRef, tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.get_wrap_mode());
  EXPECT_EQ(image(tex.get_size()), tex.template get_image<pixel_format::rgb>());
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructorSizeLimits)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    TypeParam texWithOne(sizeWithOne, texture_format::rgba, 1u);
    EXPECT_EQ(sizeWithOne, texWithOne.get_size());

    size_type sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    TypeParam texWithMax(sizeWithMax, texture_format::rgba, 1u);
    EXPECT_EQ(sizeWithMax, texWithMax.get_size());
  }
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructorMipMapLevelCountLimits)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  TypeParam texWithMinMipMapLevelcount(sizeRef, texture_format::rgba, 1u);
  EXPECT_EQ(1u, texWithMinMipMapLevelcount.get_mipmap_level_count());
  TypeParam texWithMaxMipMapLevelcount(
    sizeRef, texture_format::rgba, TypeParam::get_max_mipmap_level_count(sizeRef));
  EXPECT_EQ(TypeParam::get_max_mipmap_level_count(sizeRef),
    texWithMaxMipMapLevelcount.get_mipmap_level_count());
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, MipMapConstructorErrorInvalidSize)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(sizeWithNull, texture_format::rgba, 1u));
    size_type sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(TypeParam tex(sizeTooBig, texture_format::rgba, 1u));
  }
}



TYPED_TEST(TestTextureNotMultisampledDeathTest,
  MipMapConstructorErrorInvalidMipMapLevelCount)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  HOU_EXPECT_PRECONDITION(TypeParam tex(sizeRef, texture_format::rgba, 0u));
  HOU_EXPECT_PRECONDITION(TypeParam tex(sizeRef, texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(sizeRef) + 1));
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructor)
{
  auto imageRef = this->generateImage(this->generateSize());
  texture_format formatRef = texture_format::rgba;
  uint mipMapLevelCountRef = 3u;
  TypeParam tex(imageRef, texture_format::rgba, mipMapLevelCountRef);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(formatRef, tex.get_format());
  EXPECT_EQ(mipMapLevelCountRef, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(imageRef.get_size(), tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.get_wrap_mode());
  EXPECT_EQ(imageRef, tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorDefaultArguments)
{
  auto imageRef = this->generateImage(this->generateSize());
  TypeParam tex(imageRef);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(texture_format::rgba, tex.get_format());
  EXPECT_EQ(1u, tex.get_mipmap_level_count());
  EXPECT_EQ(1u, tex.get_sample_count());
  EXPECT_TRUE(tex.has_fixed_sample_locations());
  EXPECT_EQ(imageRef.get_size(), tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.get_wrap_mode());
  EXPECT_EQ(imageRef, tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorSizeLimits)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    auto imageWithOne = this->generateImage(sizeWithOne);
    TypeParam texWithOne(imageWithOne, texture_format::rgba, 1u);
    EXPECT_EQ(imageWithOne, texWithOne.template get_image<pixel_format::rgba>());

    size_type sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    auto imageWithMax = this->generateImage(sizeWithMax);
    TypeParam texWithMax(imageWithMax, texture_format::rgba, 1u);
    EXPECT_EQ(imageWithMax, texWithMax.template get_image<pixel_format::rgba>());
  }
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorMipMapLevelCountLimits)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  TypeParam texWithMinMipMapLevelcount(image(sizeRef), texture_format::rgba, 1u);
  EXPECT_EQ(1u, texWithMinMipMapLevelcount.get_mipmap_level_count());
  TypeParam texWithMaxMipMapLevelcount(image(sizeRef), texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(sizeRef));
  EXPECT_EQ(TypeParam::get_max_mipmap_level_count(sizeRef),
    texWithMaxMipMapLevelcount.get_mipmap_level_count());
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, ImageConstructorErrorInvalidSize)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(image(sizeWithNull), texture_format::rgba, 1u));
    size_type sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(image(sizeTooBig), texture_format::rgba, 1u));
  }
}



TYPED_TEST(TestTextureNotMultisampledDeathTest,
  ImageConstructorErrorInvalidMipMapLevelCount)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  HOU_EXPECT_PRECONDITION(
    TypeParam tex(image(sizeRef), texture_format::rgba, 0u));
  HOU_EXPECT_PRECONDITION(TypeParam tex(image(sizeRef), texture_format::rgba,
    TypeParam::get_max_mipmap_level_count(sizeRef) + 1));
}



TYPED_TEST(TestTextureNotMultisampled, SetFilter)
{
  TypeParam tex(this->generateSize());
  std::vector<texture_filter> filters = {texture_filter::nearest,
    texture_filter::linear, texture_filter::bilinear, texture_filter::trilinear};
  EXPECT_EQ(texture_filter::linear, tex.get_filter());
  for(auto filter : filters)
  {
    tex.set_filter(filter);
    EXPECT_EQ(filter, tex.get_filter());
  }
}



TYPED_TEST(TestTextureNotMultisampled, SetWrapMode)
{
  TypeParam tex(this->generateSize());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.get_wrap_mode());
  tex.set_wrap_mode(this->getAlternativeWrapMode());
  EXPECT_EQ(this->getAlternativeWrapMode(), tex.get_wrap_mode());
}



TYPED_TEST(TestTextureNotMultisampled, SetImage)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generateSize());
  EXPECT_EQ(image(tex.get_size()), tex.template get_image<pixel_format::rgba>());
  image imageRef = this->generateImage(tex.get_size());
  tex.set_image(imageRef);
  EXPECT_EQ(imageRef, tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(TestTextureNotMultisampledDeathTest, SetImageErrorInvalidSize)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generateSize());
  HOU_EXPECT_PRECONDITION(tex.set_image(image(tex.get_size() * 2)));
}



TYPED_TEST(TestTextureNotMultisampled, GetSubImage)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type texSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < texSize.get_size(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  image imageRef = this->generateImage(texSize);
  image subImageRef = imageRef.get_sub_image(subImageOffset, subImageSize);
  TypeParam tex(imageRef);

  EXPECT_EQ(subImageRef,
    tex.template get_sub_image<pixel_format::rgba>(subImageOffset, subImageSize));
}



TYPED_TEST(TestTextureNotMultisampledDeathTest, GetSubImageErrorOverflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type texSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < texSize.get_size(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }
  TypeParam tex(this->generateImage(texSize));
  HOU_EXPECT_PRECONDITION(
    tex.template get_sub_image<pixel_format::rgba>(subImageOffset, subImageSize));
}



TYPED_TEST(TestTextureNotMultisampled, SetSubImage)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type texSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < texSize.get_size(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  typename image::pixel pixelRef(1u, 2u, 3u, 4u);
  image subImageRef(subImageSize, pixelRef);
  image imageRef(texSize);
  imageRef.set_sub_image(subImageOffset, subImageRef);
  TypeParam tex(texSize);
  tex.set_sub_image(subImageOffset, subImageRef);

  EXPECT_EQ(imageRef, tex.template get_image<pixel_format::rgba>());
  EXPECT_EQ(subImageRef,
    tex.template get_sub_image<pixel_format::rgba>(subImageOffset, subImageSize));
}



TYPED_TEST(TestTextureNotMultisampledDeathTest, SetSubImageErrorOverflow)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type texSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < texSize.get_size(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam tex(texSize);
  image subImageRef(subImageSize);
  HOU_EXPECT_PRECONDITION(tex.set_sub_image(subImageOffset, subImageRef));
}



TYPED_TEST(TestTextureNotMultisampled, Clear)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generateSize());
  EXPECT_EQ(image(tex.get_size()), tex.template get_image<pixel_format::rgba>());
  pixelrgba pixelRef(1u, 2u, 3u, 4u);
  tex.clear(pixelRef);
  EXPECT_EQ(
    image(tex.get_size(), pixelRef), tex.template get_image<pixel_format::rgba>());
}



TYPED_TEST(TestTextureNotMultisampled, GetMipMapSize)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  TypeParam tex(sizeRef, texture_format::rgba, 3u);

  for(size_t i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(this->computeMipMapSize(sizeRef, i), tex.get_mipmap_size(i));
  }
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, GetMipMapSizeErrorInvalidMipMapLevel)
{
  TypeParam tex(this->generateSize(), texture_format::rgba, 3u);
  HOU_EXPECT_PRECONDITION(tex.get_mipmap_size(tex.get_mipmap_level_count() + 1u));
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructorGetMipMapImage)
{
  using image = typename TypeParam::template image<pixel_format::rgb>;

  TypeParam tex(this->generateSize(), texture_format::rgba, 3u);

  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(image(tex.get_mipmap_size(i)),
      tex.template get_mipmap_image<pixel_format::rgb>(i));
  }
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorGetMipMapImage)
{
  using image = typename TypeParam::template image<pixel_format::rgb>;

  TypeParam tex(image(this->generateSize()), texture_format::rgba, 3u);

  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(image(tex.get_mipmap_size(i)),
      tex.template get_mipmap_image<pixel_format::rgb>(i));
  }
}



TYPED_TEST(TestTextureNotMultisampled, SetImageGetMipMapImage)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;
  using size_type = typename TypeParam::size_type;

  size_type texSize;
  size_type subImageOffset;
  size_type subImageSize;
  for(size_t i = 0; i < texSize.get_size(); ++i)
  {
    texSize(i) = (i + 1) * 16;
    subImageOffset(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 8;
  }

  TypeParam tex(texSize, texture_format::rgba, 3u);

  std::vector<image> imageRefs;
  for(uint i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    imageRefs.push_back(image(tex.get_mipmap_size(i)));
    imageRefs.back().set_sub_image(this->computeMipMapSize(subImageOffset, i),
      image(this->computeMipMapSize(subImageSize, i),
        typename image::pixel(2u, 3u, 5u, 7u)));
  }

  tex.set_image(imageRefs.front());
  for(size_t i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(imageRefs[i], tex.template get_mipmap_image<pixel_format::rgba>(i));
  }
}



TYPED_TEST(TestTextureNotMultisampled, ClearGetMipMapImage)
{
  using image = typename TypeParam::template image<pixel_format::rgba>;

  TypeParam tex(this->generateSize(), texture_format::rgba, 3u);
  pixelrgba pixelRef(2u, 3u, 5u, 7u);
  tex.clear(pixelRef);
  for(size_t i = 0; i < tex.get_mipmap_level_count(); ++i)
  {
    EXPECT_EQ(image(tex.get_mipmap_size(i), pixelRef),
      tex.template get_mipmap_image<pixel_format::rgba>(i));
  }
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, GetMipMapImageErrorInvalidMipMapLevel)
{
  TypeParam tex(this->generateSize(), texture_format::rgba, 3u);
  HOU_EXPECT_PRECONDITION(tex.template get_mipmap_image<pixel_format::rgba>(
    tex.get_mipmap_level_count() + 1u));
}



// TYPED_TEST(TestTextureNotMultisampled, FormatRGBA)
// {
//   // Requires compile time iterations.
//   constexpr std::array<pixel_format, 4u> pixelFormats{
//     pixel_format::rgba, pixel_format::rgb, pixel_format::rg, pixel_format::r};
//
//   constexpr std::array<texture_format, 7u> textureFormats{
//     texture_format::rgba,
//     texture_format::rgb,
//     texture_format::rg,
//     texture_format::r,
//     texture_format::depth,
//     texture_format::stencil,
//     texture_format::depth_stencil,
//   };
//
//   for(constexpr auto tf : textureFormats)
//   {
//     for(constexpr auto pfIn : pixelFormats)
//     {
//       typename TypeParam::template image<pfIn>
//       im(this->generaImage(this->generateSize())); TypeParam tex(im, tf);
//       for(constexpr auto pfOut : pixelFormats)
//       {
//         EXPECT_EQ(typename TypeParam::template image<pfOut>(im), tex.template
//         get_image<pfOut>())
//           << "texture Format = " << tf
//           << ", Input pixel Format = " << pfIn
//           << ", OutputPixel Format = " << pfOut;
//       }
//     }
//   }
// }



TYPED_TEST(TestTextureMultisampled, MultisampleConstructor)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  texture_format formatRef = texture_format::rgb;
  uint sampleCountRef = 3u;
  TypeParam tex(sizeRef, formatRef, sampleCountRef, false);

  EXPECT_NE(0u, tex.get_handle().get_name());
  EXPECT_EQ(formatRef, tex.get_format());
  EXPECT_EQ(1u, tex.get_mipmap_level_count());
  EXPECT_EQ(sampleCountRef, tex.get_sample_count());
  EXPECT_FALSE(tex.has_fixed_sample_locations());
  EXPECT_EQ(sizeRef, tex.get_size());
  EXPECT_EQ(texture_channel_mapping::standard, tex.get_channel_mapping());
}



TYPED_TEST(TestTextureMultisampled, MultisampleConstructorSizeLimits)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    TypeParam texWithOne(sizeWithOne, texture_format::rgba, 1u, true);
    EXPECT_EQ(sizeWithOne, texWithOne.get_size());

    size_type sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    TypeParam texWithMax(sizeWithMax, texture_format::rgba, 1u, true);
    EXPECT_EQ(sizeWithMax, texWithMax.get_size());
  }
}



TYPED_TEST(TestTextureMultisampled, MultisampleConstructorSampleCountLimits)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  TypeParam texWithMinSampleCount(sizeRef, texture_format::rgba, 1u, true);
  EXPECT_EQ(1u, texWithMinSampleCount.get_sample_count());
  TypeParam texWithMaxSampleCount(
    sizeRef, texture_format::rgba, TypeParam::get_max_sample_count(), true);
  EXPECT_EQ(
    TypeParam::get_max_sample_count(), texWithMaxSampleCount.get_sample_count());
}



TYPED_TEST(TestTextureMultisampled, MultisampleConstructorSamplePositionValues)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  TypeParam texTrue(sizeRef, texture_format::rgba, 1u, true);
  EXPECT_TRUE(texTrue.has_fixed_sample_locations());
  TypeParam texFalse(sizeRef, texture_format::rgba, 1u, false);
  EXPECT_FALSE(texFalse.has_fixed_sample_locations());
}



TYPED_TEST(
  TestTextureMultisampledDeathTest, MultisampleConstructorErrorInvalidSize)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  size_type maxSize = TypeParam::get_max_size();
  for(size_t i = 0u; i < sizeRef.get_size(); ++i)
  {
    size_type sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(sizeWithNull, texture_format::rgba, 1u, true));
    size_type sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(sizeTooBig, texture_format::rgba, 1u, true));
  }
}



TYPED_TEST(
  TestTextureMultisampledDeathTest, MultisampleConstructorErrorInvalidMipMap)
{
  using size_type = typename TypeParam::size_type;

  size_type sizeRef = this->generateSize();
  HOU_EXPECT_PRECONDITION(
    TypeParam tex(sizeRef, texture_format::rgba, 0u, true));
  HOU_EXPECT_PRECONDITION(TypeParam tex(
    sizeRef, texture_format::rgba, TypeParam::get_max_sample_count() + 1, true));
}
