// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/vertex2.hpp"
#include "hou/gfx/vertex_format.hpp"

#include "hou/mth/rectangle.hpp"

using namespace testing;
using namespace hou;



namespace
{

class test_vertex2 : public Test
{};

}  // namespace



TEST_F(test_vertex2, type_size)
{
  EXPECT_EQ(8u * sizeof(GLfloat), sizeof(vertex2));
}



TEST_F(test_vertex2, default_constructor)
{
  vertex2 v;
  EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());
  EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_texture_coordinates());
  EXPECT_EQ(color(0u, 0u, 0u, 0u), v.get_color());
}



TEST_F(test_vertex2, constructor)
{
  vec2f pos_ref(1.f, 2.f);
  vec2f tc_ref(3.f, 4.f);
  color col_ref(5u, 6u, 7u, 9u);
  vertex2 v(pos_ref, tc_ref, col_ref);

  EXPECT_FLOAT_CLOSE(pos_ref, v.get_position());
  EXPECT_FLOAT_CLOSE(tc_ref, v.get_texture_coordinates());
  EXPECT_EQ(col_ref, v.get_color());
}



TEST_F(test_vertex2, set_position)
{
  vertex2 v;
  EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());

  vec2f pos_ref(1.f, 2.f);
  v.set_position(pos_ref);
  EXPECT_FLOAT_CLOSE(pos_ref, v.get_position());
}



TEST_F(test_vertex2, set_texture_coordinates)
{
  vertex2 v;
  EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_texture_coordinates());

  vec2f tc_ref(3.f, 4.f);
  v.set_texture_coordinates(tc_ref);
  EXPECT_FLOAT_CLOSE(tc_ref, v.get_texture_coordinates());
}



TEST_F(test_vertex2, set_color)
{
  vertex2 v;
  EXPECT_EQ(color(0u, 0u, 0u, 0u), v.get_color());

  color col_ref(5u, 6u, 7u, 9u);
  v.set_color(col_ref);
  EXPECT_EQ(col_ref, v.get_color());
}



TEST_F(test_vertex2, comparison)
{
  vertex2 v1(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  vertex2 v2(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  vertex2 v3(vec2f(3.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  vertex2 v4(vec2f(1.f, 2.f), vec2f(3.f, 7.f), color(5u, 6u, 7u, 8u));
  vertex2 v5(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 1u, 8u));

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
  EXPECT_FALSE(v1 == v4);
  EXPECT_FALSE(v1 == v5);

  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
  EXPECT_TRUE(v1 != v4);
  EXPECT_TRUE(v1 != v5);
}



TEST_F(test_vertex2, close_comparison)
{
  vec2f pos1(1.1234f, 3.3456f);
  vec2f pos2(1.1238f, 3.3456f);
  vec2f tc1(1.1234f, 3.3456f);
  vec2f tc2(1.1238f, 3.3456f);
  color c1(5u, 6u, 7u, 8u);
  color c2(9u, 6u, 7u, 8u);

  vertex2 v1(pos1, tc1, c1);
  vertex2 v2(v1);
  vertex2 v3(pos2, tc1, c1);
  vertex2 v4(pos1, tc2, c1);
  vertex2 v5(pos1, tc1, c2);

  EXPECT_TRUE(close(v1, v2, 1e-3f));
  EXPECT_TRUE(close(v1, v3, 1e-3f));
  EXPECT_TRUE(close(v1, v4, 1e-3f));
  EXPECT_FALSE(close(v1, v5, 1e-3f));

  EXPECT_TRUE(close(v1, v2, 1e-4f));
  EXPECT_FALSE(close(v1, v3, 1e-4f));
  EXPECT_FALSE(close(v1, v4, 1e-4f));
  EXPECT_FALSE(close(v1, v5, 1e-4f));

  EXPECT_TRUE(close(v1, v2));
  EXPECT_FALSE(close(v1, v3));
  EXPECT_FALSE(close(v1, v4));
  EXPECT_FALSE(close(v1, v5));
}



TEST_F(test_vertex2, output_stream_operator)
{
  vertex2 v(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  const char* ref_output
    = "{position = (1, 2), texture_coordinates = (3, 4), "
      "color = {red = 5, green = 6, blue = 7, alpha = 8}}";
  EXPECT_OUTPUT(ref_output, v);
}
