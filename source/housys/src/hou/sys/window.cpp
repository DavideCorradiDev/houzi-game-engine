// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/display_mode.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/sys/sdl/sdl_utils.hpp"

#include "hou/cor/narrow_cast.hpp"
#include "hou/cor/uid_generator.hpp"

#include "SDL2/SDL_video.h"

#include <limits>



namespace hou
{

namespace
{

uint32_t generate_uid() noexcept;

uint32_t generate_uid() noexcept
{
  static uid_generator uid_gen(1u);
  return uid_gen.generate();
}

}  // namespace



window::window(const std::string& title, const vec2u& size)
  : m_impl(SDL_CreateWindow(title.c_str(), 0, 0, size.x(), size.y(),
      SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS))
  , m_uid(generate_uid())
{
  HOU_ASSERT(m_impl != nullptr);
  recti bounds = display::get_usable_bounds(get_display_index());
  set_position(bounds.get_position()
    + (bounds.get_size() - narrow_cast<vec2i>(get_size())) / 2);
  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  set_max_size(vec2u(max_int, max_int));
}



window::window(window&& other)
  : m_impl(std::move(other.m_impl))
  , m_uid(std::move(other.m_uid))
{
  other.m_impl = nullptr;
  other.m_uid = 0u;
}



window::~window()
{
  if(m_impl != nullptr)
  {
    SDL_DestroyWindow(m_impl);
  }
}



window_impl window::get_impl() noexcept
{
  return m_impl;
}



uint32_t window::get_uid() const noexcept
{
  return m_uid;
}



uint window::get_display_index() const
{
  int display_idx = SDL_GetWindowDisplayIndex(m_impl);
  HOU_SDL_CHECK(display_idx >= 0);
  return narrow_cast<uint>(display_idx);
}



display::mode window::get_display_mode() const
{
  SDL_DisplayMode sdl_mode;
  HOU_SDL_CHECK(SDL_GetWindowDisplayMode(m_impl, &sdl_mode) == 0);
  return prv::convert(sdl_mode);
}



void window::set_display_mode(const display::mode& mode)
{
  SDL_DisplayMode sdl_mode = prv::convert(mode);
  HOU_SDL_CHECK(SDL_SetWindowDisplayMode(m_impl, &sdl_mode) == 0);
}



void window::set_default_display_mode()
{
  HOU_SDL_CHECK(SDL_SetWindowDisplayMode(m_impl, nullptr) == 0);
}



window_mode window::get_mode() const
{
  Uint32 flags = SDL_GetWindowFlags(m_impl);
  if(flags & SDL_WINDOW_FULLSCREEN_DESKTOP)
  {
    return window_mode::desktop_fullscreen;
  }
  if(flags & SDL_WINDOW_FULLSCREEN)
  {
    return window_mode::fullscreen;
  }
  return window_mode::windowed;
}



void window::set_mode(window_mode mode) const
{
  Uint32 flag = 0;
  if(mode == window_mode::fullscreen)
  {
    flag = SDL_WINDOW_FULLSCREEN;
  }
  else if(mode == window_mode::desktop_fullscreen)
  {
    flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  HOU_SDL_CHECK(SDL_SetWindowFullscreen(m_impl, flag) == 0);
}



std::string window::get_title() const
{
  return SDL_GetWindowTitle(m_impl);
}



void window::set_title(const std::string& title)
{
  SDL_SetWindowTitle(m_impl, title.c_str());
}



vec2u window::get_size() const
{
  int w = 0;
  int h = 0;
  SDL_GetWindowSize(m_impl, &w, &h);
  return vec2u(narrow_cast<uint>(w), narrow_cast<uint>(h));
}



void window::set_size(const vec2u& size)
{
  SDL_SetWindowSize(
    m_impl, narrow_cast<int>(size.x()), narrow_cast<int>(size.y()));
}



vec2u window::get_min_size() const
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMinimumSize(m_impl, &w, &h);
  return vec2u(narrow_cast<uint>(w), narrow_cast<uint>(h));
}



void window::set_min_size(const vec2u& min_size)
{
  SDL_SetWindowMinimumSize(
    m_impl, narrow_cast<int>(min_size.x()), narrow_cast<int>(min_size.y()));
}



vec2u window::get_max_size() const
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMaximumSize(m_impl, &w, &h);
  return vec2u(narrow_cast<uint>(w), narrow_cast<uint>(h));
}



void window::set_max_size(const vec2u& min_size)
{
  SDL_SetWindowMaximumSize(
    m_impl, narrow_cast<int>(min_size.x()), narrow_cast<int>(min_size.y()));
}



vec2i window::get_position() const
{
  int x = 0;
  int y = 0;
  SDL_GetWindowPosition(m_impl, &x, &y);
  return vec2i(x, y);
}



void window::set_position(const vec2i& position)
{
  SDL_SetWindowPosition(m_impl, position.x(), position.y());
}



bool window::is_visible() const
{
  return !(SDL_GetWindowFlags(m_impl) & SDL_WINDOW_HIDDEN);
}



void window::hide()
{
  SDL_HideWindow(m_impl);
}



void window::show()
{
  SDL_ShowWindow(m_impl);
}



bool window::is_minimized() const
{
  return SDL_GetWindowFlags(m_impl) & SDL_WINDOW_MINIMIZED;
}



bool window::is_maximized() const
{
  return SDL_GetWindowFlags(m_impl) & SDL_WINDOW_MAXIMIZED;
}



void window::minimize()
{
  SDL_MinimizeWindow(m_impl);
}



void window::maximize()
{
  SDL_MaximizeWindow(m_impl);
}



void window::restore()
{
  SDL_RestoreWindow(m_impl);
}



bool window::get_grab() const
{
  return SDL_GetWindowGrab(m_impl) == SDL_TRUE;
}



void window::set_grab(bool value)
{
  SDL_SetWindowGrab(m_impl, value ? SDL_TRUE : SDL_FALSE);
}



void window::raise()
{
  SDL_RaiseWindow(m_impl);
}

}  // namespace hou
