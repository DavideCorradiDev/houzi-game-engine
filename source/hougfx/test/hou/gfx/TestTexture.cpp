// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.


#include "hou/Test.hpp"
#include "hou/gfx/TestData.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/Texture.hpp"
#include "hou/gfx/TextureChannelMapping.hpp"

#include "hou/gl/GlError.hpp"

#include "hou/sys/Image.hpp"

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
  // with the concrete Texture type being tested (Tex). Without these it would
  // not be possible to write generic tests.
  typename Tex::Size generateSize();
  typename Tex::Size computeMipMapSize(
    const typename Tex::Size& size, uint mipMapLevel);
  typename Tex::template Image<PixelFormat::RGBA> generateImage(
    const typename Tex::Size& size);
  typename Tex::WrapMode getDefaultWrapMode() const;
  typename Tex::WrapMode getAlternativeWrapMode() const;
};



template <typename Tex>
TestTextureBase<Tex>::~TestTextureBase()
{}



template <>
typename Texture1::Size TestTextureBase<Texture1>::generateSize()
{
  return Vec1u{4u};
}



template <>
typename Texture1Array::Size TestTextureBase<Texture1Array>::generateSize()
{
  return Vec2u{4u, 8u};
}



template <>
typename Texture2::Size TestTextureBase<Texture2>::generateSize()
{
  return Vec2u{4u, 8u};
}



template <>
typename Texture2Array::Size TestTextureBase<Texture2Array>::generateSize()
{
  return Vec3u{4u, 8u, 13u};
}



template <>
typename Texture3::Size TestTextureBase<Texture3>::generateSize()
{
  return Vec3u{4u, 8u, 13u};
}



template <>
typename MultisampleTexture2::Size
  TestTextureBase<MultisampleTexture2>::generateSize()
{
  return Vec2u{4u, 8u};
}



template <>
typename MultisampleTexture2Array::Size
  TestTextureBase<MultisampleTexture2Array>::generateSize()
{
  return Vec3u{4u, 8u, 13u};
}



template <>
typename Texture1::Size TestTextureBase<Texture1>::computeMipMapSize(
  const typename Texture1::Size& size, uint mipMapLevel)
{
  return size / std::pow(2, mipMapLevel);
}



template <>
typename Texture1Array::Size TestTextureBase<Texture1Array>::computeMipMapSize(
  const typename Texture1Array::Size& size, uint mipMapLevel)
{
  Texture1Array::Size retval = size / std::pow(2, mipMapLevel);
  retval.y() = size.y();
  return retval;
}



template <>
typename Texture2::Size TestTextureBase<Texture2>::computeMipMapSize(
  const typename Texture2::Size& size, uint mipMapLevel)
{
  return size / std::pow(2, mipMapLevel);
}



template <>
typename Texture2Array::Size TestTextureBase<Texture2Array>::computeMipMapSize(
  const typename Texture2Array::Size& size, uint mipMapLevel)
{
  Texture2Array::Size retval = size / std::pow(2, mipMapLevel);
  retval.z() = size.z();
  return retval;
}



template <>
typename Texture3::Size TestTextureBase<Texture3>::computeMipMapSize(
  const typename Texture3::Size& size, uint mipMapLevel)
{
  return size / std::pow(2, mipMapLevel);
}



template <typename Tex>
typename Tex::template Image<PixelFormat::RGBA>
  TestTextureBase<Tex>::generateImage(const typename Tex::Size& size)
{
  using Image = typename Tex::template Image<PixelFormat::RGBA>;
  Image im(size);
  typename Image::PixelCollection pixels = im.getPixels();
  for(size_t i = 0; i < pixels.size(); ++i)
  {
    pixels[i].setR((i * 4) + 0);
    pixels[i].setG((i * 4) + 1);
    pixels[i].setB((i * 4) + 2);
    pixels[i].setA((i * 4) + 3);
  }
  im.setPixels(pixels);
  return im;
}



template <typename Tex>
typename Tex::WrapMode TestTextureBase<Tex>::getDefaultWrapMode() const
{
  typename Tex::WrapMode retval;
  for(size_t i = 0; i < retval.size(); ++i)
  {
    retval[i] = TextureWrapMode::Repeat;
  }
  return retval;
}



