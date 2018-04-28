// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlShaderHandle.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlError.hpp"

#include "hou/cor/Error.hpp"
#include "hou/cor/character_encodings.hpp"



namespace hou
{

namespace gl
{

namespace
{

std::string shaderTypeToString(GLenum type)
{
  switch(type)
  {
  case GL_COMPUTE_SHADER:
    return "Compute";
  case GL_FRAGMENT_SHADER:
    return "Fragment";
  case GL_GEOMETRY_SHADER:
    return "Geometry";
  case GL_TESS_CONTROL_SHADER:
    return "TessControl";
  case GL_TESS_EVALUATION_SHADER:
    return "TessEvaluation";
  case GL_VERTEX_SHADER:
    return "Vertex";
  default:
    return "";
  }
}

}



ShaderHandle ShaderHandle::create(GLenum type)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = glCreateShader(static_cast<GLenum>(type));
  HOU_GL_CHECK_ERROR();
  return ShaderHandle(name, type);
}



ShaderHandle::ShaderHandle(ShaderHandle&& other)
  : SharedObjectHandle(std::move(other))
  , mType(other.mType)
{}



ShaderHandle::~ShaderHandle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  glDeleteShader(getName());
  HOU_GL_CHECK_ERROR();
}



GLenum ShaderHandle::getType() const
{
  return mType;
}



ShaderHandle::ShaderHandle(GLuint name, GLenum type)
  : SharedObjectHandle(name)
  , mType(type)
{}



void compileShader(const ShaderHandle& shader, const GLchar* src)
{
  static constexpr size_t maxInfoLogSize = 1024;

  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(shader);

  glShaderSource(shader.getName(), 1, &src, nullptr);
  HOU_GL_CHECK_ERROR();
  glCompileShader(shader.getName());
  HOU_GL_CHECK_ERROR();

  GLint success = 0;
  glGetShaderiv(shader.getName(), GL_COMPILE_STATUS, &success);
  HOU_GL_CHECK_ERROR();
  if(success == 0)
  {
    GLchar infoLog[maxInfoLogSize];
    glGetShaderInfoLog(shader.getName(), maxInfoLogSize, nullptr, infoLog);
    HOU_GL_CHECK_ERROR();
    HOU_RUNTIME_ERROR(getText(GlError::ShaderCompilation)
      , shaderTypeToString(shader.getType()).c_str(), infoLog);
  }
}

}

}

