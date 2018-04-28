#include "hou/sys/system_window.hpp"



namespace hou
{

system_window::system_window(
  const std::string& title, const video_mode& videoMode, window_style style)
  : window(title, videoMode, style)
{}



system_window::system_window(system_window&& other)
  : window(std::move(other))
{}



void system_window::set_frame_rect(const vec2i& pos, const vec2u& size)
{
  window::set_frame_rect(pos, size);
}

void system_window::set_client_rect(const vec2i& pos, const vec2u& size)
{
  window::set_client_rect(pos, size);
}

}  // namespace hou
