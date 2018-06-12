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

/** Enumeration type for layout-independent keyboard key codes. */
enum class scan_code
{
  /** Escape */
  escape = SDL_SCANCODE_ESCAPE,

  /** Num1 */
  num1 = SDL_SCANCODE_1,
  /** Num2 */
  num2 = SDL_SCANCODE_2,
  /** Num3 */
  num3 = SDL_SCANCODE_3,
  /** Num4 */
  num4 = SDL_SCANCODE_4,
  /** Num5 */
  num5 = SDL_SCANCODE_5,
  /** Num6 */
  num6 = SDL_SCANCODE_6,
  /** Num7 */
  num7 = SDL_SCANCODE_7,
  /** Num8 */
  num8 = SDL_SCANCODE_8,
  /** Num9 */
  num9 = SDL_SCANCODE_9,
  /** Num0 */
  num0 = SDL_SCANCODE_0,
  /** Dash */
  dash = SDL_SCANCODE_MINUS,
  /** Equal */
  equal = SDL_SCANCODE_EQUALS,
  /** Backspace */
  backspace = SDL_SCANCODE_BACKSPACE,

  /** Tab */
  tab = SDL_SCANCODE_TAB,
  /** Q */
  q = SDL_SCANCODE_Q,
  /** W */
  w = SDL_SCANCODE_W,
  /** E */
  e = SDL_SCANCODE_E,
  /** r */
  r = SDL_SCANCODE_R,
  /** T */
  t = SDL_SCANCODE_T,
  /** Y */
  y = SDL_SCANCODE_Y,
  /** U */
  u = SDL_SCANCODE_U,
  /** I */
  i = SDL_SCANCODE_I,
  /** O */
  o = SDL_SCANCODE_O,
  /** P */
  p = SDL_SCANCODE_P,
  /** LBracket */
  lbracket = SDL_SCANCODE_LEFTBRACKET,
  /** RBracket */
  rbracket = SDL_SCANCODE_RIGHTBRACKET,
  /** Enter */
  enter = SDL_SCANCODE_RETURN,
  /** NumpadEnter */
  numpad_enter = SDL_SCANCODE_KP_ENTER,

  /** LCtrl */
  lctrl = SDL_SCANCODE_LCTRL,
  /** RCtrl */
  rctrl = SDL_SCANCODE_RCTRL,
  /** a */
  a = SDL_SCANCODE_A,
  /** S */
  s = SDL_SCANCODE_S,
  /** D */
  d = SDL_SCANCODE_D,
  /** F */
  f = SDL_SCANCODE_F,
  /** g */
  g = SDL_SCANCODE_G,
  /** H */
  h = SDL_SCANCODE_H,
  /** J */
  j = SDL_SCANCODE_J,
  /** K */
  k = SDL_SCANCODE_K,
  /** L */
  l = SDL_SCANCODE_L,
  /** Semicolon */
  semicolon = SDL_SCANCODE_SEMICOLON,
  /** Apostrophe */
  apostrophe = SDL_SCANCODE_APOSTROPHE,
  /** Grave */
  grave = SDL_SCANCODE_GRAVE,

  /** LShift */
  lshift = SDL_SCANCODE_LSHIFT,
  /** Backslash */
  backslash = SDL_SCANCODE_BACKSLASH,
  /** Z */
  z = SDL_SCANCODE_Z,
  /** X */
  x = SDL_SCANCODE_X,
  /** C */
  c = SDL_SCANCODE_C,
  /** V */
  v = SDL_SCANCODE_V,
  /** b */
  b = SDL_SCANCODE_B,
  /** N */
  n = SDL_SCANCODE_N,
  /** M */
  m = SDL_SCANCODE_M,
  /** Comma */
  comma = SDL_SCANCODE_COMMA,
  /** Period */
  period = SDL_SCANCODE_PERIOD,
  /** Slash */
  slash = SDL_SCANCODE_SLASH,
  /** Divide */
  numpad_divide = SDL_SCANCODE_KP_DIVIDE,
  /** RShift */
  rshift = SDL_SCANCODE_RSHIFT,

  /** Multiply */
  numpad_multiply = SDL_SCANCODE_KP_MULTIPLY,
  /** PrintScreen */
  print_screen = SDL_SCANCODE_PRINTSCREEN,
  /** LAlt */
  lalt = SDL_SCANCODE_LALT,
  /** RAlt */
  ralt = SDL_SCANCODE_RALT,
  /** Space */
  space = SDL_SCANCODE_SPACE,
  /** CapsLock */
  caps_lock = SDL_SCANCODE_CAPSLOCK,

  /** F1 */
  f1 = SDL_SCANCODE_F1,
  /** F2 */
  f2 = SDL_SCANCODE_F2,
  /** F3 */
  f3 = SDL_SCANCODE_F3,
  /** F4 */
  f4 = SDL_SCANCODE_F4,
  /** F5 */
  f5 = SDL_SCANCODE_F5,
  /** F6 */
  f6 = SDL_SCANCODE_F6,
  /** F7 */
  f7 = SDL_SCANCODE_F7,
  /** F8 */
  f8 = SDL_SCANCODE_F8,
  /** F9 */
  f9 = SDL_SCANCODE_F9,
  /** F10 */
  f10 = SDL_SCANCODE_F10,

