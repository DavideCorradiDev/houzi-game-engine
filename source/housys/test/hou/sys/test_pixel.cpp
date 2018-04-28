// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/pixel.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestPixelFormat : public Test
{};

class TestPixelFormatDeathTest : public TestPixelFormat
{};

class TestPixel : public Test
{};

template <typename pixel_t>
class TestPixelCommon : public TestPixel
{};

using PixelTypesCommon = Types<pixelr, pixelrg, pixelrgb, pixelrgba>;

template <typename pixel_t>
class TestPixelRedChannel : public TestPixel
{};

using PixelTypesRedChannel = Types<pixelr, pixelrg, pixelrgb, pixelrgba>;

template <typename pixel_t>
class TestPixelGreenChannel : public TestPixel
{};

using PixelTypesGreenChannel = Types<pixelrg, pixelrgb, pixelrgba>;

template <typename pixel_t>
class TestPixelBlueChannel : public TestPixel
{};

using PixelTypesBlueChannel = Types<pixelrgb, pixelrgba>;

template <typename pixel_t>
class TestPixelAlphaChannel : public TestPixel
{};

using PixelTypesAlphaChannel = Types<pixelrgba>;

class TestPixelR : public TestPixel
{};

class TestPixelRG : public TestPixel
{};

class TestPixelRGB : public TestPixel
{};

class TestPixelRGBA : public TestPixel
{};

}  // namespace



TYPED_TEST_CASE(TestPixelCommon, PixelTypesCommon);
TYPED_TEST_CASE(TestPixelRedChannel, PixelTypesRedChannel);
TYPED_TEST_CASE(TestPixelGreenChannel, PixelTypesGreenChannel);
TYPED_TEST_CASE(TestPixelBlueChannel, PixelTypesBlueChannel);
TYPED_TEST_CASE(TestPixelAlphaChannel, PixelTypesAlphaChannel);



TEST_F(TestPixelFormat, GetPixelFormatByteCount)
{
  EXPECT_EQ(1u, get_pixel_format_byte_count(pixel_format::r));
  EXPECT_EQ(2u, get_pixel_format_byte_count(pixel_format::rg));
  EXPECT_EQ(3u, get_pixel_format_byte_count(pixel_format::rgb));
  EXPECT_EQ(4u, get_pixel_format_byte_count(pixel_format::rgba));
}



TEST_F(TestPixelFormatDeathTest, GetPixelFormatByteCountErrorInvalidEnum)
{
  int enumVal = 5;
  HOU_EXPECT_ERROR(get_pixel_format_byte_count(pixel_format(enumVal)),
    std::logic_error, format_string(get_text(cor_error::invalid_enum), enumVal));
}



TYPED_TEST(TestPixelCommon, GetByteCount)
{
  EXPECT_EQ(
    get_pixel_format_byte_count(TypeParam::get_format()), TypeParam::get_byte_count());
}



TYPED_TEST(TestPixelCommon, NoPadding)
{
  EXPECT_EQ(TypeParam::get_byte_count(), sizeof(TypeParam));
}



TYPED_TEST(TestPixelRedChannel, SetR)
{
  TypeParam ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_r());
  ph_pixel.set_r(1u);
  EXPECT_EQ(1u, ph_pixel.get_r());
}



TYPED_TEST(TestPixelGreenChannel, SetG)
{
  TypeParam ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_g());
  ph_pixel.set_g(1u);
  EXPECT_EQ(1u, ph_pixel.get_g());
}



TYPED_TEST(TestPixelBlueChannel, SetB)
{
  TypeParam ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_b());
  ph_pixel.set_b(1u);
  EXPECT_EQ(1u, ph_pixel.get_b());
}



TYPED_TEST(TestPixelAlphaChannel, SetA)
{
  TypeParam ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_a());
  ph_pixel.set_a(1u);
  EXPECT_EQ(1u, ph_pixel.get_a());
}



TEST_F(TestPixelR, GetFormat)
{
  EXPECT_EQ(pixel_format::r, pixelr::get_format());
}



TEST_F(TestPixelR, DefaultConstructor)
{
  pixelr ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_r());
}



TEST_F(TestPixelR, ValueConstructor)
{
  pixelr ph_pixel(1u);
  EXPECT_EQ(1u, ph_pixel.get_r());
}



TEST_F(TestPixelR, PixelRGConstructor)
{
  pixelrg pxRG(1u, 2u);
  pixelr pxR(pxRG);
  EXPECT_EQ(1u, pxR.get_r());
}



TEST_F(TestPixelR, PixelRGBConstructor)
{
  pixelrgb pxRGB(200u, 118u, 93u);
  pixelr pxR(pxRGB);
  EXPECT_EQ(139u, pxR.get_r());
}



