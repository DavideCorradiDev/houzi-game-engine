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



void SystemWindow::setFrameRect(const Recti& rect)
{
  Window::setFrameRect(rect);
}

void SystemWindow::setClientRect(const Recti& rect)
{
  Window::setClientRect(rect);
}

}  // namespace hou