  /** Pause */
  pause = SDL_SCANCODE_PAUSE,
  /** NumLock */
  num_lock = SDL_SCANCODE_NUMLOCKCLEAR,
  /** ScrollLock */
  scroll_lock = SDL_SCANCODE_SCROLLLOCK,

  /** Numpad7 */
  numpad7 = SDL_SCANCODE_KP_7,
  /** Home */
  home = SDL_SCANCODE_HOME,
  /** Numpad8 */
  numpad8 = SDL_SCANCODE_KP_8,
  /** Up */
  up = SDL_SCANCODE_UP,
  /** Numpad9 */
  numpad9 = SDL_SCANCODE_KP_9,
  /** PageUp */
  page_up = SDL_SCANCODE_PAGEUP,
  /** Minus */
  numpad_minus = SDL_SCANCODE_KP_MINUS,
  /** Numpad4 */
  numpad4 = SDL_SCANCODE_KP_4,
  /** Left */
  left = SDL_SCANCODE_LEFT,
  /** Numpad5 */
  numpad5 = SDL_SCANCODE_KP_5,
  /** Numpad6 */
  numpad6 = SDL_SCANCODE_KP_6,
  /** Right */
  right = SDL_SCANCODE_RIGHT,
  /** Plus */
  numpad_plus = SDL_SCANCODE_KP_PLUS,
  /** Numpad1 */
  numpad1 = SDL_SCANCODE_KP_1,
  /** End */
  end = SDL_SCANCODE_END,
  /** Numpad2 */
  numpad2 = SDL_SCANCODE_KP_2,
  /** Down */
  down = SDL_SCANCODE_DOWN,
  /** Numpad3 */
  numpad3 = SDL_SCANCODE_KP_3,
  /** PageDown */
  page_down = SDL_SCANCODE_PAGEDOWN,
  /** Numpad0 */
  numpad0 = SDL_SCANCODE_KP_0,
  /** Insert */
  insert = SDL_SCANCODE_INSERT,
  /** Decimal */
  numpad_decimal = SDL_SCANCODE_KP_DECIMAL,
  /** Delete */
  del = SDL_SCANCODE_DELETE,

  /** F11 */
  f11 = SDL_SCANCODE_F11,
  /** F12 */
  f12 = SDL_SCANCODE_F12,

  /** LSystem */
  lsystem = SDL_SCANCODE_LGUI,
  /** RSystem */
  rsystem = SDL_SCANCODE_RGUI,
  /** Application */
  application = SDL_SCANCODE_APPLICATION,

  // Application control
  /** AC Back */
  ac_back = SDL_SCANCODE_AC_BACK,
  /** AC Forward */
  ac_forward = SDL_SCANCODE_AC_FORWARD,
  /** AC Refresh */
  ac_refresh = SDL_SCANCODE_AC_REFRESH,
  /** AC Stop */
  ac_stop = SDL_SCANCODE_AC_STOP,
  /** AC Search */
  ac_search = SDL_SCANCODE_AC_SEARCH,
  /** AC Bookmarks */
  ac_bookmarks = SDL_SCANCODE_AC_BOOKMARKS,
  /** AC Home */
  ac_home = SDL_SCANCODE_AC_HOME,

  // Sound and media.
  /** VolumeUp  */
  volume_up = SDL_SCANCODE_VOLUMEUP,
  /** VolumeDown */
  volume_down = SDL_SCANCODE_VOLUMEDOWN,
  /** VolumeMute */
  volume_mute = SDL_SCANCODE_AUDIOMUTE,
  /** MediaNextTrack */
  media_next_track = SDL_SCANCODE_AUDIONEXT,
  /** MediaPreviousTrack */
  media_previous_track = SDL_SCANCODE_AUDIOPREV,
  /** MediaStop */
  media_stop = SDL_SCANCODE_AUDIOSTOP,
  /** MediaPlayPause */
  media_play_pause = SDL_SCANCODE_AUDIOPLAY,
  /** LaunchMediaSelect */
  launch_media_select = SDL_SCANCODE_MEDIASELECT,
  /** LaunchMail */
  launch_mail = SDL_SCANCODE_MAIL,

  // Various keys
  again = SDL_SCANCODE_AGAIN,
  alt_erase = SDL_SCANCODE_ALTERASE,
  brightness_up = SDL_SCANCODE_BRIGHTNESSUP,
  brightness_down = SDL_SCANCODE_BRIGHTNESSDOWN,
};


/** Writes a scan_code enum into a stream.
 *
 * \param os the stream.
 *
 * \param sc the scan_code enum.
 *
 * \return a reference to the stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, scan_code sc);

}  // namespace hou

#endif
