// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WINDOW_HPP
#define HOU_SYS_WINDOW_HPP

#include "hou/cor/non_copyable.hpp"

#include "hou/sys/image.hpp"
#include "hou/sys/window_mode.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/not_null.hpp"
#include "hou/cor/std_string.hpp"
#include "hou/cor/uid_generator.hpp"

#include "hou/mth/matrix.hpp"



union SDL_Event;
struct SDL_Window;

namespace hou
{

namespace event
{

namespace prv
{

void process(const SDL_Event&);

}  // namespace prv

}  // namespace event

class color;
class display_mode;

/**
 * Represents a window.
 */
class HOU_SYS_API window : public non_copyable
{
public:
  /**
   * The underlying implementation type.
   */
  using impl_type = SDL_Window;

  /**
   * Type for window unique identifiers.
   */
  using uid_type = uid_generator::uid_type;

public:
  /**
   * Retrieves the window associated to a given implementation.
   *
   * \param impl the implementation.
   *
   * \return the window referenced by the implementation.
   */
  static window& get_from_impl(not_null<const impl_type*> impl);

  /**
   * Retrieves the window associated to a given id.
   *
   * \param uid the uid.
   *
   * \return the window referenced by the uid.
   */
  static window& get_from_uid(uid_type uid);

public:
  /**
   * Creates a window.
   *
   * \param title the window title.
   *
   * \param size the size of the window client area.
   *
   * \throws hou::precondition_violation if one element of size is null.
   */
  window(const std::string& title, const vec2u& size);

  /**
   * Move constructor.
   *
   * \param other the other window.
   */
  window(window&& other) noexcept;

  /**
   * Destructor.
   */
  virtual ~window() = 0;

  /**
   * Gets the window implementation.
   *
   * \return the window implementation.
   */
  const impl_type* get_impl() const noexcept;

  /**
   * Gets the window implementation.
   *
   * \return the window implementation.
   */
  impl_type* get_impl() noexcept;

  /**
   * Gets the window unique identifier.
   *
   * \return the window unique identifier, or 0 if the window is in an invalid
   * state.
   */
  uid_type get_uid() const noexcept;

  /**
   * Gets the index of the display containing the window.
   *
   * The value can be used for example in the functions in the hou::display
   * namespace.
   *
   * \return the index of the display containing the window.
   */
  uint get_display_index() const;

  /**
   * Gets the window display mode.
   *
   * This is the display mode that the library tries to set when the window
   * is in fullscreen mode.
   *
   * By default the window display mode has the current display_format and
   * refresh rate, and a resolution equal to the window client area size.
   *
   * \return the window display mode.
   */
  display_mode get_display_mode() const;

  /**
   * Sets the window display mode.
   *
   * \param mode the window display mode.
   */
  void set_display_mode(const display_mode& mode);

  /**
   * Resets the window display mode to its default value.
   */
  void set_default_display_mode();

  /**
   * Gets the window mode.
   *
   * The default value is window_mode::windowed.
   *
   * \return the window mode.
   */
  window_mode get_mode() const;

  /**
   * Sets the window mode.
   *
   * \param mode the window mode.
   */
  void set_mode(window_mode mode) const;

  /**
   * Gets the window title.
   *
   * \return the window title.
   */
  std::string get_title() const;

  /**
   * Sets the window title.
   *
   * \param title the window title.
   */
  void set_title(const std::string& title);

  /**
   * Gets the window icon.
   *
   * \return the window icon if it was set with set_icon, or an empty image
   * if the default system icon is being used.
   */
  const image2_rgba& get_icon() const noexcept;

  /**
   * Sets the window icon.
   *
   * \param icon the icon.
   */
  void set_icon(const image2_rgba& icon);

  /**
   * Gets the window client area size.
   *
   * \return the window client area size.
   */
  vec2u get_size() const;

  /**
   * Sets the window client area size.
   *
   * \param size the window client araea size.
   *
   * \throws hou::precondition_violation if one element of size is null.
   */
  void set_size(const vec2u& size);

  /**
   * Gets the window minimum client area size.
   *
   * The default value is vec2u::zero().
   *
   * \return the window minimum client area size.
   */
  vec2u get_min_size() const;

  /**
   * Sets the window minimum client area size.
   *
   * \param min_size the window minimum client area size.
   *
   * \throws hou::precondition_violation if an element of min_size is greater
   * than the corresponding element of get_max_size();
   */
  void set_min_size(const vec2u& min_size);


  /**
   * Gets the window maximum client area size.
   *
   * The default value is the maximum possible uint value.
   * Note that some values for the actual window size might be impossible for
   * the operating system to handle, even though they are lower than the
   * value returned by get_max_size().
   *
   * \return the window maximum client area size.
   */
  vec2u get_max_size() const;

