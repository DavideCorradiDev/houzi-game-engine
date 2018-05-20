// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_WINDOW_HPP
#define HOU_GFX_RENDER_WINDOW_HPP

#include "hou/gfx/gfx_config.hpp"
#include "hou/gfx/render_surface.hpp"
#include "hou/sys/window.hpp"

#include "hou/gfx/vertical_sync_mode.hpp"



namespace hou
{

class video_mode;

/** window that can be used for rendering.
 *
 * Some notes on how the size is handled:
 *
 * * get_frame_size will return the size of the window including its frame.
 *
 * * get_client_size will return the size of the window without its frame.
 *
 * * get_size will return the size of the render surface associated to the
 * window.
 *
 * get_size will normally return the same value as get_client_size, with the
 * following exceptions:
 *
 * * If one of the elements of the client size equals 0, the corresponding
 * element in the render surface size will be equal to 1. The render surface
 * must have at least one pixel.
 *
 * * If the window is resized by dragging its borders, the rendering surface
 * will be resized accordingly only when popping the resized event from the
 * event queue.
 *
 * The view port of the render surface will not be adjusted if the size of the
 * window changes for any reason. It must be adjusted manually. This can
 * normally be achieved simply by reacting to resizing events from the window
 * event queue.
 */
class HOU_GFX_API render_window final
  : public window
  , public render_surface
{
public:
  /** Creates a render_window with the desired title, size, sample count, and
   *  style.
   *
   * \param title the window title.
   *
   * \param size the size.
   *
   * \param sample_count the sample count.
   *
   * \param style the window style.
   */
  render_window(const std::string& title, const vec2u& size, window_style style,
    uint sample_count = 1u);

  /** Displays what has been rendered onto the render_window.
   */
  void display();

  /** Sets the vertical sync mode for the window.
   *
   * \param mode the vertical sync mode.
   */
  void set_vertical_sync_mode(vertical_sync_mode mode);

  /** Sets the number of samples of the render_window.
   *
   * After setting the sample count, the content of the framebuffer is reset.
   * Throws if the required sample count is larger then the maximum supported.
   *
   * \return the number of samples of the render_window.
   */
  void set_sample_count(uint sample_count);

  // window overrides.
  void set_frame_rect(const vec2i& pos, const vec2u& size) override;
  void set_client_rect(const vec2i& pos, const vec2u& size) override;

private:
  void rebuild_framebuffer_if_necessary();
};

}  // namespace hou

#endif