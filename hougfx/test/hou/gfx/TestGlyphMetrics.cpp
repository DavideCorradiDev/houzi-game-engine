// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/gfx/GlyphMetrics.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestGlyphMetrics : public Test {};

}



TEST_F(TestGlyphMetrics, DefaultConstructor)
{
  GlyphMetrics gm;

  EXPECT_EQ(Vec2u::zero(), gm.getSize());
  EXPECT_EQ(Vec2i::zero(), gm.getHorizontalBearing());
  EXPECT_EQ(0, gm.getHorizontalAdvance());
  EXPECT_EQ(Vec2i::zero(), gm.getVerticalBearing());
  EXPECT_EQ(0, gm.getVerticalAdvance());
}



TEST_F(TestGlyphMetrics, ParameterConstructor)
{
  GlyphMetrics gm(Vec2u(1u, 2u), Vec2i(-1, 3), 4, Vec2i(5, -7), -11);

  EXPECT_EQ(Vec2u(1u, 2u), gm.getSize());
  EXPECT_EQ(Vec2i(-1, 3), gm.getHorizontalBearing());
  EXPECT_EQ(4, gm.getHorizontalAdvance());
  EXPECT_EQ(Vec2i(5, -7), gm.getVerticalBearing());
  EXPECT_EQ(-11, gm.getVerticalAdvance());
}



TEST_F(TestGlyphMetrics, SetSize)
{
  GlyphMetrics gm;
  Vec2u sizeRef(2u, 7u);
  gm.setSize(sizeRef);
  EXPECT_EQ(sizeRef, gm.getSize());
}



TEST_F(TestGlyphMetrics, SetHorizontalBearing)
{
  GlyphMetrics gm;
  Vec2i bearingRef(3, 5);
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
  Vec2i bearingRef(5, 3);
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



TEST_F(TestGlyphMetrics, Comparison)
{
  GlyphMetrics gm1(Vec2u(1u, 2u), Vec2i(-1, 3), 4, Vec2i(5, -7), -11);
  GlyphMetrics gm2(Vec2u(1u, 2u), Vec2i(-1, 3), 4, Vec2i(5, -7), -11);
  GlyphMetrics gm3(Vec2u(2u, 2u), Vec2i(-1, 3), 4, Vec2i(5, -7), -11);
  GlyphMetrics gm4(Vec2u(1u, 2u), Vec2i(-3, 3), 4, Vec2i(5, -7), -11);
  GlyphMetrics gm5(Vec2u(1u, 2u), Vec2i(-1, 3), 5, Vec2i(5, -7), -11);
  GlyphMetrics gm6(Vec2u(1u, 2u), Vec2i(-1, 3), 4, Vec2i(2, -7), -11);
  GlyphMetrics gm7(Vec2u(1u, 2u), Vec2i(-1, 3), 4, Vec2i(5, -7), -21);

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
  GlyphMetrics gm(Vec2u(1u, 2u), Vec2i(-1, 3), 4, Vec2i(5, -7), -11);
  const char* refOutput
    = "{Size = (1, 2)"
    ", HorizontalBearing = (-1, 3)"
    ", HorizontalAdvance = 4"
    ", VerticalBearing = (5, -7)"
    ", VerticalAdvance = -11}";
  HOU_EXPECT_OUTPUT(refOutput, gm);
}
