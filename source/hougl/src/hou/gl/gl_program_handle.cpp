// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_program_handle.hpp"

#include "hou/gl/gl_check.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_shader_handle.hpp"

#include "hou/cor/character_encodings.hpp"
#include "hou/cor/error.hpp"



namespace hou
{

namespace gl
{

program_handle program_handle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = glCreateProgram();
  HOU_GL_CHECK_ERROR();
  return program_handle(name);
}



program_handle::program_handle(program_handle&& other)
  : shared_object_handle(std::move(other))
{}



program_handle::~program_handle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  glDeleteProgram(get_name());
  HOU_GL_CHECK_ERROR();
}



program_handle::program_handle(GLuint name)
  : shared_object_handle(name)
{}



void bind_program(const program_handle& program)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  if(!is_program_bound(program))
  {
    glUseProgram(program.get_name());
    HOU_GL_CHECK_ERROR();
    context::getCurrent()->m_tracking_data.set_bound_program(program.get_uid());
  }
}



void unbind_program()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_program_bound())
  {
    glUseProgram(0u);
    HOU_GL_CHECK_ERROR();
    context::getCurrent()->m_tracking_data.set_bound_program(0u);
  }
}



bool is_program_bound(const program_handle& program)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  return context::getCurrent()->m_tracking_data.get_bound_program()
    == program.get_uid();
}



bool is_program_bound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::getCurrent()->m_tracking_data.get_bound_program() != 0u;
}



GLuint get_bound_program_name()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(GL_CURRENT_PROGRAM, &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void attach_shader(
  const program_handle& program, const shader_handle& shd)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glAttachShader(program.get_name(), shd.get_name());
  HOU_GL_CHECK_ERROR();
}



void link_program(const program_handle& program)
{
  static constexpr size_t max_info_log_size = 1024;

  HOU_GL_CHECK_CONTEXT_EXISTENCE();

  glLinkProgram(program.get_name());
  HOU_GL_CHECK_ERROR();

  GLint success = 0;
  glGetProgramiv(program.get_name(), GL_LINK_STATUS, &success);
  HOU_GL_CHECK_ERROR();
  if(success == 0)
  {
    GLchar infoLog[max_info_log_size];
    glGetProgramInfoLog(program.get_name(), max_info_log_size, nullptr, infoLog);
    HOU_GL_CHECK_ERROR();
    HOU_RUNTIME_ERROR(get_text(gl_error::program_linking), infoLog);
  }
}



GLint get_program_uniform_location(
  const program_handle& program, const GLchar* name)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  GLint location = glGetUniformLocation(program.get_name(), name);
  HOU_GL_CHECK_ERROR();
  HOU_RUNTIME_CHECK(
    location != -1, get_text(gl_error::program_invalid_uniform), name);
  return location;
}



void set_program_uniform_i(
  const program_handle& program, GLint location, GLint v0)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform1i(program.get_name(), location, v0);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_i(
  const program_handle& program, GLint location, GLint v0, GLint v1)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform2i(program.get_name(), location, v0, v1);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_i(
  const program_handle& program, GLint location, GLint v0, GLint v1, GLint v2)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform3i(program.get_name(), location, v0, v1, v2);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_i(const program_handle& program, GLint location,
  GLint v0, GLint v1, GLint v2, GLint v3)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform4i(program.get_name(), location, v0, v1, v2, v3);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_u(
  const program_handle& program, GLuint location, GLuint v0)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform1ui(program.get_name(), location, v0);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_u(
  const program_handle& program, GLuint location, GLuint v0, GLuint v1)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform2ui(program.get_name(), location, v0, v1);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_u(const program_handle& program, GLuint location,
  GLuint v0, GLuint v1, GLuint v2)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform3ui(program.get_name(), location, v0, v1, v2);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_u(const program_handle& program, GLuint location,
  GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform4ui(program.get_name(), location, v0, v1, v2, v3);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_f(
  const program_handle& program, GLint location, GLfloat v0)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform1f(program.get_name(), location, v0);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_f(
  const program_handle& program, GLint location, GLfloat v0, GLfloat v1)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform2f(program.get_name(), location, v0, v1);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_f(const program_handle& program, GLint location,
  GLfloat v0, GLfloat v1, GLfloat v2)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform3f(program.get_name(), location, v0, v1, v2);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_f(const program_handle& program, GLint location,
  GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniform4f(program.get_name(), location, v0, v1, v2, v3);
  HOU_GL_CHECK_ERROR();
}



void set_program_uniform_mat4x4f(const program_handle& program, GLint location,
  GLsizei count, GLboolean transpose, const GLfloat* values)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(program);
  glProgramUniformMatrix4fv(
    program.get_name(), location, count, transpose, values);
  HOU_GL_CHECK_ERROR();
}

}  // namespace gl

}  // namespace hou
