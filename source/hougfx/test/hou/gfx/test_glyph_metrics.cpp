// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/glyph_metrics.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestGlyphMetrics : public Test
{};

}  // namespace



TEST_F(TestGlyphMetrics, DefaultConstructor)
{
  glyph_metrics gm;

  EXPECT_EQ(vec2u::zero(), gm.get_size());
  EXPECT_EQ(vec2i::zero(), gm.get_horizontal_bearing());
  EXPECT_EQ(0, gm.get_horizontal_advance());
  EXPECT_EQ(vec2i::zero(), gm.get_vertical_bearing());
  EXPECT_EQ(0, gm.get_vertical_advance());
}



TEST_F(TestGlyphMetrics, ParameterConstructor)
{
  glyph_metrics gm(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);

  EXPECT_EQ(vec2u(1u, 2u), gm.get_size());
  EXPECT_EQ(vec2i(-1, 3), gm.get_horizontal_bearing());
  EXPECT_EQ(4, gm.get_horizontal_advance());
  EXPECT_EQ(vec2i(5, -7), gm.get_vertical_bearing());
  EXPECT_EQ(-11, gm.get_vertical_advance());
}



TEST_F(TestGlyphMetrics, SetSize)
{
  glyph_metrics gm;
  vec2u size_ref(2u, 7u);
  gm.set_size(size_ref);
  EXPECT_EQ(size_ref, gm.get_size());
}



TEST_F(TestGlyphMetrics, SetHorizontalBearing)
{
  glyph_metrics gm;
  vec2i bearing_ref(3, 5);
  gm.setHorizontalBearing(bearing_ref);
  EXPECT_EQ(bearing_ref, gm.get_horizontal_bearing());
}



TEST_F(TestGlyphMetrics, SetHorizontalAdvance)
{
  glyph_metrics gm;
  int advance_ref = 7;
  gm.set_horizontal_advance(advance_ref);
  EXPECT_EQ(advance_ref, gm.get_horizontal_advance());
}



TEST_F(TestGlyphMetrics, SetVerticalBearing)
{
  glyph_metrics gm;
  vec2i bearing_ref(5, 3);
  gm.set_vertical_bearing(bearing_ref);
  EXPECT_EQ(bearing_ref, gm.get_vertical_bearing());
}



TEST_F(TestGlyphMetrics, SetVerticalAdvance)
{
  glyph_metrics gm;
  int advance_ref = 9;
  gm.set_vertical_advance(advance_ref);
  EXPECT_EQ(advance_ref, gm.get_vertical_advance());
}



TEST_F(TestGlyphMetrics, GetPixelSize)
{
  glyph_metrics gm;
  EXPECT_EQ(vec2u::zero(), gm.get_size());
  HOU_EXPECT_FLOAT_CLOSE(vec2f::zero(), gm.get_pixel_size());

  gm.set_size(vec2u(64u, 128u));
  EXPECT_EQ(vec2u(64u, 128u), gm.get_size());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.f, 2.f), gm.get_pixel_size());

  gm.set_size(vec2u(96u, 176u));
  EXPECT_EQ(vec2u(96u, 176u), gm.get_size());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.5f, 2.75f), gm.get_pixel_size());
}



TEST_F(TestGlyphMetrics, GetPixelHorizontalBearing)
{
  glyph_metrics gm;
  EXPECT_EQ(vec2i::zero(), gm.get_horizontal_bearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f::zero(), gm.get_pixel_horizontal_bearing());

  gm.setHorizontalBearing(vec2i(64, 128));
  EXPECT_EQ(vec2i(64, 128), gm.get_horizontal_bearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.f, 2.f), gm.get_pixel_horizontal_bearing());

  gm.setHorizontalBearing(vec2i(96, 176));
  EXPECT_EQ(vec2i(96, 176), gm.get_horizontal_bearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.5f, 2.75f), gm.get_pixel_horizontal_bearing());
}



TEST_F(TestGlyphMetrics, GetPixelHorizontalAdvance)
{
  glyph_metrics gm;
  EXPECT_EQ(0, gm.get_horizontal_advance());
  HOU_EXPECT_FLOAT_CLOSE(0.f, gm.get_pixel_horizontal_advance());

  gm.set_horizontal_advance(128);
  EXPECT_EQ(128, gm.get_horizontal_advance());
  HOU_EXPECT_FLOAT_CLOSE(2.f, gm.get_pixel_horizontal_advance());

  gm.set_horizontal_advance(176);
  EXPECT_EQ(176, gm.get_horizontal_advance());
  HOU_EXPECT_FLOAT_CLOSE(2.75f, gm.get_pixel_horizontal_advance());
}



TEST_F(TestGlyphMetrics, GetPixelVerticalBearing)
{
  glyph_metrics gm;
  EXPECT_EQ(vec2i::zero(), gm.get_vertical_bearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f::zero(), gm.get_pixel_vertical_bearing());

  gm.set_vertical_bearing(vec2i(64, 128));
  EXPECT_EQ(vec2i(64, 128), gm.get_vertical_bearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.f, 2.f), gm.get_pixel_vertical_bearing());

  gm.set_vertical_bearing(vec2i(96, 176));
  EXPECT_EQ(vec2i(96, 176), gm.get_vertical_bearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.5f, 2.75f), gm.get_pixel_vertical_bearing());
}



TEST_F(TestGlyphMetrics, GetPixelVerticalAdvance)
{
  glyph_metrics gm;
  EXPECT_EQ(0, gm.get_vertical_advance());
  HOU_EXPECT_FLOAT_CLOSE(0.f, gm.get_pixel_vertical_advance());

  gm.set_vertical_advance(128);
  EXPECT_EQ(128, gm.get_vertical_advance());
  HOU_EXPECT_FLOAT_CLOSE(2.f, gm.get_pixel_vertical_advance());

  gm.set_vertical_advance(176);
  EXPECT_EQ(176, gm.get_vertical_advance());
  HOU_EXPECT_FLOAT_CLOSE(2.75f, gm.get_pixel_vertical_advance());
}



TEST_F(TestGlyphMetrics, Comparison)
{
  glyph_metrics gm1(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics gm2(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics gm3(vec2u(2u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics gm4(vec2u(1u, 2u), vec2i(-3, 3), 4, vec2i(5, -7), -11);
  glyph_metrics gm5(vec2u(1u, 2u), vec2i(-1, 3), 5, vec2i(5, -7), -11);
  glyph_metrics gm6(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(2, -7), -11);
  glyph_metrics gm7(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -21);

  EXPECT_TRUE(gm1 == gm2);
  EXPECT_FALSE(gm1 == gm3);
  EXPECT_FALSE(gm1 == gm4);
  EXPECT_FALSE(gm1 == gm5);
  EXPECT_FALSE(gm1 == gm6);
  EXPECT_FALSE(gm1 == gm7);

  EXPECT_FALSE(gm1 != gm2);
  EXPECT_TRUE(gm1 != gm3);
  EXPECT_TRUE(gm1 != gm4);
  EXPECT_TRUE(gm1 != gm5);
  EXPECT_TRUE(gm1 != gm6);
  EXPECT_TRUE(gm1 != gm7);
}



TEST_F(TestGlyphMetrics, OutputStreamOperator)
{
  glyph_metrics gm(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  const char* refOutput
    = "{size_type = (1, 2)"
      ", HorizontalBearing = (-1, 3)"
      ", HorizontalAdvance = 4"
      ", VerticalBearing = (5, -7)"
      ", VerticalAdvance = -11}";
  HOU_EXPECT_OUTPUT(refOutput, gm);
}
