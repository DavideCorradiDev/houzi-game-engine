// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

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
  // The following functions are there to generate vectors and images consistent
  // with the concrete Texture type being tested. Without these it would
  // not be possible to write generic tests.
  static typename ImageT::Size generateSize();
  static typename ImageT::PixelCollection generatePixels(const typename ImageT::Size& size);
  static size_t multiplyElements(const typename ImageT::Size& size);
};

template <typename ImageT>
class TestImageDeathTest : public TestImage<ImageT>
{};

using ImageTypes
  = Types<Image1R, Image2R, Image3R, Image1RG, Image2RG, Image3RG, Image1RGB,
    Image2RGB, Image3RGB, Image1RGBA, Image2RGBA, Image3RGBA>;

class TestImageConversionConstructors : public Test
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



const std::string TestImageFile::testImageBmp = getDataDir() + u8"TestImage.bmp";
const std::string TestImageFile::testImagePng = getDataDir() + u8"TestImage.png";
const std::string TestImageFile::testImageJpg = getDataDir() + u8"TestImage.jpg";
const std::string TestImageFile::testImageInvalid = getDataDir() + u8"TestImage.xcf";

}



TYPED_TEST_CASE(TestImage, ImageTypes);
TYPED_TEST_CASE(TestImageDeathTest, ImageTypes);



TYPED_TEST(TestImage, GetDimensionCount)
{
  FAIL();
}



TYPED_TEST(TestImage, GetPixelFormat)
{
  FAIL();
}



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
  EXPECT_EQ(PixelCollection(TestFixture::multiplyElements(sizeRef)), image.getPixels());
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



