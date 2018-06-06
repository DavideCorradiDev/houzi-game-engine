// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_DISPLAY_HPP
#define HOU_SYS_DISPLAY_HPP

#include "hou/sys/display_mode.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_set.hpp"
#include "hou/cor/std_string.hpp"

#include "hou/mth/rectangle.hpp"

#include <functional>



namespace hou
{

namespace display
{

HOU_SYS_API uint get_count();

HOU_SYS_API std::string get_name(uint display_idx);

HOU_SYS_API recti get_bounds(uint display_idx);

HOU_SYS_API recti get_usable_bounds(uint display_idx);

// HOU_SYS_API display_dpi get_dpi(uint display_idx);

HOU_SYS_API display_mode get_mode(uint display_idx);

HOU_SYS_API std::set<display_mode> get_supported_modes(uint display_idx);

HOU_SYS_API std::string get_video_driver();

HOU_SYS_API std::set<std::string> get_video_drivers();

}  // namespace display

}  // namespace hou

#endif
