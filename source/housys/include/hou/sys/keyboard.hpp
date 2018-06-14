// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_KEYBOARD_HPP
#define HOU_SYS_KEYBOARD_HPP

#include "hou/sys/key_code.hpp"
#include "hou/sys/modifier_keys.hpp"
#include "hou/sys/scan_code.hpp"

#include "hou/sys/sys_config.hpp"



namespace hou
{

/** Functions related to the state of the keyboard.
 */
namespace keyboard
{

/** Checks if the key corresponding to the given key code is pressed.
 *
 * \param kc the key code.
 *
 * \return true if the key is pressed.
 */
HOU_SYS_API bool is_key_pressed(key_code kc) noexcept;

/** Checks if the key corresponding to the given scan code is pressed.
 *
 * \param sc the scan code.
 *
 * \return true if the key is pressed.
 */
HOU_SYS_API bool is_key_pressed(scan_code sc) noexcept;

/** Returns a bitfield representing the current state of the modifier keys.
 *
 * \return a bitfield with the bits of the modifier keys currentle pressed
 * set to 1.
 */
HOU_SYS_API modifier_keys get_modifier_keys_state() noexcept;

}  // namespace keyboard

}  // namespace hou

#endif
