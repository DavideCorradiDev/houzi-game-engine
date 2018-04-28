// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_WND_WINDOW_STYLE_HPP
#define HOU_WND_WINDOW_STYLE_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for ph_window style. */
enum class window_style
{
  /** windowed. The ph_window cannot be resized by the user. */
  windowed,
  /** windowed. The ph_window can be resized by the user. */
  windowed_resizable,
  /** fullscreen. Only a single fullscreen ph_window is allowed. */
  fullscreen,
};

/** Writes a window_style enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param ws the window_style enum.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, window_style ws);

}

#endif

