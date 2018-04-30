// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/keyboard.hpp"



namespace hou
{

namespace keyboard
{

modifier_keys get_modifier_keys_state()
{
  modifier_keys modifier_keys = modifier_keys::none;
  if(is_key_pressed(scan_code::LAlt) || is_key_pressed(scan_code::RAlt))
  {
    modifier_keys |= modifier_keys::alt;
  }
  if(is_key_pressed(scan_code::LCtrl) || is_key_pressed(scan_code::RCtrl))
  {
    modifier_keys |= modifier_keys::ctrl;
  }
  if(is_key_pressed(scan_code::LShift) || is_key_pressed(scan_code::RShift))
  {
    modifier_keys |= modifier_keys::shift;
  }
  if(is_key_pressed(scan_code::LSystem) || is_key_pressed(scan_code::RSystem))
  {
    modifier_keys |= modifier_keys::system;
  }
  return modifier_keys;
}

}  // namespace keyboard

}  // namespace hou
