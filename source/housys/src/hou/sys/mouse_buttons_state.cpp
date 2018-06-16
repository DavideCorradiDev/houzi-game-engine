// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/mouse_buttons_state.hpp"

#include "hou/cor/std_vector.hpp"



namespace hou
{

mouse_buttons_state::mouse_buttons_state(bitfield_type bitfield)
  : m_bitfield(bitfield)
{}



mouse_buttons_state::bitfield_type mouse_buttons_state::get() const
{
  return m_bitfield;
}



bool mouse_buttons_state::check(mouse_button mb) const
{
  return m_bitfield
    & SDL_BUTTON(static_cast<std::underlying_type<mouse_button>::type>(mb));
}



bool operator==(mouse_buttons_state lhs, mouse_buttons_state rhs)
{
  return lhs.get() == rhs.get();
}



bool operator!=(mouse_buttons_state lhs, mouse_buttons_state rhs)
{
  return lhs.get() != rhs.get();
}



std::ostream& operator<<(std::ostream& os, mouse_buttons_state mbs)
{
  if(mbs.get() == 0)
  {
    return os << "none";
  }

  static const std::vector<mouse_button> buttons = {mouse_button::lb,
    mouse_button::mb, mouse_button::rb, mouse_button::xb1, mouse_button::xb2};
  bool match_found = false;
  for(auto mb : buttons)
  {
    if(mbs.check(mb))
    {
      os << (match_found ? " | " : "") << mb;
      match_found = true;
    }
  }
  return os;
}

}  // namespace hou
