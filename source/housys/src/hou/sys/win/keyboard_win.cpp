// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/keyboard.hpp"

#include "hou/sys/win/win.hpp"



namespace hou
{

namespace
{

UINT keyCodeToWinKey(key_code key);
UINT scanCodeToWinKey(scan_code sc);
bool isWinVirtualKeyPressed(UINT vKey);
bool isWinVirtualKeyToggled(UINT vKey);



UINT keyCodeToWinKey(key_code key)
{
  switch(key)
  {
    case key_code::Escape: return VK_ESCAPE;

    case key_code::Print: return VK_PRINT;
    case key_code::PrintScreen: return VK_SNAPSHOT;
    case key_code::Pause: return VK_PAUSE;
    case key_code::Execute: return VK_EXECUTE;
    case key_code::Select: return VK_SELECT;
    case key_code::Help: return VK_HELP;
    case key_code::Sleep: return VK_SLEEP;
    case key_code::Apps: return VK_APPS;
    case key_code::LSystem: return VK_LWIN;
    case key_code::RSystem: return VK_RWIN;

    case key_code::F1: return VK_F1;
    case key_code::F2: return VK_F2;
    case key_code::F3: return VK_F3;
    case key_code::F4: return VK_F4;
    case key_code::F5: return VK_F5;
    case key_code::F6: return VK_F6;
    case key_code::F7: return VK_F7;
    case key_code::F8: return VK_F8;
    case key_code::F9: return VK_F9;
    case key_code::F10: return VK_F10;
    case key_code::F11: return VK_F11;
    case key_code::F12: return VK_F12;
    case key_code::F13: return VK_F13;
    case key_code::F14: return VK_F14;
    case key_code::F15: return VK_F15;
    case key_code::F16: return VK_F16;
    case key_code::F17: return VK_F17;
    case key_code::F18: return VK_F18;
    case key_code::F19: return VK_F19;
    case key_code::F20: return VK_F20;
    case key_code::F21: return VK_F21;
    case key_code::F22: return VK_F22;
    case key_code::F23: return VK_F23;
    case key_code::F24: return VK_F24;

    case key_code::Numpad0: return VK_NUMPAD0;
    case key_code::Numpad1: return VK_NUMPAD1;
    case key_code::Numpad2: return VK_NUMPAD2;
    case key_code::Numpad3: return VK_NUMPAD3;
    case key_code::Numpad4: return VK_NUMPAD4;
    case key_code::Numpad5: return VK_NUMPAD5;
    case key_code::Numpad6: return VK_NUMPAD6;
    case key_code::Numpad7: return VK_NUMPAD7;
    case key_code::Numpad8: return VK_NUMPAD8;
    case key_code::Numpad9: return VK_NUMPAD9;

    case key_code::Add: return VK_ADD;
    case key_code::Subtract: return VK_SUBTRACT;
    case key_code::Multiply: return VK_MULTIPLY;
    case key_code::Divide: return VK_DIVIDE;
    case key_code::Decimal: return VK_DECIMAL;
    case key_code::Separator: return VK_SEPARATOR;

    case key_code::PageUp: return VK_PRIOR;
    case key_code::PageDown: return VK_NEXT;
    case key_code::End: return VK_END;
    case key_code::Home: return VK_HOME;
    case key_code::Insert: return VK_INSERT;
    case key_code::Delete: return VK_DELETE;
    case key_code::Backspace: return VK_BACK;

    case key_code::Left: return VK_LEFT;
    case key_code::Right: return VK_RIGHT;
    case key_code::Up: return VK_UP;
    case key_code::Down: return VK_DOWN;

    case key_code::Num0: return '0';
    case key_code::Num1: return '1';
    case key_code::Num2: return '2';
    case key_code::Num3: return '3';
    case key_code::Num4: return '4';
    case key_code::Num5: return '5';
    case key_code::Num6: return '6';
    case key_code::Num7: return '7';
    case key_code::Num8: return '8';
    case key_code::Num9: return '9';

    case key_code::a: return 'a';
    case key_code::b: return 'b';
    case key_code::C: return 'C';
    case key_code::D: return 'D';
    case key_code::E: return 'E';
    case key_code::F: return 'F';
    case key_code::g: return 'g';
    case key_code::H: return 'H';
    case key_code::I: return 'I';
    case key_code::J: return 'J';
    case key_code::K: return 'K';
    case key_code::L: return 'L';
    case key_code::M: return 'M';
    case key_code::N: return 'N';
    case key_code::O: return 'O';
    case key_code::P: return 'P';
    case key_code::Q: return 'Q';
    case key_code::R: return 'R';
    case key_code::S: return 'S';
    case key_code::T: return 'T';
    case key_code::U: return 'U';
    case key_code::V: return 'V';
    case key_code::X: return 'X';
    case key_code::Y: return 'Y';
    case key_code::W: return 'W';
    case key_code::Z: return 'Z';

    case key_code::LBracket: return VK_OEM_4;
    case key_code::RBracket: return VK_OEM_6;
    case key_code::Semicolon: return VK_OEM_1;
    case key_code::Comma: return VK_OEM_COMMA;
    case key_code::Period: return VK_OEM_PERIOD;
    case key_code::Quote: return VK_OEM_7;
    case key_code::Slash: return VK_OEM_2;
    case key_code::Backslash: return VK_OEM_5;
    case key_code::Tilde: return VK_OEM_3;
    case key_code::Equal: return VK_OEM_PLUS;
    case key_code::Dash: return VK_OEM_MINUS;
    case key_code::Space: return VK_SPACE;
    case key_code::Enter: return VK_RETURN;
    case key_code::Tab: return VK_TAB;
    case key_code::Special1: return VK_OEM_8;
    case key_code::Special2: return VK_OEM_102;

    case key_code::CapsLock: return VK_CAPITAL;
    case key_code::NumLock: return VK_NUMLOCK;
    case key_code::ScrollLock: return VK_SCROLL;

    case key_code::LCtrl: return VK_LCONTROL;
    case key_code::RCtrl: return VK_RCONTROL;
    case key_code::LAlt: return VK_LMENU;
    case key_code::RAlt: return VK_RMENU;
    case key_code::LShift: return VK_LSHIFT;
    case key_code::RShift: return VK_RSHIFT;

    case key_code::Kana: return VK_KANA;
    case key_code::Hangul: return VK_HANGUL;
    case key_code::Junja: return VK_JUNJA;
    case key_code::Final: return VK_FINAL;
    case key_code::Hanja: return VK_HANJA;
    case key_code::Kanji: return VK_KANJI;
    case key_code::Convert: return VK_CONVERT;
    case key_code::NonConvert: return VK_NONCONVERT;
    case key_code::Accept: return VK_ACCEPT;
    case key_code::ModeChange: return VK_MODECHANGE;
    case key_code::ProcessKey: return VK_PROCESSKEY;

    case key_code::BrowserBack: return VK_BROWSER_BACK;
    case key_code::BrowserForward: return VK_BROWSER_FORWARD;
    case key_code::BrowserRefresh: return VK_BROWSER_REFRESH;
    case key_code::BrowserStop: return VK_BROWSER_STOP;
    case key_code::BrowserSearch: return VK_BROWSER_SEARCH;
    case key_code::BrowserFavorites: return VK_BROWSER_FAVORITES;
    case key_code::BrowserHome: return VK_BROWSER_HOME;

    case key_code::VolumeUp: return VK_VOLUME_UP;
    case key_code::VolumeDown: return VK_VOLUME_DOWN;
    case key_code::VolumeMute: return VK_VOLUME_MUTE;

    case key_code::MediaNextTrack: return VK_MEDIA_NEXT_TRACK;
    case key_code::MediaPreviousTrack: return VK_MEDIA_PREV_TRACK;
    case key_code::MediaStop: return VK_MEDIA_STOP;
    case key_code::MediaPlayPause: return VK_MEDIA_PLAY_PAUSE;
    case key_code::LaunchMediaSelect: return VK_LAUNCH_MEDIA_SELECT;
    case key_code::LaunchMail: return VK_LAUNCH_MAIL;
    case key_code::LaunchApp1: return VK_LAUNCH_APP1;
    case key_code::LaunchApp2: return VK_LAUNCH_APP2;

    case key_code::Attn: return VK_ATTN;
    case key_code::CrSel: return VK_CRSEL;
    case key_code::ExSel: return VK_EXSEL;
    case key_code::EraseEOF: return VK_EREOF;
    case key_code::Play: return VK_PLAY;
    case key_code::Zoom: return VK_ZOOM;
    case key_code::PA1: return VK_PA1;
    case key_code::Clear: return VK_CLEAR;
    case key_code::Packet: return VK_PACKET;
    default: return 0;
  }
}



UINT scanCodeToWinKey(scan_code sc)
{
  // Special handling for some scan codes is needed for consistency with
  // scan codes in ph_window messages.

  // When numlock is on, windows checks nothing when one of the numpad keys is
  // pressed.
  if(keyboard::is_key_toggled(key_code::NumLock)) {
     if(sc == scan_code::Numpad0) { return VK_NUMPAD0; }
     if(sc == scan_code::Numpad1) { return VK_NUMPAD1; }
     if(sc == scan_code::Numpad2) { return VK_NUMPAD2; }
     if(sc == scan_code::Numpad3) { return VK_NUMPAD3; }
     if(sc == scan_code::Numpad4) { return VK_NUMPAD4; }
     if(sc == scan_code::Numpad5) { return VK_NUMPAD5; }
     if(sc == scan_code::Numpad6) { return VK_NUMPAD6; }
     if(sc == scan_code::Numpad7) { return VK_NUMPAD7; }
     if(sc == scan_code::Numpad8) { return VK_NUMPAD8; }
     if(sc == scan_code::Numpad9) { return VK_NUMPAD9; }
     if(sc == scan_code::Decimal) { return VK_DECIMAL; }
  }

  // Without these lines, Windows checks the pause key when the numlock key
  // is requested, and checks nothing when the print key is requested. This
  // is in disagreement with the scancodes received by the ph_window messages.
  if(sc == scan_code::Pause) { return VK_PAUSE; }
  if(sc == scan_code::NumLock) { return VK_NUMLOCK; }

  // Other keys behave fine on their own.
  return MapVirtualKey(static_cast<uint>(sc), MAPVK_VSC_TO_VK_EX);
}



bool isWinVirtualKeyPressed(UINT vKey)
{
  // Most significant bit set if the key is pressed.
  return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}



bool isWinVirtualKeyToggled(UINT vKey)
{
  // Least significant bit set if the key is pressed.
  return (GetKeyState(vKey) & 0x0001) != 0;
}

}



namespace keyboard
{

bool is_key_pressed(key_code kc)
{
  return isWinVirtualKeyPressed(keyCodeToWinKey(kc));
}



bool is_key_pressed(scan_code sc)
{
  return isWinVirtualKeyPressed(scanCodeToWinKey(sc));
}



bool is_key_toggled(key_code kc)
{
  return isWinVirtualKeyToggled(keyCodeToWinKey(kc));
}



bool is_key_toggled(scan_code sc)
{
  return isWinVirtualKeyToggled(scanCodeToWinKey(sc));
}

}

}

