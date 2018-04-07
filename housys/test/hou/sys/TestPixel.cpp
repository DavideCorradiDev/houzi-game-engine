// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/sys/Pixel.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestPixel : public Test {};
class TestPixelR : public TestPixel {};
class TestPixelRG : public TestPixel {};
class TestPixelRGB : public TestPixel {};
class TestPixelRGBA : public TestPixel {};

}



TEST_F(TestPixelR, GetFormat)
{
  EXPECT_EQ(PixelFormat::R, PixelR::getFormat());
}



TEST_F(TestPixelR, GetByteCount)
{
  EXPECT_EQ(1u, PixelR::getByteCount());
}



TEST_F(TestPixelR, DefaultConstructor)
{
  PixelR pixel;
  EXPECT_EQ(0u, pixel.getR());
}



TEST_F(TestPixelR, ValueConstructor)
{
  PixelR pixel(1u);
  EXPECT_EQ(1u, pixel.getR());
}



TEST_F(TestPixelR, PixelRGConstructor)
{
  PixelRG pxRG(1u, 2u);
  PixelR pxR(pxRG);
  EXPECT_EQ(1u, pxR.getR());
}



TEST_F(TestPixelR, PixelRGBConstructor)
{
  PixelRGB pxRGB(200u, 118u, 93u);
  PixelR pxR(pxRGB);
  EXPECT_EQ(139u, pxR.getR());
}



TEST_F(TestPixelR, PixelRGBAConstructor)
{
  PixelRGBA pxRGBA(200u, 118u, 93u, 7u);
  PixelR pxR(pxRGBA);
  EXPECT_EQ(139u, pxR.getR());
}



TEST_F(TestPixelR, SetR)
{
  PixelR pixel;
  pixel.setR(1u);
  EXPECT_EQ(1u, pixel.getR());
}



TEST_F(TestPixelR, Set)
{
  PixelR pixel;
  pixel.set(1u);
  EXPECT_EQ(1u, pixel.getR());
}



