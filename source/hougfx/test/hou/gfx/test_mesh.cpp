// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/gfx/test_gfx_base.hpp"

#include "hou/cor/core_functions.hpp"
#include "hou/cor/std_vector.hpp"

#include "hou/gfx/gl_type.hpp"
#include "hou/gfx/mesh.hpp"
#include "hou/gfx/vertex_format.hpp"

#include "hou/sys/color.hpp"

using namespace hou;



namespace
{

class test_mesh : public test_gfx_base
{};

class vertex_type
{
public:
  using comparison_type = float;

public:
  static const vertex_format& get_vertex_format();

public:
  vertex_type();
  explicit vertex_type(float value);

  float get_value() const;

private:
  GLfloat m_value;
};

bool operator==(const vertex_type& lhs, const vertex_type& rhs);
bool close(const vertex_type& lhs, const vertex_type& rhs,
  float acc = std::numeric_limits<GLfloat>::epsilon());
std::ostream& operator<<(std::ostream& os, const vertex_type& v);

using MeshType = mesh_t<vertex_type>;



const vertex_format& vertex_type::get_vertex_format()
{
  static constexpr bool must_be_normalized = true;
  static const vertex_format vf(0, sizeof(vertex_type),
    {vertex_attrib_format(gl_type::float_decimal, 1,
      offsetof(vertex_type, m_value), !must_be_normalized)});
  return vf;
}



vertex_type::vertex_type()
  : m_value(0.f)
{}



vertex_type::vertex_type(float value)
  : m_value(value)
{}



float vertex_type::get_value() const
{
  return m_value;
}



bool operator==(const vertex_type& lhs, const vertex_type& rhs)
{
  return lhs.get_value() == rhs.get_value();
}



bool close(const vertex_type& lhs, const vertex_type& rhs, float acc)
{
  return hou::close(lhs.get_value(), rhs.get_value(), acc);
}



std::ostream& operator<<(std::ostream& os, const vertex_type& v)
{
  return os << "{" << v.get_value() << "}";
}

}  // namespace



TEST_F(test_mesh, constructor)
{
  mesh_draw_mode drawMode_ref = mesh_draw_mode::points;
  mesh_fill_mode polygonMode_ref = mesh_fill_mode::line;
  MeshType::vertex_collection vertices_ref{
    vertex_type(1.f), vertex_type(1.3f), vertex_type(3.5f)};

  MeshType m(drawMode_ref, polygonMode_ref, vertices_ref);

  EXPECT_EQ(mesh_draw_mode::points, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::line, m.get_fill_mode());
  EXPECT_EQ(vertices_ref.size(), m.get_vertex_count());
  EXPECT_EQ(vertices_ref, m.get_vertices());
}



TEST_F(test_mesh, move_constructor)
{
  mesh_draw_mode drawMode_ref = mesh_draw_mode::points;
  mesh_fill_mode polygonMode_ref = mesh_fill_mode::line;
  MeshType::vertex_collection vertices_ref{
    vertex_type(1.f), vertex_type(1.3f), vertex_type(3.5f)};

  MeshType m_dummy(drawMode_ref, polygonMode_ref, vertices_ref);
  MeshType m(std::move(m_dummy));

  EXPECT_EQ(mesh_draw_mode::points, m.get_draw_mode());
  EXPECT_EQ(mesh_fill_mode::line, m.get_fill_mode());
  EXPECT_EQ(vertices_ref.size(), m.get_vertex_count());
  EXPECT_EQ(vertices_ref, m.get_vertices());
}



TEST_F(test_mesh, comparison)
{
  MeshType::vertex_collection vertices1{vertex_type(1.f), vertex_type(2.f)};
  MeshType::vertex_collection vertices2{vertex_type(3.f), vertex_type(2.f)};

  MeshType m1(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices1);
  MeshType m2(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices1);
  MeshType m3(mesh_draw_mode::triangle_fan, mesh_fill_mode::fill, vertices1);
  MeshType m4(mesh_draw_mode::triangle_strip, mesh_fill_mode::line, vertices1);
  MeshType m5(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices2);

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m1 == m4);
  EXPECT_FALSE(m1 == m5);

  EXPECT_FALSE(m1 != m2);
  EXPECT_TRUE(m1 != m3);
  EXPECT_TRUE(m1 != m4);
  EXPECT_TRUE(m1 != m5);
}



TEST_F(test_mesh, close_comparison)
{
  MeshType::vertex_collection vertices1{vertex_type(1.1234f), vertex_type(2.f)};
  MeshType::vertex_collection vertices2{vertex_type(1.1238f), vertex_type(2.f)};

  MeshType m1(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices1);
  MeshType m2(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices1);
  MeshType m3(mesh_draw_mode::triangle_fan, mesh_fill_mode::fill, vertices1);
  MeshType m4(mesh_draw_mode::triangle_strip, mesh_fill_mode::line, vertices1);
  MeshType m5(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices2);

  EXPECT_TRUE(close(m1, m2, static_cast<GLfloat>(1e-3f)));
  EXPECT_FALSE(close(m1, m3, static_cast<GLfloat>(1e-3f)));
  EXPECT_FALSE(close(m1, m4, static_cast<GLfloat>(1e-3f)));
  EXPECT_TRUE(close(m1, m5, static_cast<GLfloat>(1e-3f)));

  EXPECT_TRUE(close(m1, m2, static_cast<GLfloat>(1e-4f)));
  EXPECT_FALSE(close(m1, m3, static_cast<GLfloat>(1e-4f)));
  EXPECT_FALSE(close(m1, m4, static_cast<GLfloat>(1e-4f)));
  EXPECT_FALSE(close(m1, m5, static_cast<GLfloat>(1e-4f)));

  EXPECT_TRUE(close(m1, m2));
  EXPECT_FALSE(close(m1, m3));
  EXPECT_FALSE(close(m1, m4));
  EXPECT_FALSE(close(m1, m5));
}



TEST_F(test_mesh, output_stream_operator)
{
  MeshType::vertex_collection vertices{vertex_type(1.f), vertex_type(2.f)};
  MeshType m(mesh_draw_mode::triangle_strip, mesh_fill_mode::fill, vertices);

  const char out_ref[]
    = "{draw_mode = triangle_strip, fill_mode = fill, vertices = {{1}, {2}}}";
  EXPECT_OUTPUT(out_ref, m);
}
