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
  Escape,
  /** Print */
  Print,
  /** PrintScreen */
  PrintScreen,
  /** Pause */
  Pause,
  /** Execute */
  Execute,
  /** Select */
  Select,
  /** Help */
  Help,
  /** Sleep */
  Sleep,
  /** Apps */
  Apps,
  /** F1 */
  F1,
  /** F2 */
  F2,
  /** F3 */
  F3,
  /** F4 */
  F4,
  /** F5 */
  F5,
  /** F6 */
  F6,
  /** F7 */
  F7,
  /** F8 */
  F8,
  /** F9 */
  F9,
  /** F10 */
  F10,
  /** F11 */
  F11,
  /** F12 */
  F12,
  F13,
  /** F14 */
  F14,
  /** F15 */
  F15,
  /** F16 */
  F16,
  /** F17 */
  F17,
  /** F18 */
  F18,
  /** F19 */
  F19,
  /** F20 */
  F20,
  /** F21 */
  F21,
  /** F22 */
  F22,
  /** F23 */
  F23,
  /** F24 */
  F24,

  // Numpad keys
  /** Numpad0 */
  Numpad0,
  /** Numpad1 */
  Numpad1,
  /** Numpad2 */
  Numpad2,
  /** Numpad3 */
  Numpad3,
  /** Numpad4 */
  Numpad4,
  /** Numpad5 */
  Numpad5,
  /** Numpad6 */
  Numpad6,
  /** Numpad7 */
  Numpad7,
  /** Numpad8 */
  Numpad8,
  /** Numpad9 */
  Numpad9,
  /** Add */
  Add,
  /** Subtract */
  Subtract,
  /** Multiply */
  Multiply,
  /** Divide */
  Divide,
  /** Decimal */
  Decimal,
  /** Separator */
  Separator,

  // Navigation keys
  /** PageUp */
  PageUp,
  /** PageDown */
  PageDown,
  /** End */
  End,
  /** Home */
  Home,
  /** Insert */
  Insert,
  /** Delete */
  Delete,
  /** Backspace */
  Backspace,
  /** Left */
  Left,
  /** Right */
  Right,
  /** Up */
  Up,
  /** Down */
  Down,

  // Character keys
  /** Num0 */
  Num0,
  /** Num1 */
  Num1,
  /** Num2 */
  Num2,
  /** Num3 */
  Num3,
  /** Num4 */
  Num4,
  /** Num5 */
  Num5,
  /** Num6 */
  Num6,
  /** Num7 */
  Num7,
  /** Num8 */
  Num8,
  /** Num9 */
  Num9,
  /** A */
  A,
  /** B */
  B,
  /** C */
  C,
  /** D */
  D,
  /** E */
  E,
  /** F */
  F,
  /** G */
  G,
  /** H */
  H,
  /** I */
  I,
  /** J */
  J,
  /** K */
  K,
  /** L */
  L,
  /** M */
  M,
  /** N */
  N,
  /** O */
  O,
  /** P */
  P,
  /** Q */
  Q,
  /** R */
  R,
  /** S */
  S,
  /** T */
  T,
  /** U */
  U,
  /** V */
  V,
  /** X */
  X,
  /** Y */
  Y,
  /** W */
  W,
  /** Z */
  Z,
  /** LBracket */
  LBracket,
  /** RBracket */
  RBracket,
  /** Semicolon */
  Semicolon,
  /** Comma */
  Comma,
  /** Period */
  Period,
  /** Quote */
  Quote,
  /** Slash */
  Slash,
  /** Backslash */
  Backslash,
  /** Tilde */
  Tilde,
  /** Dash */
  Dash,
  /** Enter */
  Enter,
  /** Tab */
  Tab,
  /** Space */
  Space,
  /** Equal */
  Equal,
  /** Special1 */
  Special1,
  /** Special2 */
  Special2,

  // Modifier keys
  /** CapsLock */
  CapsLock,
  /** NumLock */
  NumLock,
  /** ScrollLock */
  ScrollLock,
  /** LCtrl */
  LCtrl,
  /** RCtrl */
  RCtrl,
  /** LAlt */
  LAlt,
  /** RAlt */
  RAlt,
  /** LShift */
  LShift,
  /** RShift */
  RShift,
  /** LSystem */
  LSystem,
  /** RSystem */
  RSystem,

  // IME (input method editor)
  /** Kana */
  Kana,
  /** Hangul */
  Hangul,
  /** Junja */
  Junja,
  /** Final */
  Final,
  /** Hanja */
  Hanja,
  /** Kanji */
  Kanji,
  /** Convert */
  Convert,
  /** NonConvert */
  NonConvert,
  /** Accept */
  Accept,
  /** ModeChange */
  ModeChange,
  /** ProcessKey */
  ProcessKey,

  // Browser
  /** BrowserBack */
  BrowserBack,
  /** BrowserForward */
  BrowserForward,
  /** BrowserRefresh */
  BrowserRefresh,
  /** BrowserStop */
  BrowserStop,
  /** BrowserSearch */
  BrowserSearch,

  /** BrowserFavorites */
  BrowserFavorites,
  /** BrowserHome */
  BrowserHome,

  // Sound and media.
  /** VolumeUp  */
  VolumeUp,
  /** VolumeDown */
  VolumeDown,
  /** VolumeMute */
  VolumeMute,
  /** MediaNextTrack */
  MediaNextTrack,
  /** MediaPreviousTrack */
  MediaPreviousTrack,
  /** MediaStop */
  MediaStop,
  /** MediaPlayPause */
  MediaPlayPause,
  /** LaunchMediaSelect */
  LaunchMediaSelect,
  /** LaunchMail */
  LaunchMail,
  /** LaunchApp1 */
  LaunchApp1,
  /** LaunchApp2 */
  LaunchApp2,

  // Others
  /** Attn */
  Attn,
  /** CrSel */
  CrSel,
  /** ExSel */
  ExSel,
  /** EraseEOF */
  EraseEOF,
  /** Play */
  Play,
  /** Zoom */
  Zoom,
  /** PA1 */
  PA1,
  /** Clear */
  Clear,
  /** Packet */
  Packet,
};

/** Writes a key_code enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param kc the key_code enum.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, key_code kc);

}

#endif

