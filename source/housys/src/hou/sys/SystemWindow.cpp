#include "hou/sys/SystemWindow.hpp"



namespace hou
{

SystemWindow::SystemWindow(
  const std::string& title, const VideoMode& videoMode, WindowStyle style)
  : Window(title, videoMode, style)
{}



SystemWindow::SystemWindow(SystemWindow&& other)
  : Window(std::move(other))
{}



void SystemWindow::setFrameRect(const vec2i& pos, const vec2u& size)
{
  Window::setFrameRect(pos, size);
}

void SystemWindow::setClientRect(const vec2i& pos, const vec2u& size)
{
  Window::setClientRect(pos, size);
}

}  // namespace hou
