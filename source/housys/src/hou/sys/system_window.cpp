#include "hou/sys/system_window.hpp"



namespace hou
{

system_window::system_window(const std::string& title, const vec2u& size)
  : window(title, size)
{}



void system_window::clear(const color& color)
{
  window::clear(color);
}



void system_window::swap_buffers()
{
  window::swap_buffers();
}



void system_window::on_size_change(const vec2u& size)
{
  window::on_size_change(size);
}

}  // namespace hou
