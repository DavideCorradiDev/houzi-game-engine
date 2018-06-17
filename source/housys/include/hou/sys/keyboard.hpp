// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_KEYBOARD_HPP
#define HOU_SYS_KEYBOARD_HPP

#include "hou/sys/key_code.hpp"
#include "hou/sys/modifier_keys.hpp"
#include "hou/sys/scan_code.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/span.hpp"



namespace hou
{

class window;

/**
 * Functions related to the state of the keyboard.
 */
namespace keyboard
{

/**
 * Checks if the current platform has screen keyboard support.
 *
 * \return true if there is screenk keyboard support, false otherwise.
 */
HOU_SYS_API bool has_screen_keyboard_support();

/**
 * Checks if the screen keyboard is currently shown in a window.
 *
 * \param w the window to check.
 *
 * \return true if the screen keyboard is shown, false otherwise.
 */
HOU_SYS_API bool is_screen_keyboard_shown(window& w);

/**
 * Gets the state of all keys.
 *
 * The state is updated when processing the event queue.
 *
 * \return the state of all keys.
 */
HOU_SYS_API span<const uint8_t> get_keys_state();

/**
 * Checks if the key corresponding to the given key code is pressed.
 *
 * \param kc the key code.
 *
 * \return true if the key is pressed.
 */
HOU_SYS_API bool is_key_pressed(key_code kc);

/**
 * Checks if the key corresponding to the given scan code is pressed.
 *
 * \param sc the scan code.
 *
 * \return true if the key is pressed.
 */
HOU_SYS_API bool is_key_pressed(scan_code sc);

/**
 * Gets a bitfield representing the current state of the modifier keys.
 *
 * \return a bitfield with the bits of the modifier keys currentle pressed
 * set to 1.
 */
HOU_SYS_API modifier_keys get_modifier_keys();

/**
 * Sets the modifier keys state.
 *
 * \note this function will change the internal state of the modifier keys, but
 * will not change the state of the physical keyboard.
 *
 * \param value the value of the modifier keys.
 */
HOU_SYS_API void set_modifier_keys(modifier_keys value);

}  // namespace keyboard

}  // namespace hou

#endif
