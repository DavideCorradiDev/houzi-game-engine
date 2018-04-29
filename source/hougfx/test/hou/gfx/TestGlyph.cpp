// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/glyph.hpp"

using namespace hou;
using namespace testing;

namespace
{

class TestGlyph : public Test {};

}



TEST_F(TestGlyph, DefaultConstructor)
{
  glyph g;

  EXPECT_EQ(image2R(), g.get_image());
  EXPECT_EQ(glyph_metrics(), g.get_metrics());
}



TEST_F(TestGlyph, ParameterConstructor)
{
  image2R refImage(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 2, 3, 4, 5, 6});
  glyph_metrics refMetrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(refImage, refMetrics);

  EXPECT_EQ(refImage, g.get_image());
  EXPECT_EQ(refMetrics, g.get_metrics());
}



TEST_F(TestGlyph, Comparison)
{
  image2R refImage1(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 2, 3, 4, 5, 6});
  image2R refImage2(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 3, 3, 4, 5, 6});
  glyph_metrics refMetrics1(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics refMetrics2(vec2u(3u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g1(refImage1, refMetrics1);
  glyph g2(refImage1, refMetrics1);
  glyph g3(refImage2, refMetrics1);
  glyph g4(refImage1, refMetrics2);

  EXPECT_TRUE(g1 == g2);
  EXPECT_FALSE(g1 == g3);
  EXPECT_FALSE(g1 == g4);

  EXPECT_FALSE(g1 != g2);
  EXPECT_TRUE(g1 != g3);
  EXPECT_TRUE(g1 != g4);
}



TEST_F(TestGlyph, SetImage)
{
  image2R refImage1(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 2, 3, 4, 5, 6});
  image2R refImage2(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 3, 3, 4, 5, 6});
  glyph_metrics refMetrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(refImage1, refMetrics);
  EXPECT_EQ(refImage1, g.get_image());

  g.set_image(refImage2);
  EXPECT_EQ(refImage2, g.get_image());
}



TEST_F(TestGlyph, SetMetrics)
{
  image2R refImage(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 2, 3, 4, 5, 6});
  glyph_metrics refMetrics1(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics refMetrics2(vec2u(3u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(refImage, refMetrics1);
  EXPECT_EQ(refMetrics1, g.get_metrics());

  g.set_metrics(refMetrics2);
  EXPECT_EQ(refMetrics2, g.get_metrics());
}



TEST_F(TestGlyph, OutputStreamOperator)
{
  image2R refImage(vec2u(2u, 3u), std::vector<image2R::pixel>{1, 2, 3, 4, 5, 6});
  glyph_metrics refMetrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(refImage, refMetrics);

  const char* refOutput
    = "{image = "
      "{size_type = (2, 3)"
      ", Pixels = {{r = 1}, {r = 2}, {r = 3}, {r = 4}, {r = 5}, {r = 6}}}"
      ", Metrics = "
      "{size_type = (2, 3)"
      ", HorizontalBearing = (-1, 3)"
      ", HorizontalAdvance = 4"
      ", VerticalBearing = (5, -7)"
      ", VerticalAdvance = -11}}";

  HOU_EXPECT_OUTPUT(refOutput, g);
}

