// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_HPP
#define HOU_GL_GL_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/sys/window.hpp"

#include "SDL2/SDL_video.h"

#include <vector>



namespace hou
{

namespace gl
{

class buffer_handle;
class framebuffer_handle;
class program_handle;
class texture_handle;
class vertex_array_handle;

class HOU_GL_API context : public non_copyable
{
public:
  using impl_type = SDL_GLContext;

  using uid_type = uint32_t;

public:
  static void set_current(context& ctx, window& wnd);

  static void unset_current();

  static context* get_current() noexcept;

public:
  context(const context_settings& settings, window& wnd);

  context(const context_settings& settings, window& wnd, context& sharing_ctx);

  context(context&& other) noexcept;

  ~context();

  const impl_type& get_impl() const noexcept;

  impl_type& get_impl() noexcept;

  uid_type get_uid() const noexcept;

  uid_type get_sharing_group_uid() const noexcept;

  bool is_current() const;

private:
  class tracking_data
  {
  public:
    tracking_data() noexcept;

    uint32_t get_bound_buffer(GLenum target) const noexcept;

    void set_bound_buffer(uint32_t uid, GLenum target) noexcept;

    uint32_t get_bound_framebuffer(GLenum target) const noexcept;

    void set_bound_framebuffer(uint32_t uid, GLenum target) noexcept;

    uint32_t get_bound_program() const noexcept;

    void set_bound_program(uint32_t uid) noexcept;

    void resize_texture_vectors(size_t size);

    GLuint get_active_texture() const noexcept;

    void set_active_texture(GLuint unit);

    uint32_t get_bound_texture() const noexcept;

    GLenum get_bound_texture_target() const noexcept;

    void set_bound_texture(uint32_t uid, GLenum target);

    uint32_t get_bound_texture(GLuint unit) const noexcept;

    GLenum get_bound_texture_target(GLuint unit) const noexcept;

    void set_bound_texture(uint32_t uid, GLuint unit, GLenum target);

    uint32_t get_bound_vertex_array() const noexcept;

    void set_bound_vertex_array(uint32_t uid) noexcept;

    const recti& get_current_viewport() const noexcept;

    void set_current_viewport(const recti& viewport) noexcept;

  private:
    uint32_t m_bound_array_buffer;
    uint32_t m_bound_element_array_buffer;
    uint32_t m_bound_draw_framebuffer;
    uint32_t m_bound_read_framebuffer;
    uint32_t m_bound_program;
    uint32_t m_bound_vertex_array;
    GLuint m_active_texture;
    std::vector<uint32_t> m_bound_textures;
    std::vector<GLenum> m_bound_texture_targets;
    recti m_current_viewport;
  };

private:
  impl_type m_impl;
  uid_type m_uid;
  uid_type m_sharing_group_uid;
  tracking_data m_tracking_data;

private:
  friend HOU_GL_API void bind_buffer(
    const buffer_handle& buffer, GLenum target);
  friend HOU_GL_API void unbind_buffer(GLenum target);
  friend HOU_GL_API bool is_buffer_bound(
    const buffer_handle& buffer, GLenum target);
  friend HOU_GL_API bool is_buffer_bound(GLenum target);
  friend HOU_GL_API void bind_framebuffer(
    const framebuffer_handle& framebuffer);
  friend HOU_GL_API void bind_framebuffer(
    const framebuffer_handle& framebuffer, GLenum target);
  friend HOU_GL_API void unbind_framebuffer();
  friend HOU_GL_API void unbind_framebuffer(GLenum target);
  friend HOU_GL_API bool is_framebuffer_bound(
    const framebuffer_handle& framebuffer, GLenum target);
  friend HOU_GL_API bool is_framebuffer_bound(GLenum target);
  friend HOU_GL_API void bind_program(const program_handle& program);
  friend HOU_GL_API void unbind_program();
  friend HOU_GL_API bool is_program_bound(const program_handle& program);
  friend HOU_GL_API bool is_program_bound();
  friend HOU_GL_API void bind_texture(const texture_handle& texture);
  friend HOU_GL_API void unbind_texture();
  friend HOU_GL_API bool is_texture_bound(const texture_handle& texture);
  friend HOU_GL_API bool is_texture_bound();
  friend HOU_GL_API void bind_texture(
    const texture_handle& texture, GLuint unit);
  friend HOU_GL_API void unbind_texture(GLuint unit);
  friend HOU_GL_API bool is_texture_bound(
    const texture_handle& texture, GLuint unit);
  friend HOU_GL_API bool is_texture_bound(GLuint unit);
  friend HOU_GL_API void set_active_texture(GLuint unit);
  friend HOU_GL_API GLuint get_bound_texture_name();
  friend HOU_GL_API void bind_vertex_array(
    const vertex_array_handle& vertexArray);
  friend HOU_GL_API void unbind_vertex_array();
  friend HOU_GL_API bool is_vertex_array_bound(
    const vertex_array_handle& vertexArray);
  friend HOU_GL_API bool is_vertex_array_bound();
  friend HOU_GL_API void set_viewport(GLint x, GLint y, GLsizei w, GLsizei h);
};

}  // namespace gl

}  // namespace hou

#endif
