// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_texture_handle.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_functions.hpp"



namespace hou
{

namespace gl
{

namespace
{

GLenum to_get_gl_enum(GLenum target);

GLint get_texture_parameter_i(const texture_handle& tex, GLenum param);

void set_texture_parameter_i(
  const texture_handle& tex, GLenum param, GLint value);

GLint get_texture_level_parameter_i(
  const texture_handle& tex, GLint level, GLenum param);



GLenum to_get_gl_enum(GLenum target)
{
  switch(target)
  {
    case GL_TEXTURE_1D:
      return GL_TEXTURE_BINDING_1D;
    case GL_TEXTURE_2D:
      return GL_TEXTURE_BINDING_2D;
    case GL_TEXTURE_3D:
      return GL_TEXTURE_BINDING_3D;
    case GL_TEXTURE_1D_ARRAY:
      return GL_TEXTURE_BINDING_1D_ARRAY;
    case GL_TEXTURE_2D_ARRAY:
      return GL_TEXTURE_BINDING_2D_ARRAY;
    case GL_TEXTURE_RECTANGLE:
      return GL_TEXTURE_BINDING_RECTANGLE;
    case GL_TEXTURE_CUBE_MAP:
      return GL_TEXTURE_BINDING_CUBE_MAP;
    case GL_TEXTURE_CUBE_MAP_ARRAY:
      return GL_TEXTURE_BINDING_CUBE_MAP_ARRAY;
    case GL_TEXTURE_BUFFER:
      return GL_TEXTURE_BINDING_BUFFER;
    case GL_TEXTURE_2D_MULTISAMPLE:
      return GL_TEXTURE_BINDING_2D_MULTISAMPLE;
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
      return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY;
    default:
      return 0u;
  }
}



GLint get_texture_parameter_i(const texture_handle& tex, GLenum param)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  GLint value;
  glGetTextureParameteriv(tex.get_name(), param, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}



void set_texture_parameter_i(
  const texture_handle& tex, GLenum param, GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureParameteri(tex.get_name(), param, value);
  HOU_GL_CHECK_ERROR();
}



GLint get_texture_level_parameter_i(
  const texture_handle& tex, GLint level, GLenum param)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  GLint value;
  glGetTextureLevelParameteriv(tex.get_name(), level, param, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}

}  // namespace



texture_handle texture_handle::create(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name;
  glCreateTextures(target, 1, &name);
  HOU_GL_CHECK_ERROR();
  return texture_handle(name, target);
}



texture_handle::~texture_handle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = get_name();
  glDeleteTextures(1, &name);
  HOU_GL_CHECK_ERROR();
}



GLenum texture_handle::get_target() const noexcept
{
  return m_target;
}



texture_handle::texture_handle(GLuint name, GLenum target)
  : shared_object_handle(name)
  , m_target(target)
{}



void bind_texture(const texture_handle& tex)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  if(!is_texture_bound(tex))
  {
    glBindTexture(tex.get_target(), tex.get_name());
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_texture(
      tex.get_uid(), tex.get_target());
  }
}



void unbind_texture()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_texture_bound())
  {
    glBindTexture(
      context::get_current()->m_tracking_data.get_bound_texture_target(), 0u);
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_texture(0u, GL_TEXTURE_1D);
  }
}



void bind_texture(const texture_handle& tex, GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  if(!is_texture_bound(tex, unit))
  {
    glBindTextureUnit(unit, tex.get_name());
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_texture(
      tex.get_uid(), unit, tex.get_target());
  }
}



void unbind_texture(GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_texture_bound(unit))
  {
    glBindTextureUnit(unit, 0u);
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_texture(
      0u, unit, GL_TEXTURE_1D);
  }
}



bool is_texture_bound(const texture_handle& tex)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  return context::get_current()->m_tracking_data.get_bound_texture()
    == tex.get_uid();
}



bool is_texture_bound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::get_current()->m_tracking_data.get_bound_texture() != 0u;
}



bool is_texture_bound(const texture_handle& tex, uint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  return context::get_current()->m_tracking_data.get_bound_texture(unit)
    == tex.get_uid();
}



bool is_texture_bound(uint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::get_current()->m_tracking_data.get_bound_texture(unit) != 0u;
}



