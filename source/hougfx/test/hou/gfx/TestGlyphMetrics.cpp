// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/GlyphMetrics.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestGlyphMetrics : public Test
{};

}  // namespace



TEST_F(TestGlyphMetrics, DefaultConstructor)
{
  GlyphMetrics gm;

  EXPECT_EQ(vec2u::zero(), gm.get_size());
  EXPECT_EQ(vec2i::zero(), gm.getHorizontalBearing());
  EXPECT_EQ(0, gm.getHorizontalAdvance());
  EXPECT_EQ(vec2i::zero(), gm.getVerticalBearing());
  EXPECT_EQ(0, gm.getVerticalAdvance());
}



TEST_F(TestGlyphMetrics, ParameterConstructor)
{
  GlyphMetrics gm(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);

  EXPECT_EQ(vec2u(1u, 2u), gm.get_size());
  EXPECT_EQ(vec2i(-1, 3), gm.getHorizontalBearing());
  EXPECT_EQ(4, gm.getHorizontalAdvance());
  EXPECT_EQ(vec2i(5, -7), gm.getVerticalBearing());
  EXPECT_EQ(-11, gm.getVerticalAdvance());
}



TEST_F(TestGlyphMetrics, SetSize)
{
  GlyphMetrics gm;
  vec2u sizeRef(2u, 7u);
  gm.set_size(sizeRef);
  EXPECT_EQ(sizeRef, gm.get_size());
}



TEST_F(TestGlyphMetrics, SetHorizontalBearing)
{
  GlyphMetrics gm;
  vec2i bearingRef(3, 5);
  gm.setHorizontalBearing(bearingRef);
  EXPECT_EQ(bearingRef, gm.getHorizontalBearing());
}



TEST_F(TestGlyphMetrics, SetHorizontalAdvance)
{
  GlyphMetrics gm;
  int advanceRef = 7;
  gm.setHorizontalAdvance(advanceRef);
  EXPECT_EQ(advanceRef, gm.getHorizontalAdvance());
}



TEST_F(TestGlyphMetrics, SetVerticalBearing)
{
  GlyphMetrics gm;
  vec2i bearingRef(5, 3);
  gm.setVerticalBearing(bearingRef);
  EXPECT_EQ(bearingRef, gm.getVerticalBearing());
}



TEST_F(TestGlyphMetrics, SetVerticalAdvance)
{
  GlyphMetrics gm;
  int advanceRef = 9;
  gm.setVerticalAdvance(advanceRef);
  EXPECT_EQ(advanceRef, gm.getVerticalAdvance());
}



TEST_F(TestGlyphMetrics, GetPixelSize)
{
  GlyphMetrics gm;
  EXPECT_EQ(vec2u::zero(), gm.get_size());
  HOU_EXPECT_FLOAT_CLOSE(vec2f::zero(), gm.getPixelSize());

  gm.set_size(vec2u(64u, 128u));
  EXPECT_EQ(vec2u(64u, 128u), gm.get_size());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.f, 2.f), gm.getPixelSize());

  gm.set_size(vec2u(96u, 176u));
  EXPECT_EQ(vec2u(96u, 176u), gm.get_size());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.5f, 2.75f), gm.getPixelSize());
}



TEST_F(TestGlyphMetrics, GetPixelHorizontalBearing)
{
  GlyphMetrics gm;
  EXPECT_EQ(vec2i::zero(), gm.getHorizontalBearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f::zero(), gm.getPixelHorizontalBearing());

  gm.setHorizontalBearing(vec2i(64, 128));
  EXPECT_EQ(vec2i(64, 128), gm.getHorizontalBearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.f, 2.f), gm.getPixelHorizontalBearing());

  gm.setHorizontalBearing(vec2i(96, 176));
  EXPECT_EQ(vec2i(96, 176), gm.getHorizontalBearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.5f, 2.75f), gm.getPixelHorizontalBearing());
}



TEST_F(TestGlyphMetrics, GetPixelHorizontalAdvance)
{
  GlyphMetrics gm;
  EXPECT_EQ(0, gm.getHorizontalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(0.f, gm.getPixelHorizontalAdvance());

  gm.setHorizontalAdvance(128);
  EXPECT_EQ(128, gm.getHorizontalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(2.f, gm.getPixelHorizontalAdvance());

  gm.setHorizontalAdvance(176);
  EXPECT_EQ(176, gm.getHorizontalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(2.75f, gm.getPixelHorizontalAdvance());
}



TEST_F(TestGlyphMetrics, GetPixelVerticalBearing)
{
  GlyphMetrics gm;
  EXPECT_EQ(vec2i::zero(), gm.getVerticalBearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f::zero(), gm.getPixelVerticalBearing());

  gm.setVerticalBearing(vec2i(64, 128));
  EXPECT_EQ(vec2i(64, 128), gm.getVerticalBearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.f, 2.f), gm.getPixelVerticalBearing());

  gm.setVerticalBearing(vec2i(96, 176));
  EXPECT_EQ(vec2i(96, 176), gm.getVerticalBearing());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(1.5f, 2.75f), gm.getPixelVerticalBearing());
}



TEST_F(TestGlyphMetrics, GetPixelVerticalAdvance)
{
  GlyphMetrics gm;
  EXPECT_EQ(0, gm.getVerticalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(0.f, gm.getPixelVerticalAdvance());

  gm.setVerticalAdvance(128);
  EXPECT_EQ(128, gm.getVerticalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(2.f, gm.getPixelVerticalAdvance());

  gm.setVerticalAdvance(176);
  EXPECT_EQ(176, gm.getVerticalAdvance());
  HOU_EXPECT_FLOAT_CLOSE(2.75f, gm.getPixelVerticalAdvance());
}



TEST_F(TestGlyphMetrics, Comparison)
{
  GlyphMetrics gm1(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  GlyphMetrics gm2(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  GlyphMetrics gm3(vec2u(2u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  GlyphMetrics gm4(vec2u(1u, 2u), vec2i(-3, 3), 4, vec2i(5, -7), -11);
  GlyphMetrics gm5(vec2u(1u, 2u), vec2i(-1, 3), 5, vec2i(5, -7), -11);
  GlyphMetrics gm6(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(2, -7), -11);
  GlyphMetrics gm7(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -21);

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
  GlyphMetrics gm(vec2u(1u, 2u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  const char* refOutput
    = "{size_type = (1, 2)"
      ", HorizontalBearing = (-1, 3)"
      ", HorizontalAdvance = 4"
      ", VerticalBearing = (5, -7)"
      ", VerticalAdvance = -11}";
  HOU_EXPECT_OUTPUT(refOutput, gm);
}