template <typename Tex>
typename Tex::WrapMode TestTextureBase<Tex>::getAlternativeWrapMode() const
{
  typename Tex::WrapMode retval;

  std::vector<TextureWrapMode> wrapModes{TextureWrapMode::ClampToEdge,
    TextureWrapMode::ClampToBorder, TextureWrapMode::MirroredRepeat};
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

using TextureTypesCommon = Types<Texture1, Texture1Array, Texture2,
  Texture2Array, Texture3, MultisampleTexture2, MultisampleTexture2Array>;

template <typename Tex>
class TestTextureNotMultisampled : public TestTextureBase<Tex>
{};

template <typename Tex>
class TestTextureNotMultisampledDeathTest
  : public TestTextureNotMultisampled<Tex>
{};

using TextureTypesNotMultisampled
  = Types<Texture1, Texture1Array, Texture2, Texture2Array, Texture3>;

template <typename Tex>
class TestTextureMultisampled : public TestTextureBase<Tex>
{};

template <typename Tex>
class TestTextureMultisampledDeathTest : public TestTextureMultisampled<Tex>
{};

using TextureTypesMultisampled
  = Types<MultisampleTexture2, MultisampleTexture2Array>;

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

  EXPECT_FALSE(t0.isBound(0u));
  EXPECT_FALSE(t0.isBound(1u));
  EXPECT_FALSE(t1.isBound(0u));
  EXPECT_FALSE(t1.isBound(1u));

  TypeParam::bind(t0, 1u);
  EXPECT_FALSE(t0.isBound(0u));
  EXPECT_TRUE(t0.isBound(1u));
  EXPECT_FALSE(t1.isBound(0u));
  EXPECT_FALSE(t1.isBound(1u));

  TypeParam::bind(t0, 0u);
  EXPECT_TRUE(t0.isBound(0u));
  EXPECT_TRUE(t0.isBound(1u));
  EXPECT_FALSE(t1.isBound(0u));
  EXPECT_FALSE(t1.isBound(1u));

  TypeParam::bind(t1, 1u);
  EXPECT_TRUE(t0.isBound(0u));
  EXPECT_FALSE(t0.isBound(1u));
  EXPECT_FALSE(t1.isBound(0u));
  EXPECT_TRUE(t1.isBound(1u));

  TypeParam::unbind(0u);
  EXPECT_FALSE(t0.isBound(0u));
  EXPECT_FALSE(t0.isBound(1u));
  EXPECT_FALSE(t1.isBound(0u));
  EXPECT_TRUE(t1.isBound(1u));

  TypeParam::unbind(1u);
  EXPECT_FALSE(t0.isBound(0u));
  EXPECT_FALSE(t0.isBound(1u));
  EXPECT_FALSE(t1.isBound(0u));
  EXPECT_FALSE(t1.isBound(1u));
}



TYPED_TEST(TestTextureCommon, BindingUnitLimit)
{
  TypeParam t(this->generateSize());
  uint maxTexUnit = TypeParam::getTextureUnitCount() - 1u;

  EXPECT_FALSE(t.isBound(maxTexUnit));
  TypeParam::bind(t, maxTexUnit);
  EXPECT_TRUE(t.isBound(maxTexUnit));
  TypeParam::unbind(maxTexUnit);
  EXPECT_FALSE(t.isBound(maxTexUnit));
}



TYPED_TEST(TestTextureCommonDeathTest, BindingErrorUnitTooLarge)
{
  TypeParam t(this->generateSize());
  HOU_EXPECT_PRECONDITION(t.isBound(TypeParam::getTextureUnitCount()));
  HOU_EXPECT_PRECONDITION(TypeParam::bind(t, TypeParam::getTextureUnitCount()));
  HOU_EXPECT_PRECONDITION(TypeParam::unbind(TypeParam::getTextureUnitCount()));
}



TYPED_TEST(TestTextureCommon, SizeConstructor)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TypeParam tex(sizeRef);

  EXPECT_NE(0u, tex.getHandle().getName());
  EXPECT_EQ(TextureFormat::RGBA, tex.getFormat());
  EXPECT_EQ(1u, tex.getMipMapLevelCount());
  EXPECT_EQ(1u, tex.getSampleCount());
  EXPECT_TRUE(tex.hasFixedSampleLocations());
  EXPECT_EQ(sizeRef, tex.getSize());
  EXPECT_EQ(TextureChannelMapping::Default, tex.getChannelMapping());
}



