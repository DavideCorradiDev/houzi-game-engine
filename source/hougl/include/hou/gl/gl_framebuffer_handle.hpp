// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_FRAMEBUFFER_HANDLE_HPP
#define HOU_GL_GL_FRAMEBUFFER_HANDLE_HPP

#include "hou/gl/gl_object_handle.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

class texture_handle;

class HOU_GL_API framebuffer_handle : public non_shared_object_handle
{
public:
  static framebuffer_handle create();

public:
  framebuffer_handle(framebuffer_handle&& other) noexcept = default;

  virtual ~framebuffer_handle();

private:
  framebuffer_handle(GLuint name);
};

HOU_GL_API void bind_framebuffer(const framebuffer_handle& framebuffer);

HOU_GL_API void bind_framebuffer(
  const framebuffer_handle& framebuffer, GLenum target);

HOU_GL_API void unbind_framebuffer();

HOU_GL_API void unbind_framebuffer(GLenum target);

HOU_GL_API bool is_framebuffer_bound(
  const framebuffer_handle& framebuffer, GLenum target);

HOU_GL_API bool is_framebuffer_bound(GLenum target);

HOU_GL_API GLuint get_bound_framebuffer_name(GLenum target);

HOU_GL_API void set_framebuffer_color_texture(
  const framebuffer_handle& framebuffer, GLuint attachment,
  const texture_handle& tex, GLint level);

HOU_GL_API void set_framebuffer_depth_texture(
  const framebuffer_handle& framebuffer, const texture_handle& tex,
  GLint level);

HOU_GL_API void set_framebuffer_stencil_texture(
  const framebuffer_handle& framebuffer, const texture_handle& tex,
  GLint level);

HOU_GL_API void set_framebuffer_depth_stencil_texture(
  const framebuffer_handle& framebuffer, const texture_handle& tex,
  GLint level);

HOU_GL_API GLenum get_framebuffer_status(const framebuffer_handle& framebuffer);

HOU_GL_API void blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1,
  GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
  GLbitfield mask, GLenum filter);

HOU_GL_API void blit_framebuffer(const framebuffer_handle& src,
  const framebuffer_handle& dst, GLint srcX0, GLint srcY0, GLint srcX1,
  GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
  GLbitfield mask, GLenum filter);

HOU_GL_API GLint get_max_color_attachments();

}  // namespace gl

}  // namespace hou

#endif
