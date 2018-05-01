// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_KEY_CODE_HPP
#define HOU_SYS_KEY_CODE_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration type for layout-dependent keyboard key codes. */
enum class key_code
{
  // Function keys
  /** Escape */
  escape,
  /** Print */
  print,
  /** PrintScreen */
  print_screen,
  /** Pause */
  pause,
  /** Execute */
  execute,
  /** Select */
  select,
  /** Help */
  help,
  /** Sleep */
  sleep,
  /** Apps */
  apps,
  /** F1 */
  f1,
  /** F2 */
  f2,
  /** F3 */
  f3,
  /** F4 */
  f4,
  /** F5 */
  f5,
  /** F6 */
  f6,
  /** F7 */
  f7,
  /** F8 */
  f8,
  /** F9 */
  f9,
  /** F10 */
  f10,
  /** F11 */
  f11,
  /** F12 */
  f12,
  /** F13 */
  f13,
  /** F14 */
  f14,
  /** F15 */
  f15,
  /** F16 */
  f16,
  /** F17 */
  f17,
  /** F18 */
  f18,
  /** F19 */
  f19,
  /** F20 */
  f20,
  /** F21 */
  f21,
  /** F22 */
  f22,
  /** F23 */
  f23,
  /** F24 */
  f24,

  // Numpad keys
  /** Numpad0 */
  numpad0,
  /** Numpad1 */
  numpad1,
  /** Numpad2 */
  numpad2,
  /** Numpad3 */
  numpad3,
  /** Numpad4 */
  numpad4,
  /** Numpad5 */
  numpad5,
  /** Numpad6 */
  numpad6,
  /** Numpad7 */
  numpad7,
  /** Numpad8 */
  numpad8,
  /** Numpad9 */
  numpad9,
  /** Add */
  add,
  /** Subtract */
  subtract,
  /** Multiply */
  multiply,
  /** Divide */
  divide,
  /** Decimal */
  decimal,
  /** Separator */
  separator,

  // Navigation keys
  /** PageUp */
  page_up,
  /** PageDown */
  page_down,
  /** End */
  end,
  /** Home */
  home,
  /** Insert */
  ins,
  /** Delete */
  del,
  /** Backspace */
  backspace,
  /** Left */
  left,
  /** Right */
  right,
  /** Up */
  up,
  /** Down */
  down,

  // Character keys
  /** Num0 */
  num0,
  /** Num1 */
  num1,
  /** Num2 */
  num2,
  /** Num3 */
  num3,
  /** Num4 */
  num4,
  /** Num5 */
  num5,
  /** Num6 */
  num6,
  /** Num7 */
  num7,
  /** Num8 */
  num8,
  /** Num9 */
  num9,
  /** a */
  a,
  /** b */
  b,
  /** C */
  c,
  /** D */
  d,
  /** E */
  e,
  /** F */
  f,
  /** g */
  g,
  /** H */
  h,
  /** I */
  i,
  /** J */
  j,
  /** K */
  k,
  /** L */
  l,
  /** M */
  m,
  /** N */
  n,
  /** O */
  o,
  /** P */
  p,
  /** Q */
  q,
  /** R */
  r,
  /** S */
  s,
  /** T */
  t,
  /** U */
  u,
  /** V */
  v,
  /** X */
  x,
  /** Y */
  y,
  /** W */
  w,
  /** Z */
  z,
  /** LBracket */
  l_bracket,
  /** RBracket */
  r_bracket,
  /** Semicolon */
  semicolon,
  /** Comma */
  comma,
  /** Period */
  period,
  /** Quote */
  quote,
  /** Slash */
  slash,
  /** Backslash */
  backslash,
  /** Tilde */
  tilde,
  /** Dash */
  dash,
  /** Enter */
  enter,
  /** Tab */
  tab,
  /** Space */
  space,
  /** Equal */
  equal,
  /** Special1 */
  special1,
  /** Special2 */
  special2,

  // Modifier keys
  /** CapsLock */
  caps_lock,
  /** NumLock */
  num_lock,
  /** ScrollLock */
  scroll_lock,
  /** LCtrl */
  l_ctrl,
  /** RCtrl */
  r_ctrl,
  /** LAlt */
  l_alt,
  /** RAlt */
  r_alt,
  /** LShift */
  l_shift,
  /** RShift */
  r_shift,
  /** LSystem */
  l_system,
  /** RSystem */
  r_system,

  // IME (input method editor)
  /** Kana */
  kana,
  /** Hangul */
  hangul,
  /** Junja */
  junja,
  /** Final */
  final,
  /** Hanja */
  hanja,
  /** Kanji */
  kanji,
  /** Convert */
  convert,
  /** NonConvert */
  non_convert,
  /** Accept */
  accept,
  /** ModeChange */
  mode_change,
  /** ProcessKey */
  process_key,

  // Browser
  /** BrowserBack */
  browser_back,
  /** BrowserForward */
  browser_forward,
  /** BrowserRefresh */
  browser_refresh,
  /** BrowserStop */
  browser_stop,
  /** BrowserSearch */
  browser_search,

  /** BrowserFavorites */
  browser_favorites,
  /** BrowserHome */
  browser_home,

  // Sound and media.
  /** VolumeUp  */
  volume_up,
  /** VolumeDown */
  volume_down,
  /** VolumeMute */
  volume_mute,
  /** MediaNextTrack */
  media_next_track,
  /** MediaPreviousTrack */
  media_previous_track,
  /** MediaStop */
  media_stop,
  /** MediaPlayPause */
  media_play_pause,
  /** LaunchMediaSelect */
  launch_media_select,
  /** LaunchMail */
  launch_mail,
  /** LaunchApp1 */
  launch_app1,
  /** LaunchApp2 */
  launch_app2,

  // Others
  /** Attn */
  attn,
  /** CrSel */
  cr_sel,
  /** ExSel */
  ex_sel,
  /** EraseEOF */
  erase_eof,
  /** Play */
  play,
  /** Zoom */
  zoom,
  /** PA1 */
  pa1,
  /** Clear */
  clear,
  /** Packet */
  packet,
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
