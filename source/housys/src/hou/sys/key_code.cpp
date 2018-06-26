// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/key_code.hpp"

#include "hou/sys/scan_code.hpp"

#include "hou/cor/exception.hpp"

#define KEY_CODE_CASE(kc, os)                                                  \
  case key_code::kc:                                                           \
    return (os) << #kc



namespace hou
{

std::ostream& operator<<(std::ostream& os, key_code kc)
{
  switch(kc)
  {
    KEY_CODE_CASE(unknown, os);

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
    KEY_CODE_CASE(numpad_plus, os);
    KEY_CODE_CASE(numpad_minus, os);
    KEY_CODE_CASE(numpad_multiply, os);
    KEY_CODE_CASE(numpad_divide, os);
    KEY_CODE_CASE(numpad_decimal, os);
    KEY_CODE_CASE(numpad_enter, os);

    KEY_CODE_CASE(page_up, os);
    KEY_CODE_CASE(page_down, os);
    KEY_CODE_CASE(end, os);
    KEY_CODE_CASE(home, os);
    KEY_CODE_CASE(insert, os);
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

    KEY_CODE_CASE(lbracket, os);
    KEY_CODE_CASE(rbracket, os);
    KEY_CODE_CASE(semicolon, os);
    KEY_CODE_CASE(comma, os);
    KEY_CODE_CASE(period, os);
    KEY_CODE_CASE(apostrophe, os);
    KEY_CODE_CASE(slash, os);
    KEY_CODE_CASE(backslash, os);
    KEY_CODE_CASE(grave, os);
    KEY_CODE_CASE(equal, os);
    KEY_CODE_CASE(dash, os);
    KEY_CODE_CASE(space, os);
    KEY_CODE_CASE(enter, os);
    KEY_CODE_CASE(tab, os);

    KEY_CODE_CASE(caps_lock, os);
    KEY_CODE_CASE(num_lock, os);
    KEY_CODE_CASE(scroll_lock, os);
    KEY_CODE_CASE(lctrl, os);
    KEY_CODE_CASE(rctrl, os);
    KEY_CODE_CASE(lalt, os);
    KEY_CODE_CASE(ralt, os);
    KEY_CODE_CASE(lshift, os);
    KEY_CODE_CASE(rshift, os);
    KEY_CODE_CASE(lsystem, os);
    KEY_CODE_CASE(rsystem, os);

    KEY_CODE_CASE(ac_back, os);
    KEY_CODE_CASE(ac_forward, os);
    KEY_CODE_CASE(ac_refresh, os);
    KEY_CODE_CASE(ac_stop, os);
    KEY_CODE_CASE(ac_search, os);
    KEY_CODE_CASE(ac_bookmarks, os);
    KEY_CODE_CASE(ac_home, os);

    KEY_CODE_CASE(volume_up, os);
    KEY_CODE_CASE(volume_down, os);
    KEY_CODE_CASE(mute, os);
    KEY_CODE_CASE(media_next_track, os);
    KEY_CODE_CASE(media_previous_track, os);
    KEY_CODE_CASE(media_stop, os);
    KEY_CODE_CASE(media_play_pause, os);
    KEY_CODE_CASE(launch_media_select, os);
    KEY_CODE_CASE(launch_mail, os);

    KEY_CODE_CASE(again, os);
    KEY_CODE_CASE(application, os);
    KEY_CODE_CASE(alt_erase, os);
    KEY_CODE_CASE(brightness_up, os);
    KEY_CODE_CASE(brightness_down, os);
    KEY_CODE_CASE(calculator, os);
    KEY_CODE_CASE(cancel, os);
    KEY_CODE_CASE(clear_again, os);
    KEY_CODE_CASE(computer, os);
    KEY_CODE_CASE(copy, os);
    KEY_CODE_CASE(crsel, os);
    KEY_CODE_CASE(currency_sub_unit, os);
    KEY_CODE_CASE(currency_unit, os);
    KEY_CODE_CASE(cut, os);
    KEY_CODE_CASE(decimal_separator, os);
    KEY_CODE_CASE(display_switch, os);
    KEY_CODE_CASE(eject, os);
    KEY_CODE_CASE(escape, os);
    KEY_CODE_CASE(execute, os);
    KEY_CODE_CASE(exsel, os);
    KEY_CODE_CASE(find, os);
    KEY_CODE_CASE(help, os);
    KEY_CODE_CASE(illumination_down, os);
    KEY_CODE_CASE(illumination_up, os);
    KEY_CODE_CASE(illumination_toggle, os);
    KEY_CODE_CASE(oper, os);
    KEY_CODE_CASE(out, os);
    KEY_CODE_CASE(paste, os);
    KEY_CODE_CASE(pause, os);
    KEY_CODE_CASE(print_screen, os);
    KEY_CODE_CASE(power, os);
    KEY_CODE_CASE(prior, os);
    KEY_CODE_CASE(select, os);
    KEY_CODE_CASE(separator, os);
    KEY_CODE_CASE(sleep, os);
    KEY_CODE_CASE(sys_req, os);
    KEY_CODE_CASE(thousands_separator, os);
    KEY_CODE_CASE(undo, os);
    KEY_CODE_CASE(www, os);

    KEY_CODE_CASE(ampersand, os);
    KEY_CODE_CASE(asterisk, os);
    KEY_CODE_CASE(at, os);
    KEY_CODE_CASE(caret, os);
    KEY_CODE_CASE(colon, os);
    KEY_CODE_CASE(dollar, os);
    KEY_CODE_CASE(exclamation_mark, os);
    KEY_CODE_CASE(less, os);
    KEY_CODE_CASE(greater, os);
    KEY_CODE_CASE(hash, os);
    KEY_CODE_CASE(lparenthesis, os);
    KEY_CODE_CASE(rparentheses, os);
    KEY_CODE_CASE(percent, os);
    KEY_CODE_CASE(plus, os);
    KEY_CODE_CASE(question_mark, os);
    KEY_CODE_CASE(double_quote, os);
    KEY_CODE_CASE(underscore, os);

    default:
      return os << "key_code("
                << static_cast<std::underlying_type<key_code>::type>(kc) << ")";
  }
  HOU_UNREACHABLE();
  return os;
}



key_code get_key_code(scan_code sc)
{
  SDL_Keycode kc = SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(sc));

  // SDL performs a bitwise OR with the scancode and the mask 0x40000000 in some
  // cases. If the scancode is SDL_SCANCODE_UNKNOWN (= 0), this leads to a non
  // zero value for the keycode. They keycode shold also be 0 though.
  if(kc == 0x40000000)
  {
    kc = 0;
  }

  return key_code(kc);
}



scan_code get_scan_code(key_code kc)
{
  return scan_code(SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(kc)));
}

}  // namespace hou
