// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MOUSE_BUTTONS_HPP
#define HOU_SYS_MOUSE_BUTTONS_HPP

#include "hou/sys/mouse_button.hpp"

#include "hou/sys/sys_config.hpp"

#include <iostream>



namespace hou
{

/**
 * Represents the current status of the mouse buttons.
 */
class HOU_SYS_API mouse_buttons_state
{
public:
  /**
   * Underlying type.
   *
   * Each bit may correspond to a button.
   * If the bit is 1 the button is pressed, otherwise it is not pressed.
   */
  using bitfield_type = uint32_t;

public:
  /**
   * Creates with the given state.
   *
   * \param state the button state.
   */
  explicit mouse_buttons_state(bitfield_type state = 0u);

  /**
   * Gets the underlying state.
   *
   * \return the underlying state.
   */
  bitfield_type get() const;

  /**
   * Checks if a specific button is currently pressed.
   */
  bool check(mouse_button mb) const;

private:
  bitfield_type m_bitfield;
};

/**
 * Checks if two mouse_buttons_state objects are equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator==(mouse_buttons_state lhs, mouse_buttons_state rhs);

/**
 * Checks if two mouse_buttons_state objects are not equal.
 *
 * \param lhs the left operand.
 *
 * \param rhs the right operand.
 *
 * \return the result of the check.
 */
HOU_SYS_API bool operator!=(mouse_buttons_state lhs, mouse_buttons_state rhs);

/**
 * Writes a mouse_buttons_state object into a stream.
 *
 * \param os the stream.
 *
 * \param vm the display_mode object.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, mouse_buttons_state mbs);

}  // namespace hou

#endif
