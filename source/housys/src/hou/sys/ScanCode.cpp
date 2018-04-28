// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/ScanCode.hpp"

#define SCAN_CODE_CASE(sc, os) \
  case ScanCode::sc: return (os) << #sc



namespace hou
{

std::ostream& operator<<(std::ostream& os, ScanCode sc)
{
  switch(sc)
  {
    SCAN_CODE_CASE(Escape, os);

    SCAN_CODE_CASE(Num1, os);
    SCAN_CODE_CASE(Num2, os);
    SCAN_CODE_CASE(Num3, os);
    SCAN_CODE_CASE(Num4, os);
    SCAN_CODE_CASE(Num5, os);
    SCAN_CODE_CASE(Num6, os);
    SCAN_CODE_CASE(Num7, os);
    SCAN_CODE_CASE(Num8, os);
    SCAN_CODE_CASE(Num9, os);
    SCAN_CODE_CASE(Num0, os);
    SCAN_CODE_CASE(Dash, os);
    SCAN_CODE_CASE(Equal, os);
    SCAN_CODE_CASE(Backspace, os);

    SCAN_CODE_CASE(Tab, os);
    SCAN_CODE_CASE(Q, os);
    SCAN_CODE_CASE(W, os);
    SCAN_CODE_CASE(E, os);
    SCAN_CODE_CASE(R, os);
    SCAN_CODE_CASE(T, os);
    SCAN_CODE_CASE(Y, os);
    SCAN_CODE_CASE(U, os);
    SCAN_CODE_CASE(I, os);
    SCAN_CODE_CASE(O, os);
    SCAN_CODE_CASE(P, os);
    SCAN_CODE_CASE(LBracket, os);
    SCAN_CODE_CASE(RBracket, os);
    SCAN_CODE_CASE(Enter, os);
    SCAN_CODE_CASE(NumpadEnter, os);

    SCAN_CODE_CASE(LCtrl, os);
    SCAN_CODE_CASE(RCtrl, os);
    SCAN_CODE_CASE(A, os);
    SCAN_CODE_CASE(S, os);
    SCAN_CODE_CASE(D, os);
    SCAN_CODE_CASE(F, os);
    SCAN_CODE_CASE(G, os);
    SCAN_CODE_CASE(H, os);
    SCAN_CODE_CASE(J, os);
    SCAN_CODE_CASE(K, os);
    SCAN_CODE_CASE(L, os);
    SCAN_CODE_CASE(Semicolon, os);
    SCAN_CODE_CASE(Quote, os);
    SCAN_CODE_CASE(Tilde, os);

    SCAN_CODE_CASE(LShift, os);
    SCAN_CODE_CASE(Backslash, os);
    SCAN_CODE_CASE(Z, os);
    SCAN_CODE_CASE(X, os);
    SCAN_CODE_CASE(C, os);
    SCAN_CODE_CASE(V, os);
    SCAN_CODE_CASE(B, os);
    SCAN_CODE_CASE(N, os);
    SCAN_CODE_CASE(M, os);
    SCAN_CODE_CASE(Comma, os);
    SCAN_CODE_CASE(Period, os);
    SCAN_CODE_CASE(Slash, os);
    SCAN_CODE_CASE(Divide, os);
    SCAN_CODE_CASE(RShift, os);

    SCAN_CODE_CASE(Multiply, os);
    SCAN_CODE_CASE(PrintScreen, os);
    SCAN_CODE_CASE(LAlt, os);
    SCAN_CODE_CASE(RAlt, os);
    SCAN_CODE_CASE(Space, os);
    SCAN_CODE_CASE(CapsLock, os);

    SCAN_CODE_CASE(F1, os);
    SCAN_CODE_CASE(F2, os);
    SCAN_CODE_CASE(F3, os);
    SCAN_CODE_CASE(F4, os);
    SCAN_CODE_CASE(F5, os);
    SCAN_CODE_CASE(F6, os);
    SCAN_CODE_CASE(F7, os);
    SCAN_CODE_CASE(F8, os);
    SCAN_CODE_CASE(F9, os);
    SCAN_CODE_CASE(F10, os);

    SCAN_CODE_CASE(Pause, os);
    SCAN_CODE_CASE(NumLock, os);
    SCAN_CODE_CASE(ScrollLock, os);

    SCAN_CODE_CASE(Numpad7, os);
    SCAN_CODE_CASE(Home, os);
    SCAN_CODE_CASE(Numpad8, os);
    SCAN_CODE_CASE(Up, os);
    SCAN_CODE_CASE(Numpad9, os);
    SCAN_CODE_CASE(PageUp, os);
    SCAN_CODE_CASE(Subtract, os);
    SCAN_CODE_CASE(Numpad4, os);
    SCAN_CODE_CASE(Left, os);
    SCAN_CODE_CASE(Numpad5, os);
    SCAN_CODE_CASE(Numpad6, os);
    SCAN_CODE_CASE(Right, os);
    SCAN_CODE_CASE(Add, os);
    SCAN_CODE_CASE(Numpad1, os);
    SCAN_CODE_CASE(End, os);
    SCAN_CODE_CASE(Numpad2, os);
    SCAN_CODE_CASE(Down, os);
    SCAN_CODE_CASE(Numpad3, os);
    SCAN_CODE_CASE(PageDown, os);
    SCAN_CODE_CASE(Numpad0, os);
    SCAN_CODE_CASE(Insert, os);
    SCAN_CODE_CASE(Decimal, os);
    SCAN_CODE_CASE(Delete, os);

    SCAN_CODE_CASE(F11, os);
    SCAN_CODE_CASE(F12, os);

    // Made up scan code to cover whole keyboard.
    SCAN_CODE_CASE(LSystem, os);
    SCAN_CODE_CASE(RSystem, os);
    SCAN_CODE_CASE(Apps, os);

    default: return os;
  }
}

}

