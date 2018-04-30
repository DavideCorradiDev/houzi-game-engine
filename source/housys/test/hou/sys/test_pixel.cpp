// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/sys/pixel.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_pixel_format : public Test
{};

class test_pixel_format_death_test : public test_pixel_format
{};

class test_pixel : public Test
{};

template <typename pixel_t>
class test_pixel_common : public test_pixel
{};

using pixel_types_common = Types<pixelr, pixelrg, pixelrgb, pixelrgba>;

template <typename pixel_t>
class test_pixel_red_channel : public test_pixel
{};

using pixel_types_red_channel = Types<pixelr, pixelrg, pixelrgb, pixelrgba>;

template <typename pixel_t>
class test_pixel_green_channel : public test_pixel
{};

using pixel_types_green_channel = Types<pixelrg, pixelrgb, pixelrgba>;

template <typename pixel_t>
class test_pixel_blue_channel : public test_pixel
{};

using pixel_types_blue_channel = Types<pixelrgb, pixelrgba>;

template <typename pixel_t>
class test_pixel_alpha_channel : public test_pixel
{};

using pixel_types_alpha_channel = Types<pixelrgba>;

class test_pixelr : public test_pixel
{};

class test_pixelrg : public test_pixel
{};

class test_pixelrgb : public test_pixel
{};

class test_pixel_rgba : public test_pixel
{};

}  // namespace



TYPED_TEST_CASE(test_pixel_common, pixel_types_common);
TYPED_TEST_CASE(test_pixel_red_channel, pixel_types_red_channel);
TYPED_TEST_CASE(test_pixel_green_channel, pixel_types_green_channel);
TYPED_TEST_CASE(test_pixel_blue_channel, pixel_types_blue_channel);
TYPED_TEST_CASE(test_pixel_alpha_channel, pixel_types_alpha_channel);



TEST_F(test_pixel_format, get_pixel_format_byte_count)
{
  EXPECT_EQ(1u, get_pixel_format_byte_count(pixel_format::r));
  EXPECT_EQ(2u, get_pixel_format_byte_count(pixel_format::rg));
  EXPECT_EQ(3u, get_pixel_format_byte_count(pixel_format::rgb));
  EXPECT_EQ(4u, get_pixel_format_byte_count(pixel_format::rgba));
}



TEST_F(
  test_pixel_format_death_test, get_pixel_format_byte_count_error_invalid_enum)
{
  int enumVal = 5;
  HOU_EXPECT_ERROR(get_pixel_format_byte_count(pixel_format(enumVal)),
    std::logic_error,
    format_string(get_text(cor_error::invalid_enum), enumVal));
}



TYPED_TEST(test_pixel_common, get_byte_count)
{
  EXPECT_EQ(get_pixel_format_byte_count(TypeParam::get_format()),
    TypeParam::get_byte_count());
}



TYPED_TEST(test_pixel_common, no_padding)
{
  EXPECT_EQ(TypeParam::get_byte_count(), sizeof(TypeParam));
}



TYPED_TEST(test_pixel_red_channel, set_r)
{
  TypeParam px;
  EXPECT_EQ(0u, px.get_r());
  px.set_r(1u);
  EXPECT_EQ(1u, px.get_r());
}



TYPED_TEST(test_pixel_green_channel, set_g)
{
  TypeParam px;
  EXPECT_EQ(0u, px.get_g());
  px.set_g(1u);
  EXPECT_EQ(1u, px.get_g());
}



TYPED_TEST(test_pixel_blue_channel, set_b)
{
  TypeParam px;
  EXPECT_EQ(0u, px.get_b());
  px.set_b(1u);
  EXPECT_EQ(1u, px.get_b());
}



TYPED_TEST(test_pixel_alpha_channel, set_a)
{
  TypeParam px;
  EXPECT_EQ(0u, px.get_a());
  px.set_a(1u);
  EXPECT_EQ(1u, px.get_a());
}



TEST_F(test_pixelr, get_format)
{
  EXPECT_EQ(pixel_format::r, pixelr::get_format());
}



TEST_F(test_pixelr, default_constructor)
{
  pixelr px;
  EXPECT_EQ(0u, px.get_r());
}



TEST_F(test_pixelr, value_constructor)
{
  pixelr px(1u);
  EXPECT_EQ(1u, px.get_r());
}