TYPED_TEST(TestTextureCommon, SizeConstructorSizeLimits)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    TypeParam texWithOne(sizeWithOne);
    EXPECT_EQ(sizeWithOne, texWithOne.getSize());

    Size sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    TypeParam texWithMax(sizeWithMax);
    EXPECT_EQ(sizeWithMax, texWithMax.getSize());
  }
}



TYPED_TEST(TestTextureCommonDeathTest, SizeConstructorErrorInvalidSize)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(TypeParam tex(sizeWithNull));
    Size sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(TypeParam tex(sizeTooBig));
  }
}



TYPED_TEST(TestTextureCommon, SetChannelMapping)
{
  TypeParam tex(this->generateSize());
  EXPECT_EQ(TextureChannelMapping::Default, tex.getChannelMapping());
  tex.setChannelMapping(TextureChannelMapping::Alpha);
  EXPECT_EQ(TextureChannelMapping::Alpha, tex.getChannelMapping());
  tex.setChannelMapping(TextureChannelMapping::Luminosity);
  EXPECT_EQ(TextureChannelMapping::Luminosity, tex.getChannelMapping());
}



TYPED_TEST(TestTextureCommon, GetSingleSizeElements)
{
  TypeParam tex(this->generateSize());
  Vec3u sizeRef(1u, 1u, 1u);
  for(size_t i = 0; i < tex.getSize().getSize(); ++i)
  {
    sizeRef(i) = tex.getSize()(i);
  }

  EXPECT_EQ(tex.getWidth(), sizeRef.x());
  EXPECT_EQ(tex.getHeight(), sizeRef.y());
  EXPECT_EQ(tex.getDepth(), sizeRef.z());
}



TYPED_TEST(TestTextureCommon, GetSize1)
{
  TypeParam tex(this->generateSize());
  Vec1u sizeRef(1u);
  for(size_t i = 0; i < std::min(sizeRef.getSize(), tex.getSize().getSize());
      ++i)
  {
    sizeRef(i) = tex.getSize()(i);
  }
  EXPECT_EQ(sizeRef, tex.getSize1());
}



TYPED_TEST(TestTextureCommon, GetSize2)
{
  TypeParam tex(this->generateSize());
  Vec2u sizeRef(1u, 1u);
  for(size_t i = 0; i < std::min(sizeRef.getSize(), tex.getSize().getSize());
      ++i)
  {
    sizeRef(i) = tex.getSize()(i);
  }
  EXPECT_EQ(sizeRef, tex.getSize2());
}



TYPED_TEST(TestTextureCommon, GetSize3)
{
  TypeParam tex(this->generateSize());
  Vec3u sizeRef(1u, 1u, 1u);
  for(size_t i = 0; i < std::min(sizeRef.getSize(), tex.getSize().getSize());
      ++i)
  {
    sizeRef(i) = tex.getSize()(i);
  }
  EXPECT_EQ(sizeRef, tex.getSize3());
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructor)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGB>;
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TextureFormat formatRef = TextureFormat::RGB;
  uint mipMapLevelCountRef = 3u;
  TypeParam tex(sizeRef, formatRef, mipMapLevelCountRef);

  EXPECT_NE(0u, tex.getHandle().getName());
  EXPECT_EQ(formatRef, tex.getFormat());
  EXPECT_EQ(mipMapLevelCountRef, tex.getMipMapLevelCount());
  EXPECT_EQ(1u, tex.getSampleCount());
  EXPECT_TRUE(tex.hasFixedSampleLocations());
  EXPECT_EQ(sizeRef, tex.getSize());
  EXPECT_EQ(TextureChannelMapping::Default, tex.getChannelMapping());
  EXPECT_EQ(TextureFilter::Linear, tex.getFilter());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.getWrapMode());
  EXPECT_EQ(Image(tex.getSize()), tex.template getImage<PixelFormat::RGB>());
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructorSizeLimits)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    TypeParam texWithOne(sizeWithOne, TextureFormat::RGBA, 1u);
    EXPECT_EQ(sizeWithOne, texWithOne.getSize());

    Size sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    TypeParam texWithMax(sizeWithMax, TextureFormat::RGBA, 1u);
    EXPECT_EQ(sizeWithMax, texWithMax.getSize());
  }
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructorMipMapLevelCountLimits)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TypeParam texWithMinMipMapLevelcount(sizeRef, TextureFormat::RGBA, 1u);
  EXPECT_EQ(1u, texWithMinMipMapLevelcount.getMipMapLevelCount());
  TypeParam texWithMaxMipMapLevelcount(
    sizeRef, TextureFormat::RGBA, TypeParam::getMaxMipMapLevelCount(sizeRef));
  EXPECT_EQ(TypeParam::getMaxMipMapLevelCount(sizeRef),
    texWithMaxMipMapLevelcount.getMipMapLevelCount());
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, MipMapConstructorErrorInvalidSize)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(sizeWithNull, TextureFormat::RGBA, 1u));
    Size sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(TypeParam tex(sizeTooBig, TextureFormat::RGBA, 1u));
  }
}



