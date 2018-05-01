// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/key_code.hpp"

#define KEY_CODE_CASE(kc, os) \
  case key_code::kc: \
    return (os) << #kc



namespace hou
{

std::ostream& operator<<(std::ostream& os, key_code kc)
{
  switch(kc)
  {
    KEY_CODE_CASE(escape, os);

    KEY_CODE_CASE(print, os);
    KEY_CODE_CASE(print_screen, os);
    KEY_CODE_CASE(pause, os);
    KEY_CODE_CASE(execute, os);
    KEY_CODE_CASE(select, os);
    KEY_CODE_CASE(help, os);
    KEY_CODE_CASE(sleep, os);
    KEY_CODE_CASE(apps, os);
    KEY_CODE_CASE(l_system, os);
    KEY_CODE_CASE(r_system, os);

    KEY_CODE_CASE(f1, os);
    KEY_CODE_CASE(f2, os);
    KEY_CODE_CASE(f3, os);
    KEY_CODE_CASE(f4, os);
    KEY_CODE_CASE(f5, os);
    KEY_CODE_CASE(f6, os);
    KEY_CODE_CASE(f7, os);
    KEY_CODE_CASE(f8, os);
    KEY_CODE_CASE(f9, os);
    KEY_CODE_CASE(f10, os);
    KEY_CODE_CASE(f11, os);
    KEY_CODE_CASE(f12, os);
    KEY_CODE_CASE(f13, os);
    KEY_CODE_CASE(f14, os);
    KEY_CODE_CASE(f15, os);
    KEY_CODE_CASE(f16, os);
    KEY_CODE_CASE(f17, os);
    KEY_CODE_CASE(f18, os);
    KEY_CODE_CASE(f19, os);
    KEY_CODE_CASE(f20, os);
    KEY_CODE_CASE(f21, os);
    KEY_CODE_CASE(f22, os);
    KEY_CODE_CASE(f23, os);
    KEY_CODE_CASE(f24, os);

    KEY_CODE_CASE(numpad0, os);
    KEY_CODE_CASE(numpad1, os);
    KEY_CODE_CASE(numpad2, os);
    KEY_CODE_CASE(numpad3, os);
    KEY_CODE_CASE(numpad4, os);
    KEY_CODE_CASE(numpad5, os);
    KEY_CODE_CASE(numpad6, os);
    KEY_CODE_CASE(numpad7, os);
    KEY_CODE_CASE(numpad8, os);
    KEY_CODE_CASE(numpad9, os);

    KEY_CODE_CASE(add, os);
    KEY_CODE_CASE(subtract, os);
    KEY_CODE_CASE(multiply, os);
    KEY_CODE_CASE(divide, os);
    KEY_CODE_CASE(decimal, os);
    KEY_CODE_CASE(separator, os);

    KEY_CODE_CASE(page_up, os);
    KEY_CODE_CASE(page_down, os);
    KEY_CODE_CASE(end, os);
    KEY_CODE_CASE(home, os);
    KEY_CODE_CASE(ins, os);
    KEY_CODE_CASE(del, os);
    KEY_CODE_CASE(backspace, os);

    KEY_CODE_CASE(left, os);
    KEY_CODE_CASE(right, os);
    KEY_CODE_CASE(up, os);
    KEY_CODE_CASE(down, os);

    KEY_CODE_CASE(num0, os);
    KEY_CODE_CASE(num1, os);
    KEY_CODE_CASE(num2, os);
    KEY_CODE_CASE(num3, os);
    KEY_CODE_CASE(num4, os);
    KEY_CODE_CASE(num5, os);
    KEY_CODE_CASE(num6, os);
    KEY_CODE_CASE(num7, os);
    KEY_CODE_CASE(num8, os);
    KEY_CODE_CASE(num9, os);

    KEY_CODE_CASE(a, os);
    KEY_CODE_CASE(b, os);
    KEY_CODE_CASE(c, os);
    KEY_CODE_CASE(d, os);
    KEY_CODE_CASE(e, os);
    KEY_CODE_CASE(f, os);
    KEY_CODE_CASE(g, os);
    KEY_CODE_CASE(h, os);
    KEY_CODE_CASE(i, os);
    KEY_CODE_CASE(j, os);
    KEY_CODE_CASE(k, os);
    KEY_CODE_CASE(l, os);
    KEY_CODE_CASE(m, os);
    KEY_CODE_CASE(n, os);
    KEY_CODE_CASE(o, os);
    KEY_CODE_CASE(p, os);
    KEY_CODE_CASE(q, os);
    KEY_CODE_CASE(r, os);
    KEY_CODE_CASE(s, os);
    KEY_CODE_CASE(t, os);
    KEY_CODE_CASE(u, os);
    KEY_CODE_CASE(v, os);
    KEY_CODE_CASE(x, os);
    KEY_CODE_CASE(y, os);
    KEY_CODE_CASE(w, os);
    KEY_CODE_CASE(z, os);

    KEY_CODE_CASE(l_bracket, os);
    KEY_CODE_CASE(r_bracket, os);
    KEY_CODE_CASE(semicolon, os);
    KEY_CODE_CASE(comma, os);
    KEY_CODE_CASE(period, os);
    KEY_CODE_CASE(quote, os);
    KEY_CODE_CASE(slash, os);
    KEY_CODE_CASE(backslash, os);
    KEY_CODE_CASE(tilde, os);
    KEY_CODE_CASE(equal, os);
    KEY_CODE_CASE(dash, os);
    KEY_CODE_CASE(space, os);
    KEY_CODE_CASE(enter, os);
    KEY_CODE_CASE(tab, os);
    KEY_CODE_CASE(special1, os);
    KEY_CODE_CASE(special2, os);

    KEY_CODE_CASE(caps_lock, os);
    KEY_CODE_CASE(num_lock, os);
    KEY_CODE_CASE(scroll_lock, os);

    KEY_CODE_CASE(l_ctrl, os);
    KEY_CODE_CASE(r_ctrl, os);
    KEY_CODE_CASE(l_alt, os);
    KEY_CODE_CASE(r_alt, os);
    KEY_CODE_CASE(l_shift, os);
    KEY_CODE_CASE(r_shift, os);

    KEY_CODE_CASE(kana, os);
    KEY_CODE_CASE(hangul, os);
    KEY_CODE_CASE(junja, os);
    KEY_CODE_CASE(final, os);
    KEY_CODE_CASE(hanja, os);
    KEY_CODE_CASE(kanji, os);
    KEY_CODE_CASE(convert, os);
    KEY_CODE_CASE(non_convert, os);
    KEY_CODE_CASE(accept, os);
    KEY_CODE_CASE(mode_change, os);
    KEY_CODE_CASE(process_key, os);

    KEY_CODE_CASE(browser_back, os);
    KEY_CODE_CASE(browser_forward, os);
    KEY_CODE_CASE(browser_refresh, os);
    KEY_CODE_CASE(browser_stop, os);
    KEY_CODE_CASE(browser_search, os);
    KEY_CODE_CASE(browser_favorites, os);
    KEY_CODE_CASE(browser_home, os);

    KEY_CODE_CASE(volume_up, os);
    KEY_CODE_CASE(volume_down, os);
    KEY_CODE_CASE(volume_mute, os);

    KEY_CODE_CASE(media_next_track, os);
    KEY_CODE_CASE(media_previous_track, os);
    KEY_CODE_CASE(media_stop, os);
    KEY_CODE_CASE(media_play_pause, os);
    KEY_CODE_CASE(launch_media_select, os);
    KEY_CODE_CASE(launch_mail, os);
    KEY_CODE_CASE(launch_app1, os);
    KEY_CODE_CASE(launch_app2, os);

    KEY_CODE_CASE(attn, os);
    KEY_CODE_CASE(cr_sel, os);
    KEY_CODE_CASE(ex_sel, os);
    KEY_CODE_CASE(erase_eof, os);
    KEY_CODE_CASE(play, os);
    KEY_CODE_CASE(zoom, os);
    KEY_CODE_CASE(pa1, os);
    KEY_CODE_CASE(clear, os);
    KEY_CODE_CASE(packet, os);

    default:
      return os;
  }
}

}  // namespace hou
