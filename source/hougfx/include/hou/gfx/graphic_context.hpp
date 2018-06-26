// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GRAPHIC_CONTEXT_HPP
#define HOU_GFX_GRAPHIC_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_config.hpp"

#include "hou/gl/gl_context.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

/**
 * Represents the global state of the rendering device.
 *
 * At least one graphic_context must exist when creating rendering objects.
 * For most applications, it is sufficient to create and set as current a
 * single graphic_context at startup, and destroy it at shutdown. Each thread may
 * have a single current graphic_context. Each graphic_context may be current in a
 * single thread. Resources are not shared among contexts. Even though multiple
 * contexts in multiple threads may exist, it is suggested to perform all
 * rendering operations in a single thread. If a graphic_context is destroyed
 * while it is current, there will be nocurrent graphic_context until another
 * graphic_context is created or set as current.
 */
class HOU_GFX_API graphic_context : public non_copyable
{
public:
  /**
   * Underlying implementation type.
   */
  using impl_type = gl::context;

public:
  /**
   * Sets this context and the specified wnidow as current for the current thread.
   *
   * \param ctx the context.
   *
   * \param wnd the window.
   */
  static void set_current(graphic_context& ctx, window& wnd);

  /**
   * Sets the window as current in the current context.
   *
   * \param wnd the window.
   *
   * \throws hou::precondition_violation if there is no current context.
   */
  static void set_current(window& wnd);

  /**
   * Unsets the current graphic_context.
   */
  static void unset_current();

public:
  /**
   * Creates a graphic_context and sets it as the current graphic_context. */
  graphic_context();

  /**
   * Checks if this context is current in the current thread.
   *
   * \return true if this context is current in the current thread.
   */
  bool is_current() const;

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  const impl_type& get_impl() const noexcept;

  /**
   * Gets a reference to the underlying implementation.
   *
   * \return a reference to the underlying implementation.
   */
  impl_type& get_impl() noexcept;

private:
  void initialize();

private:
  gl::context m_gl_context;
  bool m_initialized;
};

}  // namespace hou

#endif
