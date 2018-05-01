// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/text_vertex.hpp"
#include "hou/gfx/vertex_format.hpp"

using namespace testing;
using namespace hou;



namespace
{

class test_text_vertex : public Test
{};

}  // namespace



TEST_F(test_text_vertex, type_size)
{
  EXPECT_EQ(5u * sizeof(GLfloat), sizeof(text_vertex));
}



TEST_F(test_text_vertex, default_constructor)
{
  text_vertex v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f(0.f, 0.f, 0.f), v.get_texture_coordinates());
}



TEST_F(test_text_vertex, constructor)
{
  vec2f pos_ref(1.f, 2.f);
  vec3f tc_ref(3.f, 4.f, 5.f);
  text_vertex v(pos_ref, tc_ref);

  HOU_EXPECT_FLOAT_CLOSE(pos_ref, v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(tc_ref, v.get_texture_coordinates());
}



TEST_F(test_text_vertex, set_position)
{
  text_vertex v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());

  vec2f pos_ref(1.f, 2.f);
  v.set_position(pos_ref);
  HOU_EXPECT_FLOAT_CLOSE(pos_ref, v.get_position());
}



TEST_F(test_text_vertex, set_texture_coordinates)
{
  text_vertex v;
  HOU_EXPECT_FLOAT_CLOSE(vec3f(0.f, 0.f, 0.f), v.get_texture_coordinates());

  vec3f tc_ref(3.f, 4.f, 5.f);
  v.set_texture_coordinates(tc_ref);
  HOU_EXPECT_FLOAT_CLOSE(tc_ref, v.get_texture_coordinates());
}



TEST_F(test_text_vertex, comparison)
{
  text_vertex v1(vec2f(1.f, 2.f), vec3f(3.f, 4.f, 5.f));
  text_vertex v2(vec2f(1.f, 2.f), vec3f(3.f, 4.f, 5.f));
  text_vertex v3(vec2f(3.f, 2.f), vec3f(3.f, 4.f, 5.f));
  text_vertex v4(vec2f(1.f, 2.f), vec3f(3.f, 7.f, 5.f));

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
  EXPECT_FALSE(v1 == v4);

  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
  EXPECT_TRUE(v1 != v4);
}



TEST_F(test_text_vertex, close_comparison)
{
  vec2f pos1(1.1234f, 3.3456f);
  vec2f pos2(1.1238f, 3.3456f);
  vec3f tc1(1.1234f, 3.3456f, 3.3456f);
  vec3f tc2(1.1238f, 3.3456f, 3.3456f);

  text_vertex v1(pos1, tc1);
  text_vertex v2(v1);
  text_vertex v3(pos2, tc1);
  text_vertex v4(pos1, tc2);

  EXPECT_TRUE(close(v1, v2, 1e-3f));
  EXPECT_TRUE(close(v1, v3, 1e-3f));
  EXPECT_TRUE(close(v1, v4, 1e-3f));

  EXPECT_TRUE(close(v1, v2, 1e-4f));
  EXPECT_FALSE(close(v1, v3, 1e-4f));
  EXPECT_FALSE(close(v1, v4, 1e-4f));

  EXPECT_TRUE(close(v1, v2));
  EXPECT_FALSE(close(v1, v3));
  EXPECT_FALSE(close(v1, v4));
}



TEST_F(test_text_vertex, output_stream_operator)
{
  text_vertex v(vec2f(1.f, 2.f), vec3f(3.f, 4.f, 5.f));
  const char* ref_output
    = "{position = (1, 2), texture_coordinates = (3, 4, 5)}";
  HOU_EXPECT_OUTPUT(ref_output, v);
}
