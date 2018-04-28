// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_HPP
#define HOU_SYS_MOUSE_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/sys/MouseButton.hpp"

#include "hou/cor/basic_types.hpp"

#include "hou/mth/MatrixFwd.hpp"



namespace hou
{

class Window;

/** Functions related to the state of the mouse.
*/
namespace Mouse
{

/** Checks if a button is pressed.
 *
 *  \param button the button.
 *  \return true if the button is pressed.
 */
HOU_SYS_API bool isButtonPressed(MouseButton button);

/** Retrieves the current mouse position relative to the screen.
 *
 *  Coordinates (0,0) represent the top left corner of the screen.
 *
 *  \return the mouse position relative to the screen
 */
HOU_SYS_API Vec2i getPosition();

/** Retrieves the current mouse position relative to the given window.
 *
 *  Coordinates (0,0) represent the top left corner of the given window.
 *
 *  \param window the window to compute the mouse position relative to.
 *  \return the mouse position relative to the given window.
 */
HOU_SYS_API Vec2i getPosition(const Window& window);

/** Sets the position of the mouse relative to the screen.
 *
 *  Coordinates (0,0) represent the top left corner of the screen.
 *
 *  \param value the position.
 */
HOU_SYS_API void setPosition(const Vec2i& value);

/** Sets the position of the mouse relative to the given window.
 *
 *  Coordinates (0,0) represent the top left corner of the given window.
 *
 *  \param value the position.
 *  \param window the window.
 */
HOU_SYS_API void setPosition(const Vec2i& value, const Window& window);

}

}

#endif

