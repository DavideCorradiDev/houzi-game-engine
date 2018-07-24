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
  gl::set_polygon_mode(
    GL_FRONT_AND_BACK, static_cast<GLenum>(mesh.m_fill_mode));
  gl::draw_arrays(static_cast<GLenum>(mesh.m_draw_mode), 0,
    narrow_cast<GLsizei>(mesh.m_vertex_count));
}



mesh::mesh(mesh_draw_mode dm, mesh_fill_mode fm, size_t vertex_count)
  : non_copyable()
  , m_vao()
  , m_draw_mode(dm)
  , m_fill_mode(fm)
  , m_vertex_count(vertex_count)
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



size_t mesh::get_vertex_count() const noexcept
{
  return m_vertex_count;
}

}  // namespace hou
