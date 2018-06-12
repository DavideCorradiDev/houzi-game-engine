// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_KEY_CODE_HPP
#define HOU_SYS_KEY_CODE_HPP

#include "hou/sys/sys_config.hpp"

#include "SDL2/SDL_keycode.h"

#include <iostream>



namespace hou
{

/** Enumeration type for layout-dependent keyboard key codes. */
enum class key_code
{
  // Function keys
  /** F1 */
  f1 = SDLK_F1,
  /** F2 */
  f2 = SDLK_F2,
  /** F3 */
  f3 = SDLK_F3,
  /** F4 */
  f4 = SDLK_F4,
  /** F5 */
  f5 = SDLK_F5,
  /** F6 */
  f6 = SDLK_F6,
  /** F7 */
  f7 = SDLK_F7,
  /** F8 */
  f8 = SDLK_F8,
  /** F9 */
  f9 = SDLK_F9,
  /** F10 */
  f10 = SDLK_F10,
  /** F11 */
  f11 = SDLK_F11,
  /** F12 */
  f12 = SDLK_F12,
  /** F13 */
  f13 = SDLK_F13,
  /** F14 */
  f14 = SDLK_F14,
  /** F15 */
  f15 = SDLK_F15,
  /** F16 */
  f16 = SDLK_F16,
  /** F17 */
  f17 = SDLK_F17,
  /** F18 */
  f18 = SDLK_F18,
  /** F19 */
  f19 = SDLK_F19,
  /** F20 */
  f20 = SDLK_F20,
  /** F21 */
  f21 = SDLK_F21,
  /** F22 */
  f22 = SDLK_F22,
  /** F23 */
  f23 = SDLK_F23,
  /** F24 */
  f24 = SDLK_F24,

  // Numpad
  /** Numpad0 */
  numpad0 = SDLK_KP_0,
  /** Numpad1 */
  numpad1 = SDLK_KP_1,
  /** Numpad2 */
  numpad2 = SDLK_KP_2,
  /** Numpad3 */
  numpad3 = SDLK_KP_3,
  /** Numpad4 */
  numpad4 = SDLK_KP_4,
  /** Numpad5 */
  numpad5 = SDLK_KP_5,
  /** Numpad6 */
  numpad6 = SDLK_KP_6,
  /** Numpad7 */
  numpad7 = SDLK_KP_7,
  /** Numpad8 */
  numpad8 = SDLK_KP_8,
  /** Numpad9 */
  numpad9 = SDLK_KP_9,
  /** Plus */
  numpad_plus = SDLK_KP_PLUS,
  /** Minus */
  numpad_minus = SDLK_KP_MINUS,
  /** Multiply */
  numpad_multiply = SDLK_KP_MULTIPLY,
  /** Divide */
  numpad_divide = SDLK_KP_DIVIDE,
  /** Decimal */
  numpad_decimal = SDLK_KP_DECIMAL,

  // Navigation
  /** PageUp */
  page_up = SDLK_PAGEUP,
  /** PageDown */
  page_down = SDLK_PAGEDOWN,
  /** End */
  end = SDLK_END,
  /** Home */
  home = SDLK_HOME,
  /** Insert */
  insert = SDLK_INSERT,
  /** Delete */
  del = SDLK_DELETE,
  /** Backspace */
  backspace = SDLK_BACKSPACE,
  /** Left */
  left = SDLK_LEFT,
  /** Right */
  right = SDLK_RIGHT,
  /** Up */
  up = SDLK_UP,
  /** Down */
  down = SDLK_DOWN,

  // Numbers
  /** Num0 */
  num0 = SDLK_0,
  /** Num1 */
  num1 = SDLK_1,
  /** Num2 */
  num2 = SDLK_2,
  /** Num3 */
  num3 = SDLK_3,
  /** Num4 */
  num4 = SDLK_4,
  /** Num5 */
  num5 = SDLK_5,
  /** Num6 */
  num6 = SDLK_6,
  /** Num7 */
  num7 = SDLK_7,
  /** Num8 */
  num8 = SDLK_8,
  /** Num9 */
  num9 = SDLK_9,

