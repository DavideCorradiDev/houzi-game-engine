// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_GRAPHIC_CONTEXT_HPP
#define HOU_GFX_GRAPHIC_CONTEXT_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/gl/GlContext.hpp"

#include "hou/sys/Window.hpp"



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
class HOU_GFX_API GraphicContext : public NonCopyable
{
public:
  /** Sets this as the current context for the current thread.
   */
  static void setCurrent(GraphicContext& context);

  /** Unsets the current GraphicContext.
   */
  static void unsetCurrent();

  /** Gets the number of color bits used in rendering.
   *
   * \return the number of color bits.
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

  /** Checks if this context is current in the current thread.
   *
   * \return true if this context is current in the current thread.
   */
  bool isCurrent() const;

private:
  class ExtensionInitializer
  {
  public:
    ExtensionInitializer();
  };

private:
  // Initializes some context variables when binding the context for the first
  // time. These variables should only be set the first time to provide a
  // consistent "clean state" for the context, but should not be set for
  // subsequent bindings to prevent resetting the state of the context.
  void initialize();

private:
  ExtensionInitializer mExtensionInitializer;
  Window mDefaultWindow;
  gl::Context mGlContext;
  bool mInitialized;
};

}  // namespace hou

#endif
