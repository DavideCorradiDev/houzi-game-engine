// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window_event.hpp"

#include "hou/cor/deprecated_error.hpp"

#include <iomanip>



namespace hou
{

window_event window_event::empty()
{
  window_event ev;
  ev.m_type = window_event_type::empty;
  return ev;
}



window_event window_event::closed()
{
  window_event ev;
  ev.m_type = window_event_type::closed;
  return ev;
}



window_event window_event::focus_gained()
{
  window_event ev;
  ev.m_type = window_event_type::focus_gained;
  return ev;
}



window_event window_event::focus_lost()
{
  window_event ev;
  ev.m_type = window_event_type::focus_lost;
  return ev;
}



window_event window_event::resized(uint x, uint y)
{
  window_event ev;
  ev.m_type = window_event_type::resized;
  ev.m_size.x = x;
  ev.m_size.y = y;
  return ev;
}



window_event window_event::key_pressed(
  key_code kc, scan_code sc, modifier_keys mod_keys)
{
  window_event ev;
  ev.m_type = window_event_type::key_pressed;
  ev.m_key.key_code = kc;
  ev.m_key.scan_code = sc;
  ev.m_key.modifier_keys = mod_keys;
  return ev;
}



window_event window_event::key_released(
  key_code kc, scan_code sc, modifier_keys mod_keys)
{
  window_event ev;
  ev.m_type = window_event_type::key_released;
  ev.m_key.key_code = kc;
  ev.m_key.scan_code = sc;
  ev.m_key.modifier_keys = mod_keys;
  return ev;
}



window_event window_event::text_entered(char32_t code_point)
{
  window_event ev;
  ev.m_type = window_event_type::text_entered;
  ev.m_text.code_point = code_point;
  return ev;
}



window_event window_event::mouse_moved(int x, int y)
{
  window_event ev;
  ev.m_type = window_event_type::mouse_moved;
  ev.m_mouse_move.x = x;
  ev.m_mouse_move.y = y;
  return ev;
}



window_event window_event::mouse_entered()
{
  window_event ev;
  ev.m_type = window_event_type::mouse_entered;
  return ev;
}



window_event window_event::mouse_left()
{
  window_event ev;
  ev.m_type = window_event_type::mouse_left;
  return ev;
}



window_event window_event::mouse_button_pressed(mouse_button mb, int x, int y)
{
  window_event ev;
  ev.m_type = window_event_type::mouse_button_pressed;
  ev.m_mouse_button.button = mb;
  ev.m_mouse_button.x = x;
  ev.m_mouse_button.y = y;
  return ev;
}



window_event window_event::mouse_button_released(mouse_button mb, int x, int y)
{
  window_event ev;
  ev.m_type = window_event_type::mouse_button_released;
  ev.m_mouse_button.button = mb;
  ev.m_mouse_button.x = x;
  ev.m_mouse_button.y = y;
  return ev;
}



window_event window_event::mouse_wheel_moved(
  mouse_wheel wheel, int delta, int x, int y)
{
  window_event ev;
  ev.m_type = window_event_type::mouse_wheel_moved;
  ev.m_mouse_wheel.wheel = wheel;
  ev.m_mouse_wheel.delta = delta;
  ev.m_mouse_wheel.x = x;
  ev.m_mouse_wheel.y = y;
  return ev;
}



window_event_type window_event::get_type() const
{
  return m_type;
}



const window_event::size_data& window_event::get_size_data() const
{
  DEPRECATED_HOU_EXPECT(m_type == window_event_type::resized);
  return m_size;
}



const window_event::key_data& window_event::get_key_data() const
{
  DEPRECATED_HOU_EXPECT(m_type == window_event_type::key_pressed
    || m_type == window_event_type::key_released);
  return m_key;
}



const window_event::text_data& window_event::get_text_data() const
{
  DEPRECATED_HOU_EXPECT(m_type == window_event_type::text_entered);
  return m_text;
}



const window_event::mouse_move_data& window_event::get_mouse_move_data() const
{
  DEPRECATED_HOU_EXPECT(m_type == window_event_type::mouse_moved);
  return m_mouse_move;
}



const window_event::mouse_button_data& window_event::get_mouse_button_data()
  const
{
  DEPRECATED_HOU_EXPECT(m_type == window_event_type::mouse_button_pressed
    || m_type == window_event_type::mouse_button_released);
  return m_mouse_button;
}



const window_event::mouse_wheel_data& window_event::get_mouse_wheel_data() const
{
  DEPRECATED_HOU_EXPECT(m_type == window_event_type::mouse_wheel_moved);
  return m_mouse_wheel;
}



window_event::window_event()
  : m_type()
{}



bool operator==(const window_event& l, const window_event& r)
{
  if(l.get_type() != r.get_type())
  {
    return false;
  }
  switch(l.get_type())
  {
    case window_event_type::resized:
      return l.get_size_data() == r.get_size_data();
    case window_event_type::key_pressed:
    case window_event_type::key_released:
      return l.get_key_data() == r.get_key_data();
    case window_event_type::text_entered:
      return l.get_text_data() == r.get_text_data();
    case window_event_type::mouse_moved:
      return l.get_mouse_move_data() == r.get_mouse_move_data();
    case window_event_type::mouse_button_pressed:
    case window_event_type::mouse_button_released:
      return l.get_mouse_button_data() == r.get_mouse_button_data();
    case window_event_type::mouse_wheel_moved:
      return l.get_mouse_wheel_data() == r.get_mouse_wheel_data();
    case window_event_type::empty:
    case window_event_type::closed:
    case window_event_type::focus_gained:
    case window_event_type::focus_lost:
    case window_event_type::mouse_entered:
    case window_event_type::mouse_left:
    default:
      return true;
  }
}



bool operator!=(const window_event& l, const window_event& r)
{
  return !(l == r);
}



bool operator==(
  const window_event::size_data& l, const window_event::size_data& r)
{
  return l.x == r.x && l.y == r.y;
}



bool operator==(
  const window_event::key_data& l, const window_event::key_data& r)
{
  return l.key_code == r.key_code && l.scan_code == r.scan_code
    && l.modifier_keys == r.modifier_keys;
}



bool operator==(
  const window_event::text_data& l, const window_event::text_data& r)
{
  return l.code_point == r.code_point;
}



bool operator==(const window_event::mouse_move_data& l,
  const window_event::mouse_move_data& r)
{
  return l.x == r.x && l.y == r.y;
}



bool operator==(const window_event::mouse_button_data& l,
  const window_event::mouse_button_data& r)
{
  return l.button == r.button && l.x == r.x && l.y == r.y;
}



bool operator==(const window_event::mouse_wheel_data& l,
  const window_event::mouse_wheel_data& r)
{
  return l.wheel == r.wheel && l.delta == r.delta && l.x == r.x && l.y == r.y;
}



bool operator!=(
  const window_event::size_data& l, const window_event::size_data& r)
{
  return !(l == r);
}



bool operator!=(
  const window_event::key_data& l, const window_event::key_data& r)
{
  return !(l == r);
}



bool operator!=(
  const window_event::text_data& l, const window_event::text_data& r)
{
  return !(l == r);
}



bool operator!=(const window_event::mouse_move_data& l,
  const window_event::mouse_move_data& r)
{
  return !(l == r);
}



bool operator!=(const window_event::mouse_button_data& l,
  const window_event::mouse_button_data& r)
{
  return !(l == r);
}



bool operator!=(const window_event::mouse_wheel_data& l,
  const window_event::mouse_wheel_data& r)
{
  return !(l == r);
}



std::ostream& operator<<(std::ostream& os, const window_event& e)
{
  os << "{type = " << e.get_type() << ", data = ";
  switch(e.get_type())
  {
    case window_event_type::resized:
      os << e.get_size_data();
      break;
    case window_event_type::key_pressed:
    case window_event_type::key_released:
      os << e.get_key_data();
      break;
    case window_event_type::text_entered:
      os << e.get_text_data();
      break;
    case window_event_type::mouse_moved:
      os << e.get_mouse_move_data();
      break;
    case window_event_type::mouse_button_pressed:
    case window_event_type::mouse_button_released:
      os << e.get_mouse_button_data();
      break;
    case window_event_type::mouse_wheel_moved:
      os << e.get_mouse_wheel_data();
      break;
    case window_event_type::empty:
    case window_event_type::closed:
    case window_event_type::focus_gained:
    case window_event_type::focus_lost:
    case window_event_type::mouse_entered:
    case window_event_type::mouse_left:
      os << "{}";
    default:
      break;
  }
  return os << "}";
}



std::ostream& operator<<(std::ostream& os, const window_event::size_data& e)
{
  return os << "{size_type = (" << e.x << ", " << e.y << ")}";
}



std::ostream& operator<<(std::ostream& os, const window_event::key_data& e)
{
  return os << "{key_code = " << e.key_code << ", scan_code = " << e.scan_code
            << ", modifier_keys = " << e.modifier_keys << "}";
}



std::ostream& operator<<(std::ostream& os, const window_event::text_data& e)
{
  class unicode_output_formatter
  {
  public:
    unicode_output_formatter(std::ostream& os)
      : mOldState(nullptr)
    {
      mOldState.copyfmt(os);
      os << std::setfill('0') << std::setw(8) << std::hex;
    }

    ~unicode_output_formatter()
    {
      std::cout.copyfmt(mOldState);
    }

  private:
    std::ios mOldState;
  };

  os << "{code_point = 0x";
  {
    unicode_output_formatter of(os);
    os << static_cast<uint32_t>(e.code_point);
  }
  return os << "}";
}



std::ostream& operator<<(
  std::ostream& os, const window_event::mouse_move_data& e)
{
  return os << "{position = (" << e.x << ", " << e.y << ")}";
}



std::ostream& operator<<(
  std::ostream& os, const window_event::mouse_button_data& e)
{
  return os << "{button = " << e.button << ", position = (" << e.x << ", "
            << e.y << ")}";
}



std::ostream& operator<<(
  std::ostream& os, const window_event::mouse_wheel_data& e)
{
  return os << "{wheel = " << e.wheel << ", delta = " << e.delta
            << ", position = (" << e.x << ", " << e.y << ")}";
}

}  // namespace hou
