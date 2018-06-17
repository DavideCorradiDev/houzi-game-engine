// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYSTEM_WINDOW_HPP
#define HOU_SYS_SYSTEM_WINDOW_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

/** Class representing a window.
 */
class HOU_SYS_API system_window final : public window
{
public:
  /** Creates a window object.
   *
   * The window client size corresponds to the resolution in vm.
   * The window client is be positioned in the middle of the screen.
   * The window uses the default system icon.
   * The window is not visible.
   * The window does not grab the mouse cursor.
   * Key repeat is disabled for the window.
   *
   * \param title the title of the window.
   * \param vm the video mode of the window, specifying its size and
   * bytes per pixel.
   * \param style the style of the window.
   * Only one window can be fullscreen.
   * If fullscreen mode is specified and vm is not a valid fullscreen
   * video_mode, an error will be thrown.
   */
  system_window(const std::string& title, const vec2u& size);
};

}  // namespace hou

#endif
