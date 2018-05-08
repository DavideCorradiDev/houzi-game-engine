// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GRAPHIC_CONTEXT_HPP
#define HOU_GFX_GRAPHIC_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/gfx_export.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/gl/gl_context.hpp"

#include "hou/sys/system_window.hpp"



namespace hou
{

/** Represents the global state of the rendering device.
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
  /** Sets this as the current context for the current thread.
   *
   * \param cts the context.
   */
  static void set_current(graphic_context& ctx);

  /** Unsets the current graphic_context.
   */
  static void unset_current();

  /** Gets the number of color bits used in rendering.
   *
   * \return the number of color bits.
   */
  static uint get_rendering_color_byte_count();

  /** Gets the number of depth bits used in rendering.
   *
   * \return the number of depth bits.
   */
  static uint get_rendering_depth_byte_count();

  /** Gets the number of stencil bits used in rendering.
   *
   * \return the number of stencil bits.
   */
  static uint get_rendering_stencil_byte_count();

public:
  /** Creates a graphic_context and sets it as the current graphic_context. */
  graphic_context();

  /** Move constructor.
   *
   * \param other the other graphic_context.
   */
  graphic_context(graphic_context&& other) noexcept;

  /** Checks if this context is current in the current thread.
   *
   * \return true if this context is current in the current thread.
   */
  bool is_current() const;

private:
  class extension_initializer
  {
  public:
    extension_initializer();
  };

private:
  // Initializes some context variables when binding the context for the first
  // time. These variables should only be set the first time to provide a
  // consistent "clean state" for the context, but should not be set for
  // subsequent bindings to prevent resetting the state of the context.
  void initialize();

private:
  extension_initializer m_extension_initializer;
  system_window m_default_window;
  gl::context gl_context;
  bool m_initialized;
};

}  // namespace hou

#endif
