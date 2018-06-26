// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MODIFIER_KEYS_HPP
#define HOU_SYS_MODIFIER_KEYS_HPP

#include "hou/sys/sys_config.hpp"

#include "hou/cor/bitwise_operators.hpp"

#include "SDL2/SDL_keyboard.h"

#include <iostream>



namespace hou
{

/** Enumeration for the modifier key flags, used for key related window
 * events.
 *
 * Values in this enumeration can be used as a bitfield.
 */
enum class modifier_keys : uint32_t
{
  none = 0,
  lalt = KMOD_LALT,
  ralt = KMOD_RALT,
  alt = KMOD_ALT,
  lctrl = KMOD_LCTRL,
  rctrl = KMOD_RCTRL,
  ctrl = KMOD_CTRL,
  lshift = KMOD_LSHIFT,
  rshift = KMOD_RSHIFT,
  shift = KMOD_SHIFT,
  lsystem = KMOD_LGUI,
  rsystem = KMOD_RGUI,
  system = KMOD_GUI,
  num = KMOD_NUM,
  caps = KMOD_CAPS,
  mode = KMOD_MODE,
};

/** Writes a modifier_keys enum into a stream.
 *
 *  \param os the stream.
 *  \param mkf the modifier_keys enum.
 *  \return a reference to the stream.
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
