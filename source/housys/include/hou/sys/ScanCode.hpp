// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SCAN_CODE_HPP
#define HOU_SYS_SCAN_CODE_HPP

#include "hou/sys/sys_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration type for layout-independent keyboard key codes. */
enum class scan_code
{
  /** Escape */
  Escape = 0x01u,

  /** Num1 */
  Num1 = 0x02u,
  /** Num2 */
  Num2 = 0x03u,
  /** Num3 */
  Num3 = 0x04u,
  /** Num4 */
  Num4 = 0x05u,
  /** Num5 */
  Num5 = 0x06u,
  /** Num6 */
  Num6 = 0x07u,
  /** Num7 */
  Num7 = 0x08u,
  /** Num8 */
  Num8 = 0x09u,
  /** Num9 */
  Num9 = 0x0au,
  /** Num0 */
  Num0 = 0x0bu,
  /** Dash */
  Dash = 0x0cu,
  /** Equal */
  Equal = 0x0du,
  /** Backspace */
  Backspace = 0x0eu,

  /** Tab */
  Tab = 0x0fu,
  /** Q */
  Q = 0x10u,
  /** W */
  W = 0x11u,
  /** E */
  E = 0x12u,
  /** r */
  r = 0x13u,
  /** T */
  T = 0x14u,
  /** Y */
  Y = 0x15u,
  /** U */
  U = 0x16u,
  /** I */
  I = 0x17u,
  /** O */
  O = 0x18u,
  /** P */
  P = 0x19u,
  /** LBracket */
  LBracket = 0x1au,
  /** RBracket */
  RBracket = 0x1bu,
  /** Enter */
  Enter = 0x1cu,
  /** NumpadEnter */
  NumpadEnter = 0xe01cu,

  /** LCtrl */
  LCtrl = 0x1du,
  /** RCtrl */
  RCtrl = 0xe01du,
  /** A */
  A = 0x1eu,
  /** S */
  S = 0x1fu,
  /** D */
  D = 0x20u,
  /** F */
  F = 0x21u,
  /** G */
  G = 0x22u,
  /** H */
  H = 0x23u,
  /** J */
  J = 0x24u,
  /** K */
  K = 0x25u,
  /** L */
  L = 0x26u,
  /** Semicolon */
  Semicolon = 0x27u,
  /** Quote */
  Quote = 0x28u,
  /** Tilde */
  Tilde = 0x29u,

  /** LShift */
  LShift = 0x2au,
  /** Backslash */
  Backslash = 0x2bu,
  /** Z */
  Z = 0x2cu,
  /** X */
  X = 0x2du,
  /** C */
  C = 0x2eu,
  /** V */
  V = 0x2fu,
  /** B */
  B = 0x30u,
  /** N */
  N = 0x31u,
  /** M */
  M = 0x32u,
  /** Comma */
  Comma = 0x33u,
  /** Period */
  Period = 0x34u,
  /** Slash */
  Slash = 0x35u,
  /** Divide */
  Divide = 0xe035u,
  /** RShift */
  RShift = 0x36u,

  /** Multiply */
  Multiply = 0x37u,
  /** PrintScreen */
  PrintScreen = 0xe037u,
  /** LAlt */
  LAlt = 0x38u,
  /** RAlt */
  RAlt = 0xe038u,
  /** Space */
  Space = 0x39u,
  /** CapsLock */
  CapsLock = 0x3au,

  /** F1 */
  F1 = 0x3bu,
  /** F2 */
  F2 = 0x3cu,
  /** F3 */
  F3 = 0x3du,
  /** F4 */
  F4 = 0x3eu,
  /** F5 */
  F5 = 0x3fu,
  /** F6 */
  F6 = 0x40u,
  /** F7 */
  F7 = 0x41u,
  /** F8 */
  F8 = 0x42u,
  /** F9 */
  F9 = 0x43u,
  /** F10 */
  F10 = 0x44u,

  /** Pause */
  Pause = 0x45u,
  /** NumLock */
  NumLock = 0xe045u,
  /** ScrollLock */
  ScrollLock = 0x46u,

  /** Numpad7 */
  Numpad7 = 0x47u,
  /** Home */
  Home = 0xe047u,
  /** Numpad8 */
  Numpad8 = 0x48u,
  /** Up */
  Up = 0xe048u,
  /** Numpad9 */
  Numpad9 = 0x49u,
  /** PageUp */
  PageUp = 0xe049u,
  /** Subtract */
  Subtract = 0x4au,
  /** Numpad4 */
  Numpad4 = 0x4bu,
  /** Left */
  Left = 0xe04bu,
  /** Numpad5 */
  Numpad5 = 0x4cu,
  /** Numpad6 */
  Numpad6 = 0x4du,
  /** Right */
  Right = 0xe04du,
  /** Add */
  Add = 0x4eu,
  /** Numpad1 */
  Numpad1 = 0x4fu,
  /** End */
  End = 0xe04fu,
  /** Numpad2 */
  Numpad2 = 0x50u,
  /** Down */
  Down = 0xe050u,
  /** Numpad3 */
  Numpad3 = 0x51u,
  /** PageDown */
  PageDown = 0xe051u,
  /** Numpad0 */
  Numpad0 = 0x52u,
  /** Insert */
  Insert = 0xe052u,
  /** Decimal */
  Decimal = 0x53u,
  /** Delete */
  Delete = 0xe053u,

  /** F11 */
  F11 = 0x57u,
  /** F12 */
  F12 = 0x58u,

  /** LSystem */
  LSystem = 0xe05b,
  /** RSystem */
  RSystem = 0xe05c,
  /** Apps */
  Apps = 0xe05d,
};


/** Writes a scan_code enum into a ph_stream.
 *
 *  \param os the ph_stream.
 *  \param sc the scan_code enum.
 *  \return a reference to the ph_stream.
 */
HOU_SYS_API std::ostream& operator<<(std::ostream& os, scan_code sc);

}

#endif

