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

class TestImage
  : public Test
{
public:
  static const std::string testImageBmp;
  static const std::string testImagePng;
  static const std::string testImageJpg;
  static const std::string testImageInvalid;
};

class TestImage2R : public TestImage {};
class TestImage2RG : public TestImage {};
class TestImage2RGB : public TestImage {};
class TestImage2RGBA : public TestImage {};
class TestImage2RDeathTest : public TestImage2R {};
class TestImage2RGDeathTest : public TestImage2RG {};
class TestImage2RGBDeathTest : public TestImage2RGB {};
class TestImage2RGBADeathTest : public TestImage2RGBA {};



const std::string TestImage::testImageBmp = getDataDir() + u8"TestImage.bmp";
const std::string TestImage::testImagePng = getDataDir() + u8"TestImage.png";
const std::string TestImage::testImageJpg = getDataDir() + u8"TestImage.jpg";
const std::string TestImage::testImageInvalid = getDataDir() + u8"TestImage.xcf";

}



TEST_F(TestImage2RGBA, GetDimensions)
{
  EXPECT_EQ(2u, Image2RGBA::getDimensionCount());
}



TEST_F(TestImage2RGBA, DefaultConstructor)
{
  Image2RGBA im;

  EXPECT_EQ(Image2RGBA::Size::zero(), im.getSize());
  EXPECT_EQ(std::vector<Image2RGBA::Pixel>(), im.getPixels());
}



TEST_F(TestImage2RGBA, SizeConstructor)
{
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA im(sizeRef);

  EXPECT_EQ(sizeRef, im.getSize());
  EXPECT_EQ(std::vector<Image2RGBA::Pixel>(6u, Image2RGBA::Pixel()), im.getPixels());
}



TEST_F(TestImage2RGBA, PixelConstructor)
{
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::Pixel pixelRef(4u, 5u, 6u, 7u);
  Image2RGBA::PixelCollection pixelsRef(sizeRef.x() * sizeRef.y(), pixelRef);
  Image2RGBA im(sizeRef, pixelRef);

  EXPECT_EQ(sizeRef, im.getSize());
  EXPECT_EQ(pixelsRef, im.getPixels());
}



TEST_F(TestImage2RGBA, PixelsConstructor)
{
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::PixelCollection pixelsRef
  {
    Image2RGBA::Pixel{1u, 2u, 3u, 4u},
    Image2RGBA::Pixel{6u, 7u, 8u, 9u},
    Image2RGBA::Pixel{11u, 12u, 13u, 14u},
    Image2RGBA::Pixel{16u, 17u, 18u, 19u},
    Image2RGBA::Pixel{21u, 22u, 23u, 24u},
    Image2RGBA::Pixel{26u, 27u, 28u, 29u},
  };
  Image2RGBA im(sizeRef, pixelsRef);

  EXPECT_EQ(sizeRef, im.getSize());
  EXPECT_EQ(pixelsRef, im.getPixels());
}



TEST_F(TestImage2RGBADeathTest, PixelsConstructorErrorTooFewPixels)
{
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::PixelCollection pixelsRef
  {
    Image2RGBA::Pixel{1u, 2u, 3u, 4u},
    Image2RGBA::Pixel{6u, 7u, 8u, 9u},
    Image2RGBA::Pixel{11u, 12u, 13u, 14u},
    Image2RGBA::Pixel{16u, 17u, 18u, 19u},
    Image2RGBA::Pixel{21u, 22u, 23u, 24u},
  };
  HOU_EXPECT_PRECONDITION(Image2RGBA im(sizeRef, pixelsRef));
}



TEST_F(TestImage2RGBADeathTest, PixelsConstructorErrorTooManyPixels)
{
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::PixelCollection pixelsRef
  {
    Image2RGBA::Pixel{1u, 2u, 3u, 4u},
    Image2RGBA::Pixel{6u, 7u, 8u, 9u},
    Image2RGBA::Pixel{11u, 12u, 13u, 14u},
    Image2RGBA::Pixel{16u, 17u, 18u, 19u},
    Image2RGBA::Pixel{21u, 22u, 23u, 24u},
    Image2RGBA::Pixel{26u, 27u, 28u, 29u},
    Image2RGBA::Pixel{26u, 27u, 28u, 29u},
  };
  HOU_EXPECT_PRECONDITION(Image2RGBA im(sizeRef, pixelsRef));
}



