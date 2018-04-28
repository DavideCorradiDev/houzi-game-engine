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
  gl::bindProgram(program.mHandle);
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
  , mHandle(std::move(other.mHandle))
{}



ShaderProgram::~ShaderProgram()
{}



const gl::ProgramHandle& ShaderProgram::getHandle() const
{
  return mHandle;
}



bool ShaderProgram::isBound() const
{
  return gl::isProgramBound(mHandle);
}



uint ShaderProgram::getUniformLocation(const std::string& uniformName) const
{
  return static_cast<uint>(
    gl::getProgramUniformLocation(mHandle, uniformName.c_str()));
}



ShaderProgram::ShaderProgram(
  const VertexShader& vs, const FragmentShader& fs, const GeometryShader* gs)
  : non_copyable()
  , mHandle(gl::ProgramHandle::create())
{
  gl::attachShader(mHandle, vs.getHandle());
  if(gs != nullptr)
  {
    gl::attachShader(mHandle, gs->getHandle());
  }
  gl::attachShader(mHandle, fs.getHandle());
  gl::linkProgram(mHandle);
}

}  // namespace hou