GLuint get_bound_texture_name()
{
  return static_cast<GLuint>(get_integer(to_get_gl_enum(
    context::get_current()->m_tracking_data.get_bound_texture_target())));
}



void set_active_texture(GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glActiveTexture(GL_TEXTURE0 + unit);
  context::get_current()->m_tracking_data.set_active_texture(unit);
  HOU_GL_CHECK_ERROR();
}



GLuint get_active_texture()
{
  return static_cast<GLuint>(get_integer(GL_ACTIVE_TEXTURE) - GL_TEXTURE0);
}



GLuint get_max_texture_image_units()
{
  return static_cast<GLuint>(get_integer(GL_MAX_TEXTURE_IMAGE_UNITS));
}



void set_texture_storage_1d(const texture_handle& tex, GLsizei levels,
  GLenum internalFormat, GLsizei width)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureStorage1D(tex.get_name(), levels, internalFormat, width);
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_2d(const texture_handle& tex, GLsizei levels,
  GLenum internalFormat, GLsizei width, GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureStorage2D(tex.get_name(), levels, internalFormat, width, height);
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_3d(const texture_handle& tex, GLsizei levels,
  GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureStorage3D(
    tex.get_name(), levels, internalFormat, width, height, depth);
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_2d_multisample(const texture_handle& tex,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLboolean fixed_sample_locations)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureStorage2DMultisample(tex.get_name(), samples, internalFormat, width,
    height, fixed_sample_locations);
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_3d_multisample(const texture_handle& tex,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLsizei depth, GLboolean fixed_sample_locations)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureStorage3DMultisample(tex.get_name(), samples, internalFormat, width,
    height, depth, fixed_sample_locations);
  HOU_GL_CHECK_ERROR();
}



void set_texture_sub_image_1d(const texture_handle& tex, GLint level,
  GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureSubImage1D(
    tex.get_name(), level, xoffset, width, format, type, pixels);
  HOU_GL_CHECK_ERROR();
}



void set_texture_sub_image_2d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
  GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureSubImage2D(tex.get_name(), level, xoffset, yoffset, width, height,
    format, type, pixels);
  HOU_GL_CHECK_ERROR();
}



void set_texture_sub_image_3d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height,
  GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureSubImage3D(tex.get_name(), level, xoffset, yoffset, zoffset, width,
    height, depth, format, type, pixels);
  HOU_GL_CHECK_ERROR();
}



void copy_texture_sub_image_1d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint x, GLint y, GLsizei width)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glCopyTextureSubImage1D(tex.get_name(), level, xoffset, x, y, width);
  HOU_GL_CHECK_ERROR();
}



void copy_texture_sub_image_2d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glCopyTextureSubImage2D(
    tex.get_name(), level, xoffset, yoffset, x, y, width, height);
  HOU_GL_CHECK_ERROR();
}



void copy_texture_sub_image_3d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width,
  GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glCopyTextureSubImage3D(
    tex.get_name(), level, xoffset, yoffset, zoffset, x, y, width, height);
  HOU_GL_CHECK_ERROR();
}



void get_texture_image(const texture_handle& tex, GLint level, GLenum format,
  GLenum type, GLsizei buf_size, void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glGetTextureImage(tex.get_name(), level, format, type, buf_size, pixels);
  HOU_GL_CHECK_ERROR();
}



void get_texture_sub_image(const texture_handle& tex, GLint xoffset,
  GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
  GLint level, GLenum format, GLenum type, GLsizei buf_size, void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glGetTextureSubImage(tex.get_name(), level, xoffset, yoffset, zoffset, width,
    height, depth, format, type, buf_size, pixels);
  HOU_GL_CHECK_ERROR();
}



GLsizei get_texture_width(const texture_handle& handle, GLint level)
{
  return get_texture_level_parameter_i(handle, level, GL_TEXTURE_WIDTH);
}



GLsizei get_texture_width(const texture_handle& handle)
{
  return get_texture_width(handle, 0);
}



GLsizei get_texture_height(const texture_handle& handle, GLint level)
{
  return get_texture_level_parameter_i(handle, level, GL_TEXTURE_HEIGHT);
}



GLsizei get_texture_height(const texture_handle& handle)
{
  return get_texture_height(handle, 0);
}



