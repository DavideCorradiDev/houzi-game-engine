// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/window_event.hpp"

#include "hou/cor/uid_generator.hpp"

#include "hou/mth/rectangle.hpp"

#include <thread>



namespace hou
{

namespace
{

uint32_t generate_uid();



uint32_t generate_uid()
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}

}  // namespace



window::window(
  const std::string& title, const video_mode& vm, window_style style)
  : non_copyable()
  , m_impl(title, vm, style)
  , m_uid(generate_uid())
  , m_style(style)
  , m_bytes_per_pixel(vm.get_bytes_per_pixel())
  , m_title(title)
  , m_icon_image()
{}



window::window(window&& other)
  : m_impl(std::move(other.m_impl))
  , m_uid(std::move(other.m_uid))
  , m_style(std::move(other.m_style))
  , m_bytes_per_pixel(std::move(other.m_bytes_per_pixel))
  , m_title(std::move(other.m_title))
  , m_icon_image(std::move(other.m_icon_image))
{}



window::~window()
{}



window_handle window::get_handle() const
{
  return m_impl.get_handle();
}



uint32_t window::get_uid() const
{
  return m_uid;
}



const std::string& window::get_title() const
{
  return m_title;
}



void window::set_title(const std::string& title)
{
  m_impl.set_title(title);
  m_title = title;
}



vec2i window::get_frame_position() const
{
  return m_impl.get_frame_rect().get_position();
}



vec2u window::get_frame_size() const
{
  return static_cast<vec2u>(m_impl.get_frame_rect().get_size());
}



void window::set_frame_rect(const vec2i& pos, const vec2u& size)
{
  vec2u old_client_size = get_client_size();
  m_impl.set_frame_rect(recti(pos, static_cast<vec2i>(size)));
  vec2u new_client_size = get_client_size();
  if(old_client_size != new_client_size)
  {
    push_event(window_event::resized(new_client_size.x(), new_client_size.y()));
  }
}



void window::set_frame_position(const vec2i& pos)
{
  set_frame_rect(pos, get_frame_size());
}



void window::setFrameSize(const vec2u& size)
{
  set_frame_rect(get_frame_position(), size);
}



vec2i window::get_client_position() const
{
  return m_impl.get_client_rect().get_position();
}



vec2u window::get_client_size() const
{
  return static_cast<vec2u>(m_impl.get_client_rect().get_size());
}



void window::set_client_rect(const vec2i& pos, const vec2u& size)
{
  vec2u old_client_size = get_client_size();
  m_impl.set_client_rect(recti(pos, static_cast<vec2i>(size)));
  vec2u new_client_size = get_client_size();
  if(old_client_size != new_client_size)
  {
    push_event(window_event::resized(new_client_size.x(), new_client_size.y()));
  }
}



void window::set_client_position(const vec2i& pos)
{
  set_client_rect(pos, get_client_size());
}



void window::set_client_size(const vec2u& size)
{
  set_client_rect(get_client_position(), size);
}



uint window::get_bytes_per_pixel() const
{
  return m_bytes_per_pixel;
}



window_style window::get_style() const
{
  return m_style;
}



const image2_rgba& window::get_icon() const
{
  return m_icon_image;
}



void window::set_icon(const image2_rgba& icon)
{
  m_icon_image = icon;
  m_impl.set_icon(icon);
}



void window::set_system_icon()
{
  m_icon_image = image2_rgba();
  m_impl.set_system_icon();
}



bool window::is_visible() const
{
  return m_impl.is_visible();
}



void window::set_visible(bool value)
{
  m_impl.set_visible(value);
}



bool window::is_mouse_cursor_grabbed() const
{
  return m_impl.is_mouse_cursor_grabbed();
}



void window::set_mouse_cursor_grabbed(bool value)
{
  m_impl.set_mouse_cursor_grabbed(value);
}



bool window::is_key_repeat_enabled() const
{
  return m_impl.is_key_repeat_enabled();
}



void window::set_key_repeat_enabled(bool value)
{
  m_impl.set_key_repeat_enabled(value);
}



bool window::has_focus() const
{
  return m_impl.has_focus();
}



bool window::request_focus() const
{
  return m_impl.request_focus();
}


bool window::is_event_queue_empty() const
{
  return m_impl.is_event_queue_empty();
}



void window::update_event_queue()
{
  m_impl.update_event_queue();
}



window_event window::pop_event()
{
  window_event ev = m_impl.pop_event();
  react_to_event(ev);
  return ev;
}



void window::push_event(const window_event& event)
{
  m_impl.push_event(event);
}



window_event window::wait_event()
{
  static constexpr std::chrono::milliseconds sleepTime(10);

  update_event_queue();
  while(is_event_queue_empty())
  {
    std::this_thread::sleep_for(sleepTime);
    update_event_queue();
  }
  HOU_DEV_POSTCOND(!is_event_queue_empty());
  return pop_event();
}



void window::swap_buffers()
{
  m_impl.swap_buffers();
}



void window::react_to_event(const window_event& event)
{
  // If the window has been resized by the OS user, call set_client_size to
  // make sure that special handling for the derived class is performed as well.
  // Example: render_window also resizes the framebuffer on resize.
  if(event.get_type() == window_event_type::resized)
  {
    const window_event::size_data& data = event.get_size_data();
    set_client_size(vec2u(data.x, data.y));
  }
}

}  // namespace hou
