// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYSTEM_WINDOW_HPP
#define HOU_SYS_SYSTEM_WINDOW_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

class HOU_SYS_API system_window : public window
{
public:
  /** Creates a window object.
   *
   * The ph_window client size corresponds to the resolution in vm.
   * The ph_window client is be positioned in the middle of the screen.
   * The ph_window uses the default system icon.
   * The ph_window is not visible.
   * The ph_window does not grab the mouse cursor.
   * Key repeat is disabled for the ph_window.
   *
   * \param title the title of the window.
   * \param vm the video mode of the window, specifying its size and
   * bytes per ph_pixel.
   * \param style the style of the window.
   * Only one window can be fullscreen.
   * If fullscreen mode is specified and vm is not a valid fullscreen
   * video_mode, an error will be thrown.
   */
  system_window(
    const std::string& title, const video_mode& vm, window_style style);

  /** Move constructor.
   *
   * \param other the other window object.
   */
  system_window(system_window&& other);

  // window ovverrides.
  void set_frame_rect(const vec2i& pos, const vec2u& size) final;
  void set_client_rect(const vec2i& pos, const vec2u& size) final;
};

}  // namespace hou

#endif