GLsizei get_texture_depth(const texture_handle& handle, GLint level)
{
  return get_texture_level_parameter_i(handle, level, GL_TEXTURE_DEPTH);
}



GLsizei get_texture_depth(const texture_handle& handle)
{
  return get_texture_depth(handle, 0);
}



GLenum get_texture_format(const texture_handle& handle, GLint level)
{
  return GLenum(
    get_texture_level_parameter_i(handle, level, GL_TEXTURE_INTERNAL_FORMAT));
}



GLint get_texture_base_level(const texture_handle& handle)
{
  return get_texture_parameter_i(handle, GL_TEXTURE_BASE_LEVEL);
}



GLint get_texture_max_level(const texture_handle& handle)
{
  return get_texture_parameter_i(handle, GL_TEXTURE_MAX_LEVEL);
}



GLenum get_texture_format(const texture_handle& handle)
{
  return get_texture_format(handle, 0);
}



GLenum get_texture_min_filter(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_MIN_FILTER);
}



GLenum get_texture_mag_filter(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_MAG_FILTER);
}



void set_texture_min_filter(const texture_handle& tex, GLenum filter)
{
  set_texture_parameter_i(tex, GL_TEXTURE_MIN_FILTER, filter);
}



void set_texture_mag_filter(const texture_handle& tex, GLenum filter)
{
  set_texture_parameter_i(tex, GL_TEXTURE_MAG_FILTER, filter);
}



GLenum get_texture_swizzle_r(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_R);
}



GLenum get_texture_swizzle_g(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_G);
}



GLenum get_texture_swizzle_b(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_B);
}



GLenum get_texture_swizzle_a(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_A);
}



void get_texture_swizzle(const texture_handle& tex, GLenum* swizzle)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glGetTextureParameteriv(
    tex.get_name(), GL_TEXTURE_SWIZZLE_RGBA, reinterpret_cast<GLint*>(swizzle));
  HOU_GL_CHECK_ERROR();
}



void set_texture_swizzle_r(const texture_handle& tex, GLenum swizzle)
{
  set_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_R, swizzle);
  HOU_GL_CHECK_ERROR();
}



void set_texture_swizzle_g(const texture_handle& tex, GLenum swizzle)
{
  set_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_G, swizzle);
}



void set_texture_swizzle_b(const texture_handle& tex, GLenum swizzle)
{
  set_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_B, swizzle);
}



void set_texture_swizzle_a(const texture_handle& tex, GLenum swizzle)
{
  set_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_A, swizzle);
}



void set_texture_swizzle(const texture_handle& tex, const GLenum* swizzle)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glTextureParameteriv(tex.get_name(), GL_TEXTURE_SWIZZLE_RGBA,
    reinterpret_cast<const GLint*>(swizzle));
  HOU_GL_CHECK_ERROR();
}



GLenum get_texture_wrap_mode_s(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_WRAP_S);
}



GLenum get_texture_wrap_mode_t(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_WRAP_T);
}



GLenum get_texture_wrap_mode_r(const texture_handle& tex)
{
  return get_texture_parameter_i(tex, GL_TEXTURE_WRAP_R);
}



void set_texture_wrap_mode_s(const texture_handle& tex, GLenum mode)
{
  set_texture_parameter_i(tex, GL_TEXTURE_WRAP_S, mode);
}



void set_texture_wrap_mode_t(const texture_handle& tex, GLenum mode)
{
  set_texture_parameter_i(tex, GL_TEXTURE_WRAP_T, mode);
}



void set_texture_wrap_mode_r(const texture_handle& tex, GLenum mode)
{
  set_texture_parameter_i(tex, GL_TEXTURE_WRAP_R, mode);
}



void generate_mip_map(const texture_handle& tex)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  glGenerateTextureMipmap(tex.get_name());
  HOU_GL_CHECK_ERROR();
}



GLint get_max_texture_samples()
{
  return get_integer(GL_MAX_SAMPLES);
}



GLint get_max_texture_size()
{
  return get_integer(GL_MAX_TEXTURE_SIZE);
}



GLint get_max_3d_texture_size()
{
  return get_integer(GL_MAX_3D_TEXTURE_SIZE);
}



GLint get_max_texture_layers()
{
  return get_integer(GL_MAX_ARRAY_TEXTURE_LAYERS);
}

}  // namespace gl

}  // namespace hou
