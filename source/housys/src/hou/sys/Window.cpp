// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/Window.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/WindowEvent.hpp"

#include "hou/cor/uid_generator.hpp"

#include "hou/mth/Rectangle.hpp"

#include <thread>



namespace hou
{

namespace
{

uint32_t generateUid();



uint32_t generateUid()
{
  static uid_generator uidGenerator(1u);
  return uidGenerator.generate();
}

}



Window::Window(const std::string& title, const VideoMode& videoMode
  , WindowStyle style)
  : non_copyable()
  , mImpl(title, videoMode, style)
  , mUid(generateUid())
  , mStyle(style)
  , mBytesPerPixel(videoMode.getBytesPerPixel())
  , mTitle(title)
  , mIconImage()
{}



Window::Window(Window&& other)
  : mImpl(std::move(other.mImpl))
  , mUid(std::move(other.mUid))
  , mStyle(std::move(other.mStyle))
  , mBytesPerPixel(std::move(other.mBytesPerPixel))
  , mTitle(std::move(other.mTitle))
  , mIconImage(std::move(other.mIconImage))
{}



Window::~Window()
{}



WindowHandle Window::getWindowHandle() const
{
  return mImpl.getWindowHandle();
}



uint32_t Window::getUid() const
{
  return mUid;
}



const std::string& Window::getTitle() const
{
  return mTitle;
}



void Window::setTitle(const std::string& title)
{
  mImpl.setTitle(title);
  mTitle = title;
}



Vec2i Window::getFramePosition() const
{
  return mImpl.getFrameRect().getPosition();
}



Vec2u Window::getFrameSize() const
{
  return static_cast<Vec2u>(mImpl.getFrameRect().getSize());
}



void Window::setFrameRect(const Vec2i& pos, const Vec2u& size)
{
  Vec2u oldClientSize = getClientSize();
  mImpl.setFrameRect(Recti(pos, static_cast<Vec2i>(size)));
  Vec2u newClientSize = getClientSize();
  if(oldClientSize != newClientSize)
  {
    pushEvent(WindowEvent::resized(newClientSize.x(), newClientSize.y()));
  }
}



void Window::setFramePosition(const Vec2i& pos)
{
  setFrameRect(pos, getFrameSize());
}



void Window::setFrameSize(const Vec2u& size)
{
  setFrameRect(getFramePosition(), size);
}



Vec2i Window::getClientPosition() const
{
  return mImpl.getClientRect().getPosition();
}



Vec2u Window::getClientSize() const
{
  return static_cast<Vec2u>(mImpl.getClientRect().getSize());
}



void Window::setClientRect(const Vec2i& pos, const Vec2u& size)
{
  Vec2u oldClientSize = getClientSize();
  mImpl.setClientRect(Recti(pos, static_cast<Vec2i>(size)));
  Vec2u newClientSize = getClientSize();
  if(oldClientSize != newClientSize)
  {
    pushEvent(WindowEvent::resized(newClientSize.x(), newClientSize.y()));
  }
}



void Window::setClientPosition(const Vec2i& pos)
{
  setClientRect(pos, getClientSize());
}



void Window::setClientSize(const Vec2u& size)
{
  setClientRect(getClientPosition(), size);
}



uint Window::getBytesPerPixel() const
{
  return mBytesPerPixel;
}



WindowStyle Window::getStyle() const
{
  return mStyle;
}



const Image2RGBA& Window::getIcon() const
{
  return mIconImage;
}



void Window::setIcon(const Image2RGBA& icon)
{
  mIconImage = icon;
  mImpl.setIcon(icon);
}



void Window::setSystemIcon()
{
  mIconImage = Image2RGBA();
  mImpl.setSystemIcon();
}



bool Window::isVisible() const
{
  return mImpl.isVisible();
}



void Window::setVisible(bool value)
{
  mImpl.setVisible(value);
}



bool Window::isMouseCursorGrabbed() const
{
  return mImpl.isMouseCursorGrabbed();
}



void Window::setMouseCursorGrabbed(bool value)
{
  mImpl.setMouseCursorGrabbed(value);
}



bool Window::isKeyRepeatEnabled() const
{
  return mImpl.isKeyRepeatEnabled();
}



void Window::setKeyRepeatEnabled(bool value)
{
  mImpl.setKeyRepeatEnabled(value);
}



bool Window::hasFocus() const
{
  return mImpl.hasFocus();
}



bool Window::requestFocus() const
{
  return mImpl.requestFocus();
}


bool Window::isEventQueueEmpty() const
{
  return mImpl.isEventQueueEmpty();
}



void Window::updateEventQueue()
{
  mImpl.updateEventQueue();
}



WindowEvent Window::popEvent()
{
  WindowEvent ev = mImpl.popEvent();
  reactToEvent(ev);
  return ev;
}



void Window::pushEvent(const WindowEvent& event)
{
  mImpl.pushEvent(event);
}



WindowEvent Window::waitEvent()
{
  static constexpr std::chrono::milliseconds sleepTime(10);

  updateEventQueue();
  while(isEventQueueEmpty())
  {
    std::this_thread::sleep_for(sleepTime);
    updateEventQueue();
  }
  HOU_ENSURE_DEV(!isEventQueueEmpty());
  return popEvent();
}



void Window::swapBuffers()
{
  mImpl.swapBuffers();
}



void Window::reactToEvent(const WindowEvent& event)
{
  // If the window has been resized by the OS user, call setClientSize to make
  // sure that special handling for the derived class is performed as well.
  // Example: RenderWindow also resizes the FrameBuffer on resize.
  if(event.getType() == WindowEventType::Resized)
  {
    const WindowEvent::SizeData& data = event.getSizeData();
    setClientSize(Vec2u(data.sizeX, data.sizeY));
  }
}

}

