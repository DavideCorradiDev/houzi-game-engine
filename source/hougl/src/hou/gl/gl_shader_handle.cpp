// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_shader_handle.hpp"

#include "hou/gl/gl_check.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_error.hpp"

#include "hou/cor/character_encodings.hpp"
#include "hou/cor/error.hpp"



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
      return "fragment";
    case GL_GEOMETRY_SHADER:
      return "geometry";
    case GL_TESS_CONTROL_SHADER:
      return "TessControl";
    case GL_TESS_EVALUATION_SHADER:
      return "TessEvaluation";
    case GL_VERTEX_SHADER:
      return "vertex";
    default:
      return "";
  }
}

}  // namespace



shader_handle shader_handle::create(GLenum type)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = glCreateShader(static_cast<GLenum>(type));
  HOU_GL_CHECK_ERROR();
  return shader_handle(name, type);
}



shader_handle::shader_handle(shader_handle&& other)
  : shared_object_handle(std::move(other))
  , m_type(other.m_type)
{}



shader_handle::~shader_handle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  glDeleteShader(get_name());
  HOU_GL_CHECK_ERROR();
}



GLenum shader_handle::get_type() const
{
  return m_type;
}



shader_handle::shader_handle(GLuint name, GLenum type)
  : shared_object_handle(name)
  , m_type(type)
{}



void compile_shader(const shader_handle& shd, const GLchar* src)
{
  static constexpr size_t maxInfoLogSize = 1024;

  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(shd);

  glShaderSource(shd.get_name(), 1, &src, nullptr);
  HOU_GL_CHECK_ERROR();
  glCompileShader(shd.get_name());
  HOU_GL_CHECK_ERROR();

  GLint success = 0;
  glGetShaderiv(shd.get_name(), GL_COMPILE_STATUS, &success);
  HOU_GL_CHECK_ERROR();
  if(success == 0)
  {
    GLchar infoLog[maxInfoLogSize];
    glGetShaderInfoLog(shd.get_name(), maxInfoLogSize, nullptr, infoLog);
    HOU_GL_CHECK_ERROR();
    HOU_RUNTIME_ERROR(get_text(gl_error::shader_compilation),
      shaderTypeToString(shd.get_type()).c_str(), infoLog);
  }
}

}  // namespace gl

}  // namespace hou
