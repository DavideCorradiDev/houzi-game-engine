// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_IMPL_HPP
#define HOU_SYS_WINDOW_IMPL_HPP

#include "hou/cor/non_copyable.hpp"
#include "hou/sys/sys_export.hpp"

#include "hou/cor/character_encodings.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"

#include "hou/sys/image_fwd.hpp"
#include "hou/sys/window_handle.hpp"
#include "hou/sys/window_style.hpp"
#if defined(HOU_SYSTEM_WINDOWS)
#include "hou/sys/Win/win.hpp"
#endif

#include <queue>



namespace hou
{

class video_mode;
class window_event;



namespace prv
{

class window_impl : public non_copyable
{
public:
  window_impl(
    const std::string& title, const video_mode& vm, window_style style);
  window_impl(window_impl&& other);
  ~window_impl();

  window_handle get_handle() const;

  recti get_frame_rect() const;
  void set_frame_rect(const recti& value);

  recti get_client_rect() const;
  void set_client_rect(const recti& value);

  void set_title(const std::string& value);

  void set_icon(const image2_rgba& icon);
  void set_system_icon();

  bool is_visible() const;
  void set_visible(bool value);

  bool is_mouse_cursor_grabbed() const;
  void set_mouse_cursor_grabbed(bool value);

  bool is_key_repeat_enabled() const;
  void set_key_repeat_enabled(bool value);

  bool has_focus() const;
  bool request_focus() const;

  bool is_event_queue_empty() const;
  void update_event_queue();
  window_event pop_event();
  void push_event(const window_event& event);

  void swap_buffers();

private:
  void grab_mouse_cursor();
  void ungrab_mouse_cursor();
  bool is_mouse_captured() const;
  void set_mouse_captured(bool value);

#if defined(HOU_SYSTEM_WINDOWS)
  static void register_window_class();
  static void unregister_window_class();
  static LRESULT CALLBACK wnd_procedure(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  void destroy_icon();
  void destroy_cursor();
  void destroy_window();

  void filter_event(UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

private:
  window_handle m_handle;
  bool m_cursor_grabbed;
  bool m_key_repeat_enabled;
  std::queue<window_event> m_event_queue;
#if defined(HOU_SYSTEM_WINDOWS)
  HDC m_hdc;
  HCURSOR m_cursor_handle;
  HICON m_icon_handle;
  wide::code_unit m_cached_utf16_char;
  bool m_mouse_in_window;
  vec2u m_previous_size;
#endif
};

}  // namespace prv

}  // namespace hou

#endif
