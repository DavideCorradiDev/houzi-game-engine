// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MODIFIER_KEYS_HPP
#define HOU_SYS_MODIFIER_KEYS_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/BitwiseOperators.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the modifier key flags, used for key related window events.
 */
enum class ModifierKeys
{
  /** Null flag. */
  None = 0,
  /** Alt key. */
  Alt = 1 << 0,
  /** Ctrl key. */
  Ctrl = 1 << 1,
  /** Shift key. */
  Shift = 1 << 2,
  /** System key. */
  System = 1 << 3,
};

/** Writes a ModifierKeys enum into a stream.
 *
 *  \param os the stream.
 *  \param mkf the ModifierKeys enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, ModifierKeys mkf);

/** Enables bitwise operators for ModifierKeys.
 */
template <>
  struct EnableBitwiseOperators<ModifierKeys>
{
  /** Enabling variable. */
  static constexpr bool enable = true;
};

}

#endif