TYPED_TEST(TestTextureNotMultisampledDeathTest,
  MipMapConstructorErrorInvalidMipMapLevelCount)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  HOU_EXPECT_PRECONDITION(TypeParam tex(sizeRef, TextureFormat::RGBA, 0u));
  HOU_EXPECT_PRECONDITION(TypeParam tex(sizeRef, TextureFormat::RGBA,
    TypeParam::getMaxMipMapLevelCount(sizeRef) + 1));
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructor)
{
  auto imageRef = this->generateImage(this->generateSize());
  TextureFormat formatRef = TextureFormat::RGBA;
  uint mipMapLevelCountRef = 3u;
  TypeParam tex(imageRef, TextureFormat::RGBA, mipMapLevelCountRef);

  EXPECT_NE(0u, tex.getHandle().getName());
  EXPECT_EQ(formatRef, tex.getFormat());
  EXPECT_EQ(mipMapLevelCountRef, tex.getMipMapLevelCount());
  EXPECT_EQ(1u, tex.getSampleCount());
  EXPECT_TRUE(tex.hasFixedSampleLocations());
  EXPECT_EQ(imageRef.getSize(), tex.getSize());
  EXPECT_EQ(TextureChannelMapping::Default, tex.getChannelMapping());
  EXPECT_EQ(TextureFilter::Linear, tex.getFilter());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.getWrapMode());
  EXPECT_EQ(imageRef, tex.template getImage<PixelFormat::RGBA>());
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorDefaultArguments)
{
  auto imageRef = this->generateImage(this->generateSize());
  TypeParam tex(imageRef);

  EXPECT_NE(0u, tex.getHandle().getName());
  EXPECT_EQ(TextureFormat::RGBA, tex.getFormat());
  EXPECT_EQ(1u, tex.getMipMapLevelCount());
  EXPECT_EQ(1u, tex.getSampleCount());
  EXPECT_TRUE(tex.hasFixedSampleLocations());
  EXPECT_EQ(imageRef.getSize(), tex.getSize());
  EXPECT_EQ(TextureChannelMapping::Default, tex.getChannelMapping());
  EXPECT_EQ(TextureFilter::Linear, tex.getFilter());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.getWrapMode());
  EXPECT_EQ(imageRef, tex.template getImage<PixelFormat::RGBA>());
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorSizeLimits)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    auto imageWithOne = this->generateImage(sizeWithOne);
    TypeParam texWithOne(imageWithOne, TextureFormat::RGBA, 1u);
    EXPECT_EQ(imageWithOne, texWithOne.template getImage<PixelFormat::RGBA>());

    Size sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    auto imageWithMax = this->generateImage(sizeWithMax);
    TypeParam texWithMax(imageWithMax, TextureFormat::RGBA, 1u);
    EXPECT_EQ(imageWithMax, texWithMax.template getImage<PixelFormat::RGBA>());
  }
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorMipMapLevelCountLimits)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TypeParam texWithMinMipMapLevelcount(Image(sizeRef), TextureFormat::RGBA, 1u);
  EXPECT_EQ(1u, texWithMinMipMapLevelcount.getMipMapLevelCount());
  TypeParam texWithMaxMipMapLevelcount(Image(sizeRef), TextureFormat::RGBA,
    TypeParam::getMaxMipMapLevelCount(sizeRef));
  EXPECT_EQ(TypeParam::getMaxMipMapLevelCount(sizeRef),
    texWithMaxMipMapLevelcount.getMipMapLevelCount());
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, ImageConstructorErrorInvalidSize)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(Image(sizeWithNull), TextureFormat::RGBA, 1u));
    Size sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(Image(sizeTooBig), TextureFormat::RGBA, 1u));
  }
}



