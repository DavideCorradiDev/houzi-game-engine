// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_EVENT_HPP
#define HOU_SYS_WINDOW_EVENT_HPP

#include "hou/sys/sys_export.hpp"

#include "hou/sys/key_code.hpp"
#include "hou/sys/modifier_keys.hpp"
#include "hou/sys/mouse_button.hpp"
#include "hou/sys/mouse_wheel.hpp"
#include "hou/sys/scan_code.hpp"
#include "hou/sys/window_event_type.hpp"

#include "hou/cor/basic_types.hpp"



namespace hou
{

/** Class representing a window event.
 *
 */
class HOU_SYS_API window_event
{
public:
  /** Struct containing data for ph_window resized events. */
  struct size_data
  {
    /** The new size on the x axis. */
    uint x;
    /** The new size on the y axis. */
    uint y;
  };

  /** Struct containing data for key pressed and key released events. */
  struct key_data
  {
    /** The key code corresponding to the relevant key. */
    key_code key_code;
    /** The scan code corresponding to the relevant key. */
    scan_code scan_code;
    /** Bitfield indicating what modifier keys were pressed. */
    modifier_keys modifier_keys;
  };

  /** Struct containing data for text entered events. */
  struct text_data
  {
    /** The Unicode code point corresponding to the entered character. */
    char32_t code_point;
  };

  /** Struct containing data for mouse moved events. */
  struct mouse_move_data
  {
    /** The position of the mouse cursor on the x axis. */
    int x;
    /** The position of the mouse cursor on the y axis. */
    int y;
  };

  /** Struct containing data for mouse button pressed and released events. */
  struct mouse_button_data
  {
    /** The relevant mouse button. */
    mouse_button button;
    /** The position of the mouse cursor on the x axis. */
    int x;
    /** The position of the mouse cursor on the y axis. */
    int y;
  };

  /** Struct containing data for mouse wheel events. */
  struct mouse_wheel_data
  {
    /** The relevant mouse wheel. */
    mouse_wheel wheel;
    /** The delta of the mouse wheel position. */
    int delta;
    /** The position of the mouse cursor on the x axis. */
    int x;
    /** The position of the mouse cursor on the y axis. */
    int y;
  };

public:
  /** Creates an empty ph_window event.
   *
   *  \return the ph_window event.
   */
  static window_event empty();

  /** Creates a ph_window closed event.
   *
   *  \return the ph_window event.
   */
  static window_event closed();

  /** Creates a ph_window focus gained event.
   *
   *  \return the ph_window event.
   */
  static window_event focus_gained();

  /** Creates a ph_window focus lost event.
   *
   *  \return the ph_window event.
   */
  static window_event focus_lost();

  /** Creates a mouse entered ph_window event.
   *
   *  \return the ph_window event.
   */
  static window_event mouse_entered();

  /** Creates a mouse left ph_window event.
   *
   *  \return the ph_window event.
   */
  static window_event mouse_left();

  /** Creates a ph_window resized lost event.
   *
   *  \param x the x size after the resizing.
   *  \param y the y size after the resizing.
   *  \return the ph_window event.
   */
  static window_event resized(uint x, uint y);

  /** Creates a key pressed ph_window event.
   *
   *  \param kc the key code.
   *  \param sc the scan code.
   *  \param modKeys a bitfield indicating what modifier keys were pressed.
   *  \return the ph_window event.
   */
  static window_event key_pressed(key_code kc, scan_code sc, modifier_keys modKeys);

  /** Creates a key released ph_window event.
   *
   *  \param kc the key code.
   *  \param sc the scan code.
   *  \param modKeys a bitfield indicating what modifier keys were pressed.
   *  \return the ph_window event.
   */
  static window_event key_released(key_code kc, scan_code sc, modifier_keys modKeys);

  /** Creates a text entered ph_window event.
   *
   *  \param code_point the Unicode code point of the entere character.
   *  \return the ph_window event.
   */
  static window_event text_entered(char32_t code_point);

  /** Creates a mouse moved ph_window event.
   *
   *  \param x the position of the cursor on the x axis.
   *  \param y the position of the cursor on the y axis.
   *  \return the ph_window event.
   */
  static window_event mouse_moved(int x, int y);

  /** Creates a mouse button pressed ph_window event.
   *
   *  \param mb the mouse button.
   *  \param x the position of the cursor on the x axis.
   *  \param y the position of the cursor on the y axis.
   *  \return the ph_window event.
   */
  static window_event mouse_button_pressed(mouse_button mb, int x, int y);

