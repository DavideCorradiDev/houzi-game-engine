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



void SystemWindow::setFrameRect(const Vec2i& pos, const Vec2u& size)
{
  Window::setFrameRect(pos, size);
}

void SystemWindow::setClientRect(const Vec2i& pos, const Vec2u& size)
{
  Window::setClientRect(pos, size);
}

}  // namespace hou
