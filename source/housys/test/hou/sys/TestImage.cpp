// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/TestData.hpp"

#include "hou/sys/file.hpp"
#include "hou/sys/image.hpp"
#include "hou/sys/sys_error.hpp"

using namespace hou;
using namespace testing;


namespace
{

template <typename ImageT>
class TestImage : public Test
{
public:
  static typename ImageT::size_type generateSize();
  static typename ImageT::pixel_collection generatePixels(
    const typename ImageT::size_type& size);
  static size_t multiplyElements(const typename ImageT::size_type& size);
  static size_t compute_pixel_index(
    const typename ImageT::offset_type& coordinates,
    const typename ImageT::size_type& size);
  static typename ImageT::offset_type computePixelCoordinates(
    size_t index, const typename ImageT::size_type& size);
};

template <typename ImageT>
class TestImageDeathTest : public TestImage<ImageT>
{};

using ImageTypes
  = Types<image1R, image2R, image3R, image1RG, image2RG, image3RG, image1RGB,
    image2RGB, image3RGB, image1RGBA, image2RGBA, image3RGBA>;

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
typename image1R::size_type TestImage<image1R>::generateSize()
{
  return vec1u{4u};
}



template <>
typename image1RG::size_type TestImage<image1RG>::generateSize()
{
  return vec1u{4u};
}



template <>
typename image1RGB::size_type TestImage<image1RGB>::generateSize()
{
  return vec1u{4u};
}



template <>
typename image1RGBA::size_type TestImage<image1RGBA>::generateSize()
{
  return vec1u{4u};
}



template <>
typename image2R::size_type TestImage<image2R>::generateSize()
{
  return vec2u{4u, 7u};
}



template <>
typename image2RG::size_type TestImage<image2RG>::generateSize()
{
  return vec2u{4u, 7u};
}



template <>
typename image2RGB::size_type TestImage<image2RGB>::generateSize()
{
  return vec2u{4u, 7u};
}



template <>
typename image2RGBA::size_type TestImage<image2RGBA>::generateSize()
{
  return vec2u{4u, 7u};
}



template <>
typename image3R::size_type TestImage<image3R>::generateSize()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3RG::size_type TestImage<image3RG>::generateSize()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3RGB::size_type TestImage<image3RGB>::generateSize()
{
  return vec3u{4u, 7u, 11u};
}



template <>
typename image3RGBA::size_type TestImage<image3RGBA>::generateSize()
{
  return vec3u{4u, 7u, 11u};
}



template <typename ImageT>
typename ImageT::pixel_collection TestImage<ImageT>::generatePixels(
  const typename ImageT::size_type& size)
{
  typename ImageT::pixel_collection retval(multiplyElements(size));
  for(size_t i = 0; i < retval.size(); ++i)
  {
    typename ImageT::pixel ph_pixel;
    ph_pixel.set_r(i);
    retval[i] = ph_pixel;
  }
  return retval;
}



template <typename ImageT>
size_t TestImage<ImageT>::multiplyElements(const typename ImageT::size_type& size)
{
  size_t retval = size(0);
  for(size_t i = 1; i < size.get_size(); ++i)
  {
    retval *= size(i);
  }
  return retval;
}



template <typename ImageT>
size_t TestImage<ImageT>::compute_pixel_index(
  const typename ImageT::offset_type& coordinates,
  const typename ImageT::size_type& size)
{
  size_t idx = 0;
  size_t multiplier = 1;
  for(size_t i = 0; i < coordinates.get_size(); ++i)
  {
    idx += coordinates(i) * multiplier;
    multiplier *= size(i);
  }
  return idx;
}



template <typename ImageT>
typename ImageT::offset_type TestImage<ImageT>::computePixelCoordinates(
  size_t index, const typename ImageT::size_type& size)
{
  using offset_type = typename ImageT::offset_type;

  offset_type coords;
  size_t divider = multiplyElements(size);
  for(size_t i = size.get_size() - 1; i > 0; --i)
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
  EXPECT_EQ(TypeParam::pixel::get_byte_count(), TypeParam::get_pixel_byte_count());
}



TYPED_TEST(TestImage, DefaultConstructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  TypeParam ph_image;
  EXPECT_EQ(size_type::zero(), ph_image.get_size());
  EXPECT_EQ(pixel_collection(), ph_image.get_pixels());
}



TYPED_TEST(TestImage, SizeConstructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  TypeParam ph_image(sizeRef);
  EXPECT_EQ(sizeRef, ph_image.get_size());
  EXPECT_EQ(
    pixel_collection(TestFixture::multiplyElements(sizeRef)), ph_image.get_pixels());
}



TYPED_TEST(TestImage, PixelConstructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel pixelRef;
  pixelRef.set_r(5u);
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef), pixelRef);
  TypeParam ph_image(sizeRef, pixelRef);

  EXPECT_EQ(sizeRef, ph_image.get_size());
  EXPECT_EQ(pixelsRef, ph_image.get_pixels());
}



