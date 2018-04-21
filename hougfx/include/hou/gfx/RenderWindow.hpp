// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_WINDOW_HPP
#define HOU_GFX_RENDER_WINDOW_HPP

#include "hou/gfx/GfxExport.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/sys/Window.hpp"

#include "hou/gfx/VerticalSyncMode.hpp"



namespace hou
{

class VideoMode;

/** Window that can be used for rendering.
 *
 * Some notes on how the size is handled:
 * - getFrameSize will return the size of the window including its frame.
 * - getClientSize will return the size of the window without its frame.
 * - getSize will return the size of the render surface associated to the
 * Window.
 *
 * getSize will normally return the same value as getClientSize, with the
 * following exceptions:
 * - If one of the elements of the client size equals 0, the corresponding
 * element in the render surface size will be equal to 1. The render surface
 * must have at least one pixel.
 * - If the window is resized by dragging its borders, the rendering surface
 * will be resized accordingly only when popping the resized event from the
 * event queue.
 *
 * The view port of the render surface will not be adjusted if the size of the
 * window changes for any reason. It must be adjusted manually. This can
 * normally be achieved simply by reacting to resizing events from the window
 * event queue.
 */
class HOU_GFX_API RenderWindow
  : public Window
  , public RenderSurface
{
public:
  /** Creates a RenderWindow with the desired title, size, sample count, and
   *  style.
   *
   *  \param title the window title.
   *  \param size the size.
   *  \param sampleCount the sample count.
   *  \param style the window style.
   */
  RenderWindow(const std::string& title, const Vec2u& size, uint sampleCount
    , WindowStyle style);

  /** Move constructor.
   *
   *  \param other the other RenderWindow.
   */
  RenderWindow(RenderWindow&& other);

  /** Destructor.
   */
  virtual ~RenderWindow();

  /** Displays what has been rendered onto the RenderWindow.
   */
  void display();

  /** Sets the vertical sync mode for the window.
   *
   *  \param mode the vertical sync mode.
   */
  void setVerticalSyncMode(VerticalSyncMode mode);

  /** Sets the number of samples of the RenderWindow.
   *
   *  After setting the sample count, the content of the framebuffer is reset.
   *  Throws if the required sample count is larger then the maximum supported.
   *
   *  \return the number of samples of the RenderWindow.
   */
  void setSampleCount(uint sampleCount);

  // Window overrides.
  void setFrameRect(const Vec2i& pos, const Vec2u& size) override;
  void setClientRect(const Vec2i& pos, const Vec2u& size) override;

private:
  void rebuildFramebufferIfNecessary();
};

}

#endif
