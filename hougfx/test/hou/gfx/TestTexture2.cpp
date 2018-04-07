// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"
#include "hou/gfx/TestData.hpp"

#include "hou/gfx/Texture2.hpp"

#include "hou/gl/GlError.hpp"

#include "hou/sys/Image.hpp"

using namespace hou;



namespace
{

class OldTestTexture2 : public TestGfxBase {};

class OldTestTexture2DeathTest : public OldTestTexture2 {};

const std::string testImagePng = getDataDir() + u8"TestImage.png";

}



TEST_F(OldTestTexture2, CreationWithSize)
{
  Vec2u size(3u, 4u);
  Texture2 tx(size, TextureFormat::RG);
  Image2RGBA imRef(size, Image2RGBA::Pixel(0u, 0u, 0u, 255u));

  EXPECT_EQ(size, tx.getSize());
  EXPECT_EQ(TextureFormat::RG, tx.getFormat());
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  EXPECT_EQ(imRef, tx.toImage());
}



TEST_F(OldTestTexture2, CreationWithAreaGreaterThanMaxTextureSize)
{
  Vec2u size(RenderContext::getMaxTextureSize() / 2u, 3u);
  ASSERT_GT(size.x() * size.y(), RenderContext::getMaxTextureSize());
  Texture2 tx(size, TextureFormat::RG);
  Image2RGBA imRef(size, Image2RGBA::Pixel(0u, 0u, 0u, 255u));

  EXPECT_EQ(size, tx.getSize());
  EXPECT_EQ(TextureFormat::RG, tx.getFormat());
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  EXPECT_EQ(imRef, tx.toImage());
}



TEST_F(OldTestTexture2, CreationWithSizeDefaultFormat)
{
  Vec2u size(3u, 4u);
  Texture2 tx(size);
  Image2RGBA imRef(size);

  EXPECT_EQ(size, tx.getSize());
  EXPECT_EQ(TextureFormat::RGBA, tx.getFormat());
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  EXPECT_EQ(imRef, tx.toImage());
}



TEST_F(OldTestTexture2DeathTest, CreationWithSizeNull)
{
  HOU_EXPECT_PRECONDITION(Texture2 tx(Vec2u(0u, 0u)));
  HOU_EXPECT_PRECONDITION(Texture2 tx(Vec2u(1u, 0u)));
  HOU_EXPECT_PRECONDITION(Texture2 tx(Vec2u(0u, 1u)));
}



TEST_F(OldTestTexture2DeathTest, CreationWithSizeTooLarge)
{
  const uint size = RenderContext::getMaxTextureSize() + 1;
  HOU_EXPECT_PRECONDITION(Texture2 tx(Vec2u(size, size)));
  HOU_EXPECT_PRECONDITION(Texture2 tx(Vec2u(1u, size)));
  HOU_EXPECT_PRECONDITION(Texture2 tx(Vec2u(size, 1u)));
}



TEST_F(OldTestTexture2, CreationWithImage)
{
  Image2RG im = pngReadFile<PixelFormat::RG>(testImagePng);
  Texture2 tx(im, TextureFormat::RG);

  EXPECT_EQ(im.getSize(), tx.getSize());
  EXPECT_EQ(TextureFormat::RG, tx.getFormat());
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  EXPECT_EQ(im, Image2RG(tx.toImage()));
}



TEST_F(OldTestTexture2, CreationWithImageDefaultFormat)
{
  Image2RGBA im = pngReadFile<PixelFormat::RGBA>(testImagePng);
  Texture2 tx(im);

  EXPECT_EQ(im.getSize(), tx.getSize());
  EXPECT_EQ(TextureFormat::RGBA, tx.getFormat());
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  EXPECT_EQ(im, tx.toImage());
}



