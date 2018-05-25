// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/gfx/mesh2.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_mesh2 : public test_gfx_base
{};

}  // namespace



TEST_F(test_mesh2, rectangle)
{
  mesh2 m = create_rectangle_mesh2(vec2f(1.f, 2.f));

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(4u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.f, 0.f), vec2f(0.f, 0.f), color::white()),
    vertex2(vec2f(0.f, 2.f), vec2f(0.f, 1.f), color::white()),
    vertex2(vec2f(1.f, 2.f), vec2f(1.f, 1.f), color::white()),
    vertex2(vec2f(1.f, 0.f), vec2f(1.f, 0.f), color::white())};
  EXPECT_EQ(vertices_ref, m.get_vertices());
}



TEST_F(test_mesh2, rectangle_outline)
{
  mesh2 m = create_rectangle_outline_mesh2(vec2f(6.f, 8.f), 2);

  EXPECT_EQ(mesh_draw_mode::triangle_strip, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(10u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.f, 0.f), vec2f::zero(), color::white()),
    vertex2(vec2f(2.f, 2.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.f, 8.f), vec2f::zero(), color::white()),
    vertex2(vec2f(2.f, 6.f), vec2f::zero(), color::white()),
    vertex2(vec2f(6.f, 8.f), vec2f::zero(), color::white()),
    vertex2(vec2f(4.f, 6.f), vec2f::zero(), color::white()),
    vertex2(vec2f(6.f, 0.f), vec2f::zero(), color::white()),
    vertex2(vec2f(4.f, 2.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.f, 0.f), vec2f::zero(), color::white()),
    vertex2(vec2f(2.f, 2.f), vec2f::zero(), color::white())};
  EXPECT_EQ(vertices_ref, m.get_vertices());
}



TEST_F(test_mesh2, ellipse)
{
  mesh2 m = create_ellipse_mesh2(vec2f(1.f, 2.f), 8);

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(10u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.5f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.853553f, 1.70711f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.5f, 2.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.146447f, 1.70711f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.146447f, 0.292893f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.5f, 0.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.853553f, 0.292893f), vec2f::zero(), color::white()),
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white())};
  EXPECT_CLOSE(vertices_ref, m.get_vertices(), 1e-5f);
}



TEST_F(test_mesh2, ellipse_outline)
{
  mesh2 m = create_ellipse_outline_mesh2(vec2f(1.f, 2.f), 8, 0.25);

  EXPECT_EQ(mesh_draw_mode::triangle_strip, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(18u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.75f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.853553f, 1.70711f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.676777f, 1.53033f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.5f, 2.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.5f, 1.75f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.146447f, 1.70711f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.323223f, 1.53033f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.25f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.146447f, 0.292893f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.323223f, 0.46967f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.5f, 0.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.5f, 0.25f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.853553f, 0.292893f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.676777f, 0.46967f), vec2f::zero(), color::white()),
    vertex2(vec2f(1.f, 1.f), vec2f::zero(), color::white()),
    vertex2(vec2f(0.75f, 1.f), vec2f::zero(), color::white())};
  EXPECT_CLOSE(vertices_ref, m.get_vertices(), 1e-5f);
}



TEST_F(test_mesh2, texture_quad)
{
  mesh2 m
    = create_texture_quad_mesh2(rectf(3.f, 8.f, 6.f, 4.f), vec2f(12.f, 16.f));

  EXPECT_EQ(mesh_draw_mode::triangle_fan, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::fill, m.get_fill_mode());
  EXPECT_EQ(4u, m.get_vertex_count());

  std::vector<vertex2> vertices_ref{
    vertex2(vec2f(0.f, 0.f), vec2f(0.25f, 0.5f), color::white()),
    vertex2(vec2f(0.f, 4.f), vec2f(0.25f, 0.75f), color::white()),
    vertex2(vec2f(6.f, 4.f), vec2f(0.75f, 0.75f), color::white()),
    vertex2(vec2f(6.f, 0.f), vec2f(0.75f, 0.5f), color::white())};
  EXPECT_EQ(vertices_ref, m.get_vertices());
}
