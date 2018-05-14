// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_TEXTURE_HANDLE_HPP
#define HOU_GL_GL_TEXTURE_HANDLE_HPP

#include "hou/gl/gl_object_handle.hpp"

#include "hou/gl/gl_config.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API texture_handle : public shared_object_handle
{
public:
  static texture_handle create(GLenum target);

  texture_handle(texture_handle&& other) noexcept = default;
  virtual ~texture_handle();

  GLenum get_target() const noexcept;

private:
  texture_handle(GLuint name, GLenum target);

private:
  GLenum m_target;
};

HOU_GL_API void bind_texture(const texture_handle& tex);
HOU_GL_API void unbind_texture();
HOU_GL_API bool is_texture_bound(const texture_handle& tex);
HOU_GL_API bool is_texture_bound();

HOU_GL_API void bind_texture(const texture_handle& tex, GLuint unit);
HOU_GL_API void unbind_texture(GLuint unit);
HOU_GL_API bool is_texture_bound(const texture_handle& tex, GLuint unit);
HOU_GL_API bool is_texture_bound(GLuint unit);

HOU_GL_API GLuint get_bound_texture_name();

HOU_GL_API void set_active_texture(GLuint unit);
HOU_GL_API GLuint get_active_texture();
HOU_GL_API GLuint get_max_texture_image_units();

HOU_GL_API void set_texture_storage_1d(const texture_handle& tex,
  GLsizei levels, GLenum internalFormat, GLsizei width);
HOU_GL_API void set_texture_storage_2d(const texture_handle& tex,
  GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height);
HOU_GL_API void set_texture_storage_3d(const texture_handle& tex,
  GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height,
  GLsizei depth);
HOU_GL_API void set_texture_storage_2d_multisample(const texture_handle& tex,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLboolean fixed_sample_locations);
HOU_GL_API void set_texture_storage_3d_multisample(const texture_handle& tex,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLsizei depth, GLboolean fixed_sample_locations);

HOU_GL_API void set_texture_sub_image_1d(const texture_handle& tex, GLint level,
  GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
HOU_GL_API void set_texture_sub_image_2d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
  GLenum type, const void* pixels);
HOU_GL_API void set_texture_sub_image_3d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height,
  GLsizei depth, GLenum format, GLenum type, const void* pixels);

HOU_GL_API void copy_texture_sub_image_1d(const texture_handle& tex,
  GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
HOU_GL_API void copy_texture_sub_image_2d(const texture_handle& tex,
  GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width,
  GLsizei height);
HOU_GL_API void copy_texture_sub_image_3d(const texture_handle& tex,
  GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y,
  GLsizei width, GLsizei height);

HOU_GL_API void get_texture_image(const texture_handle& tex, GLint level,
  GLenum format, GLenum type, GLsizei buf_size, void* pixels);
HOU_GL_API void get_texture_sub_image(const texture_handle& tex, GLint xoffset,
  GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
  GLint level, GLenum format, GLenum type, GLsizei buf_size, void* pixels);

HOU_GL_API GLsizei get_texture_width(const texture_handle& handle, GLint level);
HOU_GL_API GLsizei get_texture_width(const texture_handle& handle);
HOU_GL_API GLsizei get_texture_height(
  const texture_handle& handle, GLint level);
HOU_GL_API GLsizei get_texture_height(const texture_handle& handle);
HOU_GL_API GLsizei get_texture_depth(const texture_handle& handle, GLint level);
HOU_GL_API GLsizei get_texture_depth(const texture_handle& handle);

HOU_GL_API GLenum get_texture_format(const texture_handle& handle, GLint level);
HOU_GL_API GLenum get_texture_format(const texture_handle& handle);

HOU_GL_API GLint get_texture_base_level(const texture_handle& handle);
HOU_GL_API GLint get_texture_max_level(const texture_handle& handle);

HOU_GL_API GLenum get_texture_min_filter(const texture_handle& tex);
HOU_GL_API GLenum get_texture_mag_filter(const texture_handle& tex);
HOU_GL_API void set_texture_min_filter(
  const texture_handle& tex, GLenum filter);
HOU_GL_API void set_texture_mag_filter(
  const texture_handle& tex, GLenum filter);

HOU_GL_API GLenum get_texture_swizzle_r(const texture_handle& tex);
HOU_GL_API GLenum get_texture_swizzle_g(const texture_handle& tex);
HOU_GL_API GLenum get_texture_swizzle_b(const texture_handle& tex);
HOU_GL_API GLenum get_texture_swizzle_a(const texture_handle& tex);
HOU_GL_API void get_texture_swizzle(const texture_handle& tex, GLenum* swizzle);
HOU_GL_API void set_texture_swizzle_r(
  const texture_handle& tex, GLenum swizzle);
HOU_GL_API void set_texture_swizzle_g(
  const texture_handle& tex, GLenum swizzle);
HOU_GL_API void set_texture_swizzle_b(
  const texture_handle& tex, GLenum swizzle);
HOU_GL_API void set_texture_swizzle_a(
  const texture_handle& tex, GLenum swizzle);
HOU_GL_API void set_texture_swizzle(
  const texture_handle& tex, const GLenum* swizzle);

HOU_GL_API GLenum get_texture_wrap_mode_s(const texture_handle& tex);
HOU_GL_API GLenum get_texture_wrap_mode_t(const texture_handle& tex);
HOU_GL_API GLenum get_texture_wrap_mode_r(const texture_handle& tex);
HOU_GL_API void set_texture_wrap_mode_s(const texture_handle& tex, GLenum mode);
HOU_GL_API void set_texture_wrap_mode_t(const texture_handle& tex, GLenum mode);
HOU_GL_API void set_texture_wrap_mode_r(const texture_handle& tex, GLenum mode);

HOU_GL_API void generate_mip_map(const texture_handle& tex);

HOU_GL_API GLint get_texture_samples(const texture_handle& tex);
HOU_GL_API

HOU_GL_API GLint get_max_texture_samples();
HOU_GL_API GLint get_max_texture_size();
HOU_GL_API GLint get_max_3d_texture_size();
HOU_GL_API GLint get_max_texture_layers();

}  // namespace gl

}  // namespace hou

#endif
