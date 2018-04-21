// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/WindowImpl.hpp"

#include "hou/cor/Error.hpp"

#include "hou/sys/WindowEvent.hpp"



namespace hou
{

namespace prv
{

WindowHandle WindowImpl::getWindowHandle() const
{
  return mHandle;
}



bool WindowImpl::isMouseCursorGrabbed() const
{
  return mCursorGrabbed;
}



void WindowImpl::setMouseCursorGrabbed(bool value)
{
  mCursorGrabbed = value;
  value ? grabMouseCursor() : ungrabMouseCursor();
}



bool WindowImpl::isKeyRepeatEnabled() const
{
  return mKeyRepeatEnabled;
}



void WindowImpl::setKeyRepeatEnabled(bool value)
{
  mKeyRepeatEnabled = value;
}



bool WindowImpl::isEventQueueEmpty() const
{
  return mEventQueue.empty();
}



WindowEvent WindowImpl::popEvent()
{
  if(isEventQueueEmpty())
  {
    return WindowEvent::empty();
  }
  else
  {
    WindowEvent event = std::move(mEventQueue.front());
    mEventQueue.pop();
    return event;
  }
}



void WindowImpl::pushEvent(const WindowEvent& event)
{
  mEventQueue.push(event);
}

}

}