TYPED_TEST(TestImage, PixelsConstructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef = TestFixture::generatePixels(sizeRef);
  TypeParam ph_image(sizeRef, pixelsRef);

  EXPECT_EQ(sizeRef, ph_image.get_size());
  EXPECT_EQ(pixelsRef, ph_image.get_pixels());
}



TYPED_TEST(TestImageDeathTest, PixelsConstructorErrorTooFewPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef) - 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(sizeRef, pixelsRef));
}



TYPED_TEST(TestImageDeathTest, PixelsConstructorErrorTooManyPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(sizeRef, pixelsRef));
}



TYPED_TEST(TestImage, PixelsMoveConstructor)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef = TestFixture::generatePixels(sizeRef);
  pixel_collection pixels(pixelsRef);
  TypeParam ph_image(sizeRef, std::move(pixels));

  EXPECT_EQ(sizeRef, ph_image.get_size());
  EXPECT_EQ(pixelsRef, ph_image.get_pixels());
}



TYPED_TEST(TestImageDeathTest, PixelsMoveConstructorErrorTooFewPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef) - 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(sizeRef, std::move(pixelsRef)));
}



TYPED_TEST(TestImageDeathTest, PixelsMoveConstructorErrorTooManyPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef) + 1u);
  HOU_EXPECT_PRECONDITION(TypeParam ph_image(sizeRef, std::move(pixelsRef)));
}



TYPED_TEST(TestImage, SetPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef = TestFixture::generatePixels(sizeRef);
  TypeParam ph_image(sizeRef);
  ph_image.set_pixels(pixelsRef);
  EXPECT_EQ(pixelsRef, ph_image.get_pixels());
}



TYPED_TEST(TestImageDeathTest, SetPixelsErrorTooFewPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef) - 1u);
  TypeParam ph_image(sizeRef);
  HOU_EXPECT_PRECONDITION(ph_image.set_pixels(pixelsRef));
}



TYPED_TEST(TestImageDeathTest, SetPixelsErrorTooManyPixels)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef) + 1u);
  TypeParam ph_image(sizeRef);
  HOU_EXPECT_PRECONDITION(ph_image.set_pixels(pixelsRef));
}



TYPED_TEST(TestImage, GetPixel)
{
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef = TestFixture::generatePixels(sizeRef);
  TypeParam ph_image(sizeRef, pixelsRef);

  for(size_t i = 0; i < pixelsRef.size(); ++i)
  {
    EXPECT_EQ(pixelsRef[i],
      ph_image.get_pixel(TestFixture::computePixelCoordinates(i, ph_image.get_size())));
  }
}



TYPED_TEST(TestImageDeathTest, GetPixelErrorOutOfRange)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type sizeRef = TestFixture::generateSize();
  TypeParam ph_image(sizeRef);

  for(size_t i = 0; i < sizeRef.get_size(); ++i)
  {
    offset_type coords;
    coords(i) = sizeRef(i);
    HOU_EXPECT_PRECONDITION(ph_image.get_pixel(coords));
  }
  HOU_EXPECT_PRECONDITION(ph_image.get_pixel(sizeRef));
}



