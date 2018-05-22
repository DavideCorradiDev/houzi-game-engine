// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef SRC_HOU_SYS_WIN_HPP
#define SRC_HOU_SYS_WIN_HPP

#ifdef HOU_COMPILER_MSVC
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif

#include <windows.h>



// Define minimum Windows version.
#ifdef _WIN32_WINDOWS
  #undef _WIN32_WINDOWS
#endif
#define _WIN32_WINDOWS 0x0501 // Windows XP

#ifdef _WIN32_WINNT
  #undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0501

#ifdef WINVER
  #undef WINVER
#endif
#define WINVER 0x0501



// Definition of some Win32 constants missing in some compilers.
#ifndef XBUTTON1
  #define XBUTTON1 0x0001
#endif
#ifndef XBUTTON2
  #define XBUTTON2 0x0002
#endif
#ifndef WM_XBUTTONDOWN
  #define WM_XBUTTONDOWN 0x020B
#endif
#ifndef WM_XBUTTONUP
  #define WM_XBUTTONUP 0x020C
#endif
#ifndef WM_MOUSEHWHEEL
  #define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef MAPVK_VK_TO_VSC
  #define MAPVK_VK_TO_VSC 0
#endif
#ifndef GET_X_LPARAM
  #define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
  #define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

#endif

