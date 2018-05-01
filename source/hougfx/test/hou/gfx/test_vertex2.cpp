// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/mesh.hpp"
#include "hou/gfx/vertex2.hpp"
#include "hou/gfx/vertex_format.hpp"

#include "hou/mth/rectangle.hpp"

using namespace testing;
using namespace hou;



namespace
{

class TestVertex2 : public Test
{};

class TestMesh2 : public test_gfx_base
{};

}  // namespace



TEST_F(TestVertex2, size_type)
{
  EXPECT_EQ(8u * sizeof(GLfloat), sizeof(vertex2));
}



TEST_F(TestVertex2, DefaultConstructor)
{
  vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_texture_coordinates());
  EXPECT_EQ(color(0u, 0u, 0u, 0u), v.get_color());
}



TEST_F(TestVertex2, Constructor)
{
  vec2f pos_ref(1.f, 2.f);
  vec2f tc_ref(3.f, 4.f);
  color col_ref(5u, 6u, 7u, 9u);
  vertex2 v(pos_ref, tc_ref, col_ref);

  HOU_EXPECT_FLOAT_CLOSE(pos_ref, v.get_position());
  HOU_EXPECT_FLOAT_CLOSE(tc_ref, v.get_texture_coordinates());
  EXPECT_EQ(col_ref, v.get_color());
}



TEST_F(TestVertex2, SetPosition)
{
  vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_position());

  vec2f pos_ref(1.f, 2.f);
  v.set_position(pos_ref);
  HOU_EXPECT_FLOAT_CLOSE(pos_ref, v.get_position());
}



TEST_F(TestVertex2, SetTextureCoordinates)
{
  vertex2 v;
  HOU_EXPECT_FLOAT_CLOSE(vec2f(0.f, 0.f), v.get_texture_coordinates());

  vec2f tc_ref(3.f, 4.f);
  v.set_texture_coordinates(tc_ref);
  HOU_EXPECT_FLOAT_CLOSE(tc_ref, v.get_texture_coordinates());
}



TEST_F(TestVertex2, SetColor)
{
  vertex2 v;
  EXPECT_EQ(color(0u, 0u, 0u, 0u), v.get_color());

  color col_ref(5u, 6u, 7u, 9u);
  v.set_color(col_ref);
  EXPECT_EQ(col_ref, v.get_color());
}



TEST_F(TestVertex2, Comparison)
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



TEST_F(TestVertex2, CloseComparison)
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



TEST_F(TestVertex2, OutputStreamOperator)
{
  vertex2 v(vec2f(1.f, 2.f), vec2f(3.f, 4.f), color(5u, 6u, 7u, 8u));
  const char* refOutput = "{Position = (1, 2), TextureCoordinates = (3, 4), "
                          "color = {red = 5, green = 6, blue = 7, alpha = 8}}";
  HOU_EXPECT_OUTPUT(refOutput, v);
}



TEST_F(TestMesh2, rectangle)
{
  mesh2 m = create_rectangle_mesh2(vec2f(1.f, 2.f));

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(4u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.f, 0.f), vec2f(0.f, 0.f), color::white),
    vertex2(vec2f(0.f, 2.f), vec2f(0.f, 1.f), color::white),
    vertex2(vec2f(1.f, 2.f), vec2f(1.f, 1.f), color::white),
    vertex2(vec2f(1.f, 0.f), vec2f(1.f, 0.f), color::white)};
  EXPECT_EQ(vertices_ref, m.get_vertices());
}



TEST_F(TestMesh2, RectangleOutline)
{
  mesh2 m = create_rectangle_outline_mesh2(vec2f(6.f, 8.f), 2);

  EXPECT_EQ(mesh_draw_mode::triangle_strip, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(10u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.f, 0.f), vec2f::zero(), color::white),
    vertex2(vec2f(2.f, 2.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.f, 8.f), vec2f::zero(), color::white),
    vertex2(vec2f(2.f, 6.f), vec2f::zero(), color::white),
    vertex2(vec2f(6.f, 8.f), vec2f::zero(), color::white),
    vertex2(vec2f(4.f, 6.f), vec2f::zero(), color::white),
    vertex2(vec2f(6.f, 0.f), vec2f::zero(), color::white),
    vertex2(vec2f(4.f, 2.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.f, 0.f), vec2f::zero(), color::white),
    vertex2(vec2f(2.f, 2.f), vec2f::zero(), color::white)};
  EXPECT_EQ(vertices_ref, m.get_vertices());
}



TEST_F(TestMesh2, Ellipse)
{
  mesh2 m = create_ellipse_mesh2(vec2f(1.f, 2.f), 8);

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(10u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.5f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.853553f, 1.70711f), vec2f::zero(), color::white),
    vertex2(vec2f(0.5f, 2.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.146447f, 1.70711f), vec2f::zero(), color::white),
    vertex2(vec2f(0.f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.146447f, 0.292893f), vec2f::zero(), color::white),
    vertex2(vec2f(0.5f, 0.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.853553f, 0.292893f), vec2f::zero(), color::white),
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white)};
  HOU_EXPECT_CLOSE(vertices_ref, m.get_vertices(), 1e-5f);
}



TEST_F(TestMesh2, EllipseOutline)
{
  mesh2 m = create_ellipse_outline_mesh2(vec2f(1.f, 2.f), 8, 0.25);

  EXPECT_EQ(mesh_draw_mode::triangle_strip, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(18u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.75f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.853553f, 1.70711f), vec2f::zero(), color::white),
    vertex2(vec2f(0.676777f, 1.53033f), vec2f::zero(), color::white),
    vertex2(vec2f(0.5f, 2.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.5f, 1.75f), vec2f::zero(), color::white),
    vertex2(vec2f(0.146447f, 1.70711f), vec2f::zero(), color::white),
    vertex2(vec2f(0.323223f, 1.53033f), vec2f::zero(), color::white),
    vertex2(vec2f(0.f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.25f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.146447f, 0.292893f), vec2f::zero(), color::white),
    vertex2(vec2f(0.323223f, 0.46967f), vec2f::zero(), color::white),
    vertex2(vec2f(0.5f, 0.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.5f, 0.25f), vec2f::zero(), color::white),
    vertex2(vec2f(0.853553f, 0.292893f), vec2f::zero(), color::white),
    vertex2(vec2f(0.676777f, 0.46967f), vec2f::zero(), color::white),
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white),
    vertex2(vec2f(0.75f, 1.f), vec2f::zero(), color::white)};
  HOU_EXPECT_CLOSE(vertices_ref, m.get_vertices(), 1e-5f);
}



TEST_F(TestMesh2, TextureQuad)
{
  mesh2 m
    = create_texture_quad_mesh2(rectf(3.f, 8.f, 6.f, 4.f), vec2f(12.f, 16.f));

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(4u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.f, 0.f), vec2f(0.25f, 0.5f), color::white),
    vertex2(vec2f(0.f, 4.f), vec2f(0.25f, 0.75f), color::white),
    vertex2(vec2f(6.f, 4.f), vec2f(0.75f, 0.75f), color::white),
    vertex2(vec2f(6.f, 0.f), vec2f(0.75f, 0.5f), color::white)};
  EXPECT_EQ(vertices_ref, m.get_vertices());
}