TYPED_TEST(TestImage, SetPixel)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel pixelRef;
  pixelRef.set_r(42u);
  for(size_t i = 0; i < TestFixture::multiplyElements(sizeRef); ++i)
  {
    TypeParam ph_image(sizeRef);
    pixel_collection pixelsRef = ph_image.get_pixels();
    pixelsRef[i] = pixelRef;
    ph_image.set_pixel(
      TestFixture::computePixelCoordinates(i, ph_image.get_size()), pixelRef);
    EXPECT_EQ(pixelsRef[i],
      ph_image.get_pixel(TestFixture::computePixelCoordinates(i, ph_image.get_size())));
  }
}



TYPED_TEST(TestImageDeathTest, SetPixelErrorOutOfRange)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using offset_type = typename TypeParam::offset_type;

  size_type sizeRef = TestFixture::generateSize();
  TypeParam ph_image(sizeRef);

  pixel pixelRef;
  for(size_t i = 0; i < sizeRef.get_size(); ++i)
  {
    offset_type coords;
    coords(i) = sizeRef(i);
    HOU_EXPECT_PRECONDITION(ph_image.set_pixel(coords, pixelRef));
  }
  HOU_EXPECT_PRECONDITION(ph_image.set_pixel(sizeRef, pixelRef));
}



TYPED_TEST(TestImage, GetSubImage)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  pixel_collection pixelsRef = TestFixture::generatePixels(imageSize);
  pixel_collection subPixelsRef(TestFixture::multiplyElements(subImageSize));
  for(size_t i = 0; i < subPixelsRef.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::computePixelCoordinates(i, subImageSize);
    offset_type imageCoords = subImageOffset + subImageCoords;
    subPixelsRef[i]
      = pixelsRef[TestFixture::compute_pixel_index(imageCoords, imageSize)];
  }

  TypeParam ph_image(imageSize, pixelsRef);
  TypeParam subImageRef(subImageSize, subPixelsRef);
  EXPECT_EQ(subImageRef, ph_image.get_sub_image(subImageOffset, subImageSize));
}



TYPED_TEST(TestImageDeathTest, GetSubImageErrorOverflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam ph_image(imageSize);
  HOU_EXPECT_PRECONDITION(ph_image.get_sub_image(subImageOffset, subImageSize));
}



TYPED_TEST(TestImage, SetSubImage)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageSize(i) = (i + 1) * 2;
    subImageOffset(i) = i + 1;
  }

  pixel_collection pixelsRef(TestFixture::multiplyElements(imageSize));
  pixel_collection subPixelsRef(TestFixture::generatePixels(subImageSize));
  for(size_t i = 0; i < subPixelsRef.size(); ++i)
  {
    offset_type subImageCoords
      = TestFixture::computePixelCoordinates(i, subImageSize);
    offset_type imageCoords = subImageOffset + subImageCoords;
    pixelsRef[TestFixture::compute_pixel_index(imageCoords, imageSize)]
      = subPixelsRef[i];
  }

  TypeParam ph_image(imageSize);
  TypeParam imageRef(imageSize, pixelsRef);
  TypeParam subImageRef(subImageSize, subPixelsRef);
  ph_image.set_sub_image(subImageOffset, subImageRef);

  EXPECT_EQ(imageRef, ph_image);
  EXPECT_EQ(subImageRef, ph_image.get_sub_image(subImageOffset, subImageSize));
}



TYPED_TEST(TestImageDeathTest, SetSubImageErrorOverflow)
{
  using size_type = typename TypeParam::size_type;
  using offset_type = typename TypeParam::offset_type;

  size_type imageSize;
  size_type subImageSize;
  offset_type subImageOffset;
  for(size_t i = 0; i < imageSize.get_size(); ++i)
  {
    imageSize(i) = (i + 1) * 4;
    subImageOffset(i) = i + 1;
    subImageSize(i) = (i + 1) * 4 - subImageOffset(i) + 1u;
  }

  TypeParam ph_image(imageSize);
  TypeParam subImage(subImageSize);
  HOU_EXPECT_PRECONDITION(ph_image.set_sub_image(subImageOffset, subImage));
}