TYPED_TEST(TestTextureNotMultisampledDeathTest,
  ImageConstructorErrorInvalidMipMapLevelCount)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  HOU_EXPECT_PRECONDITION(
    TypeParam tex(Image(sizeRef), TextureFormat::RGBA, 0u));
  HOU_EXPECT_PRECONDITION(TypeParam tex(Image(sizeRef), TextureFormat::RGBA,
    TypeParam::getMaxMipMapLevelCount(sizeRef) + 1));
}



TYPED_TEST(TestTextureNotMultisampled, SetFilter)
{
  TypeParam tex(this->generateSize());
  std::vector<TextureFilter> filters = {TextureFilter::Nearest,
    TextureFilter::Linear, TextureFilter::Bilinear, TextureFilter::Trilinear};
  EXPECT_EQ(TextureFilter::Linear, tex.getFilter());
  for(auto filter : filters)
  {
    tex.setFilter(filter);
    EXPECT_EQ(filter, tex.getFilter());
  }
}



TYPED_TEST(TestTextureNotMultisampled, SetWrapMode)
{
  TypeParam tex(this->generateSize());
  EXPECT_EQ(this->getDefaultWrapMode(), tex.getWrapMode());
  tex.setWrapMode(this->getAlternativeWrapMode());
  EXPECT_EQ(this->getAlternativeWrapMode(), tex.getWrapMode());
}



TYPED_TEST(TestTextureNotMultisampled, SetImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;

  TypeParam tex(this->generateSize());
  EXPECT_EQ(Image(tex.getSize()), tex.template getImage<PixelFormat::RGBA>());
  Image imageRef = this->generateImage(tex.getSize());
  tex.setImage(imageRef);
  EXPECT_EQ(imageRef, tex.template getImage<PixelFormat::RGBA>());
}



TYPED_TEST(TestTextureNotMultisampledDeathTest, SetImageErrorInvalidSize)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;

  TypeParam tex(this->generateSize());
  HOU_EXPECT_PRECONDITION(tex.setImage(Image(tex.getSize() * 2)));
}



TYPED_TEST(TestTextureNotMultisampled, GetSubImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size texSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < texSize.getSize(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  Image imageRef = this->generateImage(texSize);
  Image subImageRef = imageRef.getSubImage(subImageOffset, subImageSize);
  TypeParam tex(imageRef);

  EXPECT_EQ(subImageRef,
    tex.template getSubImage<PixelFormat::RGBA>(subImageOffset, subImageSize));
}



TYPED_TEST(TestTextureNotMultisampledDeathTest, GetSubImageErrorOverflow)
{
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size texSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < texSize.getSize(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }
  TypeParam tex(this->generateImage(texSize));
  HOU_EXPECT_PRECONDITION(
    tex.template getSubImage<PixelFormat::RGBA>(subImageOffset, subImageSize));
}



TYPED_TEST(TestTextureNotMultisampled, SetSubImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size texSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < texSize.getSize(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  typename Image::Pixel pixelRef(1u, 2u, 3u, 4u);
  Image subImageRef(subImageSize, pixelRef);
  Image imageRef(texSize);
  imageRef.setSubImage(subImageOffset, subImageRef);
  TypeParam tex(texSize);
  tex.setSubImage(subImageOffset, subImageRef);

  EXPECT_EQ(imageRef, tex.template getImage<PixelFormat::RGBA>());
  EXPECT_EQ(subImageRef,
    tex.template getSubImage<PixelFormat::RGBA>(subImageOffset, subImageSize));
}



TYPED_TEST(TestTextureNotMultisampledDeathTest, SetSubImageErrorOverflow)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size texSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < texSize.getSize(); ++i)
  {
    texSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam tex(texSize);
  Image subImageRef(subImageSize);
  HOU_EXPECT_PRECONDITION(tex.setSubImage(subImageOffset, subImageRef));
}



TYPED_TEST(TestTextureNotMultisampled, Clear)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;

  TypeParam tex(this->generateSize());
  EXPECT_EQ(Image(tex.getSize()), tex.template getImage<PixelFormat::RGBA>());
  PixelRGBA pixelRef(1u, 2u, 3u, 4u);
  tex.clear(pixelRef);
  EXPECT_EQ(
    Image(tex.getSize(), pixelRef), tex.template getImage<PixelFormat::RGBA>());
}



