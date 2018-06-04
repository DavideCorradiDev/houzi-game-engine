// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/monitor.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"
#include "hou/cor/not_null.hpp"



namespace hou
{

namespace monitor
{

namespace
{

not_null<GLFWmonitor*> get_monitor_from_id(uint monitor_id);

vec2u convert_size(not_null<const GLFWvidmode*> vm);

uint convert_depth_bit_count(not_null<const GLFWvidmode*> vm);

uint convert_refresh_rate(not_null<const GLFWvidmode*> vm);

video_mode convert(not_null<const GLFWvidmode*> vm);



not_null<GLFWmonitor*> get_monitor_from_id(uint monitor_id)
{
  int monitor_n = 0;
  GLFWmonitor** monitors = glfwGetMonitors(&monitor_n);
  HOU_CHECK_N(
    monitor_id < narrow_cast<uint>(monitor_n), invalid_monitor_id, monitor_id);
  return monitors[monitor_id];
}



vec2u convert_size(not_null<const GLFWvidmode*> vm_in)
{
  return vec2u(
    narrow_cast<uint>(vm_in->width), narrow_cast<uint>(vm_in->height));
}



uint convert_depth_bit_count(not_null<const GLFWvidmode*> vm_in)
{
  return narrow_cast<uint>(vm_in->redBits + vm_in->greenBits + vm_in->blueBits);
}



uint convert_refresh_rate(not_null<const GLFWvidmode*> vm_in)
{
  return narrow_cast<uint>(vm_in->refreshRate);
}



video_mode convert(not_null<const GLFWvidmode*> vm_in)
{
  return video_mode(convert_size(vm_in), convert_depth_bit_count(vm_in),
    convert_refresh_rate(vm_in));
}

}  // namespace



uint get_count() noexcept
{
  int count = 0;
  glfwGetMonitors(&count);
  return narrow_cast<uint>(count);
}



std::string get_name(uint monitor_id)
{
  return std::string(glfwGetMonitorName(get_monitor_from_id(monitor_id)));
}



vec2u get_physical_size(uint monitor_id)
{
  int x = 0;
  int y = 0;
  glfwGetMonitorPhysicalSize(get_monitor_from_id(monitor_id), &x, &y);
  return vec2u(narrow_cast<uint>(x), narrow_cast<uint>(y));
}



vec2i get_position(uint monitor_id)
{
  int x = 0;
  int y = 0;
  glfwGetMonitorPos(get_monitor_from_id(monitor_id), &x, &y);
  return vec2i(x, y);
}



vec2u get_size(uint monitor_id)
{
  return convert_size(glfwGetVideoMode(get_monitor_from_id(monitor_id)));
}



uint get_depth_bit_count(uint monitor_id)
{
  return convert_depth_bit_count(
    glfwGetVideoMode(get_monitor_from_id(monitor_id)));
}



uint get_refresh_rate(uint monitor_id)
{
  return convert_refresh_rate(
    glfwGetVideoMode(get_monitor_from_id(monitor_id)));
}



video_mode get_video_mode(uint monitor_id)
{
  return convert(glfwGetVideoMode(get_monitor_from_id(monitor_id)));
}

}  // namespace monitor

}  // namespace hou
