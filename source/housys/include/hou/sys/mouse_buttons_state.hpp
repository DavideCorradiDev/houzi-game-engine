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

class HOU_SYS_API mouse_buttons_state
{
public:
  using bitfield_type = uint32_t;

public:
  explicit mouse_buttons_state(bitfield_type state = 0u);

  bitfield_type get() const;
  bool check(mouse_button mb) const;

private:
  bitfield_type m_bitfield;
};

HOU_SYS_API bool operator==(mouse_buttons_state lhs, mouse_buttons_state rhs);
HOU_SYS_API bool operator!=(mouse_buttons_state lhs, mouse_buttons_state rhs);
HOU_SYS_API std::ostream& operator<<(std::ostream& os, mouse_buttons_state mbs);

}  // namespace hou

#endif
