// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_SHADER_HANDLE_HPP
#define HOU_GL_GL_SHADER_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/GlObjectHandle.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API ShaderHandle
  : public SharedObjectHandle
{
public:
  static ShaderHandle create(GLenum type);

  ShaderHandle(ShaderHandle&& other);
  virtual ~ShaderHandle();

  GLenum getType() const;

private:
  ShaderHandle(GLuint name, GLenum type);

private:
  GLenum mType;
};

HOU_GL_API void compileShader(const ShaderHandle& shader, const GLchar* src);

}

}

#endif

