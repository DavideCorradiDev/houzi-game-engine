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
    KEY_CODE_CASE(Escape, os);

    KEY_CODE_CASE(Print, os);
    KEY_CODE_CASE(PrintScreen, os);
    KEY_CODE_CASE(Pause, os);
    KEY_CODE_CASE(Execute, os);
    KEY_CODE_CASE(Select, os);
    KEY_CODE_CASE(Help, os);
    KEY_CODE_CASE(Sleep, os);
    KEY_CODE_CASE(Apps, os);
    KEY_CODE_CASE(LSystem, os);
    KEY_CODE_CASE(RSystem, os);

    KEY_CODE_CASE(F1, os);
    KEY_CODE_CASE(F2, os);
    KEY_CODE_CASE(F3, os);
    KEY_CODE_CASE(F4, os);
    KEY_CODE_CASE(F5, os);
    KEY_CODE_CASE(F6, os);
    KEY_CODE_CASE(F7, os);
    KEY_CODE_CASE(F8, os);
    KEY_CODE_CASE(F9, os);
    KEY_CODE_CASE(F10, os);
    KEY_CODE_CASE(F11, os);
    KEY_CODE_CASE(F12, os);
    KEY_CODE_CASE(F13, os);
    KEY_CODE_CASE(F14, os);
    KEY_CODE_CASE(F15, os);
    KEY_CODE_CASE(F16, os);
    KEY_CODE_CASE(F17, os);
    KEY_CODE_CASE(F18, os);
    KEY_CODE_CASE(F19, os);
    KEY_CODE_CASE(F20, os);
    KEY_CODE_CASE(F21, os);
    KEY_CODE_CASE(F22, os);
    KEY_CODE_CASE(F23, os);
    KEY_CODE_CASE(F24, os);

    KEY_CODE_CASE(Numpad0, os);
    KEY_CODE_CASE(Numpad1, os);
    KEY_CODE_CASE(Numpad2, os);
    KEY_CODE_CASE(Numpad3, os);
    KEY_CODE_CASE(Numpad4, os);
    KEY_CODE_CASE(Numpad5, os);
    KEY_CODE_CASE(Numpad6, os);
    KEY_CODE_CASE(Numpad7, os);
    KEY_CODE_CASE(Numpad8, os);
    KEY_CODE_CASE(Numpad9, os);

    KEY_CODE_CASE(Add, os);
    KEY_CODE_CASE(Subtract, os);
    KEY_CODE_CASE(Multiply, os);
    KEY_CODE_CASE(Divide, os);
    KEY_CODE_CASE(Decimal, os);
    KEY_CODE_CASE(Separator, os);

    KEY_CODE_CASE(PageUp, os);
    KEY_CODE_CASE(PageDown, os);
    KEY_CODE_CASE(End, os);
    KEY_CODE_CASE(Home, os);
    KEY_CODE_CASE(Insert, os);
    KEY_CODE_CASE(Delete, os);
    KEY_CODE_CASE(Backspace, os);

    KEY_CODE_CASE(Left, os);
    KEY_CODE_CASE(Right, os);
    KEY_CODE_CASE(Up, os);
    KEY_CODE_CASE(Down, os);

    KEY_CODE_CASE(Num0, os);
    KEY_CODE_CASE(Num1, os);
    KEY_CODE_CASE(Num2, os);
    KEY_CODE_CASE(Num3, os);
    KEY_CODE_CASE(Num4, os);
    KEY_CODE_CASE(Num5, os);
    KEY_CODE_CASE(Num6, os);
    KEY_CODE_CASE(Num7, os);
    KEY_CODE_CASE(Num8, os);
    KEY_CODE_CASE(Num9, os);

    KEY_CODE_CASE(A, os);
    KEY_CODE_CASE(B, os);
    KEY_CODE_CASE(C, os);
    KEY_CODE_CASE(D, os);
    KEY_CODE_CASE(E, os);
    KEY_CODE_CASE(F, os);
    KEY_CODE_CASE(G, os);
    KEY_CODE_CASE(H, os);
    KEY_CODE_CASE(I, os);
    KEY_CODE_CASE(J, os);
    KEY_CODE_CASE(K, os);
    KEY_CODE_CASE(L, os);
    KEY_CODE_CASE(M, os);
    KEY_CODE_CASE(N, os);
    KEY_CODE_CASE(O, os);
    KEY_CODE_CASE(P, os);
    KEY_CODE_CASE(Q, os);
    KEY_CODE_CASE(R, os);
    KEY_CODE_CASE(S, os);
    KEY_CODE_CASE(T, os);
    KEY_CODE_CASE(U, os);
    KEY_CODE_CASE(V, os);
    KEY_CODE_CASE(X, os);
    KEY_CODE_CASE(Y, os);
    KEY_CODE_CASE(W, os);
    KEY_CODE_CASE(Z, os);

    KEY_CODE_CASE(LBracket, os);
    KEY_CODE_CASE(RBracket, os);
    KEY_CODE_CASE(Semicolon, os);
    KEY_CODE_CASE(Comma, os);
    KEY_CODE_CASE(Period, os);
    KEY_CODE_CASE(Quote, os);
    KEY_CODE_CASE(Slash, os);
    KEY_CODE_CASE(Backslash, os);
    KEY_CODE_CASE(Tilde, os);
    KEY_CODE_CASE(Equal, os);
    KEY_CODE_CASE(Dash, os);
    KEY_CODE_CASE(Space, os);
    KEY_CODE_CASE(Enter, os);
    KEY_CODE_CASE(Tab, os);
    KEY_CODE_CASE(Special1, os);
    KEY_CODE_CASE(Special2, os);

    KEY_CODE_CASE(CapsLock, os);
    KEY_CODE_CASE(NumLock, os);
    KEY_CODE_CASE(ScrollLock, os);

    KEY_CODE_CASE(LCtrl, os);
    KEY_CODE_CASE(RCtrl, os);
    KEY_CODE_CASE(LAlt, os);
    KEY_CODE_CASE(RAlt, os);
    KEY_CODE_CASE(LShift, os);
    KEY_CODE_CASE(RShift, os);

    KEY_CODE_CASE(Kana, os);
    KEY_CODE_CASE(Hangul, os);
    KEY_CODE_CASE(Junja, os);
    KEY_CODE_CASE(Final, os);
    KEY_CODE_CASE(Hanja, os);
    KEY_CODE_CASE(Kanji, os);
    KEY_CODE_CASE(Convert, os);
    KEY_CODE_CASE(NonConvert, os);
    KEY_CODE_CASE(Accept, os);
    KEY_CODE_CASE(ModeChange, os);
    KEY_CODE_CASE(ProcessKey, os);

    KEY_CODE_CASE(BrowserBack, os);
    KEY_CODE_CASE(BrowserForward, os);
    KEY_CODE_CASE(BrowserRefresh, os);
    KEY_CODE_CASE(BrowserStop, os);
    KEY_CODE_CASE(BrowserSearch, os);
    KEY_CODE_CASE(BrowserFavorites, os);
    KEY_CODE_CASE(BrowserHome, os);

    KEY_CODE_CASE(VolumeUp, os);
    KEY_CODE_CASE(VolumeDown, os);
    KEY_CODE_CASE(VolumeMute, os);

    KEY_CODE_CASE(MediaNextTrack, os);
    KEY_CODE_CASE(MediaPreviousTrack, os);
    KEY_CODE_CASE(MediaStop, os);
    KEY_CODE_CASE(MediaPlayPause, os);
    KEY_CODE_CASE(LaunchMediaSelect, os);
    KEY_CODE_CASE(LaunchMail, os);
    KEY_CODE_CASE(LaunchApp1, os);
    KEY_CODE_CASE(LaunchApp2, os);

    KEY_CODE_CASE(Attn, os);
    KEY_CODE_CASE(CrSel, os);
    KEY_CODE_CASE(ExSel, os);
    KEY_CODE_CASE(EraseEOF, os);
    KEY_CODE_CASE(Play, os);
    KEY_CODE_CASE(Zoom, os);
    KEY_CODE_CASE(PA1, os);
    KEY_CODE_CASE(Clear, os);
    KEY_CODE_CASE(Packet, os);

    default:
      return os;
  }
}

}  // namespace hou
