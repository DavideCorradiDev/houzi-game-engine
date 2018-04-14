// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/WindowEventType.hpp"

#define WINDOW_EVENT_TYPE_CASE(we, os) \
  case WindowEventType::we: return (os) << #we



namespace hou
{

std::ostream& operator<<(std::ostream& os, WindowEventType we)
{
  switch(we)
  {
    WINDOW_EVENT_TYPE_CASE(Empty, os);
    WINDOW_EVENT_TYPE_CASE(Closed, os);
    WINDOW_EVENT_TYPE_CASE(FocusGained, os);
    WINDOW_EVENT_TYPE_CASE(FocusLost, os);
    WINDOW_EVENT_TYPE_CASE(Resized, os);
    WINDOW_EVENT_TYPE_CASE(KeyPressed, os);
    WINDOW_EVENT_TYPE_CASE(KeyReleased, os);
    WINDOW_EVENT_TYPE_CASE(TextEntered, os);
    WINDOW_EVENT_TYPE_CASE(MouseMoved, os);
    WINDOW_EVENT_TYPE_CASE(MouseEntered, os);
    WINDOW_EVENT_TYPE_CASE(MouseLeft, os);
    WINDOW_EVENT_TYPE_CASE(MouseButtonPressed, os);
    WINDOW_EVENT_TYPE_CASE(MouseButtonReleased, os);
    WINDOW_EVENT_TYPE_CASE(MouseWheelMoved, os);
    default: return os;
  }
}

}