TEST_F(TestPixelR, PixelRGBAConstructor)
{
  pixelrgba pxRGBA(200u, 118u, 93u, 7u);
  pixelr pxR(pxRGBA);
  EXPECT_EQ(139u, pxR.get_r());
}



TEST_F(TestPixelR, Set)
{
  pixelr ph_pixel;
  ph_pixel.set(1u);
  EXPECT_EQ(1u, ph_pixel.get_r());
}



TEST_F(TestPixelR, Comparison)
{
  pixelr p0(1u);
  pixelr p1(p0);
  pixelr p2(2u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
}



TEST_F(TestPixelR, OutputStreamOperator)
{
  pixelr ph_pixel(1u);
  const char* outputRef = "{r = 1}";
  HOU_EXPECT_OUTPUT(outputRef, ph_pixel);
}



TEST_F(TestPixelRG, GetFormat)
{
  EXPECT_EQ(pixel_format::rg, pixelrg::get_format());
}



TEST_F(TestPixelRG, DefaultConstructor)
{
  pixelrg ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_r());
  EXPECT_EQ(0u, ph_pixel.get_g());
}



TEST_F(TestPixelRG, ValueConstructor)
{
  pixelrg ph_pixel(1u, 2u);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
}



TEST_F(TestPixelRG, PixelRConstructor)
{
  pixelr pxR(1u);
  pixelrg pxRG(pxR);
  EXPECT_EQ(1u, pxRG.get_r());
  EXPECT_EQ(255u, pxRG.get_g());
}



TEST_F(TestPixelRG, PixelRGBConstructor)
{
  pixelrgb pxRGB(200u, 118u, 93u);
  pixelrg pxRG(pxRGB);
  EXPECT_EQ(139u, pxRG.get_r());
  EXPECT_EQ(255u, pxRG.get_g());
}



TEST_F(TestPixelRG, PixelRGBAConstructor)
{
  pixelrgba pxRGBA(200u, 118u, 93u, 7u);
  pixelrg pxRG(pxRGBA);
  EXPECT_EQ(139u, pxRG.get_r());
  EXPECT_EQ(7u, pxRG.get_g());
}



TEST_F(TestPixelRG, Set)
{
  pixelrg ph_pixel;
  ph_pixel.set(1u, 2u);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
}



TEST_F(TestPixelRG, Comparison)
{
  pixelrg p0(1u, 2u);
  pixelrg p1(p0);
  pixelrg p2(3u, 2u);
  pixelrg p3(1u, 3u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);
  EXPECT_FALSE(p0 == p3);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
  EXPECT_TRUE(p0 != p3);
}



TEST_F(TestPixelRG, OutputStreamOperator)
{
  pixelrg ph_pixel(1u, 2u);
  const char* outputRef = "{r = 1, G = 2}";
  HOU_EXPECT_OUTPUT(outputRef, ph_pixel);
}



TEST_F(TestPixelRGB, GetFormat)
{
  EXPECT_EQ(pixel_format::rgb, pixelrgb::get_format());
}



TEST_F(TestPixelRGB, DefaultConstructor)
{
  pixelrgb ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_r());
  EXPECT_EQ(0u, ph_pixel.get_g());
  EXPECT_EQ(0u, ph_pixel.get_b());
}



TEST_F(TestPixelRGB, ValueConstructor)
{
  pixelrgb ph_pixel(1u, 2u, 3u);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
  EXPECT_EQ(3u, ph_pixel.get_b());
}



TEST_F(TestPixelRGB, PixelRConstructor)
{
  pixelr pxR(1u);
  pixelrgb pxRGB(pxR);
  EXPECT_EQ(1u, pxRGB.get_r());
  EXPECT_EQ(1u, pxRGB.get_g());
  EXPECT_EQ(1u, pxRGB.get_b());
}



TEST_F(TestPixelRGB, PixelRGConstructor)
{
  pixelrg pxRG(200u, 118u);
  pixelrgb pxRGB(pxRG);
  EXPECT_EQ(200u, pxRGB.get_r());
  EXPECT_EQ(200u, pxRGB.get_g());
  EXPECT_EQ(200u, pxRGB.get_b());
}



TEST_F(TestPixelRGB, PixelRGBAConstructor)
{
  pixelrgba pxRGBA(200u, 118u, 93u, 7u);
  pixelrgb pxRGB(pxRGBA);
  EXPECT_EQ(200, pxRGB.get_r());
  EXPECT_EQ(118u, pxRGB.get_g());
  EXPECT_EQ(93u, pxRGB.get_b());
}



