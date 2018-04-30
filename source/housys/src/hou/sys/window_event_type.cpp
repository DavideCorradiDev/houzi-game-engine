// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window_event_type.hpp"

#define WINDOW_EVENT_TYPE_CASE(we, os) \
  case window_event_type::we: \
    return (os) << #we



namespace hou
{

std::ostream& operator<<(std::ostream& os, window_event_type we)
{
  switch(we)
  {
    WINDOW_EVENT_TYPE_CASE(empty, os);
    WINDOW_EVENT_TYPE_CASE(closed, os);
    WINDOW_EVENT_TYPE_CASE(focus_gained, os);
    WINDOW_EVENT_TYPE_CASE(focus_lost, os);
    WINDOW_EVENT_TYPE_CASE(resized, os);
    WINDOW_EVENT_TYPE_CASE(key_pressed, os);
    WINDOW_EVENT_TYPE_CASE(key_released, os);
    WINDOW_EVENT_TYPE_CASE(text_entered, os);
    WINDOW_EVENT_TYPE_CASE(mouse_moved, os);
    WINDOW_EVENT_TYPE_CASE(mouse_entered, os);
    WINDOW_EVENT_TYPE_CASE(mouse_left, os);
    WINDOW_EVENT_TYPE_CASE(mouse_button_pressed, os);
    WINDOW_EVENT_TYPE_CASE(mouse_button_released, os);
    WINDOW_EVENT_TYPE_CASE(mouse_wheel_moved, os);
    default:
      return os;
  }
}

}  // namespace hou