TEST_F(OldTestTexture2, CreationWithSingleChannelImage)
{
  Image2RGBA im = pngReadFile<PixelFormat::RGBA>(testImagePng);
  Texture2 tx(im);

  EXPECT_EQ(im.getSize(), tx.getSize());
  EXPECT_EQ(TextureFormat::RGBA, tx.getFormat());
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  EXPECT_EQ(im, tx.toImage());
}



TEST_F(OldTestTexture2DeathTest, CreationWithImageNullSize)
{
  Image2RGBA im;
  HOU_EXPECT_PRECONDITION(Texture2 tx(im));
}



TEST_F(OldTestTexture2DeathTest, CreationWithImageSizeTooLarge)
{
  const uint size = RenderContext::getMaxTextureSize() + 1;
  Image2RGBA im(Vec2u(size, 1u));
  HOU_EXPECT_PRECONDITION(Texture2 tx(im));
}



TEST_F(OldTestTexture2, MoveConstructor)
{
  Image2RGB im = pngReadFile<PixelFormat::RGB>(testImagePng);
  Texture2 txDummy(im, TextureFormat::RGB);
  txDummy.setFilter(TextureFilter::Bilinear);
  txDummy.setChannelMapping(TextureChannelMapping::Luminosity);
  txDummy.setWrapModeX(TextureWrapMode::ClampToEdge);
  txDummy.setWrapModeY(TextureWrapMode::MirroredRepeat);

  Texture2 tx(std::move(txDummy));

  EXPECT_EQ(im.getSize(), tx.getSize());
  EXPECT_EQ(TextureFormat::RGB, tx.getFormat());
  EXPECT_EQ(TextureFilter::Bilinear, tx.getFilter());
  EXPECT_EQ(TextureChannelMapping::Luminosity, tx.getChannelMapping());
  EXPECT_EQ(TextureWrapMode::ClampToEdge, tx.getWrapModeX());
  EXPECT_EQ(TextureWrapMode::MirroredRepeat, tx.getWrapModeY());
  EXPECT_EQ(Image2RGBA(im), tx.toImage());
}



