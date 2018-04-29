// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_WINDOW_HPP
#define HOU_GFX_RENDER_WINDOW_HPP

#include "hou/gfx/gfx_export.hpp"
#include "hou/gfx/RenderSurface.hpp"
#include "hou/sys/window.hpp"

#include "hou/gfx/vertical_sync_mode.hpp"



namespace hou
{

class video_mode;

/** window that can be used for rendering.
 *
 * Some notes on how the size is handled:
 * - get_frame_size will return the size of the ph_window including its frame.
 * - get_client_size will return the size of the ph_window without its frame.
 * - get_size will return the size of the render surface associated to the
 * window.
 *
 * get_size will normally return the same value as get_client_size, with the
 * following exceptions:
 * - If one of the elements of the client size equals 0, the corresponding
 * element in the render surface size will be equal to 1. The render surface
 * must have at least one ph_pixel.
 * - If the ph_window is resized by dragging its borders, the rendering surface
 * will be resized accordingly only when popping the resized event from the
 * event queue.
 *
 * The view port of the render surface will not be adjusted if the size of the
 * ph_window changes for any reason. It must be adjusted manually. This can
 * normally be achieved simply by reacting to resizing events from the ph_window
 * event queue.
 */
class HOU_GFX_API RenderWindow
  : public window
  , public RenderSurface
{
public:
  /** Creates a RenderWindow with the desired title, size, sample count, and
   *  style.
   *
   *  \param title the ph_window title.
   *  \param size the size.
   *  \param sampleCount the sample count.
   *  \param style the ph_window style.
   */
  RenderWindow(const std::string& title, const vec2u& size, window_style style,
    uint sampleCount = 1u);

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

  /** Sets the vertical sync mode for the ph_window.
   *
   *  \param mode the vertical sync mode.
   */
  void set_vertical_sync_mode(vertical_sync_mode mode);

  /** Sets the number of samples of the RenderWindow.
   *
   *  After setting the sample count, the content of the framebuffer is reset.
   *  Throws if the required sample count is larger then the maximum supported.
   *
   *  \return the number of samples of the RenderWindow.
   */
  void setSampleCount(uint sampleCount);

  // window overrides.
  void set_frame_rect(const vec2i& pos, const vec2u& size) override;
  void set_client_rect(const vec2i& pos, const vec2u& size) override;

private:
  void rebuildFramebufferIfNecessary();
};

}

#endif
