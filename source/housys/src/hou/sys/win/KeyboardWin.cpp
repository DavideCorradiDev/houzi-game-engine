// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/Keyboard.hpp"

#include "hou/sys/win/Win.hpp"



namespace hou
{

namespace
{

UINT keyCodeToWinKey(KeyCode key);
UINT scanCodeToWinKey(ScanCode sc);
bool isWinVirtualKeyPressed(UINT vKey);
bool isWinVirtualKeyToggled(UINT vKey);



UINT keyCodeToWinKey(KeyCode key)
{
  switch(key)
  {
    case KeyCode::Escape: return VK_ESCAPE;

    case KeyCode::Print: return VK_PRINT;
    case KeyCode::PrintScreen: return VK_SNAPSHOT;
    case KeyCode::Pause: return VK_PAUSE;
    case KeyCode::Execute: return VK_EXECUTE;
    case KeyCode::Select: return VK_SELECT;
    case KeyCode::Help: return VK_HELP;
    case KeyCode::Sleep: return VK_SLEEP;
    case KeyCode::Apps: return VK_APPS;
    case KeyCode::LSystem: return VK_LWIN;
    case KeyCode::RSystem: return VK_RWIN;

    case KeyCode::F1: return VK_F1;
    case KeyCode::F2: return VK_F2;
    case KeyCode::F3: return VK_F3;
    case KeyCode::F4: return VK_F4;
    case KeyCode::F5: return VK_F5;
    case KeyCode::F6: return VK_F6;
    case KeyCode::F7: return VK_F7;
    case KeyCode::F8: return VK_F8;
    case KeyCode::F9: return VK_F9;
    case KeyCode::F10: return VK_F10;
    case KeyCode::F11: return VK_F11;
    case KeyCode::F12: return VK_F12;
    case KeyCode::F13: return VK_F13;
    case KeyCode::F14: return VK_F14;
    case KeyCode::F15: return VK_F15;
    case KeyCode::F16: return VK_F16;
    case KeyCode::F17: return VK_F17;
    case KeyCode::F18: return VK_F18;
    case KeyCode::F19: return VK_F19;
    case KeyCode::F20: return VK_F20;
    case KeyCode::F21: return VK_F21;
    case KeyCode::F22: return VK_F22;
    case KeyCode::F23: return VK_F23;
    case KeyCode::F24: return VK_F24;

    case KeyCode::Numpad0: return VK_NUMPAD0;
    case KeyCode::Numpad1: return VK_NUMPAD1;
    case KeyCode::Numpad2: return VK_NUMPAD2;
    case KeyCode::Numpad3: return VK_NUMPAD3;
    case KeyCode::Numpad4: return VK_NUMPAD4;
    case KeyCode::Numpad5: return VK_NUMPAD5;
    case KeyCode::Numpad6: return VK_NUMPAD6;
    case KeyCode::Numpad7: return VK_NUMPAD7;
    case KeyCode::Numpad8: return VK_NUMPAD8;
    case KeyCode::Numpad9: return VK_NUMPAD9;

    case KeyCode::Add: return VK_ADD;
    case KeyCode::Subtract: return VK_SUBTRACT;
    case KeyCode::Multiply: return VK_MULTIPLY;
    case KeyCode::Divide: return VK_DIVIDE;
    case KeyCode::Decimal: return VK_DECIMAL;
    case KeyCode::Separator: return VK_SEPARATOR;

    case KeyCode::PageUp: return VK_PRIOR;
    case KeyCode::PageDown: return VK_NEXT;
    case KeyCode::End: return VK_END;
    case KeyCode::Home: return VK_HOME;
    case KeyCode::Insert: return VK_INSERT;
    case KeyCode::Delete: return VK_DELETE;
    case KeyCode::Backspace: return VK_BACK;

    case KeyCode::Left: return VK_LEFT;
    case KeyCode::Right: return VK_RIGHT;
    case KeyCode::Up: return VK_UP;
    case KeyCode::Down: return VK_DOWN;

    case KeyCode::Num0: return '0';
    case KeyCode::Num1: return '1';
    case KeyCode::Num2: return '2';
    case KeyCode::Num3: return '3';
    case KeyCode::Num4: return '4';
    case KeyCode::Num5: return '5';
    case KeyCode::Num6: return '6';
    case KeyCode::Num7: return '7';
    case KeyCode::Num8: return '8';
    case KeyCode::Num9: return '9';

    case KeyCode::A: return 'A';
    case KeyCode::B: return 'B';
    case KeyCode::C: return 'C';
    case KeyCode::D: return 'D';
    case KeyCode::E: return 'E';
    case KeyCode::F: return 'F';
    case KeyCode::G: return 'G';
    case KeyCode::H: return 'H';
    case KeyCode::I: return 'I';
    case KeyCode::J: return 'J';
    case KeyCode::K: return 'K';
    case KeyCode::L: return 'L';
    case KeyCode::M: return 'M';
    case KeyCode::N: return 'N';
    case KeyCode::O: return 'O';
    case KeyCode::P: return 'P';
    case KeyCode::Q: return 'Q';
    case KeyCode::R: return 'R';
    case KeyCode::S: return 'S';
    case KeyCode::T: return 'T';
    case KeyCode::U: return 'U';
    case KeyCode::V: return 'V';
    case KeyCode::X: return 'X';
    case KeyCode::Y: return 'Y';
    case KeyCode::W: return 'W';
    case KeyCode::Z: return 'Z';

    case KeyCode::LBracket: return VK_OEM_4;
    case KeyCode::RBracket: return VK_OEM_6;
    case KeyCode::Semicolon: return VK_OEM_1;
    case KeyCode::Comma: return VK_OEM_COMMA;
    case KeyCode::Period: return VK_OEM_PERIOD;
    case KeyCode::Quote: return VK_OEM_7;
    case KeyCode::Slash: return VK_OEM_2;
    case KeyCode::Backslash: return VK_OEM_5;
    case KeyCode::Tilde: return VK_OEM_3;
    case KeyCode::Equal: return VK_OEM_PLUS;
    case KeyCode::Dash: return VK_OEM_MINUS;
    case KeyCode::Space: return VK_SPACE;
    case KeyCode::Enter: return VK_RETURN;
    case KeyCode::Tab: return VK_TAB;
    case KeyCode::Special1: return VK_OEM_8;
    case KeyCode::Special2: return VK_OEM_102;

    case KeyCode::CapsLock: return VK_CAPITAL;
    case KeyCode::NumLock: return VK_NUMLOCK;
    case KeyCode::ScrollLock: return VK_SCROLL;

    case KeyCode::LCtrl: return VK_LCONTROL;
    case KeyCode::RCtrl: return VK_RCONTROL;
    case KeyCode::LAlt: return VK_LMENU;
    case KeyCode::RAlt: return VK_RMENU;
    case KeyCode::LShift: return VK_LSHIFT;
    case KeyCode::RShift: return VK_RSHIFT;

    case KeyCode::Kana: return VK_KANA;
    case KeyCode::Hangul: return VK_HANGUL;
    case KeyCode::Junja: return VK_JUNJA;
    case KeyCode::Final: return VK_FINAL;
    case KeyCode::Hanja: return VK_HANJA;
    case KeyCode::Kanji: return VK_KANJI;
    case KeyCode::Convert: return VK_CONVERT;
    case KeyCode::NonConvert: return VK_NONCONVERT;
    case KeyCode::Accept: return VK_ACCEPT;
    case KeyCode::ModeChange: return VK_MODECHANGE;
    case KeyCode::ProcessKey: return VK_PROCESSKEY;

    case KeyCode::BrowserBack: return VK_BROWSER_BACK;
    case KeyCode::BrowserForward: return VK_BROWSER_FORWARD;
    case KeyCode::BrowserRefresh: return VK_BROWSER_REFRESH;
    case KeyCode::BrowserStop: return VK_BROWSER_STOP;
    case KeyCode::BrowserSearch: return VK_BROWSER_SEARCH;
    case KeyCode::BrowserFavorites: return VK_BROWSER_FAVORITES;
    case KeyCode::BrowserHome: return VK_BROWSER_HOME;

    case KeyCode::VolumeUp: return VK_VOLUME_UP;
    case KeyCode::VolumeDown: return VK_VOLUME_DOWN;
    case KeyCode::VolumeMute: return VK_VOLUME_MUTE;

    case KeyCode::MediaNextTrack: return VK_MEDIA_NEXT_TRACK;
    case KeyCode::MediaPreviousTrack: return VK_MEDIA_PREV_TRACK;
    case KeyCode::MediaStop: return VK_MEDIA_STOP;
    case KeyCode::MediaPlayPause: return VK_MEDIA_PLAY_PAUSE;
    case KeyCode::LaunchMediaSelect: return VK_LAUNCH_MEDIA_SELECT;
    case KeyCode::LaunchMail: return VK_LAUNCH_MAIL;
    case KeyCode::LaunchApp1: return VK_LAUNCH_APP1;
    case KeyCode::LaunchApp2: return VK_LAUNCH_APP2;

    case KeyCode::Attn: return VK_ATTN;
    case KeyCode::CrSel: return VK_CRSEL;
    case KeyCode::ExSel: return VK_EXSEL;
    case KeyCode::EraseEOF: return VK_EREOF;
    case KeyCode::Play: return VK_PLAY;
    case KeyCode::Zoom: return VK_ZOOM;
    case KeyCode::PA1: return VK_PA1;
    case KeyCode::Clear: return VK_CLEAR;
    case KeyCode::Packet: return VK_PACKET;
    default: return 0;
  }
}



UINT scanCodeToWinKey(ScanCode sc)
{
  // Special handling for some scan codes is needed for consistency with
  // scan codes in window messages.

  // When numlock is on, windows checks nothing when one of the numpad keys is
  // pressed.
  if(Keyboard::isKeyToggled(KeyCode::NumLock)) {
     if(sc == ScanCode::Numpad0) { return VK_NUMPAD0; }
     if(sc == ScanCode::Numpad1) { return VK_NUMPAD1; }
     if(sc == ScanCode::Numpad2) { return VK_NUMPAD2; }
     if(sc == ScanCode::Numpad3) { return VK_NUMPAD3; }
     if(sc == ScanCode::Numpad4) { return VK_NUMPAD4; }
     if(sc == ScanCode::Numpad5) { return VK_NUMPAD5; }
     if(sc == ScanCode::Numpad6) { return VK_NUMPAD6; }
     if(sc == ScanCode::Numpad7) { return VK_NUMPAD7; }
     if(sc == ScanCode::Numpad8) { return VK_NUMPAD8; }
     if(sc == ScanCode::Numpad9) { return VK_NUMPAD9; }
     if(sc == ScanCode::Decimal) { return VK_DECIMAL; }
  }

  // Without these lines, Windows checks the pause key when the numlock key
  // is requested, and checks nothing when the print key is requested. This
  // is in disagreement with the scancodes received by the window messages.
  if(sc == ScanCode::Pause) { return VK_PAUSE; }
  if(sc == ScanCode::NumLock) { return VK_NUMLOCK; }

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



namespace Keyboard
{

bool isKeyPressed(KeyCode kc)
{
  return isWinVirtualKeyPressed(keyCodeToWinKey(kc));
}



bool isKeyPressed(ScanCode sc)
{
  return isWinVirtualKeyPressed(scanCodeToWinKey(sc));
}



bool isKeyToggled(KeyCode kc)
{
  return isWinVirtualKeyToggled(keyCodeToWinKey(kc));
}



bool isKeyToggled(ScanCode sc)
{
  return isWinVirtualKeyToggled(scanCodeToWinKey(sc));
}

}

}

