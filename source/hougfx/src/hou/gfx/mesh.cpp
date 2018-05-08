// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/mesh.hpp"

#include "hou/gl/gl_functions.hpp"



namespace hou
{

void mesh::draw(const mesh& mesh)
{
  vertex_array::bind(mesh.m_vao);
  gl::set_polygon_mode(GL_FRONT_AND_BACK, static_cast<GLenum>(mesh.m_fill_mode));
  gl::draw_arrays(static_cast<GLenum>(mesh.m_draw_mode), 0, mesh.m_vertex_count);
}



mesh::mesh(mesh_draw_mode dm, mesh_fill_mode fm, uint vertex_count)
  : non_copyable()
  , m_draw_mode(dm)
  , m_fill_mode(fm)
  , m_vertex_count(vertex_count)
  , m_vao()
{}



mesh::mesh(mesh&& other) noexcept
  : non_copyable()
  , m_draw_mode(std::move(other.m_draw_mode))
  , m_fill_mode(std::move(other.m_fill_mode))
  , m_vertex_count(std::move(other.m_vertex_count))
  , m_vao(std::move(other.m_vao))
{}



mesh::~mesh()
{}



mesh_draw_mode mesh::get_draw_mode() const noexcept
{
  return m_draw_mode;
}



mesh_fill_mode mesh::get_fill_mode() const noexcept
{
  return m_fill_mode;
}



uint mesh::get_vertex_count() const noexcept
{
  return m_vertex_count;
}

}  // namespace hou
