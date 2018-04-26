// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/File.hpp"
#include "hou/sys/Image.hpp"
#include "hou/sys/SysError.hpp"

using namespace hou;
using namespace testing;


namespace
{

template <typename ImageT>
class TestImage : public Test
{
public:
  static typename ImageT::Size generateSize();
  static typename ImageT::PixelCollection generatePixels(
    const typename ImageT::Size& size);
  static size_t multiplyElements(const typename ImageT::Size& size);
  static size_t computePixelIndex(
    const typename ImageT::Coordinates& coordinates,
    const typename ImageT::Size& size);
  static typename ImageT::Coordinates computePixelCoordinates(
    size_t index, const typename ImageT::Size& size);
};

template <typename ImageT>
class TestImageDeathTest : public TestImage<ImageT>
{};

using ImageTypes
  = Types<Image1R, Image2R, Image3R, Image1RG, Image2RG, Image3RG, Image1RGB,
    Image2RGB, Image3RGB, Image1RGBA, Image2RGBA, Image3RGBA>;

class TestImageClassAttributes : public Test
{};

class TestImageConversionConstructor : public Test
{};

class TestImageFile : public Test
{
public:
  static const std::string testImageBmp;
  static const std::string testImagePng;
  static const std::string testImageJpg;
  static const std::string testImageInvalid;
};

class TestImageFileDeathTest : public TestImageFile
{};



template <>
typename Image1R::Size TestImage<Image1R>::generateSize()
{
  return Vec1u{4u};
}



template <>
typename Image1RG::Size TestImage<Image1RG>::generateSize()
{
  return Vec1u{4u};
}



template <>
typename Image1RGB::Size TestImage<Image1RGB>::generateSize()
{
  return Vec1u{4u};
}



template <>
typename Image1RGBA::Size TestImage<Image1RGBA>::generateSize()
{
  return Vec1u{4u};
}



template <>
typename Image2R::Size TestImage<Image2R>::generateSize()
{
  return Vec2u{4u, 7u};
}



template <>
typename Image2RG::Size TestImage<Image2RG>::generateSize()
{
  return Vec2u{4u, 7u};
}



template <>
typename Image2RGB::Size TestImage<Image2RGB>::generateSize()
{
  return Vec2u{4u, 7u};
}



template <>
typename Image2RGBA::Size TestImage<Image2RGBA>::generateSize()
{
  return Vec2u{4u, 7u};
}



template <>
typename Image3R::Size TestImage<Image3R>::generateSize()
{
  return Vec3u{4u, 7u, 11u};
}



template <>
typename Image3RG::Size TestImage<Image3RG>::generateSize()
{
  return Vec3u{4u, 7u, 11u};
}



template <>
typename Image3RGB::Size TestImage<Image3RGB>::generateSize()
{
  return Vec3u{4u, 7u, 11u};
}



template <>
typename Image3RGBA::Size TestImage<Image3RGBA>::generateSize()
{
  return Vec3u{4u, 7u, 11u};
}



template <typename ImageT>
typename ImageT::PixelCollection TestImage<ImageT>::generatePixels(
  const typename ImageT::Size& size)
{
  typename ImageT::PixelCollection retval(multiplyElements(size));
  for(size_t i = 0; i < retval.size(); ++i)
  {
    typename ImageT::Pixel pixel;
    pixel.setR(i);
    retval[i] = pixel;
  }
  return retval;
}



template <typename ImageT>
size_t TestImage<ImageT>::multiplyElements(const typename ImageT::Size& size)
{
  size_t retval = size(0);
  for(size_t i = 1; i < size.getSize(); ++i)
  {
    retval *= size(i);
  }
  return retval;
}



template <typename ImageT>
size_t TestImage<ImageT>::computePixelIndex(
  const typename ImageT::Coordinates& coordinates,
  const typename ImageT::Size& size)
{
  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < coordinates.getSize(); ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= size(i);
  }
  return idx;
}



