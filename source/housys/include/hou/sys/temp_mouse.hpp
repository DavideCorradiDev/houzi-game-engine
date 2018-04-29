// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_HPP
#define HOU_SYS_MOUSE_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/sys/mouse_button.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/mth/matrix_fwd.hpp"



namespace hou
{

class window;

/** Functions related to the state of the mouse.
*/
namespace mouse
{

/** Checks if a button is pressed.
 *
 *  \param button the button.
 *  \return true if the button is pressed.
 */
HOU_SYS_API bool is_button_pressed(mouse_button button);

/** Retrieves the current mouse position relative to the screen.
 *
 *  offset_type (0,0) represent the top left corner of the screen.
 *
 *  \return the mouse position relative to the screen
 */
HOU_SYS_API vec2i get_position();

/** Retrieves the current mouse position relative to the given ph_window.
 *
 *  offset_type (0,0) represent the top left corner of the given ph_window.
 *
 *  \param ph_window the ph_window to compute the mouse position relative to.
 *  \return the mouse position relative to the given ph_window.
 */
HOU_SYS_API vec2i get_position(const window& ph_window);

/** Sets the position of the mouse relative to the screen.
 *
 *  offset_type (0,0) represent the top left corner of the screen.
 *
 *  \param value the position.
 */
HOU_SYS_API void set_position(const vec2i& value);

/** Sets the position of the mouse relative to the given ph_window.
 *
 *  offset_type (0,0) represent the top left corner of the given ph_window.
 *
 *  \param value the position.
 *  \param ph_window the ph_window.
 */
HOU_SYS_API void set_position(const vec2i& value, const window& ph_window);

}

}

#endif

