// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_FRAMEBUFFER_HANDLE_HPP
#define HOU_GL_GL_FRAMEBUFFER_HANDLE_HPP

#include "hou/gl/GlExport.hpp"
#include "hou/gl/GlObjectHandle.hpp"



namespace hou
{

namespace gl
{

class TextureHandle;

class HOU_GL_API FramebufferHandle : public NonSharedObjectHandle
{
public:
  static FramebufferHandle create();

  FramebufferHandle(FramebufferHandle&& other);
  virtual ~FramebufferHandle();

private:
  FramebufferHandle(GLuint name);
};

HOU_GL_API void bindFramebuffer(const FramebufferHandle& framebuffer);
HOU_GL_API void bindFramebuffer(
  const FramebufferHandle& framebuffer, GLenum target);
HOU_GL_API void unbindFramebuffer();
HOU_GL_API void unbindFramebuffer(GLenum target);
HOU_GL_API bool isFramebufferBound(
  const FramebufferHandle& framebuffer, GLenum target);
HOU_GL_API bool isFramebufferBound(GLenum target);
HOU_GL_API GLuint getBoundFramebufferName(GLenum target);

HOU_GL_API void setFramebufferColorTexture(const FramebufferHandle& framebuffer,
  GLuint attachment, const TextureHandle& texture, GLint level);
HOU_GL_API void setFramebufferDepthTexture(const FramebufferHandle& framebuffer,
  const TextureHandle& texture, GLint level);
HOU_GL_API void setFramebufferStencilTexture(
  const FramebufferHandle& framebuffer, const TextureHandle& texture,
  GLint level);
HOU_GL_API void setFramebufferDepthStencilTexture(
  const FramebufferHandle& framebuffer, const TextureHandle& texture,
  GLint level);
HOU_GL_API GLenum getFramebufferStatus(const FramebufferHandle& framebuffer);
HOU_GL_API void blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1,
  GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLenum mask,
  GLenum filter);
HOU_GL_API void blitFramebuffer(const FramebufferHandle& src,
  const FramebufferHandle& dst, GLint srcX0, GLint srcY0, GLint srcX1,
  GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLenum mask,
  GLenum filter);
HOU_GL_API GLint getMaxColorAttachments();

}  // namespace gl

}  // namespace hou

#endif