template <typename ImageT>
typename ImageT::Coordinates TestImage<ImageT>::computePixelCoordinates(
  size_t index, const typename ImageT::Size& size)
{
  using Coordinates = typename ImageT::Coordinates;

  Coordinates coords;
  size_t divider = multiplyElements(size);
  for(size_t i = size.getSize() - 1; i > 0; --i)
  {
    divider /= size(i);
    coords(i) = index / divider;
    index %= divider;
  }
  coords(0) = index;
  return coords;
}



const std::string TestImageFile::testImageBmp
  = getDataDir() + u8"TestImage.bmp";
const std::string TestImageFile::testImagePng
  = getDataDir() + u8"TestImage.png";
const std::string TestImageFile::testImageJpg
  = getDataDir() + u8"TestImage.jpg";
const std::string TestImageFile::testImageInvalid
  = getDataDir() + u8"TestImage.xcf";

}  // namespace



TYPED_TEST_CASE(TestImage, ImageTypes);
TYPED_TEST_CASE(TestImageDeathTest, ImageTypes);



TYPED_TEST(TestImage, GetPixelByteCount)
{
  EXPECT_EQ(TypeParam::Pixel::getByteCount(), TypeParam::getPixelByteCount());
}



TYPED_TEST(TestImage, DefaultConstructor)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  TypeParam image;
  EXPECT_EQ(Size::zero(), image.getSize());
  EXPECT_EQ(PixelCollection(), image.getPixels());
}



TYPED_TEST(TestImage, SizeConstructor)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  TypeParam image(sizeRef);
  EXPECT_EQ(sizeRef, image.getSize());
  EXPECT_EQ(
    PixelCollection(TestFixture::multiplyElements(sizeRef)), image.getPixels());
}



TYPED_TEST(TestImage, PixelConstructor)
{
  using Size = typename TypeParam::Size;
  using Pixel = typename TypeParam::Pixel;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  Pixel pixelRef;
  pixelRef.setR(5u);
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef), pixelRef);
  TypeParam image(sizeRef, pixelRef);

  EXPECT_EQ(sizeRef, image.getSize());
  EXPECT_EQ(pixelsRef, image.getPixels());
}



TYPED_TEST(TestImage, PixelsConstructor)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef = TestFixture::generatePixels(sizeRef);
  TypeParam image(sizeRef, pixelsRef);

  EXPECT_EQ(sizeRef, image.getSize());
  EXPECT_EQ(pixelsRef, image.getPixels());
}



TYPED_TEST(TestImageDeathTest, PixelsConstructorErrorTooFewPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef) - 1u);
  HOU_EXPECT_PRECONDITION(TypeParam image(sizeRef, pixelsRef));
}



TYPED_TEST(TestImageDeathTest, PixelsConstructorErrorTooManyPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam image(sizeRef, pixelsRef));
}



TYPED_TEST(TestImage, PixelsMoveConstructor)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef = TestFixture::generatePixels(sizeRef);
  PixelCollection pixels(pixelsRef);
  TypeParam image(sizeRef, std::move(pixels));

  EXPECT_EQ(sizeRef, image.getSize());
  EXPECT_EQ(pixelsRef, image.getPixels());
}



TYPED_TEST(TestImageDeathTest, PixelsMoveConstructorErrorTooFewPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef) - 1u);
  HOU_EXPECT_PRECONDITION(TypeParam image(sizeRef, std::move(pixelsRef)));
}



TYPED_TEST(TestImageDeathTest, PixelsMoveConstructorErrorTooManyPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam image(sizeRef, std::move(pixelsRef)));
}



TYPED_TEST(TestImage, SetPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef = TestFixture::generatePixels(sizeRef);
  TypeParam image(sizeRef);
  image.setPixels(pixelsRef);
  EXPECT_EQ(pixelsRef, image.getPixels());
}



TYPED_TEST(TestImageDeathTest, SetPixelsErrorTooFewPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef) - 1u);
  TypeParam image(sizeRef);
  HOU_EXPECT_PRECONDITION(image.setPixels(pixelsRef));
}



