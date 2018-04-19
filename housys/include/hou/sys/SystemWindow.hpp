// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SYSTEM_WINDOW_HPP
#define HOU_SYS_SYSTEM_WINDOW_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/Window.hpp"



namespace hou
{

class HOU_SYS_API SystemWindow : public Window
{
public:
  /** Creates a Window object.
   *
   * The window client size corresponds to the resolution in videoMode.
   * The window client is be positioned in the middle of the screen.
   * The window uses the default system icon.
   * The window is not visible.
   * The window does not grab the mouse cursor.
   * Key repeat is disabled for the window.
   *
   * \param title the title of the Window.
   * \param videoMode the video mode of the Window, specifying its size and
   * bytes per pixel.
   * \param style the style of the Window.
   * Only one Window can be fullscreen.
   * If fullscreen mode is specified and videoMode is not a valid fullscreen
   * VideoMode, an error will be thrown.
   */
  SystemWindow(
    const std::string& title, const VideoMode& videoMode, WindowStyle style);

  /** Move constructor.
   *
   * \param other the other Window object.
   */
  SystemWindow(SystemWindow&& other);

  // Window ovverrides.
  void setFrameRect(const Recti& rect) final;
  void setClientRect(const Recti& rect) final;
};

}  // namespace hou

#endif
