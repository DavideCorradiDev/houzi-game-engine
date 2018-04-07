// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/sys/Window.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/WindowEvent.hpp"

#include "hou/cor/UidGenerator.hpp"

#include "hou/mth/Rectangle.hpp"



namespace hou
{

namespace
{

uint32_t generateUid();



uint32_t generateUid()
{
  static UidGenerator uidGenerator(1u);
  return uidGenerator.generate();
}

}



Window::Window(const std::string& title, const VideoMode& videoMode
  , WindowStyle style)
  : NonCopyable()
  , mImpl(title, videoMode, style)
  , mUid(generateUid())
  , mStyle(style)
  , mBitsPerPixel(videoMode.getBitsPerPixel())
  , mTitle(title)
  , mIconImage()
{}



Window::Window(Window&& other)
  : mImpl(std::move(other.mImpl))
  , mUid(std::move(other.mUid))
  , mStyle(std::move(other.mStyle))
  , mBitsPerPixel(std::move(other.mBitsPerPixel))
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



Recti Window::getFrameRect() const
{
  return mImpl.getFrameRect();
}



Vec2i Window::getFramePosition() const
{
  return getFrameRect().getPosition();
}



Vec2u Window::getFrameSize() const
{
  return getFrameRect().getSize();
}



void Window::setFrameRect(const Recti& rect)
{
  mImpl.setFrameRect(rect);
}



void Window::setFramePosition(const Vec2i& pos)
{
  Vec2u size = getFrameSize();
  setFrameRect(Recti(pos, size));
}



void Window::setFrameSize(const Vec2u& size)
{
  Vec2i pos = getFramePosition();
  setFrameRect(Recti(pos, size));
}



Recti Window::getClientRect() const
{
  return mImpl.getClientRect();
}



Vec2i Window::getClientPosition() const
{
  return getClientRect().getPosition();
}



Vec2u Window::getClientSize() const
{
  return getClientRect().getSize();
}



void Window::setClientRect(const Recti& rect)
{
  mImpl.setClientRect(rect);
}



void Window::setClientPosition(const Vec2i& pos)
{
  Vec2u size = getFrameSize();
  setClientRect(Recti(pos, size));
}



void Window::setClientSize(const Vec2u& size)
{
  Vec2i pos = getClientPosition();
  setClientRect(Recti(pos, size));
}



uint Window::getBitsPerPixel() const
{
  return mBitsPerPixel;
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
  return mImpl.popEvent();
}



void Window::pushEvent(const WindowEvent& event)
{
  mImpl.pushEvent(event);
}



WindowEvent Window::waitEvent()
{
  return mImpl.waitEvent();
}



void Window::swapBuffers()
{
  mImpl.swapBuffers();
}

}

