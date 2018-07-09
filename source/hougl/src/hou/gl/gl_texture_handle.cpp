// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_texture_handle.hpp"

#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/cor/cor_exceptions.hpp"



namespace hou
{

namespace gl
{

namespace
{

// Note: do not change active texture units in scopes where the scoped texture
// binding is used! This would cause incorrect behaviour.
class scoped_texture_binding
{
public:
  scoped_texture_binding(GLenum target, GLuint tex);
  ~scoped_texture_binding();

private:
  GLenum m_target_bkp;
  GLuint m_name_bkp;
};

class scoped_texture_unit_binding
{
public:
  scoped_texture_unit_binding(GLuint unit);
  ~scoped_texture_unit_binding();

private:
  GLuint m_unit_bkp;
};

GLenum to_get_gl_enum(GLenum target);

void get_texture_parameter_iv(
  const texture_handle& tex, GLenum param, GLint* value);

void set_texture_parameter_iv(
  const texture_handle& tex, GLenum param, const GLint* value);

GLint get_texture_parameter_i(const texture_handle& tex, GLenum param);

void set_texture_parameter_i(
  const texture_handle& tex, GLenum param, GLint value);

GLint get_texture_level_parameter_i(
  const texture_handle& tex, GLint level, GLenum param);



scoped_texture_binding::scoped_texture_binding(GLenum target, GLuint tex)
  : m_target_bkp(get_bound_texture_target())
  , m_name_bkp(get_bound_texture_name())
{
  // Set an arbitrary value if no texture is bound.
  if(m_target_bkp == 0)
  {
    m_target_bkp = target;
  }
  glBindTexture(target, tex);
  HOU_GL_CHECK_ERROR();
}



scoped_texture_binding::~scoped_texture_binding()
{
  glBindTexture(m_target_bkp, m_name_bkp);
  HOU_GL_CHECK_ERROR();
}



scoped_texture_unit_binding::scoped_texture_unit_binding(GLuint unit)
  : m_unit_bkp(
      static_cast<GLuint>(get_integer(GL_ACTIVE_TEXTURE) - GL_TEXTURE0))
{
  glActiveTexture(GL_TEXTURE0 + unit);
}



scoped_texture_unit_binding::~scoped_texture_unit_binding()
{
  glActiveTexture(GL_TEXTURE0 + m_unit_bkp);
}



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



void get_texture_parameter_iv(
  const texture_handle& tex, GLenum param, GLint* value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding binding(tex.get_target(), tex.get_name());
    glGetTexParameteriv(tex.get_target(), param, value);
  }
#else
  glGetTextureParameteriv(tex.get_name(), param, value);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_parameter_iv(
  const texture_handle& tex, GLenum param, const GLint* value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding binding(tex.get_target(), tex.get_name());
    glTexParameteriv(tex.get_target(), param, value);
  }
#else
  glTextureParameteriv(tex.get_name(), param, value);
#endif
  HOU_GL_CHECK_ERROR();
}



GLint get_texture_parameter_i(const texture_handle& tex, GLenum param)
{
  GLint value = 0;
  get_texture_parameter_iv(tex, param, &value);
  return value;
}



void set_texture_parameter_i(
  const texture_handle& tex, GLenum param, GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding binding(tex.get_target(), tex.get_name());
    glTexParameteri(tex.get_target(), param, value);
  }
#else
  glTextureParameteri(tex.get_name(), param, value);
#endif
  HOU_GL_CHECK_ERROR();
}



GLint get_texture_level_parameter_i(
  const texture_handle& tex, GLint level, GLenum param)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  GLint value = 0;
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding binding(tex.get_target(), tex.get_name());
    glGetTexLevelParameteriv(tex.get_target(), level, param, &value);
  }
#else
  glGetTextureLevelParameteriv(tex.get_name(), level, param, &value);
#endif
  HOU_GL_CHECK_ERROR();
  return value;
}

}  // namespace



texture_handle texture_handle::create(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = 0u;
#if defined(HOU_GL_ES)
  glGenTextures(1, &name);
#else
  glCreateTextures(target, 1, &name);
#endif
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
    context::get_current()->m_tracking_data.set_bound_texture(0u, 0);
  }
}



void bind_texture(const texture_handle& tex, GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
  if(!is_texture_bound(tex, unit))
  {
#if defined(HOU_GL_ES)
    {
      scoped_texture_unit_binding binding(unit);
      glBindTexture(tex.get_target(), tex.get_name());
    }
#else
    glBindTextureUnit(unit, tex.get_name());
#endif
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
#if defined(HOU_GL_ES)
    {
      scoped_texture_unit_binding binding(unit);
      glBindTexture(GL_TEXTURE_2D, 0u);
    }
#else
    glBindTextureUnit(unit, 0u);
#endif
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_texture(0u, unit, 0);
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



GLenum get_bound_texture_target()
{
    return context::get_current()->m_tracking_data.get_bound_texture_target();
}



GLuint get_bound_texture_name()
{
  GLenum binding_enum = to_get_gl_enum(get_bound_texture_target());
  return binding_enum == 0 ? 0u
                           : static_cast<GLuint>(get_integer(binding_enum));
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
  GLenum internal_format, GLsizei width)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexStorage1D(tex.get_target(), levels, internal_format, width);
  }
#else
  glTextureStorage1D(tex.get_name(), levels, internal_format, width);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_2d(const texture_handle& tex, GLsizei levels,
  GLenum internal_format, GLsizei width, GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexStorage2D(tex.get_target(), levels, internal_format, width, height);
  }
#else
  glTextureStorage2D(tex.get_name(), levels, internal_format, width, height);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_3d(const texture_handle& tex, GLsizei levels,
  GLenum internal_format, GLsizei width, GLsizei height, GLsizei depth)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexStorage3D(
      tex.get_target(), levels, internal_format, width, height, depth);
  }
