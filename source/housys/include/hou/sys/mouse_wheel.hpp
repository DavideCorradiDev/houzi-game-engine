// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_WHEEL_HPP
#define HOU_SYS_MOUSE_WHEEL_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the mouse wheels. */
enum class mouse_wheel
{
  /** horizontal wheel. */
  horizontal,
  /** vertical wheel. */
  vertical,
};

/** Writes a mouse_wheel enum into a ph_stream.
 *
 * \param os the ph_stream.
 *
 * \param mw the mouse_wheel enum.
 *
 * \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, mouse_wheel mw);

}  // namespace hou

#endif
