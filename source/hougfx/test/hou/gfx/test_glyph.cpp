// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gfx/glyph.hpp"

using namespace hou;
using namespace testing;

namespace
{

class test_glyph : public Test
{};

}  // namespace



TEST_F(test_glyph, default_constructor)
{
  glyph g;

  EXPECT_EQ(image2_r(), g.get_image());
  EXPECT_EQ(glyph_metrics(), g.get_metrics());
}



TEST_F(test_glyph, parameter_constructor)
{
  image2_r ref_im(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 2, 3, 4, 5, 6});
  glyph_metrics ref_metrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(ref_im, ref_metrics);

  EXPECT_EQ(ref_im, g.get_image());
  EXPECT_EQ(ref_metrics, g.get_metrics());
}



TEST_F(test_glyph, comparison)
{
  image2_r ref_im1(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 2, 3, 4, 5, 6});
  image2_r ref_im2(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 3, 3, 4, 5, 6});
  glyph_metrics ref_metrics1(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics ref_metrics2(vec2u(3u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g1(ref_im1, ref_metrics1);
  glyph g2(ref_im1, ref_metrics1);
  glyph g3(ref_im2, ref_metrics1);
  glyph g4(ref_im1, ref_metrics2);

  EXPECT_TRUE(g1 == g2);
  EXPECT_FALSE(g1 == g3);
  EXPECT_FALSE(g1 == g4);

  EXPECT_FALSE(g1 != g2);
  EXPECT_TRUE(g1 != g3);
  EXPECT_TRUE(g1 != g4);
}



TEST_F(test_glyph, set_image)
{
  image2_r ref_im1(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 2, 3, 4, 5, 6});
  image2_r ref_im2(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 3, 3, 4, 5, 6});
  glyph_metrics ref_metrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(ref_im1, ref_metrics);
  EXPECT_EQ(ref_im1, g.get_image());

  g.set_image(ref_im2);
  EXPECT_EQ(ref_im2, g.get_image());
}



TEST_F(test_glyph, set_metrics)
{
  image2_r ref_im(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 2, 3, 4, 5, 6});
  glyph_metrics ref_metrics1(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph_metrics ref_metrics2(vec2u(3u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(ref_im, ref_metrics1);
  EXPECT_EQ(ref_metrics1, g.get_metrics());

  g.set_metrics(ref_metrics2);
  EXPECT_EQ(ref_metrics2, g.get_metrics());
}



TEST_F(test_glyph, output_stream_operator)
{
  image2_r ref_im(
    vec2u(2u, 3u), std::vector<image2_r::pixel>{1, 2, 3, 4, 5, 6});
  glyph_metrics ref_metrics(vec2u(2u, 3u), vec2i(-1, 3), 4, vec2i(5, -7), -11);
  glyph g(ref_im, ref_metrics);

  const char* ref_output
    = "{image = "
      "{size = (2, 3)"
      ", pixels = {{r = 1}, {r = 2}, {r = 3}, {r = 4}, {r = 5}, {r = 6}}}"
      ", metrics = "
      "{size = (2, 3)"
      ", horizontal_bearing = (-1, 3)"
      ", horizontal_advance = 4"
      ", vertical_bearing = (5, -7)"
      ", vertical_advance = -11}}";

  EXPECT_OUTPUT(ref_output, g);
}