  // Characters
  /** a */
  a = SDLK_a,
  /** b */
  b = SDLK_b,
  /** C */
  c = SDLK_c,
  /** D */
  d = SDLK_d,
  /** E */
  e = SDLK_e,
  /** F */
  f = SDLK_f,
  /** g */
  g = SDLK_g,
  /** H */
  h = SDLK_h,
  /** I */
  i = SDLK_i,
  /** J */
  j = SDLK_j,
  /** K */
  k = SDLK_k,
  /** L */
  l = SDLK_l,
  /** M */
  m = SDLK_m,
  /** N */
  n = SDLK_n,
  /** O */
  o = SDLK_o,
  /** P */
  p = SDLK_p,
  /** Q */
  q = SDLK_q,
  /** R */
  r = SDLK_r,
  /** S */
  s = SDLK_s,
  /** T */
  t = SDLK_t,
  /** U */
  u = SDLK_u,
  /** V */
  v = SDLK_v,
  /** X */
  x = SDLK_x,
  /** Y */
  y = SDLK_y,
  /** W */
  w = SDLK_w,
  /** Z */
  z = SDLK_z,

  // Punctuation
  /** LBracket */
  lbracket = SDLK_LEFTBRACKET,
  /** RBracket */
  rbracket = SDLK_RIGHTBRACKET,
  /** Semicolon */
  semicolon = SDLK_SEMICOLON,
  /** Comma */
  comma = SDLK_COMMA,
  /** Period */
  period = SDLK_PERIOD,
  /** Apopstrophe */
  apostrophe = SDLK_QUOTE,
  /** Slash */
  slash = SDLK_SLASH,
  /** Backslash */
  backslash = SDLK_BACKSLASH,
  /** Grave */
  grave = SDLK_BACKQUOTE,
  /** Dash */
  dash = SDLK_MINUS,
  /** Enter */
  enter = SDLK_RETURN,
  /** Tab */
  tab = SDLK_TAB,
  /** Space */
  space = SDLK_SPACE,
  /** Equal */
  equal = SDLK_EQUALS,

  // Modifier keys
  /** CapsLock */
  caps_lock = SDLK_CAPSLOCK,
  /** NumLock */
  num_lock = SDLK_NUMLOCKCLEAR,
  /** ScrollLock */
  scroll_lock = SDLK_SCROLLLOCK,
  /** LCtrl */
  lctrl = SDLK_LCTRL,
  /** RCtrl */
  rctrl = SDLK_RCTRL,
  /** LAlt */
  lalt = SDLK_LALT,
  /** RAlt */
  ralt = SDLK_RALT,
  /** LShift */
  lshift = SDLK_LSHIFT,
  /** RShift */
  rshift = SDLK_RSHIFT,
  /** LSystem */
  lsystem = SDLK_LGUI,
  /** RSystem */
  rsystem = SDLK_RGUI,

  // Application control
  /** AC Back */
  ac_back = SDLK_AC_BACK,
  /** AC Forward */
  ac_forward = SDLK_AC_FORWARD,
  /** AC Refresh */
  ac_refresh = SDLK_AC_REFRESH,
  /** AC Stop */
  ac_stop = SDLK_AC_STOP,
  /** AC Search */
  ac_search = SDLK_AC_SEARCH,
  /** AC Bookmarks */
  ac_bookmarks = SDLK_AC_BOOKMARKS,
  /** AC Home */
  ac_home = SDLK_AC_HOME,

  // Sound and media.
  /** VolumeUp  */
  volume_up = SDLK_VOLUMEUP,
  /** VolumeDown */
  volume_down = SDLK_VOLUMEDOWN,
  /** VolumeMute */
  mute = SDLK_AUDIOMUTE,
  /** MediaNextTrack */
  media_next_track = SDLK_AUDIONEXT,
  /** MediaPreviousTrack */
  media_previous_track = SDLK_AUDIOPREV,
  /** MediaStop */
  media_stop = SDLK_AUDIOSTOP,
  /** MediaPlayPause */
  media_play_pause = SDLK_AUDIOPLAY,
  /** LaunchMediaSelect */
  launch_media_select = SDLK_MEDIASELECT,
  /** LaunchMail */
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

/** Writes a key_code enum into a stream.
 *
 *  \param os the stream.
 *  \param kc the key_code enum.
 *  \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, key_code kc);

}  // namespace hou

#endif
