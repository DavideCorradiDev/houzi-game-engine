// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_WHEEL_HPP
#define HOU_SYS_MOUSE_WHEEL_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the mouse wheels. */
enum class MouseWheel
{
  /** Horizontal wheel. */
  Horizontal,
  /** Vertical wheel. */
  Vertical,
};

/** Writes a MouseWheel enum into a stream.
 *
 *  \param os the stream.
 *  \param mw the MouseWheel enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, MouseWheel mw);

}

#endif