TYPED_TEST(TestImage, Clear)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  TypeParam ph_image(sizeRef);

  pixel pixelRef;
  pixelRef.set_r(42u);

  pixel_collection pixelsRef(TestFixture::multiplyElements(sizeRef), pixelRef);
  ph_image.clear(pixelRef);
  EXPECT_EQ(pixelsRef, ph_image.get_pixels());
}



TYPED_TEST(TestImage, Comparison)
{
  using size_type = typename TypeParam::size_type;
  using pixel = typename TypeParam::pixel;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type size1 = TestFixture::generateSize();
  size_type size2 = size1 * 2;
  pixel pixel1;
  pixel1.set_r(42);
  pixel pixel2;
  pixel2.set_r(88);
  pixel_collection pixels11(TestFixture::multiplyElements(size1), pixel1);
  pixel_collection pixels12(TestFixture::multiplyElements(size1), pixel2);
  pixel_collection pixels22(TestFixture::multiplyElements(size2), pixel2);

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
  using size_type = typename TypeParam::size_type;
  using pixel_collection = typename TypeParam::pixel_collection;

  size_type sizeRef = TestFixture::generateSize();
  pixel_collection pixelsRef = TestFixture::generatePixels(sizeRef);

  TypeParam ph_image(sizeRef, pixelsRef);

  std::stringstream ss;
  ss << "{size_type = " << transpose(sizeRef) << ", Pixels = " << pixelsRef << "}";

  HOU_EXPECT_OUTPUT(ss.str().c_str(), ph_image);
}



TEST_F(TestImageClassAttributes, GetDimensionCount)
{
  EXPECT_EQ(1u, image1R::get_dimension_count());
  EXPECT_EQ(1u, image1RG::get_dimension_count());
  EXPECT_EQ(1u, image1RGB::get_dimension_count());
  EXPECT_EQ(1u, image1RGBA::get_dimension_count());
  EXPECT_EQ(2u, image2R::get_dimension_count());
  EXPECT_EQ(2u, image2RG::get_dimension_count());
  EXPECT_EQ(2u, image2RGB::get_dimension_count());
  EXPECT_EQ(2u, image2RGBA::get_dimension_count());
  EXPECT_EQ(3u, image3R::get_dimension_count());
  EXPECT_EQ(3u, image3RG::get_dimension_count());
  EXPECT_EQ(3u, image3RGB::get_dimension_count());
  EXPECT_EQ(3u, image3RGBA::get_dimension_count());
}



TEST_F(TestImageClassAttributes, GetPixelFormat)
{
  EXPECT_EQ(pixel_format::r, image1R::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image1RG::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image1RGB::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image1RGBA::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image2R::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image2RG::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image2RGB::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image2RGBA::get_pixel_format());
  EXPECT_EQ(pixel_format::r, image3R::get_pixel_format());
  EXPECT_EQ(pixel_format::rg, image3RG::get_pixel_format());
  EXPECT_EQ(pixel_format::rgb, image3RGB::get_pixel_format());
  EXPECT_EQ(pixel_format::rgba, image3RGBA::get_pixel_format());
}



