// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_EVENT_TYPE_HPP
#define HOU_SYS_WINDOW_EVENT_TYPE_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for ph_window event type. */
enum class window_event_type
{
  /** empty or invalid event. */
  empty,
  /** window closed event. */
  closed,
  /** window focus gained event. */
  focus_gained,
  /** window focus lost event. */
  focus_lost,
  /** mouse entered ph_window event. */
  mouse_entered,
  /** mouse left ph_window event. */
  mouse_left,

  /** window resized event. It is associated to size_data. */
  resized,

  /** Key pressed event. It is associated to key_data. */
  key_pressed,
  /** Key released event. It is associated to key_data. */
  key_released,

  /** text entered event. It is associated to text_data. */
  TextEntered,

  /** mouse moved event. It is associated to mouse_move_data. */
  mouse_moved,

  /** mouse button pressed event. It is associated to mouse_button_data. */
  mouse_button_pressed,
  /** mouse button released event. It is associated to mouse_button_data. */
  mouse_button_released,

  /** mouse wheel moved event. It is associated to mouse_wheel_data. */
  mouse_wheel_moved,
};

/** Writes a window_event_type enum into a ph_stream.
 *
 * \param os the ph_stream.
 *
 * \param we the window_event_type enum.
 *
 * \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, window_event_type we);

}  // namespace hou

#endif
