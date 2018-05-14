// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_BUTTON_HPP
#define HOU_SYS_MOUSE_BUTTON_HPP

#include "hou/sys/sys_config.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the mouse buttons. */
enum class mouse_button
{
  /** Left button. */
  lb,
  /** Middle button. */
  mb,
  /** Right button. */
  rb,
  /** Extra button 1. */
  xb1,
  /** Extra button 2. */
  xb2,
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