TEST_F(TestImageConversionConstructor, R2RGBAConstructor)
{
  image2R::size_type size(2u, 3u);
  image2R::pixel_collection pixelsR{
    image2R::pixel(1u),
    image2R::pixel(2u),
    image2R::pixel(3u),
    image2R::pixel(4u),
    image2R::pixel(5u),
    image2R::pixel(6u),
  };

  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(1u, 1u, 1u, 255u),
    image2RGBA::pixel(2u, 2u, 2u, 255u),
    image2RGBA::pixel(3u, 3u, 3u, 255u),
    image2RGBA::pixel(4u, 4u, 4u, 255u),
    image2RGBA::pixel(5u, 5u, 5u, 255u),
    image2RGBA::pixel(6u, 6u, 6u, 255u),
  };

  image2R imageR(size, pixelsR);
  image2RGBA imageRGBA(imageR);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(TestImageConversionConstructor, RG2RGBAConstructor)
{
  image2RG::size_type size(2u, 3u);
  image2RG::pixel_collection pixelsRG{
    image2RG::pixel(1u, 11u),
    image2RG::pixel(2u, 12u),
    image2RG::pixel(3u, 13u),
    image2RG::pixel(4u, 14u),
    image2RG::pixel(5u, 15u),
    image2RG::pixel(6u, 16u),
  };

  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(1u, 1u, 1u, 11u),
    image2RGBA::pixel(2u, 2u, 2u, 12u),
    image2RGBA::pixel(3u, 3u, 3u, 13u),
    image2RGBA::pixel(4u, 4u, 4u, 14u),
    image2RGBA::pixel(5u, 5u, 5u, 15u),
    image2RGBA::pixel(6u, 6u, 6u, 16u),
  };

  image2RG imageRG(size, pixelsRG);
  image2RGBA imageRGBA(imageRG);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(TestImageConversionConstructor, RGB2RGBAConstructor)
{
  image2RGB::size_type size(2u, 3u);
  image2RGB::pixel_collection pixelsRGB{
    image2RGB::pixel(200u, 118u, 93u),
    image2RGB::pixel(3u, 12u, 3u),
    image2RGB::pixel(5u, 11u, 2u),
    image2RGB::pixel(200u, 100u, 0u),
    image2RGB::pixel(0u, 21u, 0u),
    image2RGB::pixel(100u, 20u, 0u),
  };

  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(200u, 118u, 93u, 255u),
    image2RGBA::pixel(3u, 12u, 3u, 255u),
    image2RGBA::pixel(5u, 11u, 2u, 255u),
    image2RGBA::pixel(200u, 100u, 0u, 255u),
    image2RGBA::pixel(0u, 21u, 0u, 255u),
    image2RGBA::pixel(100u, 20u, 0u, 255u),
  };

  image2RGB imageRGB(size, pixelsRGB);
  image2RGBA imageRGBA(imageRGB);

  EXPECT_EQ(size, imageRGBA.get_size());
  EXPECT_EQ(pixelsRGBA, imageRGBA.get_pixels());
}



TEST_F(TestImageConversionConstructor, Image1ToImage2Constructor)
{
  image1RGB::size_type size(3u);
  image1RGBA::pixel_collection pixelsRGBA{
    image1RGBA::pixel(200u, 118u, 93u, 255u),
    image1RGBA::pixel(3u, 12u, 3u, 255u),
    image1RGBA::pixel(5u, 11u, 2u, 255u),
  };
  image1RGBA image1RGBA(size, pixelsRGBA);
  image2RGBA image2RGBA(image1RGBA);
  EXPECT_EQ(vec2u(size.x(), 1u), image2RGBA.get_size());
  EXPECT_EQ(pixelsRGBA, image2RGBA.get_pixels());
}



TEST_F(TestImageConversionConstructor, Image1ToImage3Constructor)
{
  image1RGB::size_type size(3u);
  image1RGBA::pixel_collection pixelsRGBA{
    image1RGBA::pixel(200u, 118u, 93u, 255u),
    image1RGBA::pixel(3u, 12u, 3u, 255u),
    image1RGBA::pixel(5u, 11u, 2u, 255u),
  };
  image1RGBA image1RGBA(size, pixelsRGBA);
  image3RGBA image3RGBA(image1RGBA);
  EXPECT_EQ(vec3u(size.x(), 1u, 1u), image3RGBA.get_size());
  EXPECT_EQ(pixelsRGBA, image3RGBA.get_pixels());
}



TEST_F(TestImageConversionConstructor, Image2ToImage3Constructor)
{
  image2RGB::size_type size(3u, 2u);
  image2RGBA::pixel_collection pixelsRGBA{
    image2RGBA::pixel(200u, 118u, 93u, 255u),
    image2RGBA::pixel(3u, 12u, 3u, 255u),
    image2RGBA::pixel(5u, 11u, 2u, 255u),
    image2RGBA::pixel(200u, 118u, 93u, 255u),
    image2RGBA::pixel(3u, 12u, 3u, 255u),
    image2RGBA::pixel(5u, 11u, 2u, 255u),
  };
  image2RGBA image1RGBA(size, pixelsRGBA);
  image3RGBA image3RGBA(image1RGBA);
  EXPECT_EQ(vec3u(size.x(), size.y(), 1u), image3RGBA.get_size());
  EXPECT_EQ(pixelsRGBA, image3RGBA.get_pixels());
}



