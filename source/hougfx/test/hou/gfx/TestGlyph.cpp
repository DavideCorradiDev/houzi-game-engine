// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/Glyph.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestGlyph : public Test {};

}



TEST_F(TestGlyph, DefaultConstructor)
{
  Glyph g;

  EXPECT_EQ(Image2R(), g.getImage());
  EXPECT_EQ(GlyphMetrics(), g.getMetrics());
}



TEST_F(TestGlyph, ParameterConstructor)
{
  Image2R refImage(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 2, 3, 4, 5, 6});
  GlyphMetrics refMetrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  Glyph g(refImage, refMetrics);

  EXPECT_EQ(refImage, g.getImage());
  EXPECT_EQ(refMetrics, g.getMetrics());
}



TEST_F(TestGlyph, Comparison)
{
  Image2R refImage1(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 2, 3, 4, 5, 6});
  Image2R refImage2(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 3, 3, 4, 5, 6});
  GlyphMetrics refMetrics1(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  GlyphMetrics refMetrics2(vec2u(3u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  Glyph g1(refImage1, refMetrics1);
  Glyph g2(refImage1, refMetrics1);
  Glyph g3(refImage2, refMetrics1);
  Glyph g4(refImage1, refMetrics2);

  EXPECT_TRUE(g1 == g2);
  EXPECT_FALSE(g1 == g3);
  EXPECT_FALSE(g1 == g4);

  EXPECT_FALSE(g1 != g2);
  EXPECT_TRUE(g1 != g3);
  EXPECT_TRUE(g1 != g4);
}



TEST_F(TestGlyph, SetImage)
{
  Image2R refImage1(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 2, 3, 4, 5, 6});
  Image2R refImage2(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 3, 3, 4, 5, 6});
  GlyphMetrics refMetrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  Glyph g(refImage1, refMetrics);
  EXPECT_EQ(refImage1, g.getImage());

  g.setImage(refImage2);
  EXPECT_EQ(refImage2, g.getImage());
}



TEST_F(TestGlyph, SetMetrics)
{
  Image2R refImage(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 2, 3, 4, 5, 6});
  GlyphMetrics refMetrics1(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  GlyphMetrics refMetrics2(vec2u(3u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  Glyph g(refImage, refMetrics1);
  EXPECT_EQ(refMetrics1, g.getMetrics());

  g.setMetrics(refMetrics2);
  EXPECT_EQ(refMetrics2, g.getMetrics());
}



TEST_F(TestGlyph, OutputStreamOperator)
{
  Image2R refImage(vec2u(2u, 3u), std::vector<Image2R::Pixel>{1, 2, 3, 4, 5, 6});
  GlyphMetrics refMetrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  Glyph g(refImage, refMetrics);

  const char* refOutput
    = "{Image = "
      "{Size = (2, 3)"
      ", Pixels = {{R = 1}, {R = 2}, {R = 3}, {R = 4}, {R = 5}, {R = 6}}}"
      ", Metrics = "
      "{Size = (2, 3)"
      ", HorizontalBearing = (-1, 3)"
      ", HorizontalAdvance = 4"
      ", VerticalBearing = (5, -7)"
      ", VerticalAdvance = -11}}";

  HOU_EXPECT_OUTPUT(refOutput, g);
}