TEST_F(test_pixelr, pixel_rg_constructor)
{
  pixelrg pxRG(1u, 2u);
  pixelr pxR(pxRG);
  EXPECT_EQ(1u, pxR.get_r());
}



TEST_F(test_pixelr, pixel_rgb_constructor)
{
  pixelrgb pxRGB(200u, 118u, 93u);
  pixelr pxR(pxRGB);
  EXPECT_EQ(139u, pxR.get_r());
}



TEST_F(test_pixelr, pixel_rgba_constructor)
{
  pixelrgba pxRGBA(200u, 118u, 93u, 7u);
  pixelr pxR(pxRGBA);
  EXPECT_EQ(139u, pxR.get_r());
}



TEST_F(test_pixelr, set)
{
  pixelr px;
  px.set(1u);
  EXPECT_EQ(1u, px.get_r());
}



TEST_F(test_pixelr, comparison)
{
  pixelr p0(1u);
  pixelr p1(p0);
  pixelr p2(2u);

  EXPECT_TRUE(p0 == p1);
  EXPECT_FALSE(p0 == p2);

  EXPECT_FALSE(p0 != p1);
  EXPECT_TRUE(p0 != p2);
}



TEST_F(test_pixelr, output_stream_operator)
{
  pixelr px(1u);
  const char* output_ref = "{r = 1}";
  HOU_EXPECT_OUTPUT(output_ref, px);
}



TEST_F(test_pixelrg, get_format)
{
  EXPECT_EQ(pixel_format::rg, pixelrg::get_format());
}



TEST_F(test_pixelrg, default_constructor)
{
  pixelrg px;
  EXPECT_EQ(0u, px.get_r());
  EXPECT_EQ(0u, px.get_g());
}



TEST_F(test_pixelrg, value_constructor)
{
  pixelrg px(1u, 2u);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
}



TEST_F(test_pixelrg, pixel_r_constructor)
{
  pixelr pxR(1u);
  pixelrg pxRG(pxR);
  EXPECT_EQ(1u, pxRG.get_r());
  EXPECT_EQ(255u, pxRG.get_g());
}



TEST_F(test_pixelrg, pixel_rgb_constructor)
{
  pixelrgb pxRGB(200u, 118u, 93u);
  pixelrg pxRG(pxRGB);
  EXPECT_EQ(139u, pxRG.get_r());
  EXPECT_EQ(255u, pxRG.get_g());
}



TEST_F(test_pixelrg, pixel_rgba_constructor)
{
  pixelrgba pxRGBA(200u, 118u, 93u, 7u);
  pixelrg pxRG(pxRGBA);
  EXPECT_EQ(139u, pxRG.get_r());
  EXPECT_EQ(7u, pxRG.get_g());
}



TEST_F(test_pixelrg, set)
{
  pixelrg px;
  px.set(1u, 2u);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
}



TEST_F(test_pixelrg, comparison)
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



TEST_F(test_pixelrg, output_stream_operator)
{
  pixelrg px(1u, 2u);
  const char* output_ref = "{r = 1, g = 2}";
  HOU_EXPECT_OUTPUT(output_ref, px);
}



TEST_F(test_pixelrgb, get_format)
{
  EXPECT_EQ(pixel_format::rgb, pixelrgb::get_format());
}



TEST_F(test_pixelrgb, default_constructor)
{
  pixelrgb px;
  EXPECT_EQ(0u, px.get_r());
  EXPECT_EQ(0u, px.get_g());
  EXPECT_EQ(0u, px.get_b());
}



TEST_F(test_pixelrgb, value_constructor)
{
  pixelrgb px(1u, 2u, 3u);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
  EXPECT_EQ(3u, px.get_b());
}



TEST_F(test_pixelrgb, pixel_r_constructor)
{
  pixelr pxR(1u);
  pixelrgb pxRGB(pxR);
  EXPECT_EQ(1u, pxRGB.get_r());
  EXPECT_EQ(1u, pxRGB.get_g());
  EXPECT_EQ(1u, pxRGB.get_b());
}



TEST_F(test_pixelrgb, pixel_rg_constructor)
{
  pixelrg pxRG(200u, 118u);
  pixelrgb pxRGB(pxRG);
  EXPECT_EQ(200u, pxRGB.get_r());
  EXPECT_EQ(200u, pxRGB.get_g());
  EXPECT_EQ(200u, pxRGB.get_b());
}



