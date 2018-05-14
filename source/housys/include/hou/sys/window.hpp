// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_HPP
#define HOU_SYS_WINDOW_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/image.hpp"
#include "hou/sys/window_impl.hpp"

#include "hou/sys/sys_config.hpp"

#include <string>



namespace hou
{

class video_mode;
class window_event;

/** Class representing a window.
 */
class HOU_SYS_API window : public non_copyable
{
public:
  /** Creates a window object.
   *
   * The window client size corresponds to the resolution in vm.
   * The window client is be positioned in the middle of the screen.
   * The window uses the default system icon.
   * The window is not visible.
   * The window does not grab the mouse cursor.
   * Key repeat is disabled for the window.
   *
   * \param title the title of the window.
   *
   * \param vm the video mode of the window, specifying its client size and
   * bytes per pixel.
   *
   * \param style the style of the window.
   * Only one window can be fullscreen.
   * If fullscreen mode is specified and vm is not a valid fullscreen
   * video_mode, an error will be thrown.
   *
   * \throws hou::precond_error if style is fullscreen and a fullscreen window
   * already exists.
   *
   * \throws hou::os_error if the window could not be created.
   */
  window(const std::string& title, const video_mode& vm, window_style style);

  /** Move constructor.
   *
   * \param other the other window object.
   *
   * \throws hou::os_error if the window could not be created.
   */
  window(window&& other) = default;

  /** Destructor.
   */
  virtual ~window() = 0;

  /** Gets the OS dependent window handle associated to this window.
   *
   * \return the OS dependent window handle.
   */
  window_handle get_handle() const noexcept;

  /** Gets the unique identifier of this window.
   *
   * \return the unique identifier of this window.
   */
  uint32_t get_uid() const noexcept;

  /** Gets the title of this window.
   *
   * \return the title of this window.
   */
  const std::string& get_title() const noexcept;

  /** Sets the title of this window.
   *
   * \param title the title.
   */
  void set_title(const std::string& title);

  /** Gets the position of the window frame.
   *
   * The window frame position is the top left corner of the window, including
   * the borders.
   *
   * \throws hou::os_error if the window position could not be got.
   *
   * \return the position of the window frame.
   */
  vec2i get_frame_position() const;

  /** Gets the size of the window frame.
   *
   * The window frame size includes the borders.
   *
   * \throws hou::os_error if the window size could not be got.
   *
   * \return the size of the window frame.
   */
  vec2u get_frame_size() const;

  /** Sets the window frame rectangle.
   *
   * The window frame rectangle includes the borders.
   *
   * \param pos the window frame position.
   *
   * \param size the window frame size.
   *
   * \throws hou::os_error if the window rectangle could not be set.
   */
  virtual void set_frame_rect(const vec2i& pos, const vec2u& size) = 0;

  /** Sets the position of the window frame.
   *
   * The window frame position is the top left corner of the window, including
   * the borders
   *
   * \param pos the position of the window frame.
   *
   * \throws hou::os_error if the window position could not be set.
   */
  void set_frame_position(const vec2i& pos);

  /** Sets the size of the window frame.
   *
   * The window frame size includes the borders
   *
   * \param size the size of the window frame.
   *
   * \throws hou::os_error if the window size could not be set.
   */
  void setFrameSize(const vec2u& size);

  /** Gets the position of the window client.
   *
   * The window client position is the top left corner of the window, not
   * including the borders.
   *
   * \return the position of the window client.
   *
   * \throws hou::os_error if the window position could not be got
   */
  vec2i get_client_position() const;

  /** Gets the size of the window client.
   *
   * The window client size does not include the borders.
   *
   * \return the size of the window client.
   *
   * \throws hou::os_error if the window size could not be got
   */
  vec2u get_client_size() const;

  /** Sets the window client rectangle.
   *
   * The window client rectangle does not include the borders.
   *
   * \param pos the window client position.
   *
   * \param size the window client size.
   *
   * \throws hou::os_error if the window rectangle could not be set.
   */
  virtual void set_client_rect(const vec2i& pos, const vec2u& size) = 0;

  /** Sets the position of the window client.
   *
   * The window client position is the top left corner of the window, not
   * including the borders.
   *
   * \param pos the position of the window client.
   *
   * \throws hou::os_error if the window position could not be set.
   */
  void set_client_position(const vec2i& pos);

