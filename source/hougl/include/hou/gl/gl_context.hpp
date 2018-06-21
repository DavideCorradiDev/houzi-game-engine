// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_HPP
#define HOU_GL_GL_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/cor/uid_generator.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/sys/window.hpp"

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

/**
 * Represents an OpenGL context.
 *
 * The context is an object containing OpenGL related global state.
 *
 * A context must be created and set as current in order to be able to perform
 * any OpenGL call.
 * A single context is sufficient, but it is possible to create multiple context
 * objects.
 * Each thread can only have one current context at a time, and a context cannot
 * be current in more than one thread at the same time.
 * If the library was built with HOU_ENABLE_GL_CHECKS, an exception will be
 * thrown if any OpenGL operation in the hougl library is performed without a
 * current context.
 *
 * OpenGL objects built when a context is current belong to that context and,
 * as a general rule, they cannot be used when other contexts are active.
 * It is possible to explicitly set two or more contexts to share resources.
 * In this case, *some* types of OpenGL objects will be shared between them, and
 * it will be possible to use them when any of the contexts is current.
 * If the library was built with HOU_ENABLE_GL_CHECKS, an exception will be
 * thrown if an operation is performed on an object not owned by the current
 * context.
 */
class HOU_GL_API context : public non_copyable
{
public:
  /**
   * Underlying implementation type.
   */
  using impl_type = void;

  /**
   * Unique identifier type.
   */
  using uid_type = uid_generator::uid_type;

public:
  /**
   * Sets the current context in the current thread.
   *
   * Only one context per thread can be current, and a current can only be
   * current in one thread at a time.
   *
   * A context must be made current together with a window.
   * The window framebuffer will be the default framebuffer of OpenGL operations.
   *
   * \param ctx the context to make current.
   *
   * \param the window to make current.
   *
   * \throws hou::gl::context_switch_error in case setting the context failed.
   */
  static void set_current(context& ctx, window& wnd);

  /**
   * Unsets the current context in the current thread.
   *
   * After a call to this function, there will be no current context in the
   * current thread, meaning that no OpenGL call can be performed.
   *
   * \throws hou::gl::context_switch_error in case unsetting the context failed.
   */
  static void unset_current();

  /**
   * Gets the current context in the current thread.
   *
   * \return a pointer to the current context, or nullptr if there is no
   * current context.
   */
  static context* get_current();

  /**
   * Gets the uid of the current window in the current thread.
   *
   * \return the uid of the current window, or 0 if there is no current window.
   */
  static window::uid_type get_current_window_uid();

public:
  /**
   * Creates a context.
   *
   * When creating a context, a window must be provided.
   * Later, the context can be bound with any windown, not necessarily the one
   * it was created with.
   *
   * \param cs the context settings.
   *
   * \param wnd the context window.
   *
   * \throws hou::al::context_creation_error in case of an error.
   */
  context(const context_settings& cs, window& wnd);

  /**
   * Creates a context sharing with another context.
   *
   * When creating a context, a window must be provided.
   * Later, the context can be bound with any windown, not necessarily the one
   * it was created with.
   *
   * The context will share objects with sharing_ctx.
   *
   * \param cs the context settings.
   *
   * \param wnd the context window.
   *
   * \param sharing_ctx the context to share resources with.
   *
   * \throws hou::al::context_creation_error in case of an error.
   */
  context(const context_settings& cs, window& wnd, context& sharing_ctx);

  /**
   * Move constructor.
   *
   * \param other the othe context.
   */
  context(context&& other) noexcept;

  /**
   * Destructor.
   */
  ~context();

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  const impl_type* get_impl() const noexcept;

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  impl_type* get_impl() noexcept;

  /**
   * Gets the context unique identifier.
   *
   * \return the context unique identifier.
   */
  uid_type get_uid() const noexcept;

  /**
   * Gets the unique identifier of the group of contexts that this context is
   * sharing objects with.
   *
   * \return the unique identifier of the group of sharing contexts.
   */
  uid_type get_sharing_group_uid() const noexcept;

  /**
   * Checks whether this context is current in the current thread.
   *
   * \return true if the context is current, false otherwise.
   */
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
  impl_type* m_impl;
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