// TEST_F(TestImage2RGBA, GetPixelConst)
// {
//   Image2RGBA::Pixel px0(1u, 2u, 3u, 4u);
//   Image2RGBA::Pixel px1(6u, 7u, 8u, 9u);
//   Image2RGBA::Pixel px2(11u, 12u, 13u, 14u);
//   Image2RGBA::Pixel px3(16u, 17u, 18u, 19u);
//   Image2RGBA::Pixel px4(21u, 22u, 23u, 24u);
//   Image2RGBA::Pixel px5(26u, 27u, 28u, 29u);
//   Image2RGBA::Size sizeRef(2u, 3u);
//   Image2RGBA::PixelCollection pixelsRef{px0, px1, px2, px3, px4, px5};
//   const Image2RGBA im(sizeRef, pixelsRef);
// 
//   EXPECT_EQ(px0, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
//   EXPECT_EQ(px1, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
//   EXPECT_EQ(px2, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
//   EXPECT_EQ(px3, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
//   EXPECT_EQ(px4, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
//   EXPECT_EQ(px5, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
// }
// 
// 
// 
// TEST_F(TestImage2RGBADeathTest, GetPixelConstErrorOutOfRange)
// {
//   Image2RGBA::Size sizeRef(2u, 3u);
//   const Image2RGBA im(sizeRef);
// 
//   HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), 0u)));
//   HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(0u, sizeRef.y())));
//   HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), sizeRef.y())));
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, GetPixel)
// {
//   Image2RGBA::Pixel px0(1u, 2u, 3u, 4u);
//   Image2RGBA::Pixel px1(6u, 7u, 8u, 9u);
//   Image2RGBA::Pixel px2(11u, 12u, 13u, 14u);
//   Image2RGBA::Pixel px3(16u, 17u, 18u, 19u);
//   Image2RGBA::Pixel px4(21u, 22u, 23u, 24u);
//   Image2RGBA::Pixel px5(26u, 27u, 28u, 29u);
//   Image2RGBA::Size sizeRef(2u, 3u);
//   Image2RGBA::PixelCollection pixelsRef{px0, px1, px2, px3, px4, px5};
//   Image2RGBA im(sizeRef, pixelsRef);
// 
//   EXPECT_EQ(px0, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
//   EXPECT_EQ(px1, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
//   EXPECT_EQ(px2, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
//   EXPECT_EQ(px3, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
//   EXPECT_EQ(px4, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
//   EXPECT_EQ(px5, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
// 
//   im.getPixel(Image2RGBA::Coordinates(0u, 0u)) = px5;
//   im.getPixel(Image2RGBA::Coordinates(1u, 0u)) = px4;
//   im.getPixel(Image2RGBA::Coordinates(0u, 1u)) = px3;
//   im.getPixel(Image2RGBA::Coordinates(1u, 1u)) = px2;
//   im.getPixel(Image2RGBA::Coordinates(0u, 2u)) = px1;
//   im.getPixel(Image2RGBA::Coordinates(1u, 2u)) = px0;
//   EXPECT_EQ(px5, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
//   EXPECT_EQ(px4, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
//   EXPECT_EQ(px3, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
//   EXPECT_EQ(px2, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
//   EXPECT_EQ(px1, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
//   EXPECT_EQ(px0, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
// }
// 
// 
// 
// TEST_F(TestImage2RGBADeathTest, GetPixelErrorOutOfRange)
// {
//   Image2RGBA::Pixel px;
//   Image2RGBA::Size sizeRef(2u, 3u);
//   Image2RGBA im(sizeRef);
// 
//   HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), 0u)) = px);
//   HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(0u, sizeRef.y())) = px);
//   HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), sizeRef.y())) = px);
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, Clear)
// {
//   Image2RGBA::Pixel px0(1u, 2u, 3u, 4u);
//   Image2RGBA::Pixel px1(6u, 7u, 8u, 9u);
//   Image2RGBA::Pixel px2(11u, 12u, 13u, 14u);
//   Image2RGBA::Pixel px3(16u, 17u, 18u, 19u);
//   Image2RGBA::Pixel px4(21u, 22u, 23u, 24u);
//   Image2RGBA::Pixel px5(26u, 27u, 28u, 29u);
//   Image2RGBA::Pixel pxRef(31u, 32u, 33u, 34u);
//   Image2RGBA::Size sizeRef(2u, 3u);
//   Image2RGBA::PixelCollection pixelsRef{px0, px1, px2, px3, px4, px5};
//   Image2RGBA im(sizeRef, pixelsRef);
//   im.clear(pxRef);
// 
//   EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
//   EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
//   EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
//   EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
//   EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
//   EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, Comparison)
// {
//   Image2RGBA im0(Image2RGBA::Size(2u, 3u), Image2RGBA::Pixel(1u, 2u, 3u, 4u));
//   Image2RGBA im1(im0);
//   Image2RGBA im2(Image2RGBA::Size(2u, 5u), Image2RGBA::Pixel(1u, 2u, 3u, 4u));
//   Image2RGBA im3(Image2RGBA::Size(2u, 3u), Image2RGBA::Pixel(8u, 2u, 3u, 4u));
// 
//   EXPECT_TRUE(im0 == im1);
//   EXPECT_FALSE(im0 == im2);
//   EXPECT_FALSE(im0 == im3);
// 
//   EXPECT_FALSE(im0 != im1);
//   EXPECT_TRUE(im0 != im2);
//   EXPECT_TRUE(im0 != im3);
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, OutputStreamOperator)
// {
//   Image2RGBA im(Image2RGBA::Size(2u, 3u)
//     , std::vector<Image2RGBA::Pixel>
//       { Image2RGBA::Pixel{1u, 2u, 3u, 4u}
//       , Image2RGBA::Pixel{6u, 7u, 8u, 9u}
//       , Image2RGBA::Pixel{11u, 12u, 13u, 14u}
//       , Image2RGBA::Pixel{16u, 17u, 18u, 19u}
//       , Image2RGBA::Pixel{21u, 22u, 23u, 24u}
//       , Image2RGBA::Pixel{26u, 27u, 28u, 29u}});
//   const char* outRef
//     = "{Size = (2, 3), Pixels = {"
//     "{R = 1, G = 2, B = 3, A = 4}, "
//     "{R = 6, G = 7, B = 8, A = 9}, "
//     "{R = 11, G = 12, B = 13, A = 14}, "
//     "{R = 16, G = 17, B = 18, A = 19}, "
//     "{R = 21, G = 22, B = 23, A = 24}, "
//     "{R = 26, G = 27, B = 28, A = 29}}}";
// 
//   HOU_EXPECT_OUTPUT(outRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, LoadBmp)
// {
//   // Alpha channel in Bmp not supported.
//   Image2RGBA imRef(Vec2u(3u, 2u), std::vector<Image2RGBA::Pixel>
//   {
//     Image2RGBA::Pixel(50u, 100u, 150u, 255u),
//     Image2RGBA::Pixel(150u, 100u, 50u, 255u),
//     Image2RGBA::Pixel(255u, 200u, 50u, 255u),
//     Image2RGBA::Pixel(50u, 100u, 150u, 255u),
//     Image2RGBA::Pixel(0u, 255u, 255u, 255u),
//     Image2RGBA::Pixel(255u, 200u, 50u, 255u),
//   });
//   Image2RGBA im = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBADeathTest, LoadBmpError)
// {
//   HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RGBA>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, LoadPng)
// {
//   Image2RGBA imRef(Vec2u(3u, 2u), std::vector<Image2RGBA::Pixel>
//     {
//       Image2RGBA::Pixel(50u, 100u, 150u, 255u),
//       Image2RGBA::Pixel(150u, 100u, 50u, 255u),
//       Image2RGBA::Pixel(255u, 200u, 50u, 255u),
//       Image2RGBA::Pixel(50u, 100u, 150u, 63u),
//       Image2RGBA::Pixel(0u, 0u, 0u, 0u),
//       Image2RGBA::Pixel(255u, 200u, 50u, 127u),
//     });
//   Image2RGBA im = pngReadFile<PixelFormat::RGBA>(testImagePng);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBADeathTest, LoadPngError)
// {
//   HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RGBA>(testImageJpg)
//     , std::runtime_error
//     , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, LoadJpg)
// {
//   Image2RGBA imRef(Vec2u(3u, 2u), std::vector<Image2RGBA::Pixel>
//     {
//       Image2RGBA::Pixel(72u, 86u, 133u, 255u),
//       Image2RGBA::Pixel(134u, 111u, 80u, 255u),
//       Image2RGBA::Pixel(252u, 204u, 46u, 255u),
//       Image2RGBA::Pixel(189u, 225u, 247u, 255u),
//       Image2RGBA::Pixel(255u, 253u, 240u, 255u),
//       Image2RGBA::Pixel(255u, 232u, 139u, 255u),
//     });
//   Image2RGBA im = jpgReadFile<PixelFormat::RGBA>(testImageJpg);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBADeathTest, LoadJpgError)
// {
//   HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RGBA>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, SaveBmp)
// {
//   const std::string savePath = getOutputDir() + "savedBmp.bmp";
//   removeDir(savePath);
//   Image2RGBA imRef = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
//   bmpWriteFile(savePath, imRef);
//   Image2RGBA im = bmpReadFile<PixelFormat::RGBA>(savePath);
//   EXPECT_EQ(imRef, im);
//   EXPECT_TRUE(removeDir(savePath));
// }
// 
// 
// 
// TEST_F(TestImage2RGBADeathTest, SaveBmpFailure)
// {
//   const std::string savePath = getOutputDir() + "savedBmp.bmp";
//   removeDir(savePath);
//   Image2RGBA imRef = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
//   bmpWriteFile(savePath, imRef);
//   HOU_EXPECT_ERROR(bmpWriteFile<PixelFormat::RGBA>(savePath, imRef)
//     , std::runtime_error, formatString(getText(SysError::ImageBmpWrite)
//     , savePath.c_str()));
//   EXPECT_TRUE(removeDir(savePath));
// }
// 
// 
// 
// TEST_F(TestImage2RGB, LoadBmp)
// {
//   // Alpha channel in Bmp not supported.
//   Image2RGB imRef(Vec2u(3u, 2u), std::vector<Image2RGB::Pixel>
//   {
//     Image2RGB::Pixel(50u, 100u, 150u),
//     Image2RGB::Pixel(150u, 100u, 50u),
//     Image2RGB::Pixel(255u, 200u, 50u),
//     Image2RGB::Pixel(50u, 100u, 150u),
//     Image2RGB::Pixel(0u, 255u, 255u),
//     Image2RGB::Pixel(255u, 200u, 50u),
//   });
//   Image2RGB im = bmpReadFile<PixelFormat::RGB>(testImageBmp);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBDeathTest, LoadBmpError)
// {
//   HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RGB>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RGB, LoadPng)
// {
//   Image2RGB imRef(Vec2u(3u, 2u), std::vector<Image2RGB::Pixel>
//     {
//       Image2RGB::Pixel(50u, 100u, 150u),
//       Image2RGB::Pixel(150u, 100u, 50u),
//       Image2RGB::Pixel(255u, 200u, 50u),
//       Image2RGB::Pixel(50u, 100u, 150u),
//       Image2RGB::Pixel(0u, 0u, 0u),
//       Image2RGB::Pixel(255u, 200u, 50u),
//     });
//   Image2RGB im = pngReadFile<PixelFormat::RGB>(testImagePng);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBDeathTest, LoadPngError)
// {
//   HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RGB>(testImageJpg)
//     , std::runtime_error
//     , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RGB, LoadJpg)
// {
//   Image2RGB imRef(Vec2u(3u, 2u), std::vector<Image2RGB::Pixel>
//     {
//       Image2RGB::Pixel(72u, 86u, 133u),
//       Image2RGB::Pixel(134u, 111u, 80u),
//       Image2RGB::Pixel(252u, 204u, 46u),
//       Image2RGB::Pixel(189u, 225u, 247u),
//       Image2RGB::Pixel(255u, 253u, 240u),
//       Image2RGB::Pixel(255u, 232u, 139u),
//     });
//   Image2RGB im = jpgReadFile<PixelFormat::RGB>(testImageJpg);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGBDeathTest, LoadJpgError)
// {
//   HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RGB>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RG, LoadBmp)
// {
//   // Alpha channel in Bmp not supported.
//   Image2RG imRef(Vec2u(3u, 2u), std::vector<Image2RG::Pixel>
//   {
//     Image2RG::Pixel(90u, 255u),
//     Image2RG::Pixel(109u, 255u),
//     Image2RG::Pixel(199u, 255u),
//     Image2RG::Pixel(90u, 255u),
//     Image2RG::Pixel(178u, 255u),
//     Image2RG::Pixel(199u, 255u),
//   });
//   Image2RG im = bmpReadFile<PixelFormat::RG>(testImageBmp);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGDeathTest, LoadBmpError)
// {
//   HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RG>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RG, LoadPng)
// {
//   Image2RG imRef(Vec2u(3u, 2u), std::vector<Image2RG::Pixel>
//     {
//       Image2RG::Pixel(90u, 255u),
//       Image2RG::Pixel(109u, 255u),
//       Image2RG::Pixel(199u, 255u),
//       Image2RG::Pixel(90u, 63u),
//       Image2RG::Pixel(0u, 0u),
//       Image2RG::Pixel(199u, 127u),
//     });
//   Image2RG im = pngReadFile<PixelFormat::RG>(testImagePng);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGDeathTest, LoadPngError)
// {
//   HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RG>(testImageJpg)
//     , std::runtime_error
//     , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2RG, LoadJpg)
// {
//   Image2RG imRef(Vec2u(3u, 2u), std::vector<Image2RG::Pixel>
//     {
//       Image2RG::Pixel(87u, 255u),
//       Image2RG::Pixel(114u, 255u),
//       Image2RG::Pixel(200u, 255u),
//       Image2RG::Pixel(217u, 255u),
//       Image2RG::Pixel(252u, 255u),
//       Image2RG::Pixel(231u, 255u),
//     });
//   Image2RG im = jpgReadFile<PixelFormat::RG>(testImageJpg);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RGDeathTest, LoadJpgError)
// {
//   HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RG>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2R, LoadBmp)
// {
//   // Alpha channel in Bmp not supported.
//   Image2R imRef(Vec2u(3u, 2u), std::vector<Image2R::Pixel>
//   {
//     Image2R::Pixel(90u),
//     Image2R::Pixel(109u),
//     Image2R::Pixel(199u),
//     Image2R::Pixel(90u),
//     Image2R::Pixel(178u),
//     Image2R::Pixel(199u),
//   });
//   Image2R im = bmpReadFile<PixelFormat::R>(testImageBmp);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RDeathTest, LoadBmpError)
// {
//   HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::R>(testImagePng)
//     , std::runtime_error
//     , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
// }
// 
// 
// 
// TEST_F(TestImage2R, LoadPng)
// {
//   Image2R imRef(Vec2u(3u, 2u), std::vector<Image2R::Pixel>
//     {
//       Image2R::Pixel(90u),
//       Image2R::Pixel(109u),
//       Image2R::Pixel(199u),
//       Image2R::Pixel(90u),
//       Image2R::Pixel(0u),
//       Image2R::Pixel(199u),
//     });
//   Image2R im = pngReadFile<PixelFormat::R>(testImagePng);
//   EXPECT_EQ(imRef, im);
// }
// 
// 
// 
// TEST_F(TestImage2RDeathTest, LoadPngError)
// {
//   HOU_EXPECT_ERROR(pngReadFile<PixelFormat::R>(testImageJpg)
//     , std::runtime_error
//     , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
// }
// 
// TEST_F(TestImage2RGBA, Image2RConstructor)
// {
//   Image2R::Size size(2u, 3u);
//   Image2R::PixelCollection pixelsR
//   {
//     Image2R::Pixel(1u),
//     Image2R::Pixel(2u),
//     Image2R::Pixel(3u),
//     Image2R::Pixel(4u),
//     Image2R::Pixel(5u),
//     Image2R::Pixel(6u),
//   };
// 
//   Image2RGBA::PixelCollection pixelsRGBA
//   {
//     Image2RGBA::Pixel(1u, 1u, 1u, 255u),
//     Image2RGBA::Pixel(2u, 2u, 2u, 255u),
//     Image2RGBA::Pixel(3u, 3u, 3u, 255u),
//     Image2RGBA::Pixel(4u, 4u, 4u, 255u),
//     Image2RGBA::Pixel(5u, 5u, 5u, 255u),
//     Image2RGBA::Pixel(6u, 6u, 6u, 255u),
//   };
// 
//   Image2R imageR(size, pixelsR);
//   Image2RGBA imageRGBA(imageR);
// 
//   EXPECT_EQ(size, imageRGBA.getSize());
//   EXPECT_EQ(pixelsRGBA, imageRGBA.getPixels());
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, Image2RGConstructor)
// {
//   Image2RG::Size size(2u, 3u);
//   Image2RG::PixelCollection pixelsRG
//   {
//     Image2RG::Pixel(1u, 11u),
//     Image2RG::Pixel(2u, 12u),
//     Image2RG::Pixel(3u, 13u),
//     Image2RG::Pixel(4u, 14u),
//     Image2RG::Pixel(5u, 15u),
//     Image2RG::Pixel(6u, 16u),
//   };
// 
//   Image2RGBA::PixelCollection pixelsRGBA
//   {
//     Image2RGBA::Pixel(1u, 1u, 1u, 11u),
//     Image2RGBA::Pixel(2u, 2u, 2u, 12u),
//     Image2RGBA::Pixel(3u, 3u, 3u, 13u),
//     Image2RGBA::Pixel(4u, 4u, 4u, 14u),
//     Image2RGBA::Pixel(5u, 5u, 5u, 15u),
//     Image2RGBA::Pixel(6u, 6u, 6u, 16u),
//   };
// 
//   Image2RG imageRG(size, pixelsRG);
//   Image2RGBA imageRGBA(imageRG);
// 
//   EXPECT_EQ(size, imageRGBA.getSize());
//   EXPECT_EQ(pixelsRGBA, imageRGBA.getPixels());
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, Image2RGBConstructor)
// {
//   Image2RGB::Size size(2u, 3u);
//   Image2RGB::PixelCollection pixelsRGB
//   {
//     Image2RGB::Pixel(200u, 118u, 93u),
//     Image2RGB::Pixel(3u, 12u, 3u),
//     Image2RGB::Pixel(5u, 11u, 2u),
//     Image2RGB::Pixel(200u, 100u, 0u),
//     Image2RGB::Pixel(0u, 21u, 0u),
//     Image2RGB::Pixel(100u, 20u, 0u),
//   };
// 
//   Image2RGBA::PixelCollection pixelsRGBA
//   {
//     Image2RGBA::Pixel(200u, 118u, 93u, 255u),
//     Image2RGBA::Pixel(3u, 12u, 3u, 255u),
//     Image2RGBA::Pixel(5u, 11u, 2u, 255u),
//     Image2RGBA::Pixel(200u, 100u, 0u, 255u),
//     Image2RGBA::Pixel(0u, 21u, 0u, 255u),
//     Image2RGBA::Pixel(100u, 20u, 0u, 255u),
//   };
// 
//   Image2RGB imageRGB(size, pixelsRGB);
//   Image2RGBA imageRGBA(imageRGB);
// 
//   EXPECT_EQ(size, imageRGBA.getSize());
//   EXPECT_EQ(pixelsRGBA, imageRGBA.getPixels());
// }
// 
// 
// 
// TEST_F(TestImage2RGBA, Image1RGBAConstructor)
// {
//   Image1RGB::Size size(3u);
//   Image1RGBA::PixelCollection pixelsRGBA
//   {
//     Image2RGBA::Pixel(200u, 118u, 93u, 255u),
//     Image2RGBA::Pixel(3u, 12u, 3u, 255u),
//     Image2RGBA::Pixel(5u, 11u, 2u, 255u),
//   };
//   Image1RGBA image1RGBA(size, pixelsRGBA);
//   Image2RGBA image2RGBA(image1RGBA);
//   EXPECT_EQ(Vec2u(size.x(), 1u), image2RGBA.getSize());
//   EXPECT_EQ(pixelsRGBA, image2RGBA.getPixels());
// }
// 
// 
// 
