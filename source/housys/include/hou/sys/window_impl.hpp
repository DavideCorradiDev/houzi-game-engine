// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_IMPL_HPP
#define HOU_SYS_WINDOW_IMPL_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/image_fwd.hpp"
#include "hou/sys/window_handle.hpp"
#include "hou/sys/window_style.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/character_encodings.hpp"

#include "hou/mth/matrix.hpp"
#include "hou/mth/rectangle_fwd.hpp"

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

/** Internal window implementation.
 *
 * This class defines a basic window interface to be implemented for each
 * os. The hou::window class extends the interface to provide more functionalty.
 */
class HOU_SYS_API window_impl : public non_copyable
{
public:
  /** Constructor.
   *
   * \param title the window title.
   *
   * \param vm the video mode.
   *
   * \param style the window style.
   *
   * \throws hou::os_error if the window could not be created.
   */
  window_impl(
    const std::string& title, const video_mode& vm, window_style style);

  /** Move constructor.
   *
   * \param other the other hou::window_impl.
   *
   * \throws hou::os_error in case of error.
   */
  window_impl(window_impl&& other);

  /** Destructor.
   */
  ~window_impl();

  /** Retrieves the OS window handle.
   *
   * \return the OS window handle.
   */
  window_handle get_handle() const noexcept;

  /** Retrieves the window frame rectangle.
   *
   * \throws hou::os_error if the rectangle could not be got.
   *
   * \return the frame rectangle.
   */
  recti get_frame_rect() const;

  /** Sets the window frame rectangle.
   *
   * \param value the value for the window frame rectangle.
   *
   * \throws hou::os_error if the rectangle could not be set.
   */
  void set_frame_rect(const recti& value);

  /** Retrieves the window client rectangle.
   *
   * \throws hou::os_error if the rectangle could not be got.
   *
   * \return the frame rectangle.
   */
  recti get_client_rect() const;

  /** Sets the window client rectangle.
   *
   * \param value the value for the window frame rectangle.
   *
   * \throws hou::os_error if the rectangle could not be set.
   */
  void set_client_rect(const recti& value);

  /** Sets the window title.
   *
   * \param title the title.
   *
   * \throws hou::os_error if the title could not be set.
   */
  void set_title(const std::string& value);

  /** Sets the window icon.
   *
   * \param icon the icon.
   *
   * \throws hou::os_error if the icon could not be set.
   */
  void set_icon(const image2_rgba& icon);

  /** Sets the window icon to the system default.
   *
   * \throws hou::os_error if the icon could not be set.
   */
  void set_system_icon();

  /** Checks if the window is visible.
   *
   * \return true if the window is visible.
   */
  bool is_visible() const noexcept;

  /** Sets the visibility of the window.
   *
   * \param value true to make the window visible, false to make the window
   * invisible.
   *
   * \throws hou::os_error if the visibility could not be set.
   */
  void set_visible(bool value);

  /** Checks if the mouse cursor is grabbed by the window.
   *
   * \return true if the mouse cursor is grabbed by the window.
   */
  bool is_mouse_cursor_grabbed() const noexcept;

  /** Sets whether the window grabs the mouse cursor.
   *
   * \param value true if the window should grab the mouse cursor, false
   * otherwise.
   *
   * \throws hou::os_error in case of error.
   */
  void set_mouse_cursor_grabbed(bool value);

  /** Checks whether key repeat is enabled for the window.
   *
   * \return true if key repeat is enabled.
   */
  bool is_key_repeat_enabled() const noexcept;

  /** Sets whether key repeat is enabled.
   *
   * \param value true to enable key repeat, false to disable key repeat.
   */
  void set_key_repeat_enabled(bool value) noexcept;

  /** Checks whether the window currently has focus.
   *
   * \return true if the window currently has focus.
   */
  bool has_focus() const noexcept;

  /** Requests focus for this window.
   *
   * return true if focus was granted.
   */
  bool request_focus() const noexcept;

  /** Checks if the window event queue is empty.
   *
   * \return true if the event queue is empty.
   */
  bool is_event_queue_empty() const noexcept;

  /** Updates the event queue.
   *
   * \throws hou::os_error in case of an error.
   */
  void update_event_queue();

  /** Retrieves an event from the window queue.
   *
   * \return the first event in the queue. If the queue is empty, returns an
   * empty event.
   */
  window_event pop_event() noexcept;

  /** Pushes an event into the window queue.
   *
   * \param event the event to be pushed.
   *
   * \throws std::bad_alloc.
   */
  void push_event(const window_event& event);

  /** Swaps the front and back window buffers.
   *
   * \throws hou::os_error in case of an error.
   */
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
