// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_SCAN_CODE_HPP
#define HOU_SYS_SCAN_CODE_HPP

#include "hou/sys/sys_config.hpp"

#include <iostream>



namespace hou
{

/** Enumeration type for layout-independent keyboard key codes. */
enum class scan_code
{
  /** Escape */
  escape = 0x01u,

  /** Num1 */
  num1 = 0x02u,
  /** Num2 */
  num2 = 0x03u,
  /** Num3 */
  num3 = 0x04u,
  /** Num4 */
  num4 = 0x05u,
  /** Num5 */
  num5 = 0x06u,
  /** Num6 */
  num6 = 0x07u,
  /** Num7 */
  num7 = 0x08u,
  /** Num8 */
  num8 = 0x09u,
  /** Num9 */
  num9 = 0x0au,
  /** Num0 */
  num0 = 0x0bu,
  /** Dash */
  dash = 0x0cu,
  /** Equal */
  equal = 0x0du,
  /** Backspace */
  backspace = 0x0eu,

  /** Tab */
  tab = 0x0fu,
  /** Q */
  q = 0x10u,
  /** W */
  w = 0x11u,
  /** E */
  e = 0x12u,
  /** r */
  r = 0x13u,
  /** T */
  t = 0x14u,
  /** Y */
  y = 0x15u,
  /** U */
  u = 0x16u,
  /** I */
  i = 0x17u,
  /** O */
  o = 0x18u,
  /** P */
  p = 0x19u,
  /** LBracket */
  l_bracket = 0x1au,
  /** RBracket */
  r_bracket = 0x1bu,
  /** Enter */
  enter = 0x1cu,
  /** NumpadEnter */
  numpad_enter = 0xe01cu,

  /** LCtrl */
  l_ctrl = 0x1du,
  /** RCtrl */
  r_ctrl = 0xe01du,
  /** a */
  a = 0x1eu,
  /** S */
  s = 0x1fu,
  /** D */
  d = 0x20u,
  /** F */
  f = 0x21u,
  /** g */
  g = 0x22u,
  /** H */
  h = 0x23u,
  /** J */
  j = 0x24u,
  /** K */
  k = 0x25u,
  /** L */
  l = 0x26u,
  /** Semicolon */
  semicolon = 0x27u,
  /** Quote */
  quote = 0x28u,
  /** Tilde */
  tilde = 0x29u,

  /** LShift */
  l_shift = 0x2au,
  /** Backslash */
  backslash = 0x2bu,
  /** Z */
  z = 0x2cu,
  /** X */
  x = 0x2du,
  /** C */
  c = 0x2eu,
  /** V */
  v = 0x2fu,
  /** b */
  b = 0x30u,
  /** N */
  n = 0x31u,
  /** M */
  m = 0x32u,
  /** Comma */
  comma = 0x33u,
  /** Period */
  period = 0x34u,
  /** Slash */
  slash = 0x35u,
  /** Divide */
  divide = 0xe035u,
  /** RShift */
  r_shift = 0x36u,

  /** Multiply */
  multiply = 0x37u,
  /** PrintScreen */
  print_screen = 0xe037u,
  /** LAlt */
  l_alt = 0x38u,
  /** RAlt */
  r_alt = 0xe038u,
  /** Space */
  space = 0x39u,
  /** CapsLock */
  caps_lock = 0x3au,

  /** F1 */
  f1 = 0x3bu,
  /** F2 */
  f2 = 0x3cu,
  /** F3 */
  f3 = 0x3du,
  /** F4 */
  f4 = 0x3eu,
  /** F5 */
  f5 = 0x3fu,
  /** F6 */
  f6 = 0x40u,
  /** F7 */
  f7 = 0x41u,
  /** F8 */
  f8 = 0x42u,
  /** F9 */
  f9 = 0x43u,
  /** F10 */
  f10 = 0x44u,

  /** Pause */
  pause = 0x45u,
  /** NumLock */
  num_lock = 0xe045u,
  /** ScrollLock */
  scroll_lock = 0x46u,

  /** Numpad7 */
  numpad7 = 0x47u,
  /** Home */
  home = 0xe047u,
  /** Numpad8 */
  numpad8 = 0x48u,
  /** Up */
  up = 0xe048u,
  /** Numpad9 */
  numpad9 = 0x49u,
  /** PageUp */
  page_up = 0xe049u,
  /** Subtract */
  subtract = 0x4au,
  /** Numpad4 */
  numpad4 = 0x4bu,
  /** Left */
  left = 0xe04bu,
  /** Numpad5 */
  numpad5 = 0x4cu,
  /** Numpad6 */
  numpad6 = 0x4du,
  /** Right */
  right = 0xe04du,
  /** Add */
  add = 0x4eu,
  /** Numpad1 */
  numpad1 = 0x4fu,
  /** End */
  end = 0xe04fu,
  /** Numpad2 */
  numpad2 = 0x50u,
  /** Down */
  down = 0xe050u,
  /** Numpad3 */
  numpad3 = 0x51u,
  /** PageDown */
  page_down = 0xe051u,
  /** Numpad0 */
  numpad0 = 0x52u,
  /** Insert */
  ins = 0xe052u,
  /** Decimal */
  decimal = 0x53u,
  /** Delete */
  del = 0xe053u,

  /** F11 */
  f11 = 0x57u,
  /** F12 */
  f12 = 0x58u,

  /** LSystem */
  l_system = 0xe05b,
  /** RSystem */
  r_system = 0xe05c,
  /** Apps */
  apps = 0xe05d,
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
