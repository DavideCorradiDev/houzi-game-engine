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



not_null<GLFWmonitor*> get_monitor_from_id(uint monitor_id)
{
  int monitor_n = 0;
  GLFWmonitor** monitors = glfwGetMonitors(&monitor_n);
  HOU_CHECK_N(
    monitor_id < narrow_cast<uint>(monitor_n), invalid_monitor_id, monitor_id);
  return monitors[monitor_id];
}

}



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



vec2i get_position(uint monitor_id)
{
  int x = 0;
  int y = 0;
  glfwGetMonitorPos(get_monitor_from_id(monitor_id), &x, &y);
  return vec2i(x, y);
}



vec2u get_size(uint monitor_id)
{
  not_null<const GLFWvidmode*> vm
    = glfwGetVideoMode(get_monitor_from_id(monitor_id));
  return vec2u(narrow_cast<uint>(vm->width), narrow_cast<uint>(vm->height));
}



uint get_depth_bit_count(uint monitor_id)
{
  not_null<const GLFWvidmode*> vm
    = glfwGetVideoMode(get_monitor_from_id(monitor_id));
  return narrow_cast<uint>(vm->redBits + vm->greenBits + vm->blueBits);
}



uint get_refresh_rate(uint monitor_id)
{
  not_null<const GLFWvidmode*> vm
    = glfwGetVideoMode(get_monitor_from_id(monitor_id));
  return narrow_cast<uint>(vm->refreshRate);
}

}

}
