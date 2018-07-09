// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_framebuffer_handle.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_invalid_context_error.hpp"
#include "hou/gl/gl_missing_context_error.hpp"
#include "hou/gl/gl_texture_handle.hpp"



namespace hou
{

namespace gl
{

namespace
{

class scoped_framebuffer_binding
{
public:
  scoped_framebuffer_binding(GLuint draw_fb, GLuint read_fb);
  ~scoped_framebuffer_binding();

private:
  GLuint m_draw_fb_bkp;
  GLuint m_read_fb_bkp;
};

GLenum to_get_gl_enum(GLenum target);

void set_framebuffer_texture(const framebuffer_handle& framebuffer,
  GLenum attachment, const texture_handle& tex, GLint level);



scoped_framebuffer_binding::scoped_framebuffer_binding(
  GLuint draw_fb, GLuint read_fb)
  : m_draw_fb_bkp(get_bound_framebuffer_name(GL_DRAW_FRAMEBUFFER))
  , m_read_fb_bkp(get_bound_framebuffer_name(GL_READ_FRAMEBUFFER))
{
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_fb);
  HOU_GL_CHECK_ERROR();
  glBindFramebuffer(GL_READ_FRAMEBUFFER, read_fb);
  HOU_GL_CHECK_ERROR();
}



scoped_framebuffer_binding::~scoped_framebuffer_binding()
{
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_draw_fb_bkp);
  HOU_GL_CHECK_ERROR();
  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_read_fb_bkp);
  HOU_GL_CHECK_ERROR();
}



GLenum to_get_gl_enum(GLenum target)
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

void set_framebuffer_texture(const framebuffer_handle& framebuffer,
  GLenum attachment, const texture_handle& tex, GLint level)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(tex);
#if defined(HOU_GL_ES)
  {
    scoped_framebuffer_binding(framebuffer.get_name(), framebuffer.get_name());
    glFramebufferTexture(
      GL_READ_FRAMEBUFFER, attachment, tex.get_name(), level);
  }
#else
  glNamedFramebufferTexture(
    framebuffer.get_name(), attachment, tex.get_name(), level);
#endif
  HOU_GL_CHECK_ERROR();
}

}  // namespace



framebuffer_handle framebuffer_handle::create()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  GLuint name = 0u;
#if defined(HOU_GL_ES)
  glGenFramebuffers(1, &name);
#else
  glCreateFramebuffers(1, &name);
#endif
  HOU_GL_CHECK_ERROR();
  return framebuffer_handle(name);
}



framebuffer_handle::~framebuffer_handle()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(*this);
  GLuint name = get_name();
  glDeleteFramebuffers(1, &name);
  HOU_GL_CHECK_ERROR();
}



framebuffer_handle::framebuffer_handle(GLuint name)
  : non_shared_object_handle(name)
{}



void bind_framebuffer(const framebuffer_handle& framebuffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  if(!is_framebuffer_bound(framebuffer, GL_DRAW_FRAMEBUFFER)
    || !is_framebuffer_bound(framebuffer, GL_READ_FRAMEBUFFER))
  {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.get_name());
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_framebuffer(
      framebuffer.get_uid(), GL_DRAW_FRAMEBUFFER);
    context::get_current()->m_tracking_data.set_bound_framebuffer(
      framebuffer.get_uid(), GL_READ_FRAMEBUFFER);
  }
}



void bind_framebuffer(const framebuffer_handle& framebuffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  if(!is_framebuffer_bound(framebuffer, target))
  {
    glBindFramebuffer(target, framebuffer.get_name());
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_framebuffer(
      framebuffer.get_uid(), target);
  }
}


void unbind_framebuffer()
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_framebuffer_bound(GL_DRAW_FRAMEBUFFER)
    || is_framebuffer_bound(GL_READ_FRAMEBUFFER))
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0u);
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_framebuffer(
      0u, GL_DRAW_FRAMEBUFFER);
    context::get_current()->m_tracking_data.set_bound_framebuffer(
      0u, GL_READ_FRAMEBUFFER);
  }
}



void unbind_framebuffer(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  if(is_framebuffer_bound(target))
  {
    glBindFramebuffer(target, 0u);
    HOU_GL_CHECK_ERROR();
    context::get_current()->m_tracking_data.set_bound_framebuffer(0u, target);
  }
}



bool is_framebuffer_bound(const framebuffer_handle& framebuffer, GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  return context::get_current()->m_tracking_data.get_bound_framebuffer(target)
    == framebuffer.get_uid();
}



bool is_framebuffer_bound(GLenum target)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  return context::get_current()->m_tracking_data.get_bound_framebuffer(target)
    != 0u;
}



GLuint get_bound_framebuffer_name(GLenum target)
{
  return static_cast<GLuint>(get_integer(to_get_gl_enum(target)));
}



void set_framebuffer_color_texture(const framebuffer_handle& framebuffer,
  GLuint attachment, const texture_handle& tex, GLint level)
{
  set_framebuffer_texture(
    framebuffer, GL_COLOR_ATTACHMENT0 + attachment, tex, level);
}



void set_framebuffer_depth_texture(
  const framebuffer_handle& framebuffer, const texture_handle& tex, GLint level)
{
  set_framebuffer_texture(framebuffer, GL_DEPTH_ATTACHMENT, tex, level);
}



void set_framebuffer_stencil_texture(
  const framebuffer_handle& framebuffer, const texture_handle& tex, GLint level)
{
  set_framebuffer_texture(framebuffer, GL_STENCIL_ATTACHMENT, tex, level);
}



void set_framebuffer_depth_stencil_texture(
  const framebuffer_handle& framebuffer, const texture_handle& tex, GLint level)
{
  set_framebuffer_texture(framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, tex, level);
}



GLenum get_framebuffer_status(const framebuffer_handle& framebuffer)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(framebuffer);
  GLenum status;
#if defined(HOU_GL_ES)
  {
    scoped_framebuffer_binding(framebuffer.get_name(), framebuffer.get_name());
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  }
#else
  status = glCheckNamedFramebufferStatus(framebuffer.get_name(), GL_FRAMEBUFFER);
#endif
  HOU_GL_CHECK_ERROR();
  return status;
}



void blit_framebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
  GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask,
  GLenum filter)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  glBlitFramebuffer(
    srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  HOU_GL_CHECK_ERROR();
}



void blit_framebuffer(const framebuffer_handle& src,
  const framebuffer_handle& dst, GLint srcX0, GLint srcY0, GLint srcX1,
  GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
  GLbitfield mask, GLenum filter)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(src);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(dst);
#if defined(HOU_GL_ES)
  {
    scoped_framebuffer_binding(dst.get_name(), src.get_name());
    glBlitFramebuffer(
      srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
  }
#else
  glBlitNamedFramebuffer(src.get_name(), dst.get_name(), srcX0, srcY0, srcX1,
    srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
#endif
  HOU_GL_CHECK_ERROR();
}



GLint get_max_color_attachments()
{
  return get_integer(GL_MAX_COLOR_ATTACHMENTS);
}

}  // namespace gl

}  // namespace hou
