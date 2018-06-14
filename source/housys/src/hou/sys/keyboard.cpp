// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/keyboard.hpp"

#include "hou/sys/window.hpp"



namespace hou
{

namespace keyboard
{

bool has_screen_keyboard_support()
{
  return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}



bool is_screen_keyboard_shown(window& w)
{
  return SDL_IsScreenKeyboardShown(w.get_impl());
}



span<const uint8_t> get_keys_state()
{
  int keys_n = 0;
  const uint8_t* keys = SDL_GetKeyboardState(&keys_n);
  return span<const uint8_t>(keys, keys_n);
}



bool is_key_pressed(key_code kc)
{
  return is_key_pressed(get_scan_code(kc));
}



bool is_key_pressed(scan_code sc)
{
  return get_keys_state().at(
    static_cast<std::underlying_type<scan_code>::type>(sc));
}



modifier_keys get_modifier_keys()
{
  return modifier_keys(SDL_GetModState());
}



void set_modifier_keys(modifier_keys value)
{
  SDL_SetModState(static_cast<SDL_Keymod>(value));
}

}  // namespace keyboard

}  // namespace hou