TEST_F(TestPixelR, Comparison)
{
  PixelR p0(1u);
  PixelR p1(p0);
  PixelR p2(2u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
}



TEST_F(TestPixelR, OutputStreamOperator)
{
  PixelR pixel(1u);
  const char* outputRef = "{R = 1}";
  HOU_EXPECT_OUTPUT(outputRef, pixel);
}



TEST_F(TestPixelRG, GetFormat)
{
  EXPECT_EQ(PixelFormat::RG, PixelRG::getFormat());
}



TEST_F(TestPixelRG, GetByteCount)
{
  EXPECT_EQ(2u, PixelRG::getByteCount());
}



TEST_F(TestPixelRG, DefaultConstructor)
{
  PixelRG pixel;
  EXPECT_EQ(0u, pixel.getR());
  EXPECT_EQ(0u, pixel.getG());
}



TEST_F(TestPixelRG, ValueConstructor)
{
  PixelRG pixel(1u, 2u);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
}



TEST_F(TestPixelRG, PixelRConstructor)
{
  PixelR pxR(1u);
  PixelRG pxRG(pxR);
  EXPECT_EQ(1u, pxRG.getR());
  EXPECT_EQ(255u, pxRG.getG());
}



TEST_F(TestPixelRG, PixelRGBConstructor)
{
  PixelRGB pxRGB(200u, 118u, 93u);
  PixelRG pxRG(pxRGB);
  EXPECT_EQ(139u, pxRG.getR());
  EXPECT_EQ(255u, pxRG.getG());
}



TEST_F(TestPixelRG, PixelRGBAConstructor)
{
  PixelRGBA pxRGBA(200u, 118u, 93u, 7u);
  PixelRG pxRG(pxRGBA);
  EXPECT_EQ(139u, pxRG.getR());
  EXPECT_EQ(7u, pxRG.getG());
}



TEST_F(TestPixelRG, SetR)
{
  PixelRG pixel;
  pixel.setR(1u);
  EXPECT_EQ(1u, pixel.getR());
}



TEST_F(TestPixelRG, SetG)
{
  PixelRG pixel;
  pixel.setG(1u);
  EXPECT_EQ(1u, pixel.getG());
}



TEST_F(TestPixelRG, Set)
{
  PixelRG pixel;
  pixel.set(1u, 2u);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
}



TEST_F(TestPixelRG, Comparison)
{
  PixelRG p0(1u, 2u);
  PixelRG p1(p0);
  PixelRG p2(3u, 2u);
  PixelRG p3(1u, 3u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);
  EXPECT_FALSE(p0 == p3);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
  EXPECT_TRUE(p0 != p3);

}



TEST_F(TestPixelRG, OutputStreamOperator)
{
  PixelRG pixel(1u, 2u);
  const char* outputRef = "{R = 1, G = 2}";
  HOU_EXPECT_OUTPUT(outputRef, pixel);
}



TEST_F(TestPixelRGB, GetFormat)
{
  EXPECT_EQ(PixelFormat::RGB, PixelRGB::getFormat());
}



TEST_F(TestPixelRGB, GetByteCount)
{
  EXPECT_EQ(3u, PixelRGB::getByteCount());
}



TEST_F(TestPixelRGB, DefaultConstructor)
{
  PixelRGB pixel;
  EXPECT_EQ(0u, pixel.getR());
  EXPECT_EQ(0u, pixel.getG());
  EXPECT_EQ(0u, pixel.getB());
}



TEST_F(TestPixelRGB, ValueConstructor)
{
  PixelRGB pixel(1u, 2u, 3u);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
  EXPECT_EQ(3u, pixel.getB());
}



TEST_F(TestPixelRGB, PixelRConstructor)
{
  PixelR pxR(1u);
  PixelRGB pxRGB(pxR);
  EXPECT_EQ(1u, pxRGB.getR());
  EXPECT_EQ(1u, pxRGB.getG());
  EXPECT_EQ(1u, pxRGB.getB());
}



TEST_F(TestPixelRGB, PixelRGConstructor)
{
  PixelRG pxRG(200u, 118u);
  PixelRGB pxRGB(pxRG);
  EXPECT_EQ(200u, pxRGB.getR());
  EXPECT_EQ(200u, pxRGB.getG());
  EXPECT_EQ(200u, pxRGB.getB());
}



TEST_F(TestPixelRGB, PixelRGBAConstructor)
{
  PixelRGBA pxRGBA(200u, 118u, 93u, 7u);
  PixelRGB pxRGB(pxRGBA);
  EXPECT_EQ(200, pxRGB.getR());
  EXPECT_EQ(118u, pxRGB.getG());
  EXPECT_EQ(93u, pxRGB.getB());
}



TEST_F(TestPixelRGB, SetR)
{
  PixelRGB pixel;
  pixel.setR(1u);
  EXPECT_EQ(1u, pixel.getR());
}



TEST_F(TestPixelRGB, SetG)
{
  PixelRGB pixel;
  pixel.setG(1u);
  EXPECT_EQ(1u, pixel.getG());
}



TEST_F(TestPixelRGB, SetB)
{
  PixelRGB pixel;
  pixel.setB(1u);
  EXPECT_EQ(1u, pixel.getB());
}



TEST_F(TestPixelRGB, Set)
{
  PixelRGB pixel;
  pixel.set(1u, 2u, 3u);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
  EXPECT_EQ(3u, pixel.getB());
}



TEST_F(TestPixelRGB, Comparison)
{
  PixelRGB p0(1u, 2u, 3u);
  PixelRGB p1(p0);
  PixelRGB p2(4u, 2u, 3u);
  PixelRGB p3(1u, 4u, 3u);
  PixelRGB p4(1u, 2u, 4u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);
  EXPECT_FALSE(p0 == p3);
  EXPECT_FALSE(p0 == p4);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
  EXPECT_TRUE(p0 != p3);
  EXPECT_TRUE(p0 != p4);
}



TEST_F(TestPixelRGB, OutputStreamOperator)
{
  PixelRGB pixel(1u, 2u, 3u);
  const char* outputRef = "{R = 1, G = 2, B = 3}";
  HOU_EXPECT_OUTPUT(outputRef, pixel);
}



TEST_F(TestPixelRGBA, GetFormat)
{
  EXPECT_EQ(PixelFormat::RGBA, PixelRGBA::getFormat());
}



TEST_F(TestPixelRGBA, GetByteCount)
{
  EXPECT_EQ(4u, PixelRGBA::getByteCount());
}



TEST_F(TestPixelRGBA, DefaultConstructor)
{
  PixelRGBA pixel;
  EXPECT_EQ(0u, pixel.getR());
  EXPECT_EQ(0u, pixel.getG());
  EXPECT_EQ(0u, pixel.getB());
  EXPECT_EQ(0u, pixel.getA());
}



TEST_F(TestPixelRGBA, ValueConstructor)
{
  PixelRGBA pixel(1u, 2u, 3u, 4u);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
  EXPECT_EQ(3u, pixel.getB());
  EXPECT_EQ(4u, pixel.getA());
}



TEST_F(TestPixelRGBA, ColorConstructor)
{
  Color colorRef(1u, 2u, 3u, 4u);
  PixelRGBA pixel(colorRef);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
  EXPECT_EQ(3u, pixel.getB());
  EXPECT_EQ(4u, pixel.getA());
  EXPECT_EQ(colorRef, pixel.getColor());
}



TEST_F(TestPixelRGBA, PixelRConstructor)
{
  PixelR pxR(1u);
  PixelRGBA pxRGBA(pxR);
  EXPECT_EQ(1u, pxRGBA.getR());
  EXPECT_EQ(1u, pxRGBA.getG());
  EXPECT_EQ(1u, pxRGBA.getB());
  EXPECT_EQ(255u, pxRGBA.getA());
}



TEST_F(TestPixelRGBA, PixelRGConstructor)
{
  PixelRG pxRG(200u, 118u);
  PixelRGBA pxRGBA(pxRG);
  EXPECT_EQ(200u, pxRGBA.getR());
  EXPECT_EQ(200u, pxRGBA.getG());
  EXPECT_EQ(200u, pxRGBA.getB());
  EXPECT_EQ(118u, pxRGBA.getA());
}



TEST_F(TestPixelRGBA, PixelRGBConstructor)
{
  PixelRGB pxRGB(200u, 118u, 93u);
  PixelRGBA pxRGBA(pxRGB);
  EXPECT_EQ(200, pxRGBA.getR());
  EXPECT_EQ(118u, pxRGBA.getG());
  EXPECT_EQ(93u, pxRGBA.getB());
  EXPECT_EQ(255u, pxRGBA.getA());
}



TEST_F(TestPixelRGBA, SetR)
{
  PixelRGBA pixel;
  pixel.setR(1u);
  EXPECT_EQ(1u, pixel.getR());
}



TEST_F(TestPixelRGBA, SetG)
{
  PixelRGBA pixel;
  pixel.setG(1u);
  EXPECT_EQ(1u, pixel.getG());
}



TEST_F(TestPixelRGBA, SetB)
{
  PixelRGBA pixel;
  pixel.setB(1u);
  EXPECT_EQ(1u, pixel.getB());
}



TEST_F(TestPixelRGBA, SetA)
{
  PixelRGBA pixel;
  pixel.setA(1u);
  EXPECT_EQ(1u, pixel.getA());
}



TEST_F(TestPixelRGBA, Set)
{
  PixelRGBA pixel;
  pixel.set(1u, 2u, 3u, 4u);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
  EXPECT_EQ(3u, pixel.getB());
  EXPECT_EQ(4u, pixel.getA());
}



TEST_F(TestPixelRGBA, SetColor)
{
  Color colorRef(1u, 2u, 3u, 4u);
  PixelRGBA pixel;
  pixel.setColor(colorRef);
  EXPECT_EQ(1u, pixel.getR());
  EXPECT_EQ(2u, pixel.getG());
  EXPECT_EQ(3u, pixel.getB());
  EXPECT_EQ(4u, pixel.getA());
  EXPECT_EQ(colorRef, pixel.getColor());
}



TEST_F(TestPixelRGBA, Comparison)
{
  PixelRGBA p0(1u, 2u, 3u, 4u);
  PixelRGBA p1(p0);
  PixelRGBA p2(5u, 2u, 3u, 4u);
  PixelRGBA p3(1u, 5u, 3u, 4u);
  PixelRGBA p4(1u, 2u, 5u, 4u);
  PixelRGBA p5(1u, 2u, 3u, 5u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);
  EXPECT_FALSE(p0 == p3);
  EXPECT_FALSE(p0 == p4);
  EXPECT_FALSE(p0 == p5);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
  EXPECT_TRUE(p0 != p3);
  EXPECT_TRUE(p0 != p4);
  EXPECT_TRUE(p0 != p5);
}



TEST_F(TestPixelRGBA, OutputStreamOperator)
{
  PixelRGBA pixel(1u, 2u, 3u, 4u);
  const char* outputRef = "{R = 1, G = 2, B = 3, A = 4}";
  HOU_EXPECT_OUTPUT(outputRef, pixel);
}

