// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/keyboard.hpp"

namespace hou
{

namespace keyboard
{

modifier_keys get_modifier_keys_state() noexcept
{
  modifier_keys modifier_keys = modifier_keys::none;
  if(is_key_pressed(scan_code::l_alt) || is_key_pressed(scan_code::r_alt))
  {
    modifier_keys |= modifier_keys::alt;
  }
  if(is_key_pressed(scan_code::l_ctrl) || is_key_pressed(scan_code::r_ctrl))
  {
    modifier_keys |= modifier_keys::ctrl;
  }
  if(is_key_pressed(scan_code::l_shift) || is_key_pressed(scan_code::r_shift))
  {
    modifier_keys |= modifier_keys::shift;
  }
  if(is_key_pressed(scan_code::l_system) || is_key_pressed(scan_code::r_system))
  {
    modifier_keys |= modifier_keys::system;
  }
  return modifier_keys;
}

}  // namespace keyboard

}  // namespace hou
