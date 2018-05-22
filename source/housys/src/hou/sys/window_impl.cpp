// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window_impl.hpp"

#include "hou/cor/assertions.hpp"



namespace hou
{

namespace prv
{

window_handle window_impl::get_handle() const noexcept
{
  return m_handle;
}



bool window_impl::is_mouse_cursor_grabbed() const noexcept
{
  return m_cursor_grabbed;
}



void window_impl::set_mouse_cursor_grabbed(bool value)
{
  m_cursor_grabbed = value;
  value ? grab_mouse_cursor() : ungrab_mouse_cursor();
}



bool window_impl::is_key_repeat_enabled() const noexcept
{
  return m_key_repeat_enabled;
}



void window_impl::set_key_repeat_enabled(bool value) noexcept
{
  m_key_repeat_enabled = value;
}



bool window_impl::is_event_queue_empty() const noexcept
{
  return m_event_queue.empty();
}



window_event window_impl::pop_event() noexcept
{
  if(is_event_queue_empty())
  {
    return window_event::empty();
  }
  else
  {
    window_event event = std::move(m_event_queue.front());
    m_event_queue.pop();
    return event;
  }
}



void window_impl::push_event(const window_event& event)
{
  m_event_queue.push(event);
}

}  // namespace prv

}  // namespace hou
