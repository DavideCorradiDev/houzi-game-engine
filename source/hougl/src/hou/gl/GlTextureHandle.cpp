// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlTextureHandle.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlFunctions.hpp"



namespace hou
{

namespace gl
{

namespace
{

GLenum toGetGLenum(GLenum target);
GLint getTextureParameteri(const TextureHandle& texture, GLenum param);
void setTextureParameteri(
  const TextureHandle& texture, GLenum param, GLint value);
GLint getTextureLevelParameteri(
  const TextureHandle& texture, GLint level, GLenum param);



GLenum toGetGLenum(GLenum target)
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



GLint getTextureParameteri(const TextureHandle& texture, GLenum param)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  GLint value;
  glGetTextureParameteriv(texture.getName(), param, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}



void setTextureParameteri(
  const TextureHandle& texture, GLenum param, GLint value)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureParameteri(texture.getName(), param, value);
  HOU_GL_CHECK_ERROR();
}



GLint getTextureLevelParameteri(
  const TextureHandle& texture, GLint level, GLenum param)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  GLint value;
  glGetTextureLevelParameteriv(texture.getName(), level, param, &value);
  HOU_GL_CHECK_ERROR();
  return value;
}

}  // namespace



TextureHandle TextureHandle::create(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name;
  glCreateTextures(target, 1, &name);
  HOU_GL_CHECK_ERROR();
  return TextureHandle(name, target);
}



TextureHandle::TextureHandle(TextureHandle&& other)
  : SharedObjectHandle(std::move(other))
  , mTarget(other.mTarget)
{}



TextureHandle::~TextureHandle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = getName();
  glDeleteTextures(1, &name);
  HOU_GL_CHECK_ERROR();
}



GLenum TextureHandle::getTarget() const
{
  return mTarget;
}



TextureHandle::TextureHandle(GLuint name, GLenum target)
  : SharedObjectHandle(name)
  , mTarget(target)
{}



void bindTexture(const TextureHandle& texture)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  if(!isTextureBound(texture))
  {
    glBindTexture(texture.getTarget(), texture.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundTexture(
      texture.get_uid(), texture.getTarget());
  }
}



void unbindTexture()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isTextureBound())
  {
    glBindTexture(
      Context::getCurrent()->mTrackingData.getBoundTextureTarget(), 0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundTexture(0u, GL_TEXTURE_1D);
  }
}



void bindTexture(const TextureHandle& texture, GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  if(!isTextureBound(texture, unit))
  {
    glBindTextureUnit(unit, texture.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundTexture(
      texture.get_uid(), unit, texture.getTarget());
  }
}



void unbindTexture(GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isTextureBound(unit))
  {
    glBindTextureUnit(unit, 0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundTexture(
      0u, unit, GL_TEXTURE_1D);
  }
}



bool isTextureBound(const TextureHandle& texture)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  return Context::getCurrent()->mTrackingData.getBoundTexture()
    == texture.get_uid();
}



bool isTextureBound()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return Context::getCurrent()->mTrackingData.getBoundTexture() != 0u;
}



bool isTextureBound(const TextureHandle& texture, uint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  return Context::getCurrent()->mTrackingData.getBoundTexture(unit)
    == texture.get_uid();
}



bool isTextureBound(uint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return Context::getCurrent()->mTrackingData.getBoundTexture(unit) != 0u;
}



GLuint getBoundTextureName()
{
  return static_cast<GLuint>(getInteger(
    toGetGLenum(Context::getCurrent()->mTrackingData.getBoundTextureTarget())));
}



void setActiveTexture(GLuint unit)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glActiveTexture(GL_TEXTURE0 + unit);
  Context::getCurrent()->mTrackingData.setActiveTexture(unit);
  HOU_GL_CHECK_ERROR();
}



GLuint getActiveTexture()
{
  return static_cast<GLuint>(getInteger(GL_ACTIVE_TEXTURE) - GL_TEXTURE0);
}



GLuint getMaxTextureImageUnits()
{
  return static_cast<GLuint>(getInteger(GL_MAX_TEXTURE_IMAGE_UNITS));
}



