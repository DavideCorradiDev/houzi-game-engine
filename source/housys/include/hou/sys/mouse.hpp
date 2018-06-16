// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_HPP
#define HOU_SYS_MOUSE_HPP

#include "hou/sys/mouse_button.hpp"
#include "hou/sys/mouse_buttons_state.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/mth/matrix_fwd.hpp"



namespace hou
{

class window;

/** Functions related to the state of the mouse.
 */
namespace mouse
{

// May fail, may not be supported.
HOU_SYS_API bool set_capture(bool value);

HOU_SYS_API bool is_cursor_hidden();

HOU_SYS_API void set_cursor_hidden(bool value);

HOU_SYS_API bool is_relative_mode();

// May fail, may not be supported.
HOU_SYS_API bool set_relative_mode(bool value);

HOU_SYS_API mouse_buttons_state get_buttons_state();

/** Checks if a button is pressed.
 *
 * \param mb the button.
 *
 * \return true if the button is pressed.
 */
HOU_SYS_API bool is_button_pressed(mouse_button mb);

/** Retrieves the current mouse position relative to the screen.
 *
 * Position (0,0) represent the top left corner of the screen.
 *
 * \return the mouse position relative to the screen
 */
HOU_SYS_API vec2i get_position();

/** Retrieves the current mouse position relative to the given window.
 *
 * Position (0,0) represent the top left corner of the given window.
 *
 * \param w the window to compute the mouse position relative to.
 *
 * \return the mouse position relative to the given window.
 */
HOU_SYS_API vec2i get_position(const window& w);

// Since initialization or last call.
HOU_SYS_API vec2i get_position_delta();

/** Sets the position of the mouse relative to the screen.
 *
 * Position (0,0) represent the top left corner of the screen.
 *
 * \param pos the position.
 */
HOU_SYS_API void set_position(const vec2i& pos);

/** Sets the position of the mouse relative to the given window.
 *
 * Position (0,0) represent the top left corner of the given window.
 *
 * \param pos the position.
 *
 * \param w the window.
 */
HOU_SYS_API void set_position(const vec2i& pos, const window& w);

}  // namespace mouse

}  // namespace hou

#endif