  /** Sets the size of the window client.
   *
   * The window client size does not include the borders.
   *
   * \param size the size of the window client.
   *
   * \throws hou::os_error if the window size could not be set.
   */
  void set_client_size(const vec2u& size);

  /** Gets the number of bytes per pixel of this window.
   *
   * \return the number of bytes per pixel of this window.
   */
  uint get_bytes_per_pixel() const noexcept;

  /** Gets the style of this window.
   *
   * \return the style of this window.
   */
  window_style get_style() const noexcept;

  /** Gets the window icon.
   *
   * \return the window icon if a custom icon was set, an empty image if the
   * system icon is being used.
   */
  const image2_rgba& get_icon() const noexcept;

  /** Sets the window icon.
   *
   * \param icon the icon.
   *
   * \throws hou::os_error if the window icon could not be set.
   */
  void set_icon(const image2_rgba& icon);

  /** Resets the window icon to the default system icon.
   *
   * \throws hou::os_error if the window icon could not be set.
   */
  void set_system_icon();

  /** Checks if the window is visible.
   *
   * \return true if the window is visible.
   */
  bool is_visible() const noexcept;

  /** Sets if the window is visible.
   *
   * \param value whether the window is visible.
   *
   * \throws hou::os_error if the window visibilty could not be changed.
   */
  void set_visible(bool value);

  /** Checks if the window is grabbing the mouse cursor.
   *
   * \return true if the window is grabbing the mouse cursor.
   */
  bool is_mouse_cursor_grabbed() const noexcept;

  /** Sets if the window is grabbing the mouse cursor.
   *
   * \throws hou::os_error in case of error.
   *
   * \param value whether the window is grabbing the mouse cursor.
   */
  void set_mouse_cursor_grabbed(bool value);

  /** Checks if key repeat is enabled for this window.
   *
   * \return true if key repeat is enabled for this window.
   */
  bool is_key_repeat_enabled() const noexcept;

  /** Sets if key repeat is enabled for this Windows.
   *
   * \param value whether key repeat is enabled for this window.
   */
  void set_key_repeat_enabled(bool value) noexcept;

  /** Checks if this window currently has focus.
   *
   * \return whether this window currently has focus.
   */
  bool has_focus() const noexcept;

  /** Requests focus for this window.
   *
   * Requesting focus does not guarantee that the focus is actually obtained.
   * Check the return value to see if the request was successfull.
   *
   * \return true if the focus request was successfull and this window now has
   * focus.
   */
  bool request_focus() const noexcept;

  /** Checks if the event queue of this window is empty.
   *
   * This function does not automatically update the queue.
   * Call update_event_queue before to fill it with events coming from the OS.
   *
   * \return true if the event queue of this window is empty.
   */
  bool is_event_queue_empty() const noexcept;

  /** Fills the event queue of this window with events coming from the OS.
   *
   * \throws hou::os_error in case of error getting the window events.
   *
   * \throws std::bad_alloc.
   */
  void update_event_queue();

  /** Pops the front event in the queue of this window.
   *
   * This function does not automatically update the queue.
   * Call update_event_queue before to fill it with events coming from the OS.
   * This function is not blocking.
   * If the event queue is empty, an event of type empty is returned.
   *
   * \return the front event, or an event of type empty if the queue is empty.
   */
  window_event pop_event() noexcept;

  /** Pushes an event into the back of the queu of this window.
   *
   * \param event the event to be pushed.
   */
  void push_event(const window_event& event);

  /** Waits for the event queue of this window to contain at least one event and
   * pops it.
   *
   * This function always updates the event queue, so a call to
   * update_event_queue is not necessary. This function is blocking, it will
   * keep updating and checking the queue until an event is pushed. This
   * function only pops the first event. It might be that multiple events have
   * been inserted in the queue and therefore the queue might still be filled.
   *
   * \throws hou::os_error in case of error getting the window events.
   *
   * \throws std::bad_alloc.
   *
   * \return the front event.
   */
  window_event wait_event();

protected:
  /** Swaps the front and back buffers of the window.
   *
   * Throws if the window has no valid buffers.
   * Derived classes should make sure to only call this function when it is
   * safe to do so.
   */
  void swap_buffers();

private:
  void react_to_event(const window_event& event);

private:
  prv::window_impl m_impl;
  uint32_t m_uid;
  window_style m_style;
  uint m_bytes_per_pixel;
  std::string m_title;
  image2_rgba m_icon_image;
};

}  // namespace hou

#endif
