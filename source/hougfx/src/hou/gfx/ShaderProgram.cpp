// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/ShaderProgram.hpp"

#include "hou/gfx/Shader.hpp"

#include "hou/mth/matrix.hpp"



namespace hou
{

void ShaderProgram::bind(const ShaderProgram& program)
{
  gl::bind_program(program.m_handle);
}



void ShaderProgram::unbind()
{
  gl::unbind_program();
}



ShaderProgram::ShaderProgram(const VertexShader& vs, const FragmentShader& fs)
  : ShaderProgram(vs, fs, nullptr)
{}



ShaderProgram::ShaderProgram(
  const VertexShader& vs, const FragmentShader& fs, const GeometryShader& gs)
  : ShaderProgram(vs, fs, &gs)
{}



ShaderProgram::ShaderProgram(ShaderProgram&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
{}



ShaderProgram::~ShaderProgram()
{}



const gl::program_handle& ShaderProgram::get_handle() const
{
  return m_handle;
}



bool ShaderProgram::isBound() const
{
  return gl::is_program_bound(m_handle);
}



uint ShaderProgram::getUniformLocation(const std::string& uniformName) const
{
  return static_cast<uint>(
    gl::get_program_uniform_location(m_handle, uniformName.c_str()));
}



ShaderProgram::ShaderProgram(
  const VertexShader& vs, const FragmentShader& fs, const GeometryShader* gs)
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