void setTextureStorage1d(const TextureHandle& texture, GLsizei levels,
  GLenum internalFormat, GLsizei width)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureStorage1D(texture.getName(), levels, internalFormat, width);
  HOU_GL_CHECK_ERROR();
}



void setTextureStorage2d(const TextureHandle& texture, GLsizei levels,
  GLenum internalFormat, GLsizei width, GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureStorage2D(texture.getName(), levels, internalFormat, width, height);
  HOU_GL_CHECK_ERROR();
}



void setTextureStorage3d(const TextureHandle& texture, GLsizei levels,
  GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureStorage3D(
    texture.getName(), levels, internalFormat, width, height, depth);
  HOU_GL_CHECK_ERROR();
}



void setTextureStorage2dMultisample(const TextureHandle& texture,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLboolean fixedSampleLocations)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureStorage2DMultisample(texture.getName(), samples, internalFormat,
    width, height, fixedSampleLocations);
  HOU_GL_CHECK_ERROR();
}



void setTextureStorage3dMultisample(const TextureHandle& texture,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLsizei depth, GLboolean fixedSampleLocations)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureStorage3DMultisample(texture.getName(), samples, internalFormat,
    width, height, depth, fixedSampleLocations);
  HOU_GL_CHECK_ERROR();
}



void setTextureSubImage1d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureSubImage1D(
    texture.getName(), level, xoffset, width, format, type, pixels);
  HOU_GL_CHECK_ERROR();
}



void setTextureSubImage2d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
  GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureSubImage2D(texture.getName(), level, xoffset, yoffset, width, height,
    format, type, pixels);
  HOU_GL_CHECK_ERROR();
}



void setTextureSubImage3d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height,
  GLsizei depth, GLenum format, GLenum type, const void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureSubImage3D(texture.getName(), level, xoffset, yoffset, zoffset,
    width, height, depth, format, type, pixels);
  HOU_GL_CHECK_ERROR();
}



void copyTextureSubImage1d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint x, GLint y, GLsizei width)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glCopyTextureSubImage1D(texture.getName(), level, xoffset, x, y, width);
  HOU_GL_CHECK_ERROR();
}



void copyTextureSubImage2d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glCopyTextureSubImage2D(
    texture.getName(), level, xoffset, yoffset, x, y, width, height);
  HOU_GL_CHECK_ERROR();
}



void copyTextureSubImage3d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width,
  GLsizei height)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glCopyTextureSubImage3D(
    texture.getName(), level, xoffset, yoffset, zoffset, x, y, width, height);
  HOU_GL_CHECK_ERROR();
}



void getTextureImage(const TextureHandle& texture, GLint level, GLenum format,
  GLenum type, GLsizei bufSize, void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glGetTextureImage(texture.getName(), level, format, type, bufSize, pixels);
  HOU_GL_CHECK_ERROR();
}



void getTextureSubImage(const TextureHandle& texture, GLint xoffset,
  GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
  GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glGetTextureSubImage(texture.getName(), level, xoffset, yoffset, zoffset,
    width, height, depth, format, type, bufSize, pixels);
  HOU_GL_CHECK_ERROR();
}



GLsizei getTextureWidth(const TextureHandle& handle, GLint level)
{
  return getTextureLevelParameteri(handle, level, GL_TEXTURE_WIDTH);
}



GLsizei getTextureWidth(const TextureHandle& handle)
{
  return getTextureWidth(handle, 0);
}



GLsizei getTextureHeight(const TextureHandle& handle, GLint level)
{
  return getTextureLevelParameteri(handle, level, GL_TEXTURE_HEIGHT);
}



GLsizei getTextureHeight(const TextureHandle& handle)
{
  return getTextureHeight(handle, 0);
}



GLsizei getTextureDepth(const TextureHandle& handle, GLint level)
{
  return getTextureLevelParameteri(handle, level, GL_TEXTURE_DEPTH);
}



GLsizei getTextureDepth(const TextureHandle& handle)
{
  return getTextureDepth(handle, 0);
}



