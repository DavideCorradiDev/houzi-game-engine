// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SCAN_CODE_HPP
#define HOU_SYS_SCAN_CODE_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_scancode.h"

#include <iostream>



namespace hou
{

/**
 * Keyboard scan code.
 *
 * A scan code identifies a key by its phyical position on the keyboard.
 * It is therefore independent from the current keyboard layout.
 * For example, scan_code::z would refer to the same key on a US, German or
 * French layout.
 *
 * The naming refers to the position of the keys on a US keyboard.
 */
enum class scan_code
{
  // Function keys
  f1 = SDL_SCANCODE_F1,
  f2 = SDL_SCANCODE_F2,
  f3 = SDL_SCANCODE_F3,
  f4 = SDL_SCANCODE_F4,
  f5 = SDL_SCANCODE_F5,
  f6 = SDL_SCANCODE_F6,
  f7 = SDL_SCANCODE_F7,
  f8 = SDL_SCANCODE_F8,
  f9 = SDL_SCANCODE_F9,
  f10 = SDL_SCANCODE_F10,
  f11 = SDL_SCANCODE_F11,
  f12 = SDL_SCANCODE_F12,

  // Numpad
  numpad0 = SDL_SCANCODE_KP_0,
  numpad1 = SDL_SCANCODE_KP_1,
  numpad2 = SDL_SCANCODE_KP_2,
  numpad3 = SDL_SCANCODE_KP_3,
  numpad4 = SDL_SCANCODE_KP_4,
  numpad5 = SDL_SCANCODE_KP_5,
  numpad6 = SDL_SCANCODE_KP_6,
  numpad7 = SDL_SCANCODE_KP_7,
  numpad8 = SDL_SCANCODE_KP_8,
  numpad9 = SDL_SCANCODE_KP_9,
  numpad_plus = SDL_SCANCODE_KP_PLUS,
  numpad_minus = SDL_SCANCODE_KP_MINUS,
  numpad_multiply = SDL_SCANCODE_KP_MULTIPLY,
  numpad_divide = SDL_SCANCODE_KP_DIVIDE,
  numpad_decimal = SDL_SCANCODE_KP_DECIMAL,
  numpad_enter = SDL_SCANCODE_KP_ENTER,

  // Navigation
  page_up = SDL_SCANCODE_PAGEUP,
  page_down = SDL_SCANCODE_PAGEDOWN,
  end = SDL_SCANCODE_END,
  home = SDL_SCANCODE_HOME,
  insert = SDL_SCANCODE_INSERT,
  del = SDL_SCANCODE_DELETE,
  backspace = SDL_SCANCODE_BACKSPACE,
  left = SDL_SCANCODE_LEFT,
  right = SDL_SCANCODE_RIGHT,
  up = SDL_SCANCODE_UP,
  down = SDL_SCANCODE_DOWN,

  // Numbers
  num0 = SDL_SCANCODE_0,
  num1 = SDL_SCANCODE_1,
  num2 = SDL_SCANCODE_2,
  num3 = SDL_SCANCODE_3,
  num4 = SDL_SCANCODE_4,
  num5 = SDL_SCANCODE_5,
  num6 = SDL_SCANCODE_6,
  num7 = SDL_SCANCODE_7,
  num8 = SDL_SCANCODE_8,
  num9 = SDL_SCANCODE_9,

  //  Characters
  a = SDL_SCANCODE_A,
  b = SDL_SCANCODE_B,
  c = SDL_SCANCODE_C,
  d = SDL_SCANCODE_D,
  e = SDL_SCANCODE_E,
  f = SDL_SCANCODE_F,
  g = SDL_SCANCODE_G,
  h = SDL_SCANCODE_H,
  i = SDL_SCANCODE_I,
  j = SDL_SCANCODE_J,
  k = SDL_SCANCODE_K,
  l = SDL_SCANCODE_L,
  m = SDL_SCANCODE_M,
  n = SDL_SCANCODE_N,
  o = SDL_SCANCODE_O,
  p = SDL_SCANCODE_P,
  q = SDL_SCANCODE_Q,
  r = SDL_SCANCODE_R,
  s = SDL_SCANCODE_S,
  t = SDL_SCANCODE_T,
  u = SDL_SCANCODE_U,
  v = SDL_SCANCODE_V,
  x = SDL_SCANCODE_X,
  y = SDL_SCANCODE_Y,
  w = SDL_SCANCODE_W,
  z = SDL_SCANCODE_Z,

  // Punctuation
  lbracket = SDL_SCANCODE_LEFTBRACKET,
  rbracket = SDL_SCANCODE_RIGHTBRACKET,
  apostrophe = SDL_SCANCODE_APOSTROPHE,
  backslash = SDL_SCANCODE_BACKSLASH,
  comma = SDL_SCANCODE_COMMA,
  dash = SDL_SCANCODE_MINUS,
  enter = SDL_SCANCODE_RETURN,
  equal = SDL_SCANCODE_EQUALS,
  period = SDL_SCANCODE_PERIOD,
  grave = SDL_SCANCODE_GRAVE,
  semicolon = SDL_SCANCODE_SEMICOLON,
  slash = SDL_SCANCODE_SLASH,
  space = SDL_SCANCODE_SPACE,
  tab = SDL_SCANCODE_TAB,

