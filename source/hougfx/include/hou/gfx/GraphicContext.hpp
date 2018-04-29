// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GRAPHIC_CONTEXT_HPP
#define HOU_GFX_GRAPHIC_CONTEXT_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/gl/gl_context.hpp"

#include "hou/sys/system_window.hpp"



namespace hou
{

/** Represents the global state of the rendering device.
 *
 * At least one GraphicContext must exist when creating rendering objects.
 * For most applications, it is sufficient to create and set as current a
 * single GraphicContext at startup, and destroy it at shutdown. Each thread may
 * have a single current GraphicContext. Each GraphicContext may be current in a
 * single thread. Resources are not shared among contexts. Even though multiple
 * contexts in multiple threads may exist, it is suggested to perform all
 * rendering operations in a single thread. If a GraphicContext is destroyed
 * while it is current, there will be nocurrent GraphicContext until another
 * GraphicContext is created or set as current.
 */
class HOU_GFX_API GraphicContext : public non_copyable
{
public:
  /** Sets this as the current ph_context for the current thread.
   */
  static void set_current(GraphicContext& ph_context);

  /** Unsets the current GraphicContext.
   */
  static void unset_current();

  /** Gets the number of ph_color bits used in rendering.
   *
   * \return the number of ph_color bits.
   */
  static uint getRenderingColorByteCount();

  /** Gets the number of depth bits used in rendering.
   *
   * \return the number of depth bits.
   */
  static uint getRenderingDepthByteCount();

  /** Gets the number of stencil bits used in rendering.
   *
   * \return the number of stencil bits.
   */
  static uint getRenderingStencilByteCount();

public:
  /** Creates a GraphicContext and sets it as the current GraphicContext. */
  GraphicContext();

  /** Move constructor.
   *
   * \param other the other GraphicContext.
   */
  GraphicContext(GraphicContext&& other);

  /** Checks if this ph_context is current in the current thread.
   *
   * \return true if this ph_context is current in the current thread.
   */
  bool is_current() const;

private:
  class ExtensionInitializer
  {
  public:
    ExtensionInitializer();
  };

private:
  // Initializes some ph_context variables when binding the ph_context for the first
  // time. These variables should only be set the first time to provide a
  // consistent "clean state" for the ph_context, but should not be set for
  // subsequent bindings to prevent resetting the state of the ph_context.
  void initialize();

private:
  ExtensionInitializer mExtensionInitializer;
  system_window mDefaultWindow;
  gl::context gl_context;
  bool mInitialized;
};

}  // namespace hou

#endif
