// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_EVENT_TYPE_HPP
#define HOU_SYS_WINDOW_EVENT_TYPE_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for window event type. */
enum class WindowEventType
{
  /** Empty or invalid event. */
  Empty,
  /** Window closed event. */
  Closed,
  /** Window focus gained event. */
  FocusGained,
  /** Window focus lost event. */
  FocusLost,
  /** Mouse entered window event. */
  MouseEntered,
  /** Mouse left window event. */
  MouseLeft,

  /** Window resized event. It is associated to SizeData. */
  Resized,

  /** Key pressed event. It is associated to KeyData. */
  KeyPressed,
  /** Key released event. It is associated to KeyData. */
  KeyReleased,

  /** Text entered event. It is associated to TextData. */
  TextEntered,

  /** Mouse moved event. It is associated to MouseMoveData. */
  MouseMoved,

  /** Mouse button pressed event. It is associated to MouseButtonData. */
  MouseButtonPressed,
  /** Mouse button released event. It is associated to MouseButtonData. */
  MouseButtonReleased,

  /** Mouse wheel moved event. It is associated to MouseWheelData. */
  MouseWheelMoved,
};

/** Writes a WindowEventType enum into a stream.
 *
 *  \param os the stream.
 *  \param we the WindowEventType enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, WindowEventType we);

}

#endif