  /**
   * Sets the window maximum client area size.
   *
   * \param max_size the window maximum client area size.
   *
   * \throws hou::precondition_violation if an element of max_size is less
   * than the corresponding element of get_min_size();
   */
  void set_max_size(const vec2u& max_size);

  /**
   * Gets the window position.
   *
   * The returned position corresponds to the top left corner of the client
   * area.
   *
   * \return the window position.
   */
  vec2i get_position() const;

  /**
   * Sets the window position.
   *
   * \param position the window position.
   */
  void set_position(const vec2i& position);

  /**
   * Checks if the window is visible.
   *
   * \return true if the window is visible.
   */
  bool is_visible() const;

  /**
   * Sets the visibility of the window.
   *
   * \note the event queue must be processed in order to completely update the
   * internal state of the window after calling this (see the functions in the
   * hou::event namespace).
   *
   * \param value true to make the window visible, false to hide the window.
   */
  void set_visible(bool value);

  /**
   * Checks if the window is minimized.
   *
   * \return true if the window is minimized.
   */
  bool is_minimized() const;

  /**
   * Checks if the window is maximized.
   *
   * \return true if the window is maximized.
   */
  bool is_maximized() const;

  /**
   * Minimizes the window.
   *
   * \note the event queue must be processed in order to completely update the
   * internal state of the window after calling this (see the functions in the
   * hou::event namespace).
   */
  void minimize();

  /**
   * Maximizes the window.
   *
   * \note the event queue must be processed in order to completely update the
   * internal state of the window after calling this (see the functions in the
   * hou::event namespace).
   */
  void maximize();

  /**
   * Restores a previously minimized or maximized window.
   *
   * \note restoring will work only after the internal state of the window has
   * been completely updated, which normally happens after processing the
   * event queue. For this reason, for example, a call to minimize() immediately
   * followed by a call to restore() might not cause the window to be restored.
   *
   * \note on some systems the window may only be restored manually by the user
   * after it has been minimized.
   */
  void restore();

  /**
   * Checks if the window is currently grabbing the mouse cursor.
   *
   * \return true if the window is currently grabbing the mouse cursor.
   */
  bool get_grab() const;

  /**
   * Sets whether the window should grab the mouse cursor.
   *
   * \note the window must be visible and have focus to be able to grab the
   * mouse cursor.
   *
   * \note calling this function does not guarantee that the mouse cursor will
   * be grabbed.
   *
   * \param value true if the window should grab the mouse cursor, false
   * otherwise.
   */
  void set_grab(bool value);

  /**
   * Checks whether the window is resizable.
   *
   * The window can always be resized with calls to set_size.
   * This refers to the possibility to resize the window by grabbing its
   * borders.
   *
   * \return true if the window is resizable.
   */
  bool is_resizable() const;

  /**
   * Sets whether the window is resizable.
   *
   * The window can always be resized with calls to set_size.
   * This refers to the possibility to resize the window by grabbing its
   * borders.
   *
   * \param value true to make the window resizable, false otherwise.
   */
  void set_resizable(bool value);

  /**
   * Checks whether the window is bordered.
   *
   * \return true if the window is bordered.
   */
  bool is_bordered() const;

  /**
   * Sets whether the window is bordered.
   *
   * \param value true to show the window border, false otherwise.
   */
  void set_bordered(bool value);

  /**
   * Checks whether the window has keyboard focus.
   *
   * \return true if the window has keyboard focus.
   */
  bool has_keyboard_focus() const;

  /**
   * Checks whether the window has mouse focus.
   *
   * \return true if the window has mouse focus.
   */
  bool has_mouse_focus() const;

  /**
   * Request focus for the window.
   *
   * \return true if focus was given to the window, false otherwise.
   */
  bool focus();

  /**
   * Raises the window on top of other windows.
   */
  void raise();

  /**
   * Clears the window to the given color.
   *
   * \param color the color to use to clear the window.
   */
  virtual void clear(const color& color) = 0;

  /**
   * Swaps the window buffers.
   */
  virtual void swap_buffers() = 0;

protected:
  /**
   * Window resize callback.
   *
   * This function is called when set_size() is called or when the window is
   * resized by an external event.
   * The default implementation does nothing.
   * Derive classes can override this function to be able to respond to window
   * resizing.
   *
   * \param size the new window size,
   */
  virtual void on_size_change(const vec2u& size) = 0;

private:
  friend void ::hou::event::prv::process(const SDL_Event&);

private:
  impl_type* m_impl;
  image2_rgba m_icon;
};

}  // namespace hou

#endif
