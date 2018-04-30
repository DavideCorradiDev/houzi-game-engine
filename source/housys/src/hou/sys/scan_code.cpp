// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/scan_code.hpp"

#define SCAN_CODE_CASE(sc, os) \
  case scan_code::sc: \
    return (os) << #sc



namespace hou
{

std::ostream& operator<<(std::ostream& os, scan_code sc)
{
  switch(sc)
  {
    SCAN_CODE_CASE(escape, os);

    SCAN_CODE_CASE(num1, os);
    SCAN_CODE_CASE(num2, os);
    SCAN_CODE_CASE(num3, os);
    SCAN_CODE_CASE(num4, os);
    SCAN_CODE_CASE(num5, os);
    SCAN_CODE_CASE(num6, os);
    SCAN_CODE_CASE(num7, os);
    SCAN_CODE_CASE(num8, os);
    SCAN_CODE_CASE(num9, os);
    SCAN_CODE_CASE(num0, os);
    SCAN_CODE_CASE(dash, os);
    SCAN_CODE_CASE(equal, os);
    SCAN_CODE_CASE(backspace, os);

    SCAN_CODE_CASE(tab, os);
    SCAN_CODE_CASE(q, os);
    SCAN_CODE_CASE(w, os);
    SCAN_CODE_CASE(e, os);
    SCAN_CODE_CASE(r, os);
    SCAN_CODE_CASE(t, os);
    SCAN_CODE_CASE(y, os);
    SCAN_CODE_CASE(u, os);
    SCAN_CODE_CASE(i, os);
    SCAN_CODE_CASE(o, os);
    SCAN_CODE_CASE(p, os);
    SCAN_CODE_CASE(l_bracket, os);
    SCAN_CODE_CASE(r_bracket, os);
    SCAN_CODE_CASE(enter, os);
    SCAN_CODE_CASE(numpad_enter, os);

    SCAN_CODE_CASE(l_ctrl, os);
    SCAN_CODE_CASE(r_ctrl, os);
    SCAN_CODE_CASE(a, os);
    SCAN_CODE_CASE(s, os);
    SCAN_CODE_CASE(d, os);
    SCAN_CODE_CASE(f, os);
    SCAN_CODE_CASE(g, os);
    SCAN_CODE_CASE(h, os);
    SCAN_CODE_CASE(j, os);
    SCAN_CODE_CASE(k, os);
    SCAN_CODE_CASE(l, os);
    SCAN_CODE_CASE(semicolon, os);
    SCAN_CODE_CASE(quote, os);
    SCAN_CODE_CASE(tilde, os);

    SCAN_CODE_CASE(l_shift, os);
    SCAN_CODE_CASE(backslash, os);
    SCAN_CODE_CASE(z, os);
    SCAN_CODE_CASE(x, os);
    SCAN_CODE_CASE(c, os);
    SCAN_CODE_CASE(v, os);
    SCAN_CODE_CASE(b, os);
    SCAN_CODE_CASE(n, os);
    SCAN_CODE_CASE(m, os);
    SCAN_CODE_CASE(comma, os);
    SCAN_CODE_CASE(period, os);
    SCAN_CODE_CASE(slash, os);
    SCAN_CODE_CASE(divide, os);
    SCAN_CODE_CASE(r_shift, os);

    SCAN_CODE_CASE(multiply, os);
    SCAN_CODE_CASE(print_screen, os);
    SCAN_CODE_CASE(l_alt, os);
    SCAN_CODE_CASE(r_alt, os);
    SCAN_CODE_CASE(space, os);
    SCAN_CODE_CASE(caps_lock, os);

    SCAN_CODE_CASE(f1, os);
    SCAN_CODE_CASE(f2, os);
    SCAN_CODE_CASE(f3, os);
    SCAN_CODE_CASE(f4, os);
    SCAN_CODE_CASE(f5, os);
    SCAN_CODE_CASE(f6, os);
    SCAN_CODE_CASE(f7, os);
    SCAN_CODE_CASE(f8, os);
    SCAN_CODE_CASE(f9, os);
    SCAN_CODE_CASE(f10, os);

    SCAN_CODE_CASE(pause, os);
    SCAN_CODE_CASE(num_lock, os);
    SCAN_CODE_CASE(scroll_lock, os);

    SCAN_CODE_CASE(numpad7, os);
    SCAN_CODE_CASE(home, os);
    SCAN_CODE_CASE(numpad8, os);
    SCAN_CODE_CASE(up, os);
    SCAN_CODE_CASE(numpad9, os);
    SCAN_CODE_CASE(page_up, os);
    SCAN_CODE_CASE(subtract, os);
    SCAN_CODE_CASE(numpad4, os);
    SCAN_CODE_CASE(left, os);
    SCAN_CODE_CASE(numpad5, os);
    SCAN_CODE_CASE(numpad6, os);
    SCAN_CODE_CASE(right, os);
    SCAN_CODE_CASE(add, os);
    SCAN_CODE_CASE(numpad1, os);
    SCAN_CODE_CASE(end, os);
    SCAN_CODE_CASE(numpad2, os);
    SCAN_CODE_CASE(down, os);
    SCAN_CODE_CASE(numpad3, os);
    SCAN_CODE_CASE(page_down, os);
    SCAN_CODE_CASE(numpad0, os);
    SCAN_CODE_CASE(ins, os);
    SCAN_CODE_CASE(decimal, os);
    SCAN_CODE_CASE(del, os);

    SCAN_CODE_CASE(f11, os);
    SCAN_CODE_CASE(f12, os);

    // Made up scan code to cover whole keyboard.
    SCAN_CODE_CASE(l_system, os);
    SCAN_CODE_CASE(r_system, os);
    SCAN_CODE_CASE(apps, os);

    default:
      return os;
  }
}

}  // namespace hou
