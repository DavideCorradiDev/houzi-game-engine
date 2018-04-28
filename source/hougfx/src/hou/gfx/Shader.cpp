// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Shader.hpp"

#include <utility>



namespace hou
{

Shader::Shader(const std::string& source, ShaderType type)
  : non_copyable()
  , m_handle(gl::ShaderHandle::create(static_cast<GLenum>(type)))
{
  gl::compileShader(m_handle, source.c_str());
}



Shader::Shader(Shader&& other)
  : non_copyable()
  , m_handle(std::move(other.m_handle))
{}



Shader::~Shader()
{}



const gl::ShaderHandle& Shader::getHandle() const
{
  return m_handle;
}



template <ShaderType type>
ShaderTemplate<type>::ShaderTemplate(const std::string& source)
  : Shader(source, type)
{}



template <ShaderType type>
ShaderTemplate<type>::ShaderTemplate(ShaderTemplate&& other)
  : Shader(std::move(other))
{}


template class ShaderTemplate<ShaderType::Vertex>;
template class ShaderTemplate<ShaderType::Fragment>;
template class ShaderTemplate<ShaderType::Geometry>;

}  // namespace hou
