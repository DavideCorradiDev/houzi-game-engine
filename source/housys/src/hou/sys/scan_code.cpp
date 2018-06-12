// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/scan_code.hpp"

#include "hou/cor/exception.hpp"

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
    SCAN_CODE_CASE(lbracket, os);
    SCAN_CODE_CASE(rbracket, os);
    SCAN_CODE_CASE(enter, os);
    SCAN_CODE_CASE(numpad_enter, os);

    SCAN_CODE_CASE(lctrl, os);
    SCAN_CODE_CASE(rctrl, os);
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
    SCAN_CODE_CASE(apostrophe, os);
    SCAN_CODE_CASE(grave, os);

    SCAN_CODE_CASE(lshift, os);
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
    SCAN_CODE_CASE(numpad_divide, os);
    SCAN_CODE_CASE(rshift, os);

    SCAN_CODE_CASE(numpad_multiply, os);
    SCAN_CODE_CASE(print_screen, os);
    SCAN_CODE_CASE(lalt, os);
    SCAN_CODE_CASE(ralt, os);
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
    SCAN_CODE_CASE(numpad_minus, os);
    SCAN_CODE_CASE(numpad4, os);
    SCAN_CODE_CASE(left, os);
    SCAN_CODE_CASE(numpad5, os);
    SCAN_CODE_CASE(numpad6, os);
    SCAN_CODE_CASE(right, os);
    SCAN_CODE_CASE(numpad_plus, os);
    SCAN_CODE_CASE(numpad1, os);
    SCAN_CODE_CASE(end, os);
    SCAN_CODE_CASE(numpad2, os);
    SCAN_CODE_CASE(down, os);
    SCAN_CODE_CASE(numpad3, os);
    SCAN_CODE_CASE(page_down, os);
    SCAN_CODE_CASE(numpad0, os);
    SCAN_CODE_CASE(insert, os);
    SCAN_CODE_CASE(numpad_decimal, os);
    SCAN_CODE_CASE(del, os);

    SCAN_CODE_CASE(f11, os);
    SCAN_CODE_CASE(f12, os);

    SCAN_CODE_CASE(lsystem, os);
    SCAN_CODE_CASE(rsystem, os);
    SCAN_CODE_CASE(application, os);

    SCAN_CODE_CASE(ac_back, os);
    SCAN_CODE_CASE(ac_forward, os);
    SCAN_CODE_CASE(ac_refresh, os);
    SCAN_CODE_CASE(ac_stop, os);
    SCAN_CODE_CASE(ac_search, os);
    SCAN_CODE_CASE(ac_bookmarks, os);
    SCAN_CODE_CASE(ac_home, os);

    SCAN_CODE_CASE(volume_up, os);
    SCAN_CODE_CASE(volume_down, os);
    SCAN_CODE_CASE(volume_mute, os);
    SCAN_CODE_CASE(media_next_track, os);
    SCAN_CODE_CASE(media_previous_track, os);
    SCAN_CODE_CASE(media_stop, os);
    SCAN_CODE_CASE(media_play_pause, os);
    SCAN_CODE_CASE(launch_media_select, os);
    SCAN_CODE_CASE(launch_mail, os);

    SCAN_CODE_CASE(again, os);
    SCAN_CODE_CASE(alt_erase, os);

    default:
      HOU_UNREACHABLE();
      return os;
  }
}

}  // namespace hou
