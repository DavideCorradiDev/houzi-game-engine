// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/VertexFormat.hpp"

using namespace testing;
using namespace hou;



namespace
{

class TestVertex2 : public Test {};

}



TEST_F(TestVertex2, DefaultConstructor)
{
  Vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(Vec2f(0.f, 0.f), v.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(Vec2f(0.f, 0.f), v.getTextureCoordinates());
  EXPECT_EQ(Color(0u, 0u, 0u, 0u), v.getColor());
}



TEST_F(TestVertex2, Constructor)
{
  Vec2f posRef(1.f, 2.f);
  Vec2f tcRef(3.f, 4.f);
  Color colRef(5u, 6u, 7u, 9u);
  Vertex2 v(posRef, tcRef, colRef);

  HOU_EXPECT_FLOAT_CLOSE(posRef, v.getPosition());
  HOU_EXPECT_FLOAT_CLOSE(tcRef, v.getTextureCoordinates());
  EXPECT_EQ(colRef, v.getColor());
}



TEST_F(TestVertex2, SetPosition)
{
  Vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(Vec2f(0.f, 0.f), v.getPosition());

  Vec2f posRef(1.f, 2.f);
  v.setPosition(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, v.getPosition());
}



TEST_F(TestVertex2, SetTextureCoordinates)
{
  Vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(Vec2f(0.f, 0.f), v.getTextureCoordinates());

  Vec2f tcRef(3.f, 4.f);
  v.setTextureCoordinates(tcRef);
  HOU_EXPECT_FLOAT_CLOSE(tcRef, v.getTextureCoordinates());
}



TEST_F(TestVertex2, SetColor)
{
  Vertex2 v;
  EXPECT_EQ(Color(0u, 0u, 0u, 0u), v.getColor());

  Color colRef(5u, 6u, 7u, 9u);
  v.setColor(colRef);
  EXPECT_EQ(colRef, v.getColor());
}



TEST_F(TestVertex2, Comparison)
{
  Vertex2 v1(Vec2f(1.f, 2.f), Vec2f(3.f, 4.f), Color(5u, 6u, 7u, 8u));
  Vertex2 v2(Vec2f(1.f, 2.f), Vec2f(3.f, 4.f), Color(5u, 6u, 7u, 8u));
  Vertex2 v3(Vec2f(3.f, 2.f), Vec2f(3.f, 4.f), Color(5u, 6u, 7u, 8u));
  Vertex2 v4(Vec2f(1.f, 2.f), Vec2f(3.f, 7.f), Color(5u, 6u, 7u, 8u));
  Vertex2 v5(Vec2f(1.f, 2.f), Vec2f(3.f, 4.f), Color(5u, 6u, 1u, 8u));

  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 == v3);
  EXPECT_FALSE(v1 == v4);
  EXPECT_FALSE(v1 == v5);

  EXPECT_FALSE(v1 != v2);
  EXPECT_TRUE(v1 != v3);
  EXPECT_TRUE(v1 != v4);
  EXPECT_TRUE(v1 != v5);
}



TEST_F(TestVertex2, CloseComparison)
{
  Vec2f pos1(1.1234f, 3.3456f);
  Vec2f pos2(1.1238f, 3.3456f);
  Vec2f tc1(1.1234f, 3.3456f);
  Vec2f tc2(1.1238f, 3.3456f);
  Color c1(5u, 6u, 7u, 8u);
  Color c2(9u, 6u, 7u, 8u);

  Vertex2 v1(pos1, tc1, c1);
  Vertex2 v2(v1);
  Vertex2 v3(pos2, tc1, c1);
  Vertex2 v4(pos1, tc2, c1);
  Vertex2 v5(pos1, tc1, c2);

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



TEST_F(TestVertex2, OutputStreamOperator)
{
  Vertex2 v(Vec2f(1.f, 2.f), Vec2f(3.f, 4.f), Color(5u, 6u, 7u, 8u));
  const char* refOutput = "{Position = (1, 2), TextureCoordinates = (3, 4), "
    "Color = {Red = 5, Green = 6, Blue = 7, Alpha = 8}}";
  HOU_EXPECT_OUTPUT(refOutput, v);
}

