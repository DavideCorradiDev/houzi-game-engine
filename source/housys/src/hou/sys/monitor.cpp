// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/monitor.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"
#include "hou/cor/not_null.hpp"

#include <algorithm>



namespace hou
{

namespace monitor
{

// namespace
// {
// 
// not_null<GLFWmonitor*> get_monitor_from_id(uint monitor_id);
// 
// uint get_id_from_monitor(not_null<const GLFWmonitor*> monitor);
// 
// vec2u convert_size(const GLFWvidmode& vm);
// 
// uint convert_depth_bit_count(const GLFWvidmode& vm);
// 
// uint convert_refresh_rate(const GLFWvidmode& vm);
// 
// video_mode convert(const GLFWvidmode& vm);
// 
// void glfw_monitor_callback(GLFWmonitor* monitor, int event);
// 
// connected_callback& get_connected_callback();
// 
// disconnected_callback& get_disconnected_callback();
// 
// 
// 
// not_null<GLFWmonitor*> get_monitor_from_id(uint monitor_id)
// {
//   int monitors_n = 0;
//   GLFWmonitor** monitors = glfwGetMonitors(&monitors_n);
//   HOU_CHECK_N(
//     monitor_id < narrow_cast<uint>(monitors_n), invalid_monitor_id, monitor_id);
//   return monitors[monitor_id];
// }
// 
// 
// 
// uint get_id_from_monitor(not_null<const GLFWmonitor*> monitor)
// {
//   int monitors_n = 0;
//   GLFWmonitor** monitors = glfwGetMonitors(&monitors_n);
//   auto monitor_it = std::find(monitors, monitors + monitors_n, monitor.get());
//   HOU_PRECOND(monitor_it != (monitors + monitors_n));
//   return std::distance(monitors, monitor_it);
// }
// 
// 
// 
// vec2u convert_size(const GLFWvidmode& vm_in)
// {
//   return vec2u(narrow_cast<uint>(vm_in.width), narrow_cast<uint>(vm_in.height));
// }
// 
// 
// 
// uint convert_depth_bit_count(const GLFWvidmode& vm_in)
// {
//   return narrow_cast<uint>(vm_in.redBits + vm_in.greenBits + vm_in.blueBits);
// }
// 
// 
// 
// uint convert_refresh_rate(const GLFWvidmode& vm_in)
// {
//   return narrow_cast<uint>(vm_in.refreshRate);
// }
// 
// 
// 
// video_mode convert(const GLFWvidmode& vm_in)
// {
//   return video_mode(convert_size(vm_in), convert_depth_bit_count(vm_in),
//     convert_refresh_rate(vm_in));
// }
// 
// 
// 
// void glfw_monitor_callback(GLFWmonitor* monitor, int event)
// {
//   if(monitor == nullptr)
//   {
//     return;
//   }
// 
//   uint monitor_id = get_id_from_monitor(monitor);
//   if(event == GLFW_CONNECTED && get_connected_callback() != nullptr)
//   {
//     get_connected_callback()(monitor_id);
//   }
//   else if(event == GLFW_DISCONNECTED && get_disconnected_callback() != nullptr)
//   {
//     get_disconnected_callback()();
//   }
// }
// 
// 
// 
// connected_callback& get_connected_callback()
// {
//   static connected_callback f = nullptr;
//   return f;
// }
// 
// 
// 
// disconnected_callback& get_disconnected_callback()
// {
//   static disconnected_callback f = nullptr;
//   return f;
// }
// 
// }  // namespace
// 
// 
// 
// uint get_count() noexcept
// {
//   int count = 0;
//   glfwGetMonitors(&count);
//   return narrow_cast<uint>(count);
// }
// 
// 
// 
// std::string get_name(uint monitor_id)
// {
//   return std::string(glfwGetMonitorName(get_monitor_from_id(monitor_id)));
// }
// 
// 
// 
// vec2u get_physical_size(uint monitor_id)
// {
//   int x = 0;
//   int y = 0;
//   glfwGetMonitorPhysicalSize(get_monitor_from_id(monitor_id), &x, &y);
//   return vec2u(narrow_cast<uint>(x), narrow_cast<uint>(y));
// }
// 
// 
// 
// vec2i get_position(uint monitor_id)
// {
//   int x = 0;
//   int y = 0;
//   glfwGetMonitorPos(get_monitor_from_id(monitor_id), &x, &y);
//   return vec2i(x, y);
// }
// 
// 
// 
// vec2u get_size(uint monitor_id)
// {
//   return convert_size(*glfwGetVideoMode(get_monitor_from_id(monitor_id)));
// }
// 
// 
// 
// uint get_depth_bit_count(uint monitor_id)
// {
//   return convert_depth_bit_count(
//     *glfwGetVideoMode(get_monitor_from_id(monitor_id)));
// }
// 
// 
// 
// uint get_refresh_rate(uint monitor_id)
// {
//   return convert_refresh_rate(
//     *glfwGetVideoMode(get_monitor_from_id(monitor_id)));
// }
// 
// 
// 
// video_mode get_video_mode(uint monitor_id)
// {
//   return convert(*glfwGetVideoMode(get_monitor_from_id(monitor_id)));
// }
// 
// 
// 
// std::set<video_mode> get_supported_video_modes(uint monitor_id)
// {
//   std::set<video_mode> modes_out;
//   int modes_in_n = 0;
//   const GLFWvidmode* modes_in
//     = glfwGetVideoModes(get_monitor_from_id(monitor_id), &modes_in_n);
//   for(int i = 0; i < modes_in_n; ++i)
//   {
//     modes_out.insert(convert(modes_in[i]));
//   }
//   return modes_out;
// }
// 
// 
// 
// HOU_SYS_API connected_callback set_connected_callback(connected_callback f)
// {
//   connected_callback previous = get_connected_callback();
//   get_connected_callback() = f;
//   glfwSetMonitorCallback(glfw_monitor_callback);
//   return previous;
// }
// 
// 
// 
// HOU_SYS_API disconnected_callback set_disconnected_callback(
//   disconnected_callback f)
// {
//   disconnected_callback previous = get_disconnected_callback();
//   get_disconnected_callback() = f;
//   glfwSetMonitorCallback(glfw_monitor_callback);
//   return previous;
// }

}  // namespace monitor

}  // namespace hou