#else
  glTextureStorage3D(
    tex.get_name(), levels, internal_format, width, height, depth);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_2d_multisample(const texture_handle& tex,
  GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height,
  GLboolean fixed_sample_locations)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexStorage2DMultisample(tex.get_target(), samples, internal_format, width,
      height, fixed_sample_locations);
  }
#else
  glTextureStorage2DMultisample(tex.get_name(), samples, internal_format, width,
    height, fixed_sample_locations);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_storage_3d_multisample(const texture_handle& tex,
  GLsizei samples, GLenum internal_format, GLsizei width, GLsizei height,
  GLsizei depth, GLboolean fixed_sample_locations)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexStorage3DMultisample(tex.get_target(), samples, internal_format, width,
      height, depth, fixed_sample_locations);
  }
#else
  glTextureStorage3DMultisample(tex.get_name(), samples, internal_format, width,
    height, depth, fixed_sample_locations);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_sub_image_1d(const texture_handle& tex, GLint level,
  GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexSubImage1D(
      tex.get_target(), level, xoffset, width, format, type, pixels);
  }
#else
  glTextureSubImage1D(
    tex.get_name(), level, xoffset, width, format, type, pixels);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_sub_image_2d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
  GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexSubImage2D(tex.get_target(), level, xoffset, yoffset, width, height,
      format, type, pixels);
  }
#else
  glTextureSubImage2D(tex.get_name(), level, xoffset, yoffset, width, height,
    format, type, pixels);
#endif
  HOU_GL_CHECK_ERROR();
}



void set_texture_sub_image_3d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height,
  GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glTexSubImage3D(tex.get_target(), level, xoffset, yoffset, zoffset, width,
      height, depth, format, type, pixels);
  }
#else
  glTextureSubImage3D(tex.get_name(), level, xoffset, yoffset, zoffset, width,
    height, depth, format, type, pixels);
#endif
  HOU_GL_CHECK_ERROR();
}



void copy_texture_sub_image_1d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint x, GLint y, GLsizei width)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glCopyTexSubImage1D(tex.get_target(), level, xoffset, x, y, width);
  }
#else
  glCopyTextureSubImage1D(tex.get_name(), level, xoffset, x, y, width);
#endif
  HOU_GL_CHECK_ERROR();
}



void copy_texture_sub_image_2d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glCopyTexSubImage2D(
      tex.get_target(), level, xoffset, yoffset, x, y, width, height);
  }
#else
  glCopyTextureSubImage2D(
    tex.get_name(), level, xoffset, yoffset, x, y, width, height);
#endif
  HOU_GL_CHECK_ERROR();
}



void copy_texture_sub_image_3d(const texture_handle& tex, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width,
  GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glCopyTexSubImage3D(
      tex.get_target(), level, xoffset, yoffset, zoffset, x, y, width, height);
  }
#else
  glCopyTextureSubImage3D(
    tex.get_name(), level, xoffset, yoffset, zoffset, x, y, width, height);
#endif
  HOU_GL_CHECK_ERROR();
}



void get_texture_image(const texture_handle& tex, GLint level, GLenum format,
  GLenum type, GLsizei buf_size, void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding(tex.get_target(), tex.get_name());
    glGetnTexImage(tex.get_target(), level, format, type, buf_size, pixels);
  }
#else
  glGetTextureImage(tex.get_name(), level, format, type, buf_size, pixels);
#endif
  HOU_GL_CHECK_ERROR();
}



#if defined(HOU_GL_ES)
void get_texture_sub_image(const texture_handle&, GLint, GLint, GLint, GLsizei,
  GLsizei, GLsizei, GLint, GLenum, GLenum, GLsizei, void*)
{
  HOU_ERROR_N(unsupported_error, "This function is not supported on GLES.");
}
#else
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
#endif



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
  get_texture_parameter_iv(
    tex, GL_TEXTURE_SWIZZLE_RGBA, reinterpret_cast<GLint*>(swizzle));
}



void set_texture_swizzle_r(const texture_handle& tex, GLenum swizzle)
{
  set_texture_parameter_i(tex, GL_TEXTURE_SWIZZLE_R, swizzle);
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
  set_texture_parameter_iv(
    tex, GL_TEXTURE_SWIZZLE_RGBA, reinterpret_cast<const GLint*>(swizzle));
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
#if defined(HOU_GL_ES)
  {
    scoped_texture_binding binding(tex.get_target(), tex.get_name());
    glGenerateMipmap(tex.get_target());
  }
#else
  glGenerateTextureMipmap(tex.get_name());
#endif
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
