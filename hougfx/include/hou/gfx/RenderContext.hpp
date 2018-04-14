// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GFX_RENDER_CONTEXT_HPP
#define HOU_GFX_RENDER_CONTEXT_HPP

#include "hou/cor/NonCopyable.hpp"
#include "hou/gfx/GfxExport.hpp"

#include "hou/cor/BasicTypes.hpp"

#include "hou/gl/GlContext.hpp"

#include "hou/sys/Window.hpp"



namespace hou
{

/** Represents the global state of the rendering device.
 *
 *  At least one RenderContext must exist when creating rendering objects.
 *  For most applications, it is sufficient to create a single RenderContext
 *  at startup and destroy it at shutdown.
 *  Each thread may have a single current RenderContext.
 *  Each RenderContext may be current in a single thread.
 *  Resources are not shared among contexts.
 *  Even though multiple contexts in multiple threads may exist, it is suggested
 *  to perform all rendering operations in a single thread.
 *  If a RenderContext is destroyed while it is current, there will be no
 * current RenderContext until another RenderContext is created or set as
 * current.
 */
class HOU_GFX_API RenderContext : public NonCopyable
{
public:
  /** Sets this as the current context for the current thread.
   */
  static void setCurrent(RenderContext& context);

  /** Unsets the current RenderContext.
   */
  static void unsetCurrent(RenderContext& context);

  /** Gets the number of color bits used in rendering.
   *
   *  \return the number of color bits.
   */
  static uint getRenderingColorByteCount();

  /** Gets the number of depth bits used in rendering.
   *
   *  \return the number of depth bits.
   */
  static uint getRenderingDepthByteCount();

  /** Gets the number of stencil bits used in rendering.
   *
   *  \return the number of stencil bits.
   */
  static uint getRenderingStencilByteCount();

public:
  /** Creates a RenderContext and sets it as the current RenderContext. */
  RenderContext();

  /** Move constructor.
   *
   *  \param other the other RenderContext.
   */
  RenderContext(RenderContext&& other);

  /** Checks if this context is current in the current thread.
   *
   *  \return true if this context is current in the current thread.
   */
  bool isCurrent() const;

private:
  class ExtensionInitializer
  {
  public:
    ExtensionInitializer();
  };

private:
  ExtensionInitializer mExtensionInitializer;
  Window mDefaultWindow;
  gl::Context mGlContext;
};

}  // namespace hou

#endif