TEST_F(test_pixelrgb, pixel_rgba_constructor)
{
  pixelrgba pxRGBA(200u, 118u, 93u, 7u);
  pixelrgb pxRGB(pxRGBA);
  EXPECT_EQ(200, pxRGB.get_r());
  EXPECT_EQ(118u, pxRGB.get_g());
  EXPECT_EQ(93u, pxRGB.get_b());
}



TEST_F(test_pixelrgb, set)
{
  pixelrgb px;
  px.set(1u, 2u, 3u);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
  EXPECT_EQ(3u, px.get_b());
}



TEST_F(test_pixelrgb, comparison)
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



TEST_F(test_pixelrgb, output_stream_operator)
{
  pixelrgb px(1u, 2u, 3u);
  const char* output_ref = "{r = 1, g = 2, b = 3}";
  HOU_EXPECT_OUTPUT(output_ref, px);
}



TEST_F(test_pixel_rgba, get_format)
{
  EXPECT_EQ(pixel_format::rgba, pixelrgba::get_format());
}



TEST_F(test_pixel_rgba, default_constructor)
{
  pixelrgba px;
  EXPECT_EQ(0u, px.get_r());
  EXPECT_EQ(0u, px.get_g());
  EXPECT_EQ(0u, px.get_b());
  EXPECT_EQ(0u, px.get_a());
}



TEST_F(test_pixel_rgba, value_constructor)
{
  pixelrgba px(1u, 2u, 3u, 4u);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
  EXPECT_EQ(3u, px.get_b());
  EXPECT_EQ(4u, px.get_a());
}



TEST_F(test_pixel_rgba, color_constructor)
{
  color color_ref(1u, 2u, 3u, 4u);
  pixelrgba px(color_ref);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
  EXPECT_EQ(3u, px.get_b());
  EXPECT_EQ(4u, px.get_a());
  EXPECT_EQ(color_ref, px.get_color());
}



TEST_F(test_pixel_rgba, pixel_r_constructor)
{
  pixelr pxR(1u);
  pixelrgba pxRGBA(pxR);
  EXPECT_EQ(1u, pxRGBA.get_r());
  EXPECT_EQ(1u, pxRGBA.get_g());
  EXPECT_EQ(1u, pxRGBA.get_b());
  EXPECT_EQ(255u, pxRGBA.get_a());
}



TEST_F(test_pixel_rgba, pixel_rg_constructor)
{
  pixelrg pxRG(200u, 118u);
  pixelrgba pxRGBA(pxRG);
  EXPECT_EQ(200u, pxRGBA.get_r());
  EXPECT_EQ(200u, pxRGBA.get_g());
  EXPECT_EQ(200u, pxRGBA.get_b());
  EXPECT_EQ(118u, pxRGBA.get_a());
}



TEST_F(test_pixel_rgba, pixel_rgb_constructor)
{
  pixelrgb pxRGB(200u, 118u, 93u);
  pixelrgba pxRGBA(pxRGB);
  EXPECT_EQ(200, pxRGBA.get_r());
  EXPECT_EQ(118u, pxRGBA.get_g());
  EXPECT_EQ(93u, pxRGBA.get_b());
  EXPECT_EQ(255u, pxRGBA.get_a());
}



TEST_F(test_pixel_rgba, set)
{
  pixelrgba px;
  px.set(1u, 2u, 3u, 4u);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
  EXPECT_EQ(3u, px.get_b());
  EXPECT_EQ(4u, px.get_a());
}



TEST_F(test_pixel_rgba, set_color)
{
  color color_ref(1u, 2u, 3u, 4u);
  pixelrgba px;
  px.set_color(color_ref);
  EXPECT_EQ(1u, px.get_r());
  EXPECT_EQ(2u, px.get_g());
  EXPECT_EQ(3u, px.get_b());
  EXPECT_EQ(4u, px.get_a());
  EXPECT_EQ(color_ref, px.get_color());
}



TEST_F(test_pixel_rgba, comparison)
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



TEST_F(test_pixel_rgba, output_stream_operator)
{
  pixelrgba px(1u, 2u, 3u, 4u);
  const char* output_ref = "{r = 1, g = 2, b = 3, a = 4}";
  HOU_EXPECT_OUTPUT(output_ref, px);
}
