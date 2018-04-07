// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_SYS_MOUSE_BUTTON_HPP
#define HOU_SYS_MOUSE_BUTTON_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the mouse buttons. */
enum class MouseButton
{
  /** Left button. */
  LB,
  /** Middle button. */
  MB,
  /** Right button. */
  RB,
  /** Extra button 1. */
  XB1,
  /** Extra button 2. */
  XB2,
};

/** Writes a MouseButton enum into a stream.
 *
 *  \param os the stream.
 *  \param mb the MouseButton enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, MouseButton mb);

}

#endif

