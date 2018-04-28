// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/TextVertex.hpp"
#include "hou/gfx/VertexFormat.hpp"

using namespace testing;
using namespace hou;



namespace
{

class TestTextVertex : public Test
{};

}  // namespace



TEST_F(TestTextVertex, Size)
{
  EXPECT_EQ(5u * sizeof(GLfloat), sizeof(TextVertex));
}



TEST_F(TestTextVertex, DefaultConstructor)
{
  TextVertex v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f(0.f, 0.f, 0.f), v.getTextureCoordinates());
}



TEST_F(TestTextVertex, Constructor)
{
  vec2f posRef(1.f, 2.f);
  vec3f tcRef(3.f, 4.f, 5.f);
  TextVertex v(posRef, tcRef);

  HOU_EXPECT_FLOAT_CLOSE(posRef, v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(tcRef, v.getTextureCoordinates());
}



TEST_F(TestTextVertex, SetPosition)
{
  TextVertex v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());

  vec2f posRef(1.f, 2.f);
  v.set_position(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, v.get_position());
}



TEST_F(TestTextVertex, SetTextureCoordinates)
{
  TextVertex v;
  HOU_EXPECT_FLOAT_CLOSE(vec3f(0.f, 0.f, 0.f), v.getTextureCoordinates());

  vec3f tcRef(3.f, 4.f, 5.f);
  v.setTextureCoordinates(tcRef);
  HOU_EXPECT_FLOAT_CLOSE(tcRef, v.getTextureCoordinates());
}



TEST_F(TestTextVertex, Comparison)
{
  TextVertex v1(vec2f(1.f, 2.f), vec3f(3.f, 4.f, 5.f));
  TextVertex v2(vec2f(1.f, 2.f), vec3f(3.f, 4.f, 5.f));
  TextVertex v3(vec2f(3.f, 2.f), vec3f(3.f, 4.f, 5.f));
  TextVertex v4(vec2f(1.f, 2.f), vec3f(3.f, 7.f, 5.f));

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
  EXPECT_FALSE(v1 == v4);

  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
  EXPECT_TRUE(v1 != v4);
}



TEST_F(TestTextVertex, CloseComparison)
{
  vec2f pos1(1.1234f, 3.3456f);
  vec2f pos2(1.1238f, 3.3456f);
  vec3f tc1(1.1234f, 3.3456f, 3.3456f);
  vec3f tc2(1.1238f, 3.3456f, 3.3456f);

  TextVertex v1(pos1, tc1);
  TextVertex v2(v1);
  TextVertex v3(pos2, tc1);
  TextVertex v4(pos1, tc2);

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



TEST_F(TestTextVertex, OutputStreamOperator)
{
  TextVertex v(vec2f(1.f, 2.f), vec3f(3.f, 4.f, 5.f));
  const char* refOutput = "{Position = (1, 2), TextureCoordinates = (3, 4, 5)}";
  HOU_EXPECT_OUTPUT(refOutput, v);
}