  // Modifier keys
  caps_lock = SDL_SCANCODE_CAPSLOCK,
  num_lock = SDL_SCANCODE_NUMLOCKCLEAR,
  scroll_lock = SDL_SCANCODE_SCROLLLOCK,
  lctrl = SDL_SCANCODE_LCTRL,
  rctrl = SDL_SCANCODE_RCTRL,
  lalt = SDL_SCANCODE_LALT,
  ralt = SDL_SCANCODE_RALT,
  lshift = SDL_SCANCODE_LSHIFT,
  rshift = SDL_SCANCODE_RSHIFT,
  lsystem = SDL_SCANCODE_LGUI,
  rsystem = SDL_SCANCODE_RGUI,

  // Application control
  ac_back = SDL_SCANCODE_AC_BACK,
  ac_forward = SDL_SCANCODE_AC_FORWARD,
  ac_refresh = SDL_SCANCODE_AC_REFRESH,
  ac_stop = SDL_SCANCODE_AC_STOP,
  ac_search = SDL_SCANCODE_AC_SEARCH,
  ac_bookmarks = SDL_SCANCODE_AC_BOOKMARKS,
  ac_home = SDL_SCANCODE_AC_HOME,

  // Sound and media.
  volume_up = SDL_SCANCODE_VOLUMEUP,
  volume_down = SDL_SCANCODE_VOLUMEDOWN,
  mute = SDL_SCANCODE_AUDIOMUTE,
  media_next_track = SDL_SCANCODE_AUDIONEXT,
  media_previous_track = SDL_SCANCODE_AUDIOPREV,
  media_stop = SDL_SCANCODE_AUDIOSTOP,
  media_play_pause = SDL_SCANCODE_AUDIOPLAY,
  launch_media_select = SDL_SCANCODE_MEDIASELECT,
  launch_mail = SDL_SCANCODE_MAIL,

  // Others
  again = SDL_SCANCODE_AGAIN,
  alt_erase = SDL_SCANCODE_ALTERASE,
  application = SDL_SCANCODE_APPLICATION,
  brightness_up = SDL_SCANCODE_BRIGHTNESSUP,
  brightness_down = SDL_SCANCODE_BRIGHTNESSDOWN,
  calculator = SDL_SCANCODE_CALCULATOR,
  cancel = SDL_SCANCODE_CANCEL,
  clear_again = SDL_SCANCODE_CLEARAGAIN,
  computer = SDL_SCANCODE_COMPUTER,
  copy = SDL_SCANCODE_COPY,
  crsel = SDL_SCANCODE_CRSEL,
  currency_sub_unit = SDL_SCANCODE_CURRENCYSUBUNIT,
  currency_unit = SDL_SCANCODE_CURRENCYUNIT,
  cut = SDL_SCANCODE_CUT,
  decimal_separator = SDL_SCANCODE_DECIMALSEPARATOR,
  display_switch = SDL_SCANCODE_DISPLAYSWITCH,
  eject = SDL_SCANCODE_EJECT,
  escape = SDL_SCANCODE_ESCAPE,
  execute = SDL_SCANCODE_EXECUTE,
  exsel = SDL_SCANCODE_EXSEL,
  find = SDL_SCANCODE_FIND,
  help = SDL_SCANCODE_HELP,
  illumination_down = SDL_SCANCODE_KBDILLUMDOWN,
  illumination_up = SDL_SCANCODE_KBDILLUMUP,
  illumination_toggle = SDL_SCANCODE_KBDILLUMTOGGLE,
  oper = SDL_SCANCODE_OPER,
  out = SDL_SCANCODE_OUT,
  paste = SDL_SCANCODE_PASTE,
  pause = SDL_SCANCODE_PAUSE,
  power = SDL_SCANCODE_POWER,
  print_screen = SDL_SCANCODE_PRINTSCREEN,
  prior = SDL_SCANCODE_PRIOR,
  separator = SDL_SCANCODE_SEPARATOR,
  select = SDL_SCANCODE_SELECT,
  sleep = SDL_SCANCODE_SLEEP,
  sys_req = SDL_SCANCODE_SYSREQ,
  thousands_separator = SDL_SCANCODE_THOUSANDSSEPARATOR,
  undo = SDL_SCANCODE_UNDO,
  www = SDL_SCANCODE_WWW,

  // Scan codes without associated key code.
  international1 = SDL_SCANCODE_INTERNATIONAL1,
  international2 = SDL_SCANCODE_INTERNATIONAL2,
  international3 = SDL_SCANCODE_INTERNATIONAL3,
  international4 = SDL_SCANCODE_INTERNATIONAL4,
  international5 = SDL_SCANCODE_INTERNATIONAL5,
  international6 = SDL_SCANCODE_INTERNATIONAL6,
  international7 = SDL_SCANCODE_INTERNATIONAL7,
  international8 = SDL_SCANCODE_INTERNATIONAL8,
  international9 = SDL_SCANCODE_INTERNATIONAL9,
  language1 = SDL_SCANCODE_LANG1,
  language2 = SDL_SCANCODE_LANG2,
  language3 = SDL_SCANCODE_LANG3,
  language4 = SDL_SCANCODE_LANG4,
  language5 = SDL_SCANCODE_LANG5,
  language6 = SDL_SCANCODE_LANG6,
  language7 = SDL_SCANCODE_LANG7,
  language8 = SDL_SCANCODE_LANG8,
  language9 = SDL_SCANCODE_LANG9,
  non_us_backslash = SDL_SCANCODE_NONUSBACKSLASH,
  non_us_hash = SDL_SCANCODE_NONUSHASH,
};

/**
 * Writes a scan_code enum into a stream.
 *
 * \param os the stream.
 *
 * \param sc the scan_code enum.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, scan_code sc);

}  // namespace hou

#endif
