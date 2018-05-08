// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_PROGRAM_HANDLE_HPP
#define HOU_GL_GL_PROGRAM_HANDLE_HPP

#include "hou/gl/gl_export.hpp"
#include "hou/gl/gl_object_handle.hpp"



namespace hou
{

namespace gl
{

class shader_handle;

class HOU_GL_API program_handle : public shared_object_handle
{
public:
  static program_handle create();

  program_handle(program_handle&& other) noexcept = default;
  virtual ~program_handle();

private:
  program_handle(GLuint name);
};

HOU_GL_API void bind_program(const program_handle& program);
HOU_GL_API void unbind_program();
HOU_GL_API bool is_program_bound(const program_handle& program);
HOU_GL_API bool is_program_bound();
HOU_GL_API GLuint get_bound_program_name();

HOU_GL_API void attach_shader(
  const program_handle& program, const shader_handle& shd);
HOU_GL_API void link_program(const program_handle& program);

HOU_GL_API GLint get_program_uniform_location(
  const program_handle& program, const GLchar* name);

HOU_GL_API void set_program_uniform_i(
  const program_handle& program, GLint location, GLint v0);
HOU_GL_API void set_program_uniform_i(
  const program_handle& program, GLint location, GLint v0, GLint v1);
HOU_GL_API void set_program_uniform_i(
  const program_handle& program, GLint location, GLint v0, GLint v1, GLint v3);
HOU_GL_API void set_program_uniform_i(const program_handle& program,
  GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
HOU_GL_API void set_program_uniform_u(
  const program_handle& program, GLuint location, GLuint v0);
HOU_GL_API void set_program_uniform_u(
  const program_handle& program, GLuint location, GLuint v0, GLuint v1);
HOU_GL_API void set_program_uniform_u(const program_handle& program,
  GLuint location, GLuint v0, GLuint v1, GLuint v3);
HOU_GL_API void set_program_uniform_u(const program_handle& program,
  GLuint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
HOU_GL_API void set_program_uniform_f(
  const program_handle& program, GLint location, GLfloat v0);
HOU_GL_API void set_program_uniform_f(
  const program_handle& program, GLint location, GLfloat v0, GLfloat v1);
HOU_GL_API void set_program_uniform_f(const program_handle& program,
  GLint location, GLfloat v0, GLfloat v1, GLfloat v3);
HOU_GL_API void set_program_uniform_f(const program_handle& program,
  GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

HOU_GL_API void set_program_uniform_mat4x4f(const program_handle& program,
  GLint location, GLsizei count, GLboolean transpose, const GLfloat* values);

}  // namespace gl

}  // namespace hou

#endif
