// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MODIFIER_KEYS_HPP
#define HOU_SYS_MODIFIER_KEYS_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/cor/bitwise_operators.hpp"

#include <iostream>



namespace hou
{

/** Enumeration for the modifier key flags, used for key related ph_window
 * events.
 */
enum class modifier_keys
{
  /** Null flag. */
  none = 0,
  /** alt key. */
  alt = 1 << 0,
  /** ctrl key. */
  ctrl = 1 << 1,
  /** shift key. */
  shift = 1 << 2,
  /** system key. */
  system = 1 << 3,
};

/** Writes a modifier_keys enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param mkf the modifier_keys enum.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, modifier_keys mkf);

/** Enables bitwise operators for modifier_keys.
 */
template <>
struct enable_bitwise_operators<modifier_keys>
{
  /** Enabling variable. */
  static constexpr bool enable = true;
};

}  // namespace hou

#endif
