// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_HPP
#define HOU_SYS_MOUSE_HPP

#include "hou/sys/mouse_button.hpp"

#include "hou/sys/sys_config.hpp"

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
 * \param button the button.
 *
 * \return true if the button is pressed.
 */
HOU_SYS_API bool is_button_pressed(mouse_button button) noexcept;

/** Retrieves the current mouse position relative to the screen.
 *
 * Position (0,0) represent the top left corner of the screen.
 *
 * \return the mouse position relative to the screen
 */
HOU_SYS_API vec2i get_position() noexcept;

/** Retrieves the current mouse position relative to the given window.
 *
 * Position (0,0) represent the top left corner of the given window.
 *
 * \param w the window to compute the mouse position relative to.
 *
 * \return the mouse position relative to the given window.
 */
HOU_SYS_API vec2i get_position(const window& w) noexcept;

/** Sets the position of the mouse relative to the screen.
 *
 * Position (0,0) represent the top left corner of the screen.
 *
 * \param value the position.
 */
HOU_SYS_API void set_position(const vec2i& value) noexcept;

/** Sets the position of the mouse relative to the given window.
 *
 * Position (0,0) represent the top left corner of the given window.
 *
 * \param value the position.
 *
 * \param w the window.
 */
HOU_SYS_API void set_position(const vec2i& value, const window& w) noexcept;

}  // namespace mouse

}  // namespace hou

#endif