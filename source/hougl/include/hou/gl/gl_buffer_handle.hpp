// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_BUFFER_HANDLE_HPP
#define HOU_GL_GL_BUFFER_HANDLE_HPP

#include "hou/gl/gl_object_handle.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API buffer_handle : public shared_object_handle
{
public:
  static buffer_handle create();

  buffer_handle(buffer_handle&& other) noexcept = default;

  virtual ~buffer_handle();

private:
  buffer_handle(GLuint name);
};

HOU_GL_API void bind_buffer(const buffer_handle& buffer, GLenum target);

HOU_GL_API void unbind_buffer(GLenum target);

HOU_GL_API bool is_buffer_bound(const buffer_handle& buffer, GLenum target);

HOU_GL_API bool is_buffer_bound(GLenum target);

HOU_GL_API GLuint get_bound_buffer_name(GLenum target);

HOU_GL_API void set_buffer_storage(const buffer_handle& buffer, GLsizei size,
  const GLvoid* data, GLbitfield flags);

HOU_GL_API void set_buffer_sub_data(const buffer_handle& buffer,
  GLintptr offset, GLsizei size, const GLvoid* data);

HOU_GL_API void get_buffer_sub_data(
  const buffer_handle& buffer, GLintptr offset, GLsizei size, GLvoid* data);

}  // namespace gl

}  // namespace hou

#endif