TEST_F(TestPixelRGB, Set)
{
  pixelrgb ph_pixel;
  ph_pixel.set(1u, 2u, 3u);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
  EXPECT_EQ(3u, ph_pixel.get_b());
}



TEST_F(TestPixelRGB, Comparison)
{
  pixelrgb p0(1u, 2u, 3u);
  pixelrgb p1(p0);
  pixelrgb p2(4u, 2u, 3u);
  pixelrgb p3(1u, 4u, 3u);
  pixelrgb p4(1u, 2u, 4u);

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
  pixelrgb ph_pixel(1u, 2u, 3u);
  const char* outputRef = "{r = 1, G = 2, B = 3}";
  HOU_EXPECT_OUTPUT(outputRef, ph_pixel);
}



TEST_F(TestPixelRGBA, GetFormat)
{
  EXPECT_EQ(pixel_format::rgba, pixelrgba::get_format());
}



TEST_F(TestPixelRGBA, DefaultConstructor)
{
  pixelrgba ph_pixel;
  EXPECT_EQ(0u, ph_pixel.get_r());
  EXPECT_EQ(0u, ph_pixel.get_g());
  EXPECT_EQ(0u, ph_pixel.get_b());
  EXPECT_EQ(0u, ph_pixel.get_a());
}



TEST_F(TestPixelRGBA, ValueConstructor)
{
  pixelrgba ph_pixel(1u, 2u, 3u, 4u);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
  EXPECT_EQ(3u, ph_pixel.get_b());
  EXPECT_EQ(4u, ph_pixel.get_a());
}



TEST_F(TestPixelRGBA, ColorConstructor)
{
  color colorRef(1u, 2u, 3u, 4u);
  pixelrgba ph_pixel(colorRef);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
  EXPECT_EQ(3u, ph_pixel.get_b());
  EXPECT_EQ(4u, ph_pixel.get_a());
  EXPECT_EQ(colorRef, ph_pixel.get_color());
}



TEST_F(TestPixelRGBA, PixelRConstructor)
{
  pixelr pxR(1u);
  pixelrgba pxRGBA(pxR);
  EXPECT_EQ(1u, pxRGBA.get_r());
  EXPECT_EQ(1u, pxRGBA.get_g());
  EXPECT_EQ(1u, pxRGBA.get_b());
  EXPECT_EQ(255u, pxRGBA.get_a());
}



TEST_F(TestPixelRGBA, PixelRGConstructor)
{
  pixelrg pxRG(200u, 118u);
  pixelrgba pxRGBA(pxRG);
  EXPECT_EQ(200u, pxRGBA.get_r());
  EXPECT_EQ(200u, pxRGBA.get_g());
  EXPECT_EQ(200u, pxRGBA.get_b());
  EXPECT_EQ(118u, pxRGBA.get_a());
}



TEST_F(TestPixelRGBA, PixelRGBConstructor)
{
  pixelrgb pxRGB(200u, 118u, 93u);
  pixelrgba pxRGBA(pxRGB);
  EXPECT_EQ(200, pxRGBA.get_r());
  EXPECT_EQ(118u, pxRGBA.get_g());
  EXPECT_EQ(93u, pxRGBA.get_b());
  EXPECT_EQ(255u, pxRGBA.get_a());
}



TEST_F(TestPixelRGBA, Set)
{
  pixelrgba ph_pixel;
  ph_pixel.set(1u, 2u, 3u, 4u);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
  EXPECT_EQ(3u, ph_pixel.get_b());
  EXPECT_EQ(4u, ph_pixel.get_a());
}



TEST_F(TestPixelRGBA, SetColor)
{
  color colorRef(1u, 2u, 3u, 4u);
  pixelrgba ph_pixel;
  ph_pixel.set_color(colorRef);
  EXPECT_EQ(1u, ph_pixel.get_r());
  EXPECT_EQ(2u, ph_pixel.get_g());
  EXPECT_EQ(3u, ph_pixel.get_b());
  EXPECT_EQ(4u, ph_pixel.get_a());
  EXPECT_EQ(colorRef, ph_pixel.get_color());
}



TEST_F(TestPixelRGBA, Comparison)
{
  pixelrgba p0(1u, 2u, 3u, 4u);
  pixelrgba p1(p0);
  pixelrgba p2(5u, 2u, 3u, 4u);
  pixelrgba p3(1u, 5u, 3u, 4u);
  pixelrgba p4(1u, 2u, 5u, 4u);
  pixelrgba p5(1u, 2u, 3u, 5u);

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
  pixelrgba ph_pixel(1u, 2u, 3u, 4u);
  const char* outputRef = "{r = 1, G = 2, B = 3, A = 4}";
  HOU_EXPECT_OUTPUT(outputRef, ph_pixel);
}