// TEST_F(OldTestTexture2, FormatConsistency)
// {
//   Image imR = pngReadFile(testImagePng, ImageFormat::R);
//   Image imRG = pngReadFile(testImagePng, ImageFormat::RG);
//   Image imRGB = pngReadFile(testImagePng, ImageFormat::RGB);
//   Image imRGBA = pngReadFile(testImagePng, ImageFormat::RGBA);
// 
//   Texture2 txR2R(imR, TextureFormat::R);
//   Texture2 txR2RG(imR, TextureFormat::RG);
//   Texture2 txR2RGB(imR, TextureFormat::RGB);
//   Texture2 txR2RGBA(imR, TextureFormat::RGBA);
// 
//   Texture2 txRG2R(imRG, TextureFormat::R);
//   Texture2 txRG2RG(imRG, TextureFormat::RG);
//   Texture2 txRG2RGB(imRG, TextureFormat::RGB);
//   Texture2 txRG2RGBA(imRG, TextureFormat::RGBA);
// 
//   Texture2 txRGB2R(imRGB, TextureFormat::R);
//   Texture2 txRGB2RG(imRGB, TextureFormat::RG);
//   Texture2 txRGB2RGB(imRGB, TextureFormat::RGB);
//   Texture2 txRGB2RGBA(imRGB, TextureFormat::RGBA);
// 
//   Texture2 txRGBA2R(imRGBA, TextureFormat::R);
//   Texture2 txRGBA2RG(imRGBA, TextureFormat::RG);
//   Texture2 txRGBA2RGB(imRGBA, TextureFormat::RGB);
//   Texture2 txRGBA2RGBA(imRGBA, TextureFormat::RGBA);
// 
// 
//   EXPECT_EQ(imR, txR2R.toImage(ImageFormat::R));
//   EXPECT_EQ(imR, txR2RG.toImage(ImageFormat::R));
//   EXPECT_EQ(imR, txR2RGB.toImage(ImageFormat::R));
//   EXPECT_EQ(imR, txR2RGBA.toImage(ImageFormat::R));
// 
//   EXPECT_EQ(imR, txRG2R.toImage(ImageFormat::R));
//   EXPECT_EQ(imR, txRG2RG.toImage(ImageFormat::R));
//   EXPECT_EQ(imR, txRG2RGB.toImage(ImageFormat::R));
//   EXPECT_EQ(imR, txRG2RGBA.toImage(ImageFormat::R));
// 
//   // EXPECT_EQ(imR, txRGB2R.toImage(ImageFormat::R));
//   // EXPECT_EQ(imR, txRGB2RG.toImage(ImageFormat::R));
//   // EXPECT_EQ(imR, txRGB2RGB.toImage(ImageFormat::R));
//   // EXPECT_EQ(imR, txRGB2RGBA.toImage(ImageFormat::R));
// 
//   // EXPECT_EQ(imR, txRGBA2R.toImage(ImageFormat::R));
//   // EXPECT_EQ(imR, txRGBA2RG.toImage(ImageFormat::R));
//   // EXPECT_EQ(imR, txRGBA2RGB.toImage(ImageFormat::R));
//   // EXPECT_EQ(imR, txRGBA2RGBA.toImage(ImageFormat::R));
// 
// 
//   // EXPECT_EQ(imRG, txR2R.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txR2RG.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txR2RGB.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txR2RGBA.toImage(ImageFormat::RG));
// 
//   // EXPECT_EQ(imRG, txRG2R.toImage(ImageFormat::RG));
//   EXPECT_EQ(imRG, txRG2RG.toImage(ImageFormat::RG));
//   EXPECT_EQ(imRG, txRG2RGB.toImage(ImageFormat::RG));
//   EXPECT_EQ(imRG, txRG2RGBA.toImage(ImageFormat::RG));
// 
//   // EXPECT_EQ(imRG, txRGB2R.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txRGB2RG.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txRGB2RGB.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txRGB2RGBA.toImage(ImageFormat::RG));
// 
//   // EXPECT_EQ(imRG, txRGBA2R.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txRGBA2RG.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txRGBA2RGB.toImage(ImageFormat::RG));
//   // EXPECT_EQ(imRG, txRGBA2RGBA.toImage(ImageFormat::RG));
// 
// 
//   // EXPECT_EQ(imRGB, txR2R.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txR2RG.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txR2RGB.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txR2RGBA.toImage(ImageFormat::RGB));
// 
//   // EXPECT_EQ(imRGB, txRG2R.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txRG2RG.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txRG2RGB.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txRG2RGBA.toImage(ImageFormat::RGB));
// 
//   // EXPECT_EQ(imRGB, txRGB2R.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txRGB2RG.toImage(ImageFormat::RGB));
//   EXPECT_EQ(imRGB, txRGB2RGB.toImage(ImageFormat::RGB));
//   EXPECT_EQ(imRGB, txRGB2RGBA.toImage(ImageFormat::RGB));
// 
//   // EXPECT_EQ(imRGB, txRGBA2R.toImage(ImageFormat::RGB));
//   // EXPECT_EQ(imRGB, txRGBA2RG.toImage(ImageFormat::RGB));
//   EXPECT_EQ(imRGB, txRGBA2RGB.toImage(ImageFormat::RGB));
//   EXPECT_EQ(imRGB, txRGBA2RGBA.toImage(ImageFormat::RGB));
// 
// 
//   // EXPECT_EQ(imRGBA, txR2R.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txR2RG.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txR2RGB.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txR2RGBA.toImage(ImageFormat::RGBA));
// 
//   // EXPECT_EQ(imRGBA, txRG2R.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txRG2RG.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txRG2RGB.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txRG2RGBA.toImage(ImageFormat::RGBA));
// 
//   // EXPECT_EQ(imRGBA, txRGB2R.toImage(ImageFormat::RGBA));
//   //EXPECT_EQ(imRGBA, txRGB2RG.toImage(ImageFormat::RGBA));
//   //EXPECT_EQ(imRGBA, txRGB2RGB.toImage(ImageFormat::RGBA));
//   //EXPECT_EQ(imRGBA, txRGB2RGBA.toImage(ImageFormat::RGBA));
// 
//   // EXPECT_EQ(imRGBA, txRGBA2R.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txRGBA2RG.toImage(ImageFormat::RGBA));
//   // EXPECT_EQ(imRGBA, txRGBA2RGB.toImage(ImageFormat::RGBA));
//   EXPECT_EQ(imRGBA, txRGBA2RGBA.toImage(ImageFormat::RGBA));
// }



