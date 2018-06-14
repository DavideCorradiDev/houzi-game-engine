// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_KEY_CODE_HPP
#define HOU_SYS_KEY_CODE_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_keyboard.h"

#include <iostream>



namespace hou
{

enum class scan_code;

/**
 * Keyboard key code.
 *
 * A key code identifies a key by its value under the current keyboard layout.
 * For example, the key corresponding to key_code::z in a US layout will
 * correspond to key_code::y in a German layout and to key_code::w in a French
 * layout.
 */
enum class key_code
{
  // Unknown.
  unknown = SDLK_UNKNOWN,

  // Function keys
  f1 = SDLK_F1,
  f2 = SDLK_F2,
  f3 = SDLK_F3,
  f4 = SDLK_F4,
  f5 = SDLK_F5,
  f6 = SDLK_F6,
  f7 = SDLK_F7,
  f8 = SDLK_F8,
  f9 = SDLK_F9,
  f10 = SDLK_F10,
  f11 = SDLK_F11,
  f12 = SDLK_F12,
  f13 = SDLK_F13,
  f14 = SDLK_F14,
  f15 = SDLK_F15,
  f16 = SDLK_F16,
  f17 = SDLK_F17,
  f18 = SDLK_F18,
  f19 = SDLK_F19,
  f20 = SDLK_F20,
  f21 = SDLK_F21,
  f22 = SDLK_F22,
  f23 = SDLK_F23,
  f24 = SDLK_F24,

  // Numpad
  numpad0 = SDLK_KP_0,
  numpad1 = SDLK_KP_1,
  numpad2 = SDLK_KP_2,
  numpad3 = SDLK_KP_3,
  numpad4 = SDLK_KP_4,
  numpad5 = SDLK_KP_5,
  numpad6 = SDLK_KP_6,
  numpad7 = SDLK_KP_7,
  numpad8 = SDLK_KP_8,
  numpad9 = SDLK_KP_9,
  numpad_plus = SDLK_KP_PLUS,
  numpad_minus = SDLK_KP_MINUS,
  numpad_multiply = SDLK_KP_MULTIPLY,
  numpad_divide = SDLK_KP_DIVIDE,
  numpad_decimal = SDLK_KP_DECIMAL,
  numpad_enter = SDLK_KP_ENTER,

  // Navigation
  page_up = SDLK_PAGEUP,
  page_down = SDLK_PAGEDOWN,
  end = SDLK_END,
  home = SDLK_HOME,
  insert = SDLK_INSERT,
  del = SDLK_DELETE,
  backspace = SDLK_BACKSPACE,
  left = SDLK_LEFT,
  right = SDLK_RIGHT,
  up = SDLK_UP,
  down = SDLK_DOWN,

  // Numbers
  num0 = SDLK_0,
  num1 = SDLK_1,
  num2 = SDLK_2,
  num3 = SDLK_3,
  num4 = SDLK_4,
  num5 = SDLK_5,
  num6 = SDLK_6,
  num7 = SDLK_7,
  num8 = SDLK_8,
  num9 = SDLK_9,

  // Characters
  a = SDLK_a,
  b = SDLK_b,
  c = SDLK_c,
  d = SDLK_d,
  e = SDLK_e,
  f = SDLK_f,
  g = SDLK_g,
  h = SDLK_h,
  i = SDLK_i,
  j = SDLK_j,
  k = SDLK_k,
  l = SDLK_l,
  m = SDLK_m,
  n = SDLK_n,
  o = SDLK_o,
  p = SDLK_p,
  q = SDLK_q,
  r = SDLK_r,
  s = SDLK_s,
  t = SDLK_t,
  u = SDLK_u,
  v = SDLK_v,
  x = SDLK_x,
  y = SDLK_y,
  w = SDLK_w,
  z = SDLK_z,

  // Punctuation
  lbracket = SDLK_LEFTBRACKET,
  rbracket = SDLK_RIGHTBRACKET,
  apostrophe = SDLK_QUOTE,
  backslash = SDLK_BACKSLASH,
  comma = SDLK_COMMA,
  dash = SDLK_MINUS,
  enter = SDLK_RETURN,
  equal = SDLK_EQUALS,
  grave = SDLK_BACKQUOTE,
  period = SDLK_PERIOD,
  semicolon = SDLK_SEMICOLON,
  slash = SDLK_SLASH,
  space = SDLK_SPACE,
  tab = SDLK_TAB,

