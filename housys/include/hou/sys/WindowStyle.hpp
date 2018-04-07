// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_WND_WINDOW_STYLE_HPP
#define HOU_WND_WINDOW_STYLE_HPP

#include "hou/sys/SysExport.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for window style. */
enum class WindowStyle
{
  /** Windowed. The window cannot be resized by the user. */
  Windowed,
  /** Windowed. The window can be resized by the user. */
  WindowedResizable,
  /** Fullscreen. Only a single fullscreen window is allowed. */
  Fullscreen,
};

/** Writes a WindowStyle enum into a stream.
 *
 *  \param os the stream.
 *  \param ws the WindowStyle enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, WindowStyle ws);

}

#endif

