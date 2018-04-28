// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_TEXTURE_HANDLE_HPP
#define HOU_GL_GL_TEXTURE_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/GlObjectHandle.hpp"



namespace hou
{

namespace gl
{

class HOU_GL_API TextureHandle : public SharedObjectHandle
{
public:
  static TextureHandle create(GLenum target);

  TextureHandle(TextureHandle&& other);
  virtual ~TextureHandle();

  GLenum getTarget() const;

private:
  TextureHandle(GLuint name, GLenum target);

private:
  GLenum mTarget;
};

HOU_GL_API void bindTexture(const TextureHandle& texture);
HOU_GL_API void unbindTexture();
HOU_GL_API bool isTextureBound(const TextureHandle& texture);
HOU_GL_API bool isTextureBound();

HOU_GL_API void bindTexture(const TextureHandle& texture, GLuint unit);
HOU_GL_API void unbindTexture(GLuint unit);
HOU_GL_API bool isTextureBound(const TextureHandle& texture, GLuint unit);
HOU_GL_API bool isTextureBound(GLuint unit);

HOU_GL_API GLuint getBoundTextureName();

HOU_GL_API void setActiveTexture(GLuint unit);
HOU_GL_API GLuint getActiveTexture();
HOU_GL_API GLuint getMaxTextureImageUnits();

HOU_GL_API void setTextureStorage1d(const TextureHandle& texture,
  GLsizei levels, GLenum internalFormat, GLsizei width);
HOU_GL_API void setTextureStorage2d(const TextureHandle& texture,
  GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height);
HOU_GL_API void setTextureStorage3d(const TextureHandle& texture,
  GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height,
  GLsizei depth);
HOU_GL_API void setTextureStorage2dMultisample(const TextureHandle& texture,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLboolean fixedSampleLocations);
HOU_GL_API void setTextureStorage3dMultisample(const TextureHandle& texture,
  GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height,
  GLsizei depth, GLboolean fixedSampleLocations);

HOU_GL_API void setTextureSubImage1d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
HOU_GL_API void setTextureSubImage2d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format,
  GLenum type, const void* pixels);
HOU_GL_API void setTextureSubImage3d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height,
  GLsizei depth, GLenum format, GLenum type, const void* pixels);

HOU_GL_API void copyTextureSubImage1d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint x, GLint y, GLsizei width);
HOU_GL_API void copyTextureSubImage2d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width,
  GLsizei height);
HOU_GL_API void copyTextureSubImage3d(const TextureHandle& texture, GLint level,
  GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width,
  GLsizei height);

HOU_GL_API void getTextureImage(const TextureHandle& texture, GLint level,
  GLenum format, GLenum type, GLsizei bufSize, void* pixels);
HOU_GL_API void getTextureSubImage(const TextureHandle& texture, GLint xoffset,
  GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
  GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels);

HOU_GL_API GLsizei getTextureWidth(const TextureHandle& handle, GLint level);
HOU_GL_API GLsizei getTextureWidth(const TextureHandle& handle);
HOU_GL_API GLsizei getTextureHeight(const TextureHandle& handle, GLint level);
HOU_GL_API GLsizei getTextureHeight(const TextureHandle& handle);
HOU_GL_API GLsizei getTextureDepth(const TextureHandle& handle, GLint level);
HOU_GL_API GLsizei getTextureDepth(const TextureHandle& handle);

HOU_GL_API GLenum getTextureFormat(const TextureHandle& handle, GLint level);
HOU_GL_API GLenum getTextureFormat(const TextureHandle& handle);

HOU_GL_API GLint getTextureBaseLevel(const TextureHandle& handle);
HOU_GL_API GLint getTextureMaxLevel(const TextureHandle& handle);

HOU_GL_API GLenum getTextureMinFilter(const TextureHandle& texture);
HOU_GL_API GLenum getTextureMagFilter(const TextureHandle& texture);
HOU_GL_API void setTextureMinFilter(
  const TextureHandle& texture, GLenum filter);
HOU_GL_API void setTextureMagFilter(
  const TextureHandle& texture, GLenum filter);

HOU_GL_API GLenum getTextureSwizzleR(const TextureHandle& texture);
HOU_GL_API GLenum getTextureSwizzleG(const TextureHandle& texture);
HOU_GL_API GLenum getTextureSwizzleB(const TextureHandle& texture);
HOU_GL_API GLenum getTextureSwizzleA(const TextureHandle& texture);
HOU_GL_API void getTextureSwizzle(
  const TextureHandle& texture, GLenum* swizzle);
HOU_GL_API void setTextureSwizzleR(
  const TextureHandle& texture, GLenum swizzle);
HOU_GL_API void setTextureSwizzleG(
  const TextureHandle& texture, GLenum swizzle);
HOU_GL_API void setTextureSwizzleB(
  const TextureHandle& texture, GLenum swizzle);
HOU_GL_API void setTextureSwizzleA(
  const TextureHandle& texture, GLenum swizzle);
HOU_GL_API void setTextureSwizzle(
  const TextureHandle& texture, const GLenum* swizzle);

HOU_GL_API GLenum getTextureWrapModeS(const TextureHandle& texture);
HOU_GL_API GLenum getTextureWrapModeT(const TextureHandle& texture);
HOU_GL_API GLenum getTextureWrapModeR(const TextureHandle& texture);
HOU_GL_API void setTextureWrapModeS(const TextureHandle& texture, GLenum mode);
HOU_GL_API void setTextureWrapModeT(const TextureHandle& texture, GLenum mode);
HOU_GL_API void setTextureWrapModeR(const TextureHandle& texture, GLenum mode);

HOU_GL_API void generateMipMap(const TextureHandle& texture);

HOU_GL_API GLint getTextureSamples(const TextureHandle& texture);
HOU_GL_API

HOU_GL_API GLint getMaxTextureSamples();
HOU_GL_API GLint getMaxTextureSize();
HOU_GL_API GLint getMax3dTextureSize();
HOU_GL_API GLint getMaxTextureLayers();

}  // namespace gl

}  // namespace hou

#endif
