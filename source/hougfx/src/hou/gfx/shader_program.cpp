// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/shader_program.hpp"

#include "hou/gfx/shader.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

void shader_program::bind(const shader_program& program)
{
  gl::bind_program(program.m_handle);
}



void shader_program::unbind()
{
  gl::unbind_program();
}



shader_program::shader_program(
  const vertex_shader& vs, const fragment_shader& fs)
  : shader_program(vs, fs, nullptr)
{}



shader_program::shader_program(
  const vertex_shader& vs, const fragment_shader& fs, const geometry_shader& gs)
  : shader_program(vs, fs, &gs)
{}



shader_program::shader_program(shader_program&& other) noexcept
  : non_copyable()
  , m_handle(std::move(other.m_handle))
{}



shader_program::~shader_program()
{}



const gl::program_handle& shader_program::get_handle() const noexcept
{
  return m_handle;
}



bool shader_program::is_bound() const
{
  return gl::is_program_bound(m_handle);
}



uint shader_program::get_uniform_location(const std::string& uniform_name) const
{
  return static_cast<uint>(
    gl::get_program_uniform_location(m_handle, uniform_name.c_str()));
}



shader_program::shader_program(
  const vertex_shader& vs, const fragment_shader& fs, const geometry_shader* gs)
  : non_copyable()
  , m_handle(gl::program_handle::create())
{
  gl::attach_shader(m_handle, vs.get_handle());
  if(gs != nullptr)
  {
    gl::attach_shader(m_handle, gs->get_handle());
  }
  gl::attach_shader(m_handle, fs.get_handle());
  gl::link_program(m_handle);
}

}  // namespace hou