TYPED_TEST(TestTextureNotMultisampled, GetMipMapSize)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TypeParam tex(sizeRef, TextureFormat::RGBA, 3u);

  for(size_t i = 0; i < tex.getMipMapLevelCount(); ++i)
  {
    EXPECT_EQ(this->computeMipMapSize(sizeRef, i), tex.getMipMapSize(i));
  }
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, GetMipMapSizeErrorInvalidMipMapLevel)
{
  TypeParam tex(this->generateSize(), TextureFormat::RGBA, 3u);
  HOU_EXPECT_PRECONDITION(tex.getMipMapSize(tex.getMipMapLevelCount() + 1u));
}



TYPED_TEST(TestTextureNotMultisampled, MipMapConstructorGetMipMapImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGB>;

  TypeParam tex(this->generateSize(), TextureFormat::RGBA, 3u);

  for(uint i = 0; i < tex.getMipMapLevelCount(); ++i)
  {
    EXPECT_EQ(Image(tex.getMipMapSize(i)),
      tex.template getMipMapImage<PixelFormat::RGB>(i));
  }
}



TYPED_TEST(TestTextureNotMultisampled, ImageConstructorGetMipMapImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGB>;

  TypeParam tex(Image(this->generateSize()), TextureFormat::RGBA, 3u);

  for(uint i = 0; i < tex.getMipMapLevelCount(); ++i)
  {
    EXPECT_EQ(Image(tex.getMipMapSize(i)),
      tex.template getMipMapImage<PixelFormat::RGB>(i));
  }
}



TYPED_TEST(TestTextureNotMultisampled, SetImageGetMipMapImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;
  using Size = typename TypeParam::Size;

  Size texSize;
  Size subImageOffset;
  Size subImageSize;
  for(size_t i = 0; i < texSize.getSize(); ++i)
  {
    texSize(i) = (i + 1) * 16;
    subImageOffset(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 8;
  }

  TypeParam tex(texSize, TextureFormat::RGBA, 3u);

  std::vector<Image> imageRefs;
  for(uint i = 0; i < tex.getMipMapLevelCount(); ++i)
  {
    imageRefs.push_back(Image(tex.getMipMapSize(i)));
    imageRefs.back().setSubImage(this->computeMipMapSize(subImageOffset, i),
      Image(this->computeMipMapSize(subImageSize, i),
        typename Image::Pixel(2u, 3u, 5u, 7u)));
  }

  tex.setImage(imageRefs.front());
  for(size_t i = 0; i < tex.getMipMapLevelCount(); ++i)
  {
    EXPECT_EQ(imageRefs[i], tex.template getMipMapImage<PixelFormat::RGBA>(i));
  }
}



TYPED_TEST(TestTextureNotMultisampled, ClearGetMipMapImage)
{
  using Image = typename TypeParam::template Image<PixelFormat::RGBA>;

  TypeParam tex(this->generateSize(), TextureFormat::RGBA, 3u);
  PixelRGBA pixelRef(2u, 3u, 5u, 7u);
  tex.clear(pixelRef);
  for(size_t i = 0; i < tex.getMipMapLevelCount(); ++i)
  {
    EXPECT_EQ(Image(tex.getMipMapSize(i), pixelRef),
      tex.template getMipMapImage<PixelFormat::RGBA>(i));
  }
}



TYPED_TEST(
  TestTextureNotMultisampledDeathTest, GetMipMapImageErrorInvalidMipMapLevel)
{
  TypeParam tex(this->generateSize(), TextureFormat::RGBA, 3u);
  HOU_EXPECT_PRECONDITION(tex.template getMipMapImage<PixelFormat::RGBA>(
    tex.getMipMapLevelCount() + 1u));
}



// TYPED_TEST(TestTextureNotMultisampled, FormatRGBA)
// {
//   // Requires compile time iterations.
//   constexpr std::array<PixelFormat, 4u> pixelFormats{
//     PixelFormat::RGBA, PixelFormat::RGB, PixelFormat::RG, PixelFormat::R};
//
//   constexpr std::array<TextureFormat, 7u> textureFormats{
//     TextureFormat::RGBA,
//     TextureFormat::RGB,
//     TextureFormat::RG,
//     TextureFormat::R,
//     TextureFormat::Depth,
//     TextureFormat::Stencil,
//     TextureFormat::DepthStencil,
//   };
//
//   for(constexpr auto tf : textureFormats)
//   {
//     for(constexpr auto pfIn : pixelFormats)
//     {
//       typename TypeParam::template Image<pfIn>
//       im(this->generaImage(this->generateSize())); TypeParam tex(im, tf);
//       for(constexpr auto pfOut : pixelFormats)
//       {
//         EXPECT_EQ(typename TypeParam::template Image<pfOut>(im), tex.template
//         getImage<pfOut>())
//           << "Texture Format = " << tf
//           << ", Input Pixel Format = " << pfIn
//           << ", OutputPixel Format = " << pfOut;
//       }
//     }
//   }
// }



TYPED_TEST(TestTextureMultisampled, MultisampleConstructor)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TextureFormat formatRef = TextureFormat::RGB;
  uint sampleCountRef = 3u;
  TypeParam tex(sizeRef, formatRef, sampleCountRef, false);

  EXPECT_NE(0u, tex.getHandle().getName());
  EXPECT_EQ(formatRef, tex.getFormat());
  EXPECT_EQ(1u, tex.getMipMapLevelCount());
  EXPECT_EQ(sampleCountRef, tex.getSampleCount());
  EXPECT_FALSE(tex.hasFixedSampleLocations());
  EXPECT_EQ(sizeRef, tex.getSize());
  EXPECT_EQ(TextureChannelMapping::Default, tex.getChannelMapping());
}



