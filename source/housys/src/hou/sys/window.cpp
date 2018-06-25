// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/window.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/display_mode.hpp"

#include "hou/sys/sys_exceptions.hpp"

#include "hou/cor/narrow_cast.hpp"

#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_video.h"

#include <limits>



namespace hou
{

namespace
{

static constexpr const char* g_impl_data_name = "houwnd";

}  // namespace



window& window::get_from_impl(not_null<const impl_type*> impl)
{
  window* wnd = reinterpret_cast<window*>(
    SDL_GetWindowData(const_cast<impl_type*>(impl.get()), g_impl_data_name));
  HOU_POSTCOND(wnd != nullptr);
  return *wnd;
}



window& window::get_from_uid(uid_type uid)
{
  SDL_Window* wnd = SDL_GetWindowFromID(uid);
  HOU_SDL_CHECK(wnd != nullptr);
  return window::get_from_impl(wnd);
}



window::window(const std::string& title, const vec2u& size)
  : m_impl(nullptr)
  , m_icon()
{
  HOU_PRECOND(size.x() != 0u && size.y() != 0);
  m_impl = SDL_CreateWindow(title.c_str(), 0, 0, size.x(), size.y(),
      SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_BORDERLESS);
  HOU_SDL_CHECK(m_impl != nullptr);

  // Create the window at the center of the screen.
  recti bounds = display::get_usable_bounds(get_display_index());
  set_position(bounds.get_position()
    + (bounds.get_size() - narrow_cast<vec2i>(get_size())) / 2);

  // The initial value for the max size is 0 rather than the actual maximum.
  // This is confusing and makes some checks behave incorrectly.
  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  set_max_size(vec2u(max_int, max_int));

  // SDL seems to forbid resizing the window to a size of (0,0), limiting it to
  // (1,1), but the default minimum size is (0,0). Here the initial minimum size
  // is set explicitly to (1,1) to keep things consistent.
  set_min_size(vec2u(1u, 1u));

  // Set pointer to this in the custom data of m_impl, so that functions
  // taking a pointer to an SDL_Window* can get a reference to the hou::window.
  SDL_SetWindowData(m_impl, g_impl_data_name, this);
}



window::window(window&& other) noexcept
  : m_impl(std::move(other.m_impl))
  , m_icon(std::move(other.m_icon))
{
  other.m_impl = nullptr;
  SDL_SetWindowData(m_impl, g_impl_data_name, this);
}



window::~window()
{
  if(m_impl != nullptr)
  {
    SDL_DestroyWindow(m_impl);
  }
}



const window::impl_type* window::get_impl() const noexcept
{
  return m_impl;
}



window::impl_type* window::get_impl() noexcept
{
  return m_impl;
}



window::uid_type window::get_uid() const noexcept
{
  return SDL_GetWindowID(m_impl);
}



uint window::get_display_index() const
{
  int display_idx = SDL_GetWindowDisplayIndex(m_impl);
  HOU_SDL_CHECK(display_idx >= 0);
  return narrow_cast<uint>(display_idx);
}



display_mode window::get_display_mode() const
{
  SDL_DisplayMode sdl_mode;
  HOU_SDL_CHECK(SDL_GetWindowDisplayMode(m_impl, &sdl_mode) == 0);
  return prv::convert(sdl_mode);
}



void window::set_display_mode(const display_mode& mode)
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
  // Note: it is necessary to check SDL_WINDOW_FULLSCREEN_DESKTOP first, because
  // the SDL_WINDOW_FULLSCREEN bit is also set in SDL_WINDOW_FULLSCREEN_DESKTOP.
  Uint32 flags = SDL_GetWindowFlags(m_impl);
  if((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP)
  {
    return window_mode::desktop_fullscreen;
  }
  else if((flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
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



const image2_rgba& window::get_icon() const noexcept
{
  return m_icon;
}



void window::set_icon(const image2_rgba& icon)
{
  // clang-format off
  SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
    const_cast<pixel_rgba*>(icon.get_pixels().data()),
    icon.get_size().x(),
    icon.get_size().y(),
    image2_rgba::pixel_bit_count,
    icon.get_size().x() * image2_rgba::pixel_byte_count,
    0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
  // clang-format on
  HOU_SDL_CHECK(surface != nullptr);
  SDL_SetWindowIcon(m_impl, surface);
  SDL_FreeSurface(surface);
  m_icon = icon;
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
  HOU_PRECOND(size.x() != 0u && size.y() != 0u);
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
  HOU_PRECOND(min_size.x() > 0u && min_size.y() > 0u
    && min_size.x() <= get_max_size().x()
    && min_size.y() <= get_max_size().x());
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



void window::set_max_size(const vec2u& max_size)
{
  HOU_PRECOND(
    max_size.x() >= get_min_size().x() && max_size.y() >= get_min_size().x());
  SDL_SetWindowMaximumSize(
    m_impl, narrow_cast<int>(max_size.x()), narrow_cast<int>(max_size.y()));
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



void window::set_visible(bool value)
{
  if(value)
  {
    SDL_ShowWindow(m_impl);
  }
  else
  {
    SDL_HideWindow(m_impl);
  }
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
  // If the window is not resizable, SDL_MaximizeWindow will not actually
  // maximize the window, but will still flag it as maximized.
  if(is_resizable())
  {
    SDL_MaximizeWindow(m_impl);
  }
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



bool window::is_resizable() const
{
  return SDL_GetWindowFlags(m_impl) & SDL_WINDOW_RESIZABLE;
}



void window::set_resizable(bool value)
{
  SDL_SetWindowResizable(m_impl, value ? SDL_TRUE : SDL_FALSE);
}



bool window::is_bordered() const
{
  return !(SDL_GetWindowFlags(m_impl) & SDL_WINDOW_BORDERLESS);
}



void window::set_bordered(bool value)
{
  SDL_SetWindowBordered(m_impl, value ? SDL_TRUE : SDL_FALSE);
}



bool window::has_keyboard_focus() const
{
  return SDL_GetKeyboardFocus() == m_impl;
}



bool window::has_mouse_focus() const
{
  return SDL_GetMouseFocus() == m_impl;
}



bool window::focus()
{
  return SDL_SetWindowInputFocus(m_impl) >= 0;
}



void window::raise()
{
  SDL_RaiseWindow(m_impl);
}



void window::clear(const color& color)
{
  SDL_Surface* screen_surface = SDL_GetWindowSurface(m_impl);
  SDL_FillRect(screen_surface, nullptr,
    SDL_MapRGB(screen_surface->format, color.get_red(), color.get_green(),
      color.get_blue()));
  HOU_SDL_CHECK(SDL_UpdateWindowSurface(m_impl) == 0);
}



void window::swap_buffers()
{
  SDL_GL_SwapWindow(m_impl);
}

}  // namespace hou
