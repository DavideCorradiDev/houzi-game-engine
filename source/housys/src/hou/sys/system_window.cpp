#include "hou/sys/system_window.hpp"



namespace hou
{

system_window::system_window(const std::string& title, const vec2u& size)
  : window(title, size)
{}

}  // namespace hou