TYPED_TEST(TestTextureMultisampled, MultisampleConstructorSizeLimits)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithOne = sizeRef;
    sizeWithOne(i) = 1u;
    TypeParam texWithOne(sizeWithOne, TextureFormat::RGBA, 1u, true);
    EXPECT_EQ(sizeWithOne, texWithOne.getSize());

    Size sizeWithMax = sizeRef;
    sizeWithMax(i) = maxSize(i);
    TypeParam texWithMax(sizeWithMax, TextureFormat::RGBA, 1u, true);
    EXPECT_EQ(sizeWithMax, texWithMax.getSize());
  }
}



TYPED_TEST(TestTextureMultisampled, MultisampleConstructorSampleCountLimits)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TypeParam texWithMinSampleCount(sizeRef, TextureFormat::RGBA, 1u, true);
  EXPECT_EQ(1u, texWithMinSampleCount.getSampleCount());
  TypeParam texWithMaxSampleCount(
    sizeRef, TextureFormat::RGBA, TypeParam::getMaxSampleCount(), true);
  EXPECT_EQ(
    TypeParam::getMaxSampleCount(), texWithMaxSampleCount.getSampleCount());
}



TYPED_TEST(TestTextureMultisampled, MultisampleConstructorSamplePositionValues)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  TypeParam texTrue(sizeRef, TextureFormat::RGBA, 1u, true);
  EXPECT_TRUE(texTrue.hasFixedSampleLocations());
  TypeParam texFalse(sizeRef, TextureFormat::RGBA, 1u, false);
  EXPECT_FALSE(texFalse.hasFixedSampleLocations());
}



TYPED_TEST(
  TestTextureMultisampledDeathTest, MultisampleConstructorErrorInvalidSize)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  Size maxSize = TypeParam::getMaxSize();
  for(size_t i = 0u; i < sizeRef.getSize(); ++i)
  {
    Size sizeWithNull = sizeRef;
    sizeWithNull(i) = 0u;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(sizeWithNull, TextureFormat::RGBA, 1u, true));
    Size sizeTooBig = sizeRef;
    sizeTooBig(i) = maxSize(i) + 1;
    HOU_EXPECT_PRECONDITION(
      TypeParam tex(sizeTooBig, TextureFormat::RGBA, 1u, true));
  }
}



TYPED_TEST(
  TestTextureMultisampledDeathTest, MultisampleConstructorErrorInvalidMipMap)
{
  using Size = typename TypeParam::Size;

  Size sizeRef = this->generateSize();
  HOU_EXPECT_PRECONDITION(
    TypeParam tex(sizeRef, TextureFormat::RGBA, 0u, true));
  HOU_EXPECT_PRECONDITION(TypeParam tex(
    sizeRef, TextureFormat::RGBA, TypeParam::getMaxSampleCount() + 1, true));
}
