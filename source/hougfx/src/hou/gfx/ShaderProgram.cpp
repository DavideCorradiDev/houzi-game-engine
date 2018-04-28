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
  gl::bindProgram(program.m_handle);
}



void ShaderProgram::unbind()
{
  gl::unbindProgram();
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



const gl::ProgramHandle& ShaderProgram::getHandle() const
{
  return m_handle;
}



bool ShaderProgram::isBound() const
{
  return gl::isProgramBound(m_handle);
}



uint ShaderProgram::getUniformLocation(const std::string& uniformName) const
{
  return static_cast<uint>(
    gl::getProgramUniformLocation(m_handle, uniformName.c_str()));
}



ShaderProgram::ShaderProgram(
  const VertexShader& vs, const FragmentShader& fs, const GeometryShader* gs)
  : non_copyable()
  , m_handle(gl::ProgramHandle::create())
{
  gl::attachShader(m_handle, vs.getHandle());
  if(gs != nullptr)
  {
    gl::attachShader(m_handle, gs->getHandle());
  }
  gl::attachShader(m_handle, fs.getHandle());
  gl::linkProgram(m_handle);
}

}  // namespace hou
