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

#include "hou/mth/matrix.hpp"



struct SDL_Window;

namespace hou
{

namespace display
{

class mode;

}

class color;

using window_impl = SDL_Window;

class HOU_SYS_API window : public non_copyable
{
public:
  static window& get_impl_window(not_null<const window_impl*> impl);

public:
  window(const std::string& title, const vec2u& size);

  window(window&& other);

  virtual ~window() = 0;

  not_null<window_impl*> get_impl();

  uint32_t get_uid() const noexcept;

  uint get_display_index() const;

  display::mode get_display_mode() const;
  void set_display_mode(const display::mode& mode);
  void set_default_display_mode();

  window_mode get_mode() const;
  void set_mode(window_mode mode) const;

  std::string get_title() const;
  void set_title(const std::string& title);

  // Returns an empty image if unset.
  const image2_rgba& get_icon() const noexcept;
  void set_icon(const image2_rgba& icon);

  vec2u get_size() const;
  void set_size(const vec2u& size);

  vec2u get_min_size() const;
  void set_min_size(const vec2u& min_size);

  vec2u get_max_size() const;
  void set_max_size(const vec2u& min_size);

  vec2i get_position() const;
  void set_position(const vec2i& position);

  bool is_visible() const;
  void hide();
  // Should process the event queue to correctly update the state afterwards.
  void show();

  // The flag is not properly set after calling minimize.
  // The flag is set only after processing the event queue.
  // Moreover, it is necessary to wait a bit for the event to be registered.
  bool is_minimized() const;
  // The flag is not properly set after calling maximize.
  // The flag is set only after processing the event queue.
  // Moreover, it is necessary to wait a bit for the event to be registered.
  bool is_maximized() const;
  void minimize();
  // Will do nothing if the window is not resizable.
  void maximize();
  // Minimized windows will be restored only after the minimized flag has been
  // properly set. This requires processing the event queue.
  // Restoring a minimized window doesn't seem to actually restore it.
  void restore();

  bool get_grab() const;
  // Works only if the window is visible and with focus.
  void set_grab(bool value);

  bool is_resizable() const;
  void set_resizable(bool value);

  bool is_bordered() const;
  void set_bordered(bool value);

  void clear(const color& color);
  bool focus();
  void raise();

private:
  window_impl* m_impl;
  uint32_t m_uid;
  image2_rgba m_icon;
};

}  // namespace hou

#endif
