// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_WND_WINDOW_HANDLE_HPP
#define HOU_WND_WINDOW_HANDLE_HPP

#include "hou/sys/sys_export.hpp"



#if defined(HOU_SYSTEM_WINDOWS)
  struct HWND__;
#endif



namespace hou
{

#if defined(HOU_SYSTEM_WINDOWS)
  using window_handle = HWND__*;
#endif

}  // namespace hou

#endif
