// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_shader_handle.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/character_encodings.hpp"



namespace hou
{

namespace gl
{

shader_handle shader_handle::create(GLenum type)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = glCreateShader(static_cast<GLenum>(type));
  HOU_GL_CHECK_ERROR();
  return shader_handle(name, type);
}



shader_handle::~shader_handle()
{
  HOU_DISABLE_EXCEPTIONS_BEGIN;
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  glDeleteShader(get_name());
  HOU_GL_CHECK_ERROR();
  HOU_DISABLE_EXCEPTIONS_END;
}



GLenum shader_handle::get_type() const noexcept
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
    HOU_ERROR_N(shader_compiler_error, shd.get_type(), infoLog);
  }
}

}  // namespace gl

}  // namespace hou