TEST_F(TestImage2RGBA, Image2RConstructor)
{
  Image2R::Size size(2u, 3u);
  Image2R::PixelCollection pixelsR
  {
    Image2R::Pixel(1u),
    Image2R::Pixel(2u),
    Image2R::Pixel(3u),
    Image2R::Pixel(4u),
    Image2R::Pixel(5u),
    Image2R::Pixel(6u),
  };

  Image2RGBA::PixelCollection pixelsRGBA
  {
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



TEST_F(TestImage2RGBA, Image2RGConstructor)
{
  Image2RG::Size size(2u, 3u);
  Image2RG::PixelCollection pixelsRG
  {
    Image2RG::Pixel(1u, 11u),
    Image2RG::Pixel(2u, 12u),
    Image2RG::Pixel(3u, 13u),
    Image2RG::Pixel(4u, 14u),
    Image2RG::Pixel(5u, 15u),
    Image2RG::Pixel(6u, 16u),
  };

  Image2RGBA::PixelCollection pixelsRGBA
  {
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



TEST_F(TestImage2RGBA, Image2RGBConstructor)
{
  Image2RGB::Size size(2u, 3u);
  Image2RGB::PixelCollection pixelsRGB
  {
    Image2RGB::Pixel(200u, 118u, 93u),
    Image2RGB::Pixel(3u, 12u, 3u),
    Image2RGB::Pixel(5u, 11u, 2u),
    Image2RGB::Pixel(200u, 100u, 0u),
    Image2RGB::Pixel(0u, 21u, 0u),
    Image2RGB::Pixel(100u, 20u, 0u),
  };

  Image2RGBA::PixelCollection pixelsRGBA
  {
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



TEST_F(TestImage2RGBA, Image1RGBAConstructor)
{
  Image1RGB::Size size(3u);
  Image1RGBA::PixelCollection pixelsRGBA
  {
    Image2RGBA::Pixel(200u, 118u, 93u, 255u),
    Image2RGBA::Pixel(3u, 12u, 3u, 255u),
    Image2RGBA::Pixel(5u, 11u, 2u, 255u),
  };
  Image1RGBA image1RGBA(size, pixelsRGBA);
  Image2RGBA image2RGBA(image1RGBA);
  EXPECT_EQ(Vec2u(size.x(), 1u), image2RGBA.getSize());
  EXPECT_EQ(pixelsRGBA, image2RGBA.getPixels());
}



TEST_F(TestImage2RGBA, GetPixelConst)
{
  Image2RGBA::Pixel px0(1u, 2u, 3u, 4u);
  Image2RGBA::Pixel px1(6u, 7u, 8u, 9u);
  Image2RGBA::Pixel px2(11u, 12u, 13u, 14u);
  Image2RGBA::Pixel px3(16u, 17u, 18u, 19u);
  Image2RGBA::Pixel px4(21u, 22u, 23u, 24u);
  Image2RGBA::Pixel px5(26u, 27u, 28u, 29u);
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::PixelCollection pixelsRef{px0, px1, px2, px3, px4, px5};
  const Image2RGBA im(sizeRef, pixelsRef);

  EXPECT_EQ(px0, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
  EXPECT_EQ(px1, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
  EXPECT_EQ(px2, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
  EXPECT_EQ(px3, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
  EXPECT_EQ(px4, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
  EXPECT_EQ(px5, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
}



TEST_F(TestImage2RGBADeathTest, GetPixelConstErrorOutOfRange)
{
  Image2RGBA::Size sizeRef(2u, 3u);
  const Image2RGBA im(sizeRef);

  HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), 0u)));
  HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(0u, sizeRef.y())));
  HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), sizeRef.y())));
}



TEST_F(TestImage2RGBA, GetPixel)
{
  Image2RGBA::Pixel px0(1u, 2u, 3u, 4u);
  Image2RGBA::Pixel px1(6u, 7u, 8u, 9u);
  Image2RGBA::Pixel px2(11u, 12u, 13u, 14u);
  Image2RGBA::Pixel px3(16u, 17u, 18u, 19u);
  Image2RGBA::Pixel px4(21u, 22u, 23u, 24u);
  Image2RGBA::Pixel px5(26u, 27u, 28u, 29u);
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::PixelCollection pixelsRef{px0, px1, px2, px3, px4, px5};
  Image2RGBA im(sizeRef, pixelsRef);

  EXPECT_EQ(px0, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
  EXPECT_EQ(px1, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
  EXPECT_EQ(px2, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
  EXPECT_EQ(px3, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
  EXPECT_EQ(px4, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
  EXPECT_EQ(px5, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));

  im.getPixel(Image2RGBA::Coordinates(0u, 0u)) = px5;
  im.getPixel(Image2RGBA::Coordinates(1u, 0u)) = px4;
  im.getPixel(Image2RGBA::Coordinates(0u, 1u)) = px3;
  im.getPixel(Image2RGBA::Coordinates(1u, 1u)) = px2;
  im.getPixel(Image2RGBA::Coordinates(0u, 2u)) = px1;
  im.getPixel(Image2RGBA::Coordinates(1u, 2u)) = px0;
  EXPECT_EQ(px5, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
  EXPECT_EQ(px4, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
  EXPECT_EQ(px3, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
  EXPECT_EQ(px2, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
  EXPECT_EQ(px1, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
  EXPECT_EQ(px0, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
}



TEST_F(TestImage2RGBADeathTest, GetPixelErrorOutOfRange)
{
  Image2RGBA::Pixel px;
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA im(sizeRef);

  HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), 0u)) = px);
  HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(0u, sizeRef.y())) = px);
  HOU_EXPECT_PRECONDITION(im.getPixel(Image2RGBA::Coordinates(sizeRef.x(), sizeRef.y())) = px);
}



TEST_F(TestImage2RGBA, Clear)
{
  Image2RGBA::Pixel px0(1u, 2u, 3u, 4u);
  Image2RGBA::Pixel px1(6u, 7u, 8u, 9u);
  Image2RGBA::Pixel px2(11u, 12u, 13u, 14u);
  Image2RGBA::Pixel px3(16u, 17u, 18u, 19u);
  Image2RGBA::Pixel px4(21u, 22u, 23u, 24u);
  Image2RGBA::Pixel px5(26u, 27u, 28u, 29u);
  Image2RGBA::Pixel pxRef(31u, 32u, 33u, 34u);
  Image2RGBA::Size sizeRef(2u, 3u);
  Image2RGBA::PixelCollection pixelsRef{px0, px1, px2, px3, px4, px5};
  Image2RGBA im(sizeRef, pixelsRef);
  im.clear(pxRef);

  EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(0u, 0u)));
  EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(1u, 0u)));
  EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(0u, 1u)));
  EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(1u, 1u)));
  EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(0u, 2u)));
  EXPECT_EQ(pxRef, im.getPixel(Image2RGBA::Coordinates(1u, 2u)));
}



