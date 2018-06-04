// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_MONITOR_HPP
#define HOU_SYS_MONITOR_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/sys_config.hpp"
#include "hou/sys/video_mode.hpp"

#include "hou/mth/matrix.hpp"

#include "GLFW/glfw3.h"



namespace hou
{

namespace monitor
{

constexpr uint primary = 0u;

HOU_SYS_API uint get_count();

HOU_SYS_API vec2i get_position(uint monitor_id);

HOU_SYS_API vec2u get_physical_size(uint monitor_id);

HOU_SYS_API video_mode get_video_mode(uint monitor_id);

// HOU_SYS_API std::list<video_mode> get_supported_video_modes(uint monitor_id);

}  // namespace monitor

}  // namespace hou

#endif
