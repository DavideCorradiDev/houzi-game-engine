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

/**
 * Functions related to the state of the mouse.
 */
namespace mouse
{

/**
 * Sets mouse capture.
 *
 * Mouse capture causes mouse events to be registered even when the mouse is
 * not inside a window created by this library.
 *
 * \note mouse capture might not be supported on some platforms.
 *
 * \param value true to capture the mouse ,false otherwise.
 *
 * \return true if the call was successfull, false otherwise.
 */
HOU_SYS_API bool set_capture(bool value);

/**
 * Checks if the mouse cursor is visible.
 *
 * \return true if the mouse cursor is visible.
 */
HOU_SYS_API bool is_cursor_visible();

/**
 * Sets the visibility of the mouse cursor.
 *
 * \param value true to show the mouse cursor, false to hide the mouse cursor.
 */
HOU_SYS_API void set_cursor_visible(bool value);

/**
 * Checks if relative mode active.
 *
 * \return true if relative mode is active.
 */
HOU_SYS_API bool is_relative_mode();

/**
 * Sets relative mode for the mouse.
 *
 * \note relative mode might not be supported.
 *
 * \param value true if relative mode should be activated, false otherwise.
 *
 * \return true if the call was successfull, false otherwise.
 */
HOU_SYS_API bool set_relative_mode(bool value);

/**
 * Gets the state of the mouse buttons.
 *
 * \return the state of the mouse buttons.
 */
HOU_SYS_API mouse_buttons_state get_buttons_state();

/** Checks if a button is pressed.
 *
 * \param mb the button.
 *
 * \return true if the button is pressed.
 */
HOU_SYS_API bool is_button_pressed(mouse_button mb);

/**
 * Gets the current mouse position relative to the screen.
 *
 * Position (0,0) represent the top left corner of the screen.
 *
 * \return the mouse position relative to the screen
 */
HOU_SYS_API vec2i get_position();

/**
 * Gets the current mouse position relative to the given window.
 *
 * Position (0,0) represent the top left corner of the given window.
 *
 * \param w the window to compute the mouse position relative to.
 *
 * \return the mouse position relative to the given window.
 */
HOU_SYS_API vec2i get_position(const window& w);

/**
 * Gets the differnce in the position of the mouse since the last call.
 *
 * The first time this function is called, the difference is relative to the
 * position of the mouse at the moment the system module was initialized.
 *
 * \return the difference in the mouse position.
 */
HOU_SYS_API vec2i get_position_delta();

/**
 * Sets the position of the mouse relative to the screen.
 *
 * Position (0,0) represent the top left corner of the screen.
 *
 * \param pos the position.
 */
HOU_SYS_API void set_position(const vec2i& pos);

/**
 * Sets the position of the mouse relative to the given window.
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
