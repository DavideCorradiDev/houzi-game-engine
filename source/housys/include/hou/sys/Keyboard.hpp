// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_KEYBOARD_HPP
#define HOU_SYS_KEYBOARD_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/KeyCode.hpp"
#include "hou/sys/ModifierKeys.hpp"
#include "hou/sys/ScanCode.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

/** Functions related to the state of the keyboard.
 */
namespace Keyboard
{

/** Checks if the key corresponding to the given key code is pressed.
 *
 *  \param kc the key code.
 *  \return true if the key is pressed.
 */
HOU_SYS_API bool isKeyPressed(KeyCode kc);

/** Checks if the key corresponding to the given scan code is pressed.
 *
 *  \param sc the scan code.
 *  \return true if the key is pressed.
 */
HOU_SYS_API bool isKeyPressed(ScanCode sc);

/** Checks if the key corresponding to the given key code is currently on.
 *
 *  \param kc the key code.
 *  \return true if the key is on.
 */
HOU_SYS_API bool isKeyToggled(KeyCode kc);

/** Checks if the key corresponding to the given scan code is currently on.
 *
 *  \param sc the scan code.
 *  \return true if the key is on.
 */
HOU_SYS_API bool isKeyToggled(ScanCode sc);

/** Returns a bitfield representing the current state of the modifier keys.
 *
 *  \return a bitfield with the bits of the modifier keys currentle pressed
 *  set to 1.
 */
HOU_SYS_API ModifierKeys getModifierKeysState();

}

}


#endif