TYPED_TEST(TestImageDeathTest, SetPixelsErrorTooManyPixels)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef) + 1u);
  TypeParam image(sizeRef);
  HOU_EXPECT_PRECONDITION(image.setPixels(pixelsRef));
}



TYPED_TEST(TestImage, GetPixel)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef = TestFixture::generatePixels(sizeRef);
  TypeParam image(sizeRef, pixelsRef);

  for(size_t i = 0; i < pixelsRef.size(); ++i)
  {
    EXPECT_EQ(pixelsRef[i],
      image.getPixel(TestFixture::computePixelCoordinates(i, image.getSize())));
  }
}



TYPED_TEST(TestImageDeathTest, GetPixelErrorOutOfRange)
{
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size sizeRef = TestFixture::generateSize();
  TypeParam image(sizeRef);

  for(size_t i = 0; i < sizeRef.getSize(); ++i)
  {
    Coordinates coords;
    coords(i) = sizeRef(i);
    HOU_EXPECT_PRECONDITION(image.getPixel(coords));
  }
  HOU_EXPECT_PRECONDITION(image.getPixel(sizeRef));
}



TYPED_TEST(TestImage, SetPixel)
{
  using Size = typename TypeParam::Size;
  using Pixel = typename TypeParam::Pixel;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  Pixel pixelRef;
  pixelRef.setR(42u);
  for(size_t i = 0; i < TestFixture::multiplyElements(sizeRef); ++i)
  {
    TypeParam image(sizeRef);
    PixelCollection pixelsRef = image.getPixels();
    pixelsRef[i] = pixelRef;
    image.setPixel(
      TestFixture::computePixelCoordinates(i, image.getSize()), pixelRef);
    EXPECT_EQ(pixelsRef[i],
      image.getPixel(TestFixture::computePixelCoordinates(i, image.getSize())));
  }
}



TYPED_TEST(TestImageDeathTest, SetPixelErrorOutOfRange)
{
  using Size = typename TypeParam::Size;
  using Pixel = typename TypeParam::Pixel;
  using Coordinates = typename TypeParam::Coordinates;

  Size sizeRef = TestFixture::generateSize();
  TypeParam image(sizeRef);

  Pixel pixelRef;
  for(size_t i = 0; i < sizeRef.getSize(); ++i)
  {
    Coordinates coords;
    coords(i) = sizeRef(i);
    HOU_EXPECT_PRECONDITION(image.setPixel(coords, pixelRef));
  }
  HOU_EXPECT_PRECONDITION(image.setPixel(sizeRef, pixelRef));
}