TEST_F(OldTestTexture2, Binding)
{
  Texture2 tx(pngReadFile<PixelFormat::RGBA>(testImagePng));

  EXPECT_FALSE(tx.isBound(0u));
  EXPECT_FALSE(tx.isBound(1u));

  Texture2::bind(tx, 1u);
  EXPECT_FALSE(tx.isBound(0u));
  EXPECT_TRUE(tx.isBound(1u));
  EXPECT_FALSE(tx.isBound(RenderContext::getTextureUnitCount() - 1u));

  Texture2::bind(tx, 0u);
  EXPECT_TRUE(tx.isBound(0u));
  EXPECT_TRUE(tx.isBound(1u));
  EXPECT_FALSE(tx.isBound(RenderContext::getTextureUnitCount() - 1u));

  Texture2::bind(tx, RenderContext::getTextureUnitCount() - 1u);
  EXPECT_TRUE(tx.isBound(0u));
  EXPECT_TRUE(tx.isBound(1u));
  EXPECT_TRUE(tx.isBound(RenderContext::getTextureUnitCount() - 1u));
}



TEST_F(OldTestTexture2DeathTest, BindingErrorInvalidTextureUnit)
{
  Texture2 tx(pngReadFile<PixelFormat::RGBA>(testImagePng));
  HOU_EXPECT_PRECONDITION(Texture2::bind(tx, RenderContext::getTextureUnitCount()));
}



TEST_F(OldTestTexture2, Filter)
{
  Texture2 tx(pngReadFile<PixelFormat::RGBA>(testImagePng));

  tx.setFilter(TextureFilter::Bilinear);
  EXPECT_EQ(TextureFilter::Bilinear, tx.getFilter());

  tx.setFilter(TextureFilter::Nearest);
  EXPECT_EQ(TextureFilter::Nearest, tx.getFilter());
}



TEST_F(OldTestTexture2, ChannelMapping)
{
  Texture2 tx(pngReadFile<PixelFormat::RGBA>(testImagePng));

  EXPECT_EQ(TextureChannelMapping::Default, tx.getChannelMapping());

  TextureChannelMapping tcmRef(TextureChannel::A, TextureChannel::R
    , TextureChannel::Zero, TextureChannel::One);
  tx.setChannelMapping(tcmRef);
  EXPECT_EQ(tcmRef, tx.getChannelMapping());
}



TEST_F(OldTestTexture2, WrapModeX)
{
  Texture2 tx(pngReadFile<PixelFormat::RGBA>(testImagePng));
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeX());
  tx.setWrapModeX(TextureWrapMode::ClampToEdge);
  EXPECT_EQ(TextureWrapMode::ClampToEdge, tx.getWrapModeX());
}



TEST_F(OldTestTexture2, WrapModeY)
{
  Texture2 tx(pngReadFile<PixelFormat::RGBA>(testImagePng));
  EXPECT_EQ(TextureWrapMode::Repeat, tx.getWrapModeY());
  tx.setWrapModeY(TextureWrapMode::ClampToEdge);
  EXPECT_EQ(TextureWrapMode::ClampToEdge, tx.getWrapModeY());
}

