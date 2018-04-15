// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/Shader.hpp"

#include <utility>



namespace hou
{

Shader::Shader(const std::string& source, ShaderType type)
  : NonCopyable()
  , mHandle(gl::ShaderHandle::create(static_cast<GLenum>(type)))
{
  gl::compileShader(mHandle, source.c_str());
}



Shader::Shader(Shader&& other)
  : NonCopyable()
  , mHandle(std::move(other.mHandle))
{}



Shader::~Shader()
{}



const gl::ShaderHandle& Shader::getHandle() const
{
  return mHandle;
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