GLenum getTextureFormat(const TextureHandle& handle, GLint level)
{
  return GLenum(
    getTextureLevelParameteri(handle, level, GL_TEXTURE_INTERNAL_FORMAT));
}



GLint getTextureBaseLevel(const TextureHandle& handle)
{
  return getTextureParameteri(handle, GL_TEXTURE_BASE_LEVEL);
}



GLint getTextureMaxLevel(const TextureHandle& handle)
{
  return getTextureParameteri(handle, GL_TEXTURE_MAX_LEVEL);
}



GLenum getTextureFormat(const TextureHandle& handle)
{
  return getTextureFormat(handle, 0);
}



GLenum getTextureMinFilter(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_MIN_FILTER);
}



GLenum getTextureMagFilter(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_MAG_FILTER);
}



void setTextureMinFilter(const TextureHandle& texture, GLenum filter)
{
  setTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, filter);
}



void setTextureMagFilter(const TextureHandle& texture, GLenum filter)
{
  setTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, filter);
}



GLenum getTextureSwizzleR(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_SWIZZLE_R);
}



GLenum getTextureSwizzleG(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_SWIZZLE_G);
}



GLenum getTextureSwizzleB(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_SWIZZLE_B);
}



GLenum getTextureSwizzleA(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_SWIZZLE_A);
}



void getTextureSwizzle(const TextureHandle& texture, GLenum* swizzle)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glGetTextureParameteriv(texture.getName(), GL_TEXTURE_SWIZZLE_RGBA,
    reinterpret_cast<GLint*>(swizzle));
  HOU_GL_CHECK_ERROR();
}



void setTextureSwizzleR(const TextureHandle& texture, GLenum swizzle)
{
  setTextureParameteri(texture, GL_TEXTURE_SWIZZLE_R, swizzle);
  HOU_GL_CHECK_ERROR();
}



void setTextureSwizzleG(const TextureHandle& texture, GLenum swizzle)
{
  setTextureParameteri(texture, GL_TEXTURE_SWIZZLE_G, swizzle);
}



void setTextureSwizzleB(const TextureHandle& texture, GLenum swizzle)
{
  setTextureParameteri(texture, GL_TEXTURE_SWIZZLE_B, swizzle);
}



void setTextureSwizzleA(const TextureHandle& texture, GLenum swizzle)
{
  setTextureParameteri(texture, GL_TEXTURE_SWIZZLE_A, swizzle);
}



void setTextureSwizzle(const TextureHandle& texture, const GLenum* swizzle)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glTextureParameteriv(texture.getName(), GL_TEXTURE_SWIZZLE_RGBA,
    reinterpret_cast<const GLint*>(swizzle));
  HOU_GL_CHECK_ERROR();
}



GLenum getTextureWrapModeS(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_WRAP_S);
}



GLenum getTextureWrapModeT(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_WRAP_T);
}



GLenum getTextureWrapModeR(const TextureHandle& texture)
{
  return getTextureParameteri(texture, GL_TEXTURE_WRAP_R);
}



void setTextureWrapModeS(const TextureHandle& texture, GLenum mode)
{
  setTextureParameteri(texture, GL_TEXTURE_WRAP_S, mode);
}



void setTextureWrapModeT(const TextureHandle& texture, GLenum mode)
{
  setTextureParameteri(texture, GL_TEXTURE_WRAP_T, mode);
}



void setTextureWrapModeR(const TextureHandle& texture, GLenum mode)
{
  setTextureParameteri(texture, GL_TEXTURE_WRAP_R, mode);
}



void generateMipMap(const TextureHandle& texture)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glGenerateTextureMipmap(texture.getName());
  HOU_GL_CHECK_ERROR();
}



GLint getMaxTextureSamples()
{
  return getInteger(GL_MAX_SAMPLES);
}



GLint getMaxTextureSize()
{
  return getInteger(GL_MAX_TEXTURE_SIZE);
}



GLint getMax3dTextureSize()
{
  return getInteger(GL_MAX_3D_TEXTURE_SIZE);
}



GLint getMaxTextureLayers()
{
  return getInteger(GL_MAX_ARRAY_TEXTURE_LAYERS);
}

}  // namespace gl

}  // namespace hou
