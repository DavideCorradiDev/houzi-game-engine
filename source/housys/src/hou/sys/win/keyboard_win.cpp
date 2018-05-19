// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/keyboard.hpp"

#include "hou/sys/win/win.hpp"

#include "hou/cor/exception.hpp"



namespace hou
{

namespace
{

constexpr UINT key_code_to_win_key(key_code key) noexcept;

UINT scan_code_to_win_key(scan_code sc) noexcept;

bool is_win_virtual_key_pressed(UINT v_key) noexcept;

bool is_win_virtual_key_toggled(UINT v_key) noexcept;



constexpr UINT key_code_to_win_key(key_code key) noexcept
{
  switch(key)
  {
    case key_code::escape:
      return VK_ESCAPE;

    case key_code::print:
      return VK_PRINT;
    case key_code::print_screen:
      return VK_SNAPSHOT;
    case key_code::pause:
      return VK_PAUSE;
    case key_code::execute:
      return VK_EXECUTE;
    case key_code::select:
      return VK_SELECT;
    case key_code::help:
      return VK_HELP;
    case key_code::sleep:
      return VK_SLEEP;
    case key_code::apps:
      return VK_APPS;
    case key_code::l_system:
      return VK_LWIN;
    case key_code::r_system:
      return VK_RWIN;

    case key_code::f1:
      return VK_F1;
    case key_code::f2:
      return VK_F2;
    case key_code::f3:
      return VK_F3;
    case key_code::f4:
      return VK_F4;
    case key_code::f5:
      return VK_F5;
    case key_code::f6:
      return VK_F6;
    case key_code::f7:
      return VK_F7;
    case key_code::f8:
      return VK_F8;
    case key_code::f9:
      return VK_F9;
    case key_code::f10:
      return VK_F10;
    case key_code::f11:
      return VK_F11;
    case key_code::f12:
      return VK_F12;
    case key_code::f13:
      return VK_F13;
    case key_code::f14:
      return VK_F14;
    case key_code::f15:
      return VK_F15;
    case key_code::f16:
      return VK_F16;
    case key_code::f17:
      return VK_F17;
    case key_code::f18:
      return VK_F18;
    case key_code::f19:
      return VK_F19;
    case key_code::f20:
      return VK_F20;
    case key_code::f21:
      return VK_F21;
    case key_code::f22:
      return VK_F22;
    case key_code::f23:
      return VK_F23;
    case key_code::f24:
      return VK_F24;

    case key_code::numpad0:
      return VK_NUMPAD0;
    case key_code::numpad1:
      return VK_NUMPAD1;
    case key_code::numpad2:
      return VK_NUMPAD2;
    case key_code::numpad3:
      return VK_NUMPAD3;
    case key_code::numpad4:
      return VK_NUMPAD4;
    case key_code::numpad5:
      return VK_NUMPAD5;
    case key_code::numpad6:
      return VK_NUMPAD6;
    case key_code::numpad7:
      return VK_NUMPAD7;
    case key_code::numpad8:
      return VK_NUMPAD8;
    case key_code::numpad9:
      return VK_NUMPAD9;

    case key_code::add:
      return VK_ADD;
    case key_code::subtract:
      return VK_SUBTRACT;
    case key_code::multiply:
      return VK_MULTIPLY;
    case key_code::divide:
      return VK_DIVIDE;
    case key_code::decimal:
      return VK_DECIMAL;
    case key_code::separator:
      return VK_SEPARATOR;

    case key_code::page_up:
      return VK_PRIOR;
    case key_code::page_down:
      return VK_NEXT;
    case key_code::end:
      return VK_END;
    case key_code::home:
      return VK_HOME;
    case key_code::ins:
      return VK_INSERT;
    case key_code::del:
      return VK_DELETE;
    case key_code::backspace:
      return VK_BACK;

    case key_code::left:
      return VK_LEFT;
    case key_code::right:
      return VK_RIGHT;
    case key_code::up:
      return VK_UP;
    case key_code::down:
      return VK_DOWN;

    case key_code::num0:
      return '0';
    case key_code::num1:
      return '1';
    case key_code::num2:
      return '2';
    case key_code::num3:
      return '3';
    case key_code::num4:
      return '4';
    case key_code::num5:
      return '5';
    case key_code::num6:
      return '6';
    case key_code::num7:
      return '7';
    case key_code::num8:
      return '8';
    case key_code::num9:
      return '9';

    case key_code::a:
      return 'A';
    case key_code::b:
      return 'B';
    case key_code::c:
      return 'C';
    case key_code::d:
      return 'D';
    case key_code::e:
      return 'E';
    case key_code::f:
      return 'F';
    case key_code::g:
      return 'G';
    case key_code::h:
      return 'H';
    case key_code::i:
      return 'I';
    case key_code::j:
      return 'J';
    case key_code::k:
      return 'K';
    case key_code::l:
      return 'L';
    case key_code::m:
      return 'M';
    case key_code::n:
      return 'N';
    case key_code::o:
      return 'O';
    case key_code::p:
      return 'P';
    case key_code::q:
      return 'Q';
    case key_code::r:
      return 'R';
    case key_code::s:
      return 'S';
    case key_code::t:
      return 'T';
    case key_code::u:
      return 'U';
    case key_code::v:
      return 'V';
    case key_code::x:
      return 'X';
    case key_code::y:
      return 'Y';
    case key_code::w:
      return 'W';
    case key_code::z:
      return 'Z';

    case key_code::l_bracket:
      return VK_OEM_4;
    case key_code::r_bracket:
      return VK_OEM_6;
    case key_code::semicolon:
      return VK_OEM_1;
    case key_code::comma:
      return VK_OEM_COMMA;
    case key_code::period:
      return VK_OEM_PERIOD;
    case key_code::quote:
      return VK_OEM_7;
    case key_code::slash:
      return VK_OEM_2;
    case key_code::backslash:
      return VK_OEM_5;
    case key_code::tilde:
      return VK_OEM_3;
    case key_code::equal:
      return VK_OEM_PLUS;
    case key_code::dash:
      return VK_OEM_MINUS;
    case key_code::space:
      return VK_SPACE;
    case key_code::enter:
      return VK_RETURN;
    case key_code::tab:
      return VK_TAB;
    case key_code::special1:
      return VK_OEM_8;
    case key_code::special2:
      return VK_OEM_102;

    case key_code::caps_lock:
      return VK_CAPITAL;
    case key_code::num_lock:
      return VK_NUMLOCK;
    case key_code::scroll_lock:
      return VK_SCROLL;

    case key_code::l_ctrl:
      return VK_LCONTROL;
    case key_code::r_ctrl:
      return VK_RCONTROL;
    case key_code::l_alt:
      return VK_LMENU;
    case key_code::r_alt:
      return VK_RMENU;
    case key_code::l_shift:
      return VK_LSHIFT;
    case key_code::r_shift:
      return VK_RSHIFT;

    case key_code::kana:
      return VK_KANA;
    case key_code::hangul:
      return VK_HANGUL;
    case key_code::junja:
      return VK_JUNJA;
    case key_code::final:
      return VK_FINAL;
    case key_code::hanja:
      return VK_HANJA;
    case key_code::kanji:
      return VK_KANJI;
    case key_code::convert:
      return VK_CONVERT;
    case key_code::non_convert:
      return VK_NONCONVERT;
    case key_code::accept:
      return VK_ACCEPT;
    case key_code::mode_change:
      return VK_MODECHANGE;
    case key_code::process_key:
      return VK_PROCESSKEY;

    case key_code::browser_back:
      return VK_BROWSER_BACK;
    case key_code::browser_forward:
      return VK_BROWSER_FORWARD;
    case key_code::browser_refresh:
      return VK_BROWSER_REFRESH;
    case key_code::browser_stop:
      return VK_BROWSER_STOP;
    case key_code::browser_search:
      return VK_BROWSER_SEARCH;
    case key_code::browser_favorites:
      return VK_BROWSER_FAVORITES;
    case key_code::browser_home:
      return VK_BROWSER_HOME;

    case key_code::volume_up:
      return VK_VOLUME_UP;
    case key_code::volume_down:
      return VK_VOLUME_DOWN;
    case key_code::volume_mute:
      return VK_VOLUME_MUTE;

    case key_code::media_next_track:
      return VK_MEDIA_NEXT_TRACK;
    case key_code::media_previous_track:
      return VK_MEDIA_PREV_TRACK;
    case key_code::media_stop:
      return VK_MEDIA_STOP;
    case key_code::media_play_pause:
      return VK_MEDIA_PLAY_PAUSE;
    case key_code::launch_media_select:
      return VK_LAUNCH_MEDIA_SELECT;
    case key_code::launch_mail:
      return VK_LAUNCH_MAIL;
    case key_code::launch_app1:
      return VK_LAUNCH_APP1;
    case key_code::launch_app2:
      return VK_LAUNCH_APP2;

    case key_code::attn:
      return VK_ATTN;
    case key_code::cr_sel:
      return VK_CRSEL;
    case key_code::ex_sel:
      return VK_EXSEL;
    case key_code::erase_eof:
      return VK_EREOF;
    case key_code::play:
      return VK_PLAY;
    case key_code::zoom:
      return VK_ZOOM;
    case key_code::pa1:
      return VK_PA1;
    case key_code::clear:
      return VK_CLEAR;
    case key_code::packet:
      return VK_PACKET;
    default:
      HOU_UNREACHABLE();
      return 0;
  }
}



UINT scan_code_to_win_key(scan_code sc) noexcept
{
  // Special handling for some scan codes is needed for consistency with
  // scan codes in window messages.

  // When numlock is on, windows checks nothing when one of the numpad keys is
  // pressed.
  // When numlock is off, if a numpad key is pressed both the numpad key and the
  // corresponding alternative key are seen as pressed.
  // To avoid these problems, these scan codes must be explicitly converted.
  if(sc == scan_code::numpad0)
  {
    return VK_NUMPAD0;
  }
  else if(sc == scan_code::numpad1)
  {
    return VK_NUMPAD1;
  }
  else if(sc == scan_code::numpad2)
  {
    return VK_NUMPAD2;
  }
  else if(sc == scan_code::numpad3)
  {
    return VK_NUMPAD3;
  }
  else if(sc == scan_code::numpad4)
  {
    return VK_NUMPAD4;
  }
  else if(sc == scan_code::numpad5)
  {
    return VK_NUMPAD5;
  }
  else if(sc == scan_code::numpad6)
  {
    return VK_NUMPAD6;
  }
  else if(sc == scan_code::numpad7)
  {
    return VK_NUMPAD7;
  }
  else if(sc == scan_code::numpad8)
  {
    return VK_NUMPAD8;
  }
  else if(sc == scan_code::numpad9)
  {
    return VK_NUMPAD9;
  }
  else if(sc == scan_code::decimal)
  {
    return VK_DECIMAL;
  }
  // Without these lines, Windows checks the pause key when the numlock key
  // is requested, and checks nothing when the print key is requested. This
  // is in disagreement with the scancodes received by the window messages.
  else if(sc == scan_code::pause)
  {
    return VK_PAUSE;
  }
  else if(sc == scan_code::num_lock)
  {
    return VK_NUMLOCK;
  }

  // Other keys behave fine on their own.
  return MapVirtualKey(static_cast<uint>(sc), MAPVK_VSC_TO_VK_EX);
}



bool is_win_virtual_key_pressed(UINT v_key) noexcept
{
  // Most significant bit set if the key is pressed.
  return (GetAsyncKeyState(v_key) & 0x8000) != 0;
}



bool is_win_virtual_key_toggled(UINT v_key) noexcept
{
  // Least significant bit set if the key is pressed.
  return (GetKeyState(v_key) & 0x0001) != 0;
}

}  // namespace



namespace keyboard
{

bool is_key_pressed(key_code kc) noexcept
{
  return is_win_virtual_key_pressed(key_code_to_win_key(kc));
}



bool is_key_pressed(scan_code sc) noexcept
{
  return is_win_virtual_key_pressed(scan_code_to_win_key(sc));
}



bool is_key_toggled(key_code kc) noexcept
{
  return is_win_virtual_key_toggled(key_code_to_win_key(kc));
}



bool is_key_toggled(scan_code sc) noexcept
{
  return is_win_virtual_key_toggled(scan_code_to_win_key(sc));
}

}  // namespace keyboard

}  // namespace hou
