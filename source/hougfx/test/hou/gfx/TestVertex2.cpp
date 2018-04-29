// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/TestGfxBase.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/Vertex2.hpp"
#include "hou/gfx/VertexFormat.hpp"

#include "hou/mth/rectangle.hpp"

using namespace testing;
using namespace hou;



namespace
{

class TestVertex2 : public Test
{};

class TestMesh2 : public TestGfxBase
{};

}  // namespace



TEST_F(TestVertex2, size_type)
{
  EXPECT_EQ(8u * sizeof(GLfloat), sizeof(Vertex2));
}



TEST_F(TestVertex2, DefaultConstructor)
{
  Vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.getTextureCoordinates());
  EXPECT_EQ(color(0u, 0u, 0u, 0u), v.get_color());
}



TEST_F(TestVertex2, Constructor)
{
  vec2f posRef(1.f, 2.f);
  vec2f tcRef(3.f, 4.f);
  color colRef(5u, 6u, 7u, 9u);
  Vertex2 v(posRef, tcRef, colRef);

  HOU_EXPECT_FLOAT_CLOSE(posRef, v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(tcRef, v.getTextureCoordinates());
  EXPECT_EQ(colRef, v.get_color());
}



TEST_F(TestVertex2, SetPosition)
{
  Vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());

  vec2f posRef(1.f, 2.f);
  v.set_position(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, v.get_position());
}



TEST_F(TestVertex2, SetTextureCoordinates)
{
  Vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.getTextureCoordinates());

  vec2f tcRef(3.f, 4.f);
  v.setTextureCoordinates(tcRef);
  HOU_EXPECT_FLOAT_CLOSE(tcRef, v.getTextureCoordinates());
}



TEST_F(TestVertex2, SetColor)
{
  Vertex2 v;
  EXPECT_EQ(color(0u, 0u, 0u, 0u), v.get_color());

  color colRef(5u, 6u, 7u, 9u);
  v.set_color(colRef);
  EXPECT_EQ(colRef, v.get_color());
}



TEST_F(TestVertex2, Comparison)
{
  Vertex2 v1(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  Vertex2 v2(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  Vertex2 v3(vec2f(3.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  Vertex2 v4(vec2f(1.f, 2.f), vec2f(3.f, 7.f), color(5u, 6u, 7u, 8u));
  Vertex2 v5(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 1u, 8u));

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
  vec2f pos1(1.1234f, 3.3456f);
  vec2f pos2(1.1238f, 3.3456f);
  vec2f tc1(1.1234f, 3.3456f);
  vec2f tc2(1.1238f, 3.3456f);
  color c1(5u, 6u, 7u, 8u);
  color c2(9u, 6u, 7u, 8u);

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
  Vertex2 v(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  const char* refOutput = "{Position = (1, 2), TextureCoordinates = (3, 4), "
                          "color = {red = 5, green = 6, blue = 7, Alpha = 8}}";
  HOU_EXPECT_OUTPUT(refOutput, v);
}



TEST_F(TestMesh2, rectangle)
{
  Mesh2 m = createRectangleMesh2(vec2f(1.f, 2.f));

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(4u, m.get_vertex_count());

  std::vector<Vertex2> verticesRef{
    Vertex2(vec2f(0.f, 0.f), vec2f(0.f, 0.f), color::white),
    Vertex2(vec2f(0.f, 2.f), vec2f(0.f, 1.f), color::white),
    Vertex2(vec2f(1.f, 2.f), vec2f(1.f, 1.f), color::white),
    Vertex2(vec2f(1.f, 0.f), vec2f(1.f, 0.f), color::white)};
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, RectangleOutline)
{
  Mesh2 m = createRectangleOutlineMesh2(vec2f(6.f, 8.f), 2);

  EXPECT_EQ(mesh_draw_mode::triangle_strip, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(10u, m.get_vertex_count());

  std::vector<Vertex2> verticesRef{
    Vertex2(vec2f(0.f, 0.f), vec2f::zero(), color::white),
    Vertex2(vec2f(2.f, 2.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.f, 8.f), vec2f::zero(), color::white),
    Vertex2(vec2f(2.f, 6.f), vec2f::zero(), color::white),
    Vertex2(vec2f(6.f, 8.f), vec2f::zero(), color::white),
    Vertex2(vec2f(4.f, 6.f), vec2f::zero(), color::white),
    Vertex2(vec2f(6.f, 0.f), vec2f::zero(), color::white),
    Vertex2(vec2f(4.f, 2.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.f, 0.f), vec2f::zero(), color::white),
    Vertex2(vec2f(2.f, 2.f), vec2f::zero(), color::white)};
  EXPECT_EQ(verticesRef, m.getVertices());
}



TEST_F(TestMesh2, Ellipse)
{
  Mesh2 m = createEllipseMesh2(vec2f(1.f, 2.f), 8);

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(10u, m.get_vertex_count());

  std::vector<Vertex2> verticesRef{
    Vertex2(vec2f(0.5f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.853553f, 1.70711f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.5f, 2.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.146447f, 1.70711f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.146447f, 0.292893f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.5f, 0.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.853553f, 0.292893f), vec2f::zero(), color::white),
    Vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white)};
  HOU_EXPECT_CLOSE(verticesRef, m.getVertices(), 1e-5f);
}



TEST_F(TestMesh2, EllipseOutline)
{
  Mesh2 m = createEllipseOutlineMesh2(vec2f(1.f, 2.f), 8, 0.25);

  EXPECT_EQ(mesh_draw_mode::triangle_strip, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(18u, m.get_vertex_count());

  std::vector<Vertex2> verticesRef{
    Vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.75f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.853553f, 1.70711f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.676777f, 1.53033f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.5f, 2.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.5f, 1.75f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.146447f, 1.70711f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.323223f, 1.53033f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.25f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.146447f, 0.292893f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.323223f, 0.46967f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.5f, 0.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.5f, 0.25f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.853553f, 0.292893f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.676777f, 0.46967f), vec2f::zero(), color::white),
    Vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white),
    Vertex2(vec2f(0.75f, 1.f), vec2f::zero(), color::white)};
  HOU_EXPECT_CLOSE(verticesRef, m.getVertices(), 1e-5f);
}



TEST_F(TestMesh2, TextureQuad)
{
  Mesh2 m
    = createTextureQuadMesh2(rectf(3.f, 8.f, 6.f, 4.f), vec2f(12.f, 16.f));

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(4u, m.get_vertex_count());

  std::vector<Vertex2> verticesRef{
    Vertex2(vec2f(0.f, 0.f), vec2f(0.25f, 0.5f), color::white),
    Vertex2(vec2f(0.f, 4.f), vec2f(0.25f, 0.75f), color::white),
    Vertex2(vec2f(6.f, 4.f), vec2f(0.75f, 0.75f), color::white),
    Vertex2(vec2f(6.f, 0.f), vec2f(0.75f, 0.5f), color::white)};
  EXPECT_EQ(verticesRef, m.getVertices());
}
