// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_BUTTON_HPP
#define HOU_SYS_MOUSE_BUTTON_HPP

#include "hou/sys/sys_config.hpp"

#include <iostream>

#include "SDL_mouse.h"



namespace hou
{

/** Enumeration for the mouse buttons. */
enum class mouse_button
{
  /** Left button. */
  lb = SDL_BUTTON_LEFT,
  /** Middle button. */
  mb = SDL_BUTTON_MIDDLE,
  /** Right button. */
  rb = SDL_BUTTON_RIGHT,
  /** Extra button 1. */
  xb1 = SDL_BUTTON_X1,
  /** Extra button 2. */
  xb2 = SDL_BUTTON_X2,
};

/** Writes a mouse_button enum into a stream.
 *
 * \param os the stream.
 *
 * \param mb the mouse_button enum.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, mouse_button mb);

}  // namespace hou

#endif
