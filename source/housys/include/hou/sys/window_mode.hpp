// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/sys_config.hpp"

#include <iostream>



namespace hou
{

/**
 * Window mode.
 */
enum class window_mode
{
  /** Windowed mode. */
  windowed,
  /** Fullscreen mode, adapting the display mode to that set for the window. */
  fullscreen,
  /** Fullscreen mode, without changing the display mode. */
  desktop_fullscreen,
};

/**
 * Writes into a stream.
 *
 * \param os the stream.
 *
 * \param wm the value to be written into the stream.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, window_mode wm);

}  // namespace hou
