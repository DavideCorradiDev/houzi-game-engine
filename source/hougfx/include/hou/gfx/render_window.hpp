// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_RENDER_WINDOW_HPP
#define HOU_GFX_RENDER_WINDOW_HPP

#include "hou/gfx/render_surface.hpp"

#include "hou/gfx/gfx_config.hpp"

#include "hou/sys/window.hpp"

#include "hou/gl/gl_vsync_mode.hpp"



namespace hou
{

/**
 * Window that can be used as a rendering target or source.
 *
 * render_window inherits from window and render_surface, which both have a
 * get_size method.
 * When calling get_size() on a render_window object through a window reference,
 * window::get_size() will be called, and when calling it through a
 * render_surface reference, render_surface::get_size() will be called.
 *
 * render_window defines two methods to conveniently call a specific get_size
 * method:
 *
 * * get_window_size will get the size of the window client, as if calling
 * window::get_size().
 *
 * * get_framebuffer_size will get the size of the framebuffer, as if calling
 * render_surface::get_size().
 *
 * These two methods will normally return the same values, with the following
 * exceptions:
 *
 * * If one of the elements of the window client size equals 0, the
 * corresponding element in the framebuffer size will be equal to 1. OpenGL
 * framebuffers must have at least one pixel.
 *
 * * If the window is resized by dragging its borders, the rendering surface
 * will be resized accordingly only after processing events.
 */
class HOU_GFX_API render_window final
  : public window
  , public render_surface
{
public:
  using vsync_mode = gl::vsync_mode;

public:
  /**
   * Creates a render_window with the desired title, size, sample count, and
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
  render_window(
    const std::string& title, const vec2u& size, uint sample_count = 1u);

  vec2u get_window_size() const;
  vec2u get_framebuffer_size() const;

  /**
   * Gets the window vertical sync mode.
   *
   * \return the vertical sync mode.
   */
  vsync_mode get_vsync_mode() const;

  /**
   * Sets the vertical sync mode for the window.
   *
   * \param mode the vertical sync mode.
   */
  void set_vsync_mode(vsync_mode mode);

  /**
   * Sets the number of samples of the render_window.
   *
   * After setting the sample count, the content of the framebuffer is reset.
   * Throws if the required sample count is larger then the maximum supported.
   *
   * \return the number of samples of the render_window.
   */
  void set_sample_count(uint sample_count);

  // Overrides.
  void clear(const color& color) final;
  void swap_buffers() final;

private:
  // Overrides.
  void on_size_change(const vec2u& size) final;

private:
  vsync_mode m_vsync_mode;
};

}  // namespace hou

#endif