TEST_F(TestImage2RGBA, Comparison)
{
  Image2RGBA im0(Image2RGBA::Size(2u, 3u), Image2RGBA::Pixel(1u, 2u, 3u, 4u));
  Image2RGBA im1(im0);
  Image2RGBA im2(Image2RGBA::Size(2u, 5u), Image2RGBA::Pixel(1u, 2u, 3u, 4u));
  Image2RGBA im3(Image2RGBA::Size(2u, 3u), Image2RGBA::Pixel(8u, 2u, 3u, 4u));

  EXPECT_TRUE(im0 == im1);
  EXPECT_FALSE(im0 == im2);
  EXPECT_FALSE(im0 == im3);

  EXPECT_FALSE(im0 != im1);
  EXPECT_TRUE(im0 != im2);
  EXPECT_TRUE(im0 != im3);
}



TEST_F(TestImage2RGBA, OutputStreamOperator)
{
  Image2RGBA im(Image2RGBA::Size(2u, 3u)
    , std::vector<Image2RGBA::Pixel>
      { Image2RGBA::Pixel{1u, 2u, 3u, 4u}
      , Image2RGBA::Pixel{6u, 7u, 8u, 9u}
      , Image2RGBA::Pixel{11u, 12u, 13u, 14u}
      , Image2RGBA::Pixel{16u, 17u, 18u, 19u}
      , Image2RGBA::Pixel{21u, 22u, 23u, 24u}
      , Image2RGBA::Pixel{26u, 27u, 28u, 29u}});
  const char* outRef
    = "{Size = (2, 3), Pixels = {"
    "{R = 1, G = 2, B = 3, A = 4}, "
    "{R = 6, G = 7, B = 8, A = 9}, "
    "{R = 11, G = 12, B = 13, A = 14}, "
    "{R = 16, G = 17, B = 18, A = 19}, "
    "{R = 21, G = 22, B = 23, A = 24}, "
    "{R = 26, G = 27, B = 28, A = 29}}}";

  HOU_EXPECT_OUTPUT(outRef, im);
}