TEST_F(TestImageFile, LoadBmpRGBA)
{
  // Alpha channel in Bmp not supported.
  image2RGBA imRef(vec2u(3u, 2u),
    std::vector<image2RGBA::pixel>{
      image2RGBA::pixel(50u, 100u, 150u, 255u),
      image2RGBA::pixel(150u, 100u, 50u, 255u),
      image2RGBA::pixel(255u, 200u, 50u, 255u),
      image2RGBA::pixel(50u, 100u, 150u, 255u),
      image2RGBA::pixel(0u, 255u, 255u, 255u),
      image2RGBA::pixel(255u, 200u, 50u, 255u),
    });
  image2RGBA im = bmp_read_file<pixel_format::rgba>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRGBAError)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::rgba>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngRGBA)
{
  image2RGBA imRef(vec2u(3u, 2u),
    std::vector<image2RGBA::pixel>{
      image2RGBA::pixel(50u, 100u, 150u, 255u),
      image2RGBA::pixel(150u, 100u, 50u, 255u),
      image2RGBA::pixel(255u, 200u, 50u, 255u),
      image2RGBA::pixel(50u, 100u, 150u, 63u),
      image2RGBA::pixel(0u, 0u, 0u, 0u),
      image2RGBA::pixel(255u, 200u, 50u, 127u),
    });
  image2RGBA im = png_read_file<pixel_format::rgba>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRGBAError)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::rgba>(testImageJpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgRGBA)
{
  image2RGBA imRef(vec2u(3u, 2u),
    std::vector<image2RGBA::pixel>{
      image2RGBA::pixel(72u, 86u, 133u, 255u),
      image2RGBA::pixel(134u, 111u, 80u, 255u),
      image2RGBA::pixel(252u, 204u, 46u, 255u),
      image2RGBA::pixel(189u, 225u, 247u, 255u),
      image2RGBA::pixel(255u, 253u, 240u, 255u),
      image2RGBA::pixel(255u, 232u, 139u, 255u),
    });
  image2RGBA im = jpg_read_file<pixel_format::rgba>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRGBAError)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::rgba>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, SaveBmpRGBA)
{
  const std::string savePath = getOutputDir() + "savedBmp.bmp";
  remove_dir(savePath);
  image2RGBA imRef = bmp_read_file<pixel_format::rgba>(testImageBmp);
  bmp_write_file(savePath, imRef);
  image2RGBA im = bmp_read_file<pixel_format::rgba>(savePath);
  EXPECT_EQ(imRef, im);
  EXPECT_TRUE(remove_dir(savePath));
}



TEST_F(TestImageFileDeathTest, SaveBmpErrorRGBA)
{
  const std::string savePath = getOutputDir() + "savedBmp.bmp";
  remove_dir(savePath);
  image2RGBA imRef = bmp_read_file<pixel_format::rgba>(testImageBmp);
  bmp_write_file(savePath, imRef);
  HOU_EXPECT_ERROR(bmp_write_file<pixel_format::rgba>(savePath, imRef),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_write), savePath.c_str()));
  EXPECT_TRUE(remove_dir(savePath));
}



