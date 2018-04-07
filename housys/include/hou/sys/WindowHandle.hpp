// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_WND_WINDOW_HANDLE_HPP
#define HOU_WND_WINDOW_HANDLE_HPP

#include "hou/Config.hpp"



#if defined(HOU_SYSTEM_WINDOWS)
  struct HWND__;
#endif



namespace hou {

#if defined(HOU_SYSTEM_WINDOWS)
  using WindowHandle = HWND__*;
#endif

}

#endif