TYPED_TEST(TestImage, GetSubImage)
{
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size imageSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < imageSize.getSize(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  PixelCollection pixelsRef = TestFixture::generatePixels(imageSize);
  PixelCollection subPixelsRef(TestFixture::multiplyElements(subImageSize));
  for(size_t i = 0; i < subPixelsRef.size(); ++i)
  {
    Coordinates subImageCoords
      = TestFixture::computePixelCoordinates(i, subImageSize);
    Coordinates imageCoords = subImageOffset + subImageCoords;
    subPixelsRef[i]
      = pixelsRef[TestFixture::computePixelIndex(imageCoords, imageSize)];
  }

  TypeParam image(imageSize, pixelsRef);
  TypeParam subImageRef(subImageSize, subPixelsRef);
  EXPECT_EQ(subImageRef, image.getSubImage(subImageOffset, subImageSize));
}



TYPED_TEST(TestImageDeathTest, GetSubImageErrorOverflow)
{
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size imageSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < imageSize.getSize(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam image(imageSize);
  HOU_EXPECT_PRECONDITION(image.getSubImage(subImageOffset, subImageSize));
}



TYPED_TEST(TestImage, SetSubImage)
{
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size imageSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < imageSize.getSize(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  PixelCollection pixelsRef(TestFixture::multiplyElements(imageSize));
  PixelCollection subPixelsRef(TestFixture::generatePixels(subImageSize));
  for(size_t i = 0; i < subPixelsRef.size(); ++i)
  {
    Coordinates subImageCoords
      = TestFixture::computePixelCoordinates(i, subImageSize);
    Coordinates imageCoords = subImageOffset + subImageCoords;
    pixelsRef[TestFixture::computePixelIndex(imageCoords, imageSize)]
      = subPixelsRef[i];
  }

  TypeParam image(imageSize);
  TypeParam imageRef(imageSize, pixelsRef);
  TypeParam subImageRef(subImageSize, subPixelsRef);
  image.setSubImage(subImageOffset, subImageRef);

  EXPECT_EQ(imageRef, image);
  EXPECT_EQ(subImageRef, image.getSubImage(subImageOffset, subImageSize));
}



TYPED_TEST(TestImageDeathTest, SetSubImageErrorOverflow)
{
  using Size = typename TypeParam::Size;
  using Coordinates = typename TypeParam::Coordinates;

  Size imageSize;
  Size subImageSize;
  Coordinates subImageOffset;
  for(size_t i = 0; i < imageSize.getSize(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam image(imageSize);
  TypeParam subImage(subImageSize);
  HOU_EXPECT_PRECONDITION(image.setSubImage(subImageOffset, subImage));
}



TYPED_TEST(TestImage, Clear)
{
  using Size = typename TypeParam::Size;
  using Pixel = typename TypeParam::Pixel;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  TypeParam image(sizeRef);

  Pixel pixelRef;
  pixelRef.setR(42u);

  PixelCollection pixelsRef(TestFixture::multiplyElements(sizeRef), pixelRef);
  image.clear(pixelRef);
  EXPECT_EQ(pixelsRef, image.getPixels());
}



TYPED_TEST(TestImage, Comparison)
{
  using Size = typename TypeParam::Size;
  using Pixel = typename TypeParam::Pixel;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size size1 = TestFixture::generateSize();
  Size size2 = size1 * 2;
  Pixel pixel1;
  pixel1.setR(42);
  Pixel pixel2;
  pixel2.setR(88);
  PixelCollection pixels11(TestFixture::multiplyElements(size1), pixel1);
  PixelCollection pixels12(TestFixture::multiplyElements(size1), pixel2);
  PixelCollection pixels22(TestFixture::multiplyElements(size2), pixel2);

  TypeParam im0(size1, pixels11);
  TypeParam im1(im0);
  TypeParam im2(size1, pixels12);
  TypeParam im3(size2, pixels22);

  EXPECT_TRUE(im0 == im1);
  EXPECT_FALSE(im0 == im2);
  EXPECT_FALSE(im0 == im3);

  EXPECT_FALSE(im0 != im1);
  EXPECT_TRUE(im0 != im2);
  EXPECT_TRUE(im0 != im3);
}



TYPED_TEST(TestImage, OutputStreamOperator)
{
  using Size = typename TypeParam::Size;
  using PixelCollection = typename TypeParam::PixelCollection;

  Size sizeRef = TestFixture::generateSize();
  PixelCollection pixelsRef = TestFixture::generatePixels(sizeRef);

  TypeParam image(sizeRef, pixelsRef);

  std::stringstream ss;
  ss << "{Size = " << transpose(sizeRef) << ", Pixels = " << pixelsRef << "}";

  HOU_EXPECT_OUTPUT(ss.str().c_str(), image);
}



TEST_F(TestImageClassAttributes, GetDimensionCount)
{
  EXPECT_EQ(1u, Image1R::getDimensionCount());
  EXPECT_EQ(1u, Image1RG::getDimensionCount());
  EXPECT_EQ(1u, Image1RGB::getDimensionCount());
  EXPECT_EQ(1u, Image1RGBA::getDimensionCount());
  EXPECT_EQ(2u, Image2R::getDimensionCount());
  EXPECT_EQ(2u, Image2RG::getDimensionCount());
  EXPECT_EQ(2u, Image2RGB::getDimensionCount());
  EXPECT_EQ(2u, Image2RGBA::getDimensionCount());
  EXPECT_EQ(3u, Image3R::getDimensionCount());
  EXPECT_EQ(3u, Image3RG::getDimensionCount());
  EXPECT_EQ(3u, Image3RGB::getDimensionCount());
  EXPECT_EQ(3u, Image3RGBA::getDimensionCount());
}



TEST_F(TestImageClassAttributes, GetPixelFormat)
{
  EXPECT_EQ(PixelFormat::R, Image1R::getPixelFormat());
  EXPECT_EQ(PixelFormat::RG, Image1RG::getPixelFormat());
  EXPECT_EQ(PixelFormat::RGB, Image1RGB::getPixelFormat());
  EXPECT_EQ(PixelFormat::RGBA, Image1RGBA::getPixelFormat());
  EXPECT_EQ(PixelFormat::R, Image2R::getPixelFormat());
  EXPECT_EQ(PixelFormat::RG, Image2RG::getPixelFormat());
  EXPECT_EQ(PixelFormat::RGB, Image2RGB::getPixelFormat());
  EXPECT_EQ(PixelFormat::RGBA, Image2RGBA::getPixelFormat());
  EXPECT_EQ(PixelFormat::R, Image3R::getPixelFormat());
  EXPECT_EQ(PixelFormat::RG, Image3RG::getPixelFormat());
  EXPECT_EQ(PixelFormat::RGB, Image3RGB::getPixelFormat());
  EXPECT_EQ(PixelFormat::RGBA, Image3RGBA::getPixelFormat());
}



TEST_F(TestImageConversionConstructor, R2RGBAConstructor)
{
  Image2R::Size size(2u, 3u);
  Image2R::PixelCollection pixelsR{
    Image2R::Pixel(1u),
    Image2R::Pixel(2u),
    Image2R::Pixel(3u),
    Image2R::Pixel(4u),
    Image2R::Pixel(5u),
    Image2R::Pixel(6u),
  };

  Image2RGBA::PixelCollection pixelsRGBA{
    Image2RGBA::Pixel(1u, 1u, 1u, 255u),
    Image2RGBA::Pixel(2u, 2u, 2u, 255u),
    Image2RGBA::Pixel(3u, 3u, 3u, 255u),
    Image2RGBA::Pixel(4u, 4u, 4u, 255u),
    Image2RGBA::Pixel(5u, 5u, 5u, 255u),
    Image2RGBA::Pixel(6u, 6u, 6u, 255u),
  };

  Image2R imageR(size, pixelsR);
  Image2RGBA imageRGBA(imageR);

  EXPECT_EQ(size, imageRGBA.getSize());
  EXPECT_EQ(pixelsRGBA, imageRGBA.getPixels());
}



TEST_F(TestImageConversionConstructor, RG2RGBAConstructor)
{
  Image2RG::Size size(2u, 3u);
  Image2RG::PixelCollection pixelsRG{
    Image2RG::Pixel(1u, 11u),
    Image2RG::Pixel(2u, 12u),
    Image2RG::Pixel(3u, 13u),
    Image2RG::Pixel(4u, 14u),
    Image2RG::Pixel(5u, 15u),
    Image2RG::Pixel(6u, 16u),
  };

  Image2RGBA::PixelCollection pixelsRGBA{
    Image2RGBA::Pixel(1u, 1u, 1u, 11u),
    Image2RGBA::Pixel(2u, 2u, 2u, 12u),
    Image2RGBA::Pixel(3u, 3u, 3u, 13u),
    Image2RGBA::Pixel(4u, 4u, 4u, 14u),
    Image2RGBA::Pixel(5u, 5u, 5u, 15u),
    Image2RGBA::Pixel(6u, 6u, 6u, 16u),
  };

  Image2RG imageRG(size, pixelsRG);
  Image2RGBA imageRGBA(imageRG);

  EXPECT_EQ(size, imageRGBA.getSize());
  EXPECT_EQ(pixelsRGBA, imageRGBA.getPixels());
}



TEST_F(TestImageConversionConstructor, RGB2RGBAConstructor)
{
  Image2RGB::Size size(2u, 3u);
  Image2RGB::PixelCollection pixelsRGB{
    Image2RGB::Pixel(200u, 118u, 93u),
    Image2RGB::Pixel(3u, 12u, 3u),
    Image2RGB::Pixel(5u, 11u, 2u),
    Image2RGB::Pixel(200u, 100u, 0u),
    Image2RGB::Pixel(0u, 21u, 0u),
    Image2RGB::Pixel(100u, 20u, 0u),
  };

  Image2RGBA::PixelCollection pixelsRGBA{
    Image2RGBA::Pixel(200u, 118u, 93u, 255u),
    Image2RGBA::Pixel(3u, 12u, 3u, 255u),
    Image2RGBA::Pixel(5u, 11u, 2u, 255u),
    Image2RGBA::Pixel(200u, 100u, 0u, 255u),
    Image2RGBA::Pixel(0u, 21u, 0u, 255u),
    Image2RGBA::Pixel(100u, 20u, 0u, 255u),
  };

  Image2RGB imageRGB(size, pixelsRGB);
  Image2RGBA imageRGBA(imageRGB);

  EXPECT_EQ(size, imageRGBA.getSize());
  EXPECT_EQ(pixelsRGBA, imageRGBA.getPixels());
}



TEST_F(TestImageConversionConstructor, Image1ToImage2Constructor)
{
  Image1RGB::Size size(3u);
  Image1RGBA::PixelCollection pixelsRGBA{
    Image1RGBA::Pixel(200u, 118u, 93u, 255u),
    Image1RGBA::Pixel(3u, 12u, 3u, 255u),
    Image1RGBA::Pixel(5u, 11u, 2u, 255u),
  };
  Image1RGBA image1RGBA(size, pixelsRGBA);
  Image2RGBA image2RGBA(image1RGBA);
  EXPECT_EQ(Vec2u(size.x(), 1u), image2RGBA.getSize());
  EXPECT_EQ(pixelsRGBA, image2RGBA.getPixels());
}



TEST_F(TestImageConversionConstructor, Image1ToImage3Constructor)
{
  Image1RGB::Size size(3u);
  Image1RGBA::PixelCollection pixelsRGBA{
    Image1RGBA::Pixel(200u, 118u, 93u, 255u),
    Image1RGBA::Pixel(3u, 12u, 3u, 255u),
    Image1RGBA::Pixel(5u, 11u, 2u, 255u),
  };
  Image1RGBA image1RGBA(size, pixelsRGBA);
  Image3RGBA image3RGBA(image1RGBA);
  EXPECT_EQ(Vec3u(size.x(), 1u, 1u), image3RGBA.getSize());
  EXPECT_EQ(pixelsRGBA, image3RGBA.getPixels());
}



TEST_F(TestImageConversionConstructor, Image2ToImage3Constructor)
{
  Image2RGB::Size size(3u, 2u);
  Image2RGBA::PixelCollection pixelsRGBA{
    Image2RGBA::Pixel(200u, 118u, 93u, 255u),
    Image2RGBA::Pixel(3u, 12u, 3u, 255u),
    Image2RGBA::Pixel(5u, 11u, 2u, 255u),
    Image2RGBA::Pixel(200u, 118u, 93u, 255u),
    Image2RGBA::Pixel(3u, 12u, 3u, 255u),
    Image2RGBA::Pixel(5u, 11u, 2u, 255u),
  };
  Image2RGBA image1RGBA(size, pixelsRGBA);
  Image3RGBA image3RGBA(image1RGBA);
  EXPECT_EQ(Vec3u(size.x(), size.y(), 1u), image3RGBA.getSize());
  EXPECT_EQ(pixelsRGBA, image3RGBA.getPixels());
}



TEST_F(TestImageFile, LoadBmpRGBA)
{
  // Alpha channel in Bmp not supported.
  Image2RGBA imRef(Vec2u(3u, 2u),
    std::vector<Image2RGBA::Pixel>{
      Image2RGBA::Pixel(50u, 100u, 150u, 255u),
      Image2RGBA::Pixel(150u, 100u, 50u, 255u),
      Image2RGBA::Pixel(255u, 200u, 50u, 255u),
      Image2RGBA::Pixel(50u, 100u, 150u, 255u),
      Image2RGBA::Pixel(0u, 255u, 255u, 255u),
      Image2RGBA::Pixel(255u, 200u, 50u, 255u),
    });
  Image2RGBA im = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRGBAError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RGBA>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngRGBA)
{
  Image2RGBA imRef(Vec2u(3u, 2u),
    std::vector<Image2RGBA::Pixel>{
      Image2RGBA::Pixel(50u, 100u, 150u, 255u),
      Image2RGBA::Pixel(150u, 100u, 50u, 255u),
      Image2RGBA::Pixel(255u, 200u, 50u, 255u),
      Image2RGBA::Pixel(50u, 100u, 150u, 63u),
      Image2RGBA::Pixel(0u, 0u, 0u, 0u),
      Image2RGBA::Pixel(255u, 200u, 50u, 127u),
    });
  Image2RGBA im = pngReadFile<PixelFormat::RGBA>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRGBAError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RGBA>(testImageJpg),
    std::runtime_error,
    formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgRGBA)
{
  Image2RGBA imRef(Vec2u(3u, 2u),
    std::vector<Image2RGBA::Pixel>{
      Image2RGBA::Pixel(72u, 86u, 133u, 255u),
      Image2RGBA::Pixel(134u, 111u, 80u, 255u),
      Image2RGBA::Pixel(252u, 204u, 46u, 255u),
      Image2RGBA::Pixel(189u, 225u, 247u, 255u),
      Image2RGBA::Pixel(255u, 253u, 240u, 255u),
      Image2RGBA::Pixel(255u, 232u, 139u, 255u),
    });
  Image2RGBA im = jpgReadFile<PixelFormat::RGBA>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRGBAError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RGBA>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, SaveBmpRGBA)
{
  const std::string savePath = getOutputDir() + "savedBmp.bmp";
  removeDir(savePath);
  Image2RGBA imRef = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
  bmpWriteFile(savePath, imRef);
  Image2RGBA im = bmpReadFile<PixelFormat::RGBA>(savePath);
  EXPECT_EQ(imRef, im);
  EXPECT_TRUE(removeDir(savePath));
}



TEST_F(TestImageFileDeathTest, SaveBmpErrorRGBA)
{
  const std::string savePath = getOutputDir() + "savedBmp.bmp";
  removeDir(savePath);
  Image2RGBA imRef = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
  bmpWriteFile(savePath, imRef);
  HOU_EXPECT_ERROR(bmpWriteFile<PixelFormat::RGBA>(savePath, imRef),
    std::runtime_error,
    formatString(getText(SysError::ImageBmpWrite), savePath.c_str()));
  EXPECT_TRUE(removeDir(savePath));
}



TEST_F(TestImageFile, LoadBmpRGB)
{
  // Alpha channel in Bmp not supported.
  Image2RGB imRef(Vec2u(3u, 2u),
    std::vector<Image2RGB::Pixel>{
      Image2RGB::Pixel(50u, 100u, 150u),
      Image2RGB::Pixel(150u, 100u, 50u),
      Image2RGB::Pixel(255u, 200u, 50u),
      Image2RGB::Pixel(50u, 100u, 150u),
      Image2RGB::Pixel(0u, 255u, 255u),
      Image2RGB::Pixel(255u, 200u, 50u),
    });
  Image2RGB im = bmpReadFile<PixelFormat::RGB>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRGBError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RGB>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngRGB)
{
  Image2RGB imRef(Vec2u(3u, 2u),
    std::vector<Image2RGB::Pixel>{
      Image2RGB::Pixel(50u, 100u, 150u),
      Image2RGB::Pixel(150u, 100u, 50u),
      Image2RGB::Pixel(255u, 200u, 50u),
      Image2RGB::Pixel(50u, 100u, 150u),
      Image2RGB::Pixel(0u, 0u, 0u),
      Image2RGB::Pixel(255u, 200u, 50u),
    });
  Image2RGB im = pngReadFile<PixelFormat::RGB>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRGBError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RGB>(testImageJpg),
    std::runtime_error,
    formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgRGB)
{
  Image2RGB imRef(Vec2u(3u, 2u),
    std::vector<Image2RGB::Pixel>{
      Image2RGB::Pixel(72u, 86u, 133u),
      Image2RGB::Pixel(134u, 111u, 80u),
      Image2RGB::Pixel(252u, 204u, 46u),
      Image2RGB::Pixel(189u, 225u, 247u),
      Image2RGB::Pixel(255u, 253u, 240u),
      Image2RGB::Pixel(255u, 232u, 139u),
    });
  Image2RGB im = jpgReadFile<PixelFormat::RGB>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRGBError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RGB>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadBmpRG)
{
  // Alpha channel in Bmp not supported.
  Image2RG imRef(Vec2u(3u, 2u),
    std::vector<Image2RG::Pixel>{
      Image2RG::Pixel(90u, 255u),
      Image2RG::Pixel(109u, 255u),
      Image2RG::Pixel(199u, 255u),
      Image2RG::Pixel(90u, 255u),
      Image2RG::Pixel(178u, 255u),
      Image2RG::Pixel(199u, 255u),
    });
  Image2RG im = bmpReadFile<PixelFormat::RG>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRGError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RG>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngRG)
{
  Image2RG imRef(Vec2u(3u, 2u),
    std::vector<Image2RG::Pixel>{
      Image2RG::Pixel(90u, 255u),
      Image2RG::Pixel(109u, 255u),
      Image2RG::Pixel(199u, 255u),
      Image2RG::Pixel(90u, 63u),
      Image2RG::Pixel(0u, 0u),
      Image2RG::Pixel(199u, 127u),
    });
  Image2RG im = pngReadFile<PixelFormat::RG>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRGError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RG>(testImageJpg),
    std::runtime_error,
    formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgRG)
{
  Image2RG imRef(Vec2u(3u, 2u),
    std::vector<Image2RG::Pixel>{
      Image2RG::Pixel(87u, 255u),
      Image2RG::Pixel(114u, 255u),
      Image2RG::Pixel(200u, 255u),
      Image2RG::Pixel(217u, 255u),
      Image2RG::Pixel(252u, 255u),
      Image2RG::Pixel(231u, 255u),
    });
  Image2RG im = jpgReadFile<PixelFormat::RG>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRGError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RG>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadBmpR)
{
  // Alpha channel in Bmp not supported.
  Image2R imRef(Vec2u(3u, 2u),
    std::vector<Image2R::Pixel>{
      Image2R::Pixel(90u),
      Image2R::Pixel(109u),
      Image2R::Pixel(199u),
      Image2R::Pixel(90u),
      Image2R::Pixel(178u),
      Image2R::Pixel(199u),
    });
  Image2R im = bmpReadFile<PixelFormat::R>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::R>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngR)
{
  Image2R imRef(Vec2u(3u, 2u),
    std::vector<Image2R::Pixel>{
      Image2R::Pixel(90u),
      Image2R::Pixel(109u),
      Image2R::Pixel(199u),
      Image2R::Pixel(90u),
      Image2R::Pixel(0u),
      Image2R::Pixel(199u),
    });
  Image2R im = pngReadFile<PixelFormat::R>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::R>(testImageJpg),
    std::runtime_error,
    formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgR)
{
  Image2R imRef(Vec2u(3u, 2u),
    std::vector<Image2R::Pixel>{
      Image2R::Pixel(87u),
      Image2R::Pixel(114u),
      Image2R::Pixel(200u),
      Image2R::Pixel(217u),
      Image2R::Pixel(252u),
      Image2R::Pixel(231u),
    });
  Image2R im = jpgReadFile<PixelFormat::R>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::R>(testImagePng),
    std::runtime_error,
    formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}