TEST_F(TestImage2RGBA, LoadBmp)
{
  // Alpha channel in Bmp not supported.
  Image2RGBA imRef(Vec2u(3u, 2u), std::vector<Image2RGBA::Pixel>
  {
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



TEST_F(TestImage2RGBADeathTest, LoadBmpError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RGBA>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImage2RGBA, LoadPng)
{
  Image2RGBA imRef(Vec2u(3u, 2u), std::vector<Image2RGBA::Pixel>
    {
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



TEST_F(TestImage2RGBADeathTest, LoadPngError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RGBA>(testImageJpg)
    , std::runtime_error
    , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImage2RGBA, LoadJpg)
{
  Image2RGBA imRef(Vec2u(3u, 2u), std::vector<Image2RGBA::Pixel>
    {
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



TEST_F(TestImage2RGBADeathTest, LoadJpgError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RGBA>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}



TEST_F(TestImage2RGBA, SaveBmp)
{
  const std::string savePath = getOutputDir() + "savedBmp.bmp";
  removeDir(savePath);
  Image2RGBA imRef = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
  bmpWriteFile(savePath, imRef);
  Image2RGBA im = bmpReadFile<PixelFormat::RGBA>(savePath);
  EXPECT_EQ(imRef, im);
  EXPECT_TRUE(removeDir(savePath));
}



TEST_F(TestImage2RGBADeathTest, SaveBmpFailure)
{
  const std::string savePath = getOutputDir() + "savedBmp.bmp";
  removeDir(savePath);
  Image2RGBA imRef = bmpReadFile<PixelFormat::RGBA>(testImageBmp);
  bmpWriteFile(savePath, imRef);
  HOU_EXPECT_ERROR(bmpWriteFile<PixelFormat::RGBA>(savePath, imRef)
    , std::runtime_error, formatString(getText(SysError::ImageBmpWrite)
    , savePath.c_str()));
  EXPECT_TRUE(removeDir(savePath));
}



TEST_F(TestImage2RGB, LoadBmp)
{
  // Alpha channel in Bmp not supported.
  Image2RGB imRef(Vec2u(3u, 2u), std::vector<Image2RGB::Pixel>
  {
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



TEST_F(TestImage2RGBDeathTest, LoadBmpError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RGB>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImage2RGB, LoadPng)
{
  Image2RGB imRef(Vec2u(3u, 2u), std::vector<Image2RGB::Pixel>
    {
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



TEST_F(TestImage2RGBDeathTest, LoadPngError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RGB>(testImageJpg)
    , std::runtime_error
    , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImage2RGB, LoadJpg)
{
  Image2RGB imRef(Vec2u(3u, 2u), std::vector<Image2RGB::Pixel>
    {
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



TEST_F(TestImage2RGBDeathTest, LoadJpgError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RGB>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}



TEST_F(TestImage2RG, LoadBmp)
{
  // Alpha channel in Bmp not supported.
  Image2RG imRef(Vec2u(3u, 2u), std::vector<Image2RG::Pixel>
  {
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



TEST_F(TestImage2RGDeathTest, LoadBmpError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::RG>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImage2RG, LoadPng)
{
  Image2RG imRef(Vec2u(3u, 2u), std::vector<Image2RG::Pixel>
    {
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



TEST_F(TestImage2RGDeathTest, LoadPngError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::RG>(testImageJpg)
    , std::runtime_error
    , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}



TEST_F(TestImage2RG, LoadJpg)
{
  Image2RG imRef(Vec2u(3u, 2u), std::vector<Image2RG::Pixel>
    {
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



TEST_F(TestImage2RGDeathTest, LoadJpgError)
{
  HOU_EXPECT_ERROR(jpgReadFile<PixelFormat::RG>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageJpgRead), testImagePng.c_str()));
}



TEST_F(TestImage2R, LoadBmp)
{
  // Alpha channel in Bmp not supported.
  Image2R imRef(Vec2u(3u, 2u), std::vector<Image2R::Pixel>
  {
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



TEST_F(TestImage2RDeathTest, LoadBmpError)
{
  HOU_EXPECT_ERROR(bmpReadFile<PixelFormat::R>(testImagePng)
    , std::runtime_error
    , formatString(getText(SysError::ImageBmpRead), testImagePng.c_str()));
}



TEST_F(TestImage2R, LoadPng)
{
  Image2R imRef(Vec2u(3u, 2u), std::vector<Image2R::Pixel>
    {
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



TEST_F(TestImage2RDeathTest, LoadPngError)
{
  HOU_EXPECT_ERROR(pngReadFile<PixelFormat::R>(testImageJpg)
    , std::runtime_error
    , formatString(getText(SysError::ImagePngRead), testImageJpg.c_str()));
}

