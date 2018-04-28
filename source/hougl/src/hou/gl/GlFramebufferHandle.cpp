// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlFramebufferHandle.hpp"

#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlTextureHandle.hpp"
#include "hou/gl/GlFunctions.hpp"



namespace hou
{

namespace gl
{

namespace
{

GLenum toGetGLenum(GLenum target);



GLenum toGetGLenum(GLenum target)
{
  switch(target)
  {
  case GL_DRAW_FRAMEBUFFER:
    return GL_DRAW_FRAMEBUFFER_BINDING;
  case GL_READ_FRAMEBUFFER:
    return GL_READ_FRAMEBUFFER_BINDING;
  default:
    return 0u;
  }
}

}  // namespace



FramebufferHandle FramebufferHandle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name;
  glCreateFramebuffers(1, &name);
  HOU_GL_CHECK_ERROR();
  return FramebufferHandle(name);
}



FramebufferHandle::FramebufferHandle(FramebufferHandle&& other)
  : NonSharedObjectHandle(std::move(other))
{}



FramebufferHandle::~FramebufferHandle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = getName();
  glDeleteFramebuffers(1, &name);
  HOU_GL_CHECK_ERROR();
}



FramebufferHandle::FramebufferHandle(GLuint name)
  : NonSharedObjectHandle(name)
{}



void bindFramebuffer(const FramebufferHandle& framebuffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  if(!isFramebufferBound(framebuffer, GL_DRAW_FRAMEBUFFER)
    || !isFramebufferBound(framebuffer, GL_READ_FRAMEBUFFER))
  {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundFramebuffer(
      framebuffer.get_uid(), GL_DRAW_FRAMEBUFFER);
    Context::getCurrent()->mTrackingData.setBoundFramebuffer(
      framebuffer.get_uid(), GL_READ_FRAMEBUFFER);
  }
}



void bindFramebuffer(const FramebufferHandle& framebuffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  if(!isFramebufferBound(framebuffer, target))
  {
    glBindFramebuffer(target, framebuffer.getName());
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundFramebuffer(
      framebuffer.get_uid(), target);
  }
}


void unbindFramebuffer()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isFramebufferBound(GL_DRAW_FRAMEBUFFER)
    || isFramebufferBound(GL_READ_FRAMEBUFFER))
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundFramebuffer(
      0u, GL_DRAW_FRAMEBUFFER);
    Context::getCurrent()->mTrackingData.setBoundFramebuffer(
      0u, GL_READ_FRAMEBUFFER);
  }
}



void unbindFramebuffer(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(isFramebufferBound(target))
  {
    glBindFramebuffer(target, 0u);
    HOU_GL_CHECK_ERROR();
    Context::getCurrent()->mTrackingData.setBoundFramebuffer(0u, target);
  }
}



bool isFramebufferBound(const FramebufferHandle& framebuffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  return Context::getCurrent()->mTrackingData.getBoundFramebuffer(target)
    == framebuffer.get_uid();
}



bool isFramebufferBound(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return Context::getCurrent()->mTrackingData.getBoundFramebuffer(target) != 0u;
}



GLuint getBoundFramebufferName(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLint name;
  glGetIntegerv(toGetGLenum(target), &name);
  HOU_GL_CHECK_ERROR();
  return static_cast<GLuint>(name);
}



void setFramebufferColorTexture(const FramebufferHandle& framebuffer,
  GLuint attachment, const TextureHandle& texture, GLint level)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glNamedFramebufferTexture(framebuffer.getName(),
    GL_COLOR_ATTACHMENT0 + attachment, texture.getName(), level);
  HOU_GL_CHECK_ERROR();
}



void setFramebufferDepthTexture(const FramebufferHandle& framebuffer,
  const TextureHandle& texture, GLint level)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glNamedFramebufferTexture(
    framebuffer.getName(), GL_DEPTH_ATTACHMENT, texture.getName(), level);
  HOU_GL_CHECK_ERROR();
}



void setFramebufferStencilTexture(const FramebufferHandle& framebuffer,
  const TextureHandle& texture, GLint level)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glNamedFramebufferTexture(
    framebuffer.getName(), GL_STENCIL_ATTACHMENT, texture.getName(), level);
  HOU_GL_CHECK_ERROR();
}



void setFramebufferDepthStencilTexture(const FramebufferHandle& framebuffer,
  const TextureHandle& texture, GLint level)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(texture);
  glNamedFramebufferTexture(framebuffer.getName(), GL_DEPTH_STENCIL_ATTACHMENT,
    texture.getName(), level);
  HOU_GL_CHECK_ERROR();
}



GLenum getFramebufferStatus(const FramebufferHandle& framebuffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  GLenum status
    = glCheckNamedFramebufferStatus(framebuffer.getName(), GL_FRAMEBUFFER);
  HOU_GL_CHECK_ERROR();
  return status;
}



void blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
  GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask,
  GLenum filter)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlitFramebuffer(
    srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  HOU_GL_CHECK_ERROR();
}



void blitFramebuffer(const FramebufferHandle& src, const FramebufferHandle& dst,
  GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,
  GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(src);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(dst);
  glBlitNamedFramebuffer(src.getName(), dst.getName(), srcX0, srcY0, srcX1,
    srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  HOU_GL_CHECK_ERROR();
}

GLint getMaxColorAttachments()
{
  return getInteger(GL_MAX_COLOR_ATTACHMENTS);
}

}  // namespace gl

}  // namespace hou