  // Modifier keys
  caps_lock = SDLK_CAPSLOCK,
  num_lock = SDLK_NUMLOCKCLEAR,
  scroll_lock = SDLK_SCROLLLOCK,
  lctrl = SDLK_LCTRL,
  rctrl = SDLK_RCTRL,
  lalt = SDLK_LALT,
  ralt = SDLK_RALT,
  lshift = SDLK_LSHIFT,
  rshift = SDLK_RSHIFT,
  lsystem = SDLK_LGUI,
  rsystem = SDLK_RGUI,

  // Application control
  ac_back = SDLK_AC_BACK,
  ac_forward = SDLK_AC_FORWARD,
  ac_refresh = SDLK_AC_REFRESH,
  ac_stop = SDLK_AC_STOP,
  ac_search = SDLK_AC_SEARCH,
  ac_bookmarks = SDLK_AC_BOOKMARKS,
  ac_home = SDLK_AC_HOME,

  // Sound and media.
  volume_up = SDLK_VOLUMEUP,
  volume_down = SDLK_VOLUMEDOWN,
  mute = SDLK_AUDIOMUTE,
  media_next_track = SDLK_AUDIONEXT,
  media_previous_track = SDLK_AUDIOPREV,
  media_stop = SDLK_AUDIOSTOP,
  media_play_pause = SDLK_AUDIOPLAY,
  launch_media_select = SDLK_MEDIASELECT,
  launch_mail = SDLK_MAIL,

  // Others
  again = SDLK_AGAIN,
  alt_erase = SDLK_ALTERASE,
  application = SDLK_APPLICATION,
  brightness_up = SDLK_BRIGHTNESSUP,
  brightness_down = SDLK_BRIGHTNESSDOWN,
  calculator = SDLK_CALCULATOR,
  cancel = SDLK_CANCEL,
  clear_again = SDLK_CLEARAGAIN,
  computer = SDLK_COMPUTER,
  copy = SDLK_COPY,
  crsel = SDLK_CRSEL,
  currency_sub_unit = SDLK_CURRENCYSUBUNIT,
  currency_unit = SDLK_CURRENCYUNIT,
  cut = SDLK_CUT,
  decimal_separator = SDLK_DECIMALSEPARATOR,
  display_switch = SDLK_DISPLAYSWITCH,
  eject = SDLK_EJECT,
  escape = SDLK_ESCAPE,
  execute = SDLK_EXECUTE,
  exsel = SDLK_EXSEL,
  find = SDLK_FIND,
  help = SDLK_HELP,
  illumination_down = SDLK_KBDILLUMDOWN,
  illumination_up = SDLK_KBDILLUMUP,
  illumination_toggle = SDLK_KBDILLUMTOGGLE,
  oper = SDLK_OPER,
  out = SDLK_OUT,
  paste = SDLK_PASTE,
  pause = SDLK_PAUSE,
  power = SDLK_POWER,
  print_screen = SDLK_PRINTSCREEN,
  prior = SDLK_PRIOR,
  separator = SDLK_SEPARATOR,
  select = SDLK_SELECT,
  sleep = SDLK_SLEEP,
  sys_req = SDLK_SYSREQ,
  thousands_separator = SDLK_THOUSANDSSEPARATOR,
  undo = SDLK_UNDO,
  www = SDLK_WWW,

  // Key codes without associated scan code.
  ampersand = SDLK_AMPERSAND,
  asterisk = SDLK_ASTERISK,
  at = SDLK_AT,
  caret = SDLK_CARET,
  colon = SDLK_COLON,
  dollar = SDLK_DOLLAR,
  exclamation_mark = SDLK_EXCLAIM,
  less = SDLK_LESS,
  greater = SDLK_GREATER,
  hash = SDLK_HASH,
  lparenthesis = SDLK_LEFTPAREN,
  rparentheses = SDLK_RIGHTPAREN,
  percent = SDLK_PERCENT,
  plus = SDLK_PLUS,
  question_mark = SDLK_QUESTION,
  double_quote = SDLK_QUOTEDBL,
  underscore = SDLK_UNDERSCORE,
};

/**
 * Writes a key_code enum into a stream.
 *
 * \param os the stream.
 *
 * \param kc the key_code enum.
 *
 * \return a reference to os.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, key_code kc);

HOU_SYS_API key_code get_key_code(scan_code sc);

HOU_SYS_API scan_code get_scan_code(key_code kc);

}  // namespace hou

#endif