TEST_F(TestImageFile, LoadBmpRGB)
{
  // Alpha channel in Bmp not supported.
  image2RGB imRef(vec2u(3u, 2u),
    std::vector<image2RGB::pixel>{
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(150u, 100u, 50u),
      image2RGB::pixel(255u, 200u, 50u),
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(0u, 255u, 255u),
      image2RGB::pixel(255u, 200u, 50u),
    });
  image2RGB im = bmp_read_file<pixel_format::rgb>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRGBError)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::rgb>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngRGB)
{
  image2RGB imRef(vec2u(3u, 2u),
    std::vector<image2RGB::pixel>{
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(150u, 100u, 50u),
      image2RGB::pixel(255u, 200u, 50u),
      image2RGB::pixel(50u, 100u, 150u),
      image2RGB::pixel(0u, 0u, 0u),
      image2RGB::pixel(255u, 200u, 50u),
    });
  image2RGB im = png_read_file<pixel_format::rgb>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRGBError)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::rgb>(testImageJpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgRGB)
{
  image2RGB imRef(vec2u(3u, 2u),
    std::vector<image2RGB::pixel>{
      image2RGB::pixel(72u, 86u, 133u),
      image2RGB::pixel(134u, 111u, 80u),
      image2RGB::pixel(252u, 204u, 46u),
      image2RGB::pixel(189u, 225u, 247u),
      image2RGB::pixel(255u, 253u, 240u),
      image2RGB::pixel(255u, 232u, 139u),
    });
  image2RGB im = jpg_read_file<pixel_format::rgb>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRGBError)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::rgb>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadBmpRG)
{
  // Alpha channel in Bmp not supported.
  image2RG imRef(vec2u(3u, 2u),
    std::vector<image2RG::pixel>{
      image2RG::pixel(90u, 255u),
      image2RG::pixel(109u, 255u),
      image2RG::pixel(199u, 255u),
      image2RG::pixel(90u, 255u),
      image2RG::pixel(178u, 255u),
      image2RG::pixel(199u, 255u),
    });
  image2RG im = bmp_read_file<pixel_format::rg>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRGError)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::rg>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngRG)
{
  image2RG imRef(vec2u(3u, 2u),
    std::vector<image2RG::pixel>{
      image2RG::pixel(90u, 255u),
      image2RG::pixel(109u, 255u),
      image2RG::pixel(199u, 255u),
      image2RG::pixel(90u, 63u),
      image2RG::pixel(0u, 0u),
      image2RG::pixel(199u, 127u),
    });
  image2RG im = png_read_file<pixel_format::rg>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRGError)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::rg>(testImageJpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgRG)
{
  image2RG imRef(vec2u(3u, 2u),
    std::vector<image2RG::pixel>{
      image2RG::pixel(87u, 255u),
      image2RG::pixel(114u, 255u),
      image2RG::pixel(200u, 255u),
      image2RG::pixel(217u, 255u),
      image2RG::pixel(252u, 255u),
      image2RG::pixel(231u, 255u),
    });
  image2RG im = jpg_read_file<pixel_format::rg>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRGError)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::rg>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadBmpR)
{
  // Alpha channel in Bmp not supported.
  image2R imRef(vec2u(3u, 2u),
    std::vector<image2R::pixel>{
      image2R::pixel(90u),
      image2R::pixel(109u),
      image2R::pixel(199u),
      image2R::pixel(90u),
      image2R::pixel(178u),
      image2R::pixel(199u),
    });
  image2R im = bmp_read_file<pixel_format::r>(testImageBmp);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadBmpRError)
{
  HOU_EXPECT_ERROR(bmp_read_file<pixel_format::r>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_bmp_read), testImagePng.c_str()));
}



TEST_F(TestImageFile, LoadPngR)
{
  image2R imRef(vec2u(3u, 2u),
    std::vector<image2R::pixel>{
      image2R::pixel(90u),
      image2R::pixel(109u),
      image2R::pixel(199u),
      image2R::pixel(90u),
      image2R::pixel(0u),
      image2R::pixel(199u),
    });
  image2R im = png_read_file<pixel_format::r>(testImagePng);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadPngRError)
{
  HOU_EXPECT_ERROR(png_read_file<pixel_format::r>(testImageJpg),
    std::runtime_error,
    format_string(get_text(sys_error::image_png_read), testImageJpg.c_str()));
}



TEST_F(TestImageFile, LoadJpgR)
{
  image2R imRef(vec2u(3u, 2u),
    std::vector<image2R::pixel>{
      image2R::pixel(87u),
      image2R::pixel(114u),
      image2R::pixel(200u),
      image2R::pixel(217u),
      image2R::pixel(252u),
      image2R::pixel(231u),
    });
  image2R im = jpg_read_file<pixel_format::r>(testImageJpg);
  EXPECT_EQ(imRef, im);
}



TEST_F(TestImageFileDeathTest, LoadJpgRError)
{
  HOU_EXPECT_ERROR(jpg_read_file<pixel_format::r>(testImagePng),
    std::runtime_error,
    format_string(get_text(sys_error::image_jpg_read), testImagePng.c_str()));
}