  /** Creates a mouse button released ph_window event.
   *
   *  \param mb the mouse button.
   *  \param x the position of the cursor on the x axis.
   *  \param y the position of the cursor on the y axis.
   *  \return the ph_window event.
   */
  static window_event mouse_button_released(mouse_button mb, int x, int y);

  /** Creates a mouse wheel moved ph_window event.
   *
   *  \param wheel the mouse wheel.
   *  \param delta the wheel position delta.
   *  \param x the position of the cursor on the x axis.
   *  \param y the position of the cursor on the y axis.
   *  \return the ph_window event.
   */
  static window_event mouse_wheel_moved(mouse_wheel wheel, int delta, int x
    , int y);

public:
  /** Retrieves the type of the ph_window event.
   *
   *  \return the type of the ph_window event.
   */
  window_event_type get_type() const;

  /** Returns the size data of this event.
   *
   *  Throws if the event is not of type resized.
   *
   *  \return the event data.
   */
  const size_data& get_size_data() const;

  /** Returns the key data of this event.
   *
   *  Throws if the event is not of type key_pressed or key_released.
   *
   *  \return the event data.
   */
  const key_data& get_key_data() const;

  /** Returns the text data of this event.
   *
   *  Throws if the event is not of type TextEntered.
   *
   *  \return the event data.
   */
  const text_data& get_text_data() const;

  /** Returns the mouse moved data of this event.
   *
   *  Throws if the event is not of type mouse_moved.
   *
   *  \return the event data.
   */
  const mouse_move_data& get_mouse_move_data() const;

  /** Returns the mouse button data of this event.
   *
   *  Throws if the event is not of type mouse_button_pressed or mouse_button_released.
   *
   *  \return the event data.
   */
  const mouse_button_data& get_mouse_button_data() const;

  /** Returns the mouse wheel moved data of this event.
   *
   *  Throws if the event is not of type mouse_wheel_moved.
   *
   *  \return the event data.
   */
  const mouse_wheel_data& get_mouse_wheel_data() const;

private:
  window_event();

private:
  window_event_type m_type;
  union
  {
    size_data m_size;
    key_data m_key;
    text_data m_text;
    mouse_move_data m_mouse_move;
    mouse_button_data m_mouse_button;
    mouse_wheel_data m_mouse_wheel;
  };
};

/** Checks if two window_event objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event& lhs, const window_event& rhs);

/** Checks if two size_data objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event::size_data& lhs
  , const window_event::size_data& rhs);

/** Checks if two key_data objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event::key_data& lhs
  , const window_event::key_data& rhs);

/** Checks if two text_data objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event::text_data& lhs
  , const window_event::text_data& rhs);

/** Checks if two mouse_move_data objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event::mouse_move_data& lhs
  , const window_event::mouse_move_data& rhs);

/** Checks if two mouse_button_data objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event::mouse_button_data& lhs
  , const window_event::mouse_button_data& rhs);

/** Checks if two mouse_wheel_data objects are equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator==(const window_event::mouse_wheel_data& lhs
  , const window_event::mouse_wheel_data& rhs);

/** Checks if two window_event objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event& lhs, const window_event& rhs);

/** Checks if two size_data objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event::size_data& lhs
  , const window_event::size_data& rhs);

/** Checks if two key_data objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event::key_data& lhs
  , const window_event::key_data& rhs);

/** Checks if two text_data objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event::text_data& lhs
  , const window_event::text_data& rhs);

/** Checks if two mouse_move_data objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event::mouse_move_data& lhs
  , const window_event::mouse_move_data& rhs);

/** Checks if two mouse_button_data objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event::mouse_button_data& lhs
  , const window_event::mouse_button_data& rhs);

/** Checks if two mouse_wheel_data objects are not equal.
 *
 *  \param lhs the left operand.
 *  \param rhs the right operand.
 *  \return the result of the check.
 */
HOU_SYS_API bool operator!=(const window_event::mouse_wheel_data& lhs
  , const window_event::mouse_wheel_data& rhs);

/** Writes a window_event object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the window_event object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, const window_event& e);

/** Writes a size_data object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the size_data object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const window_event::size_data& e);

/** Writes a key_data object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the key_data object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const window_event::key_data& e);

/** Writes a text_data object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the text_data object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const window_event::text_data& e);

/** Writes a mouse_move_data object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the mouse_move_data object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const window_event::mouse_move_data& e);

/** Writes a mouse_button_data object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the mouse_button_data object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const window_event::mouse_button_data& e);

/** Writes a mouse_wheel_data object into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param e the mouse_wheel_data object.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os
  , const window_event::mouse_wheel_data& e);

}

#endif

