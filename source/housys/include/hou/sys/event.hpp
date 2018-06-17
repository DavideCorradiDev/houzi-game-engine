// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_EVENT_HPP
#define HOU_SYS_EVENT_HPP

#include "hou/sys/keyboard.hpp"
#include "hou/sys/mouse.hpp"
#include "hou/sys/window.hpp"

#include "hou/sys/sys_config.hpp"

#include "hou/cor/std_chrono.hpp"

#include <functional>



namespace hou
{

/**
 * Namespace containing event related functions.
 */
namespace event
{

namespace prv
{

/**
 * Processes an SDL_Event.
 *
 * This function parses the event and calls the corresponding callback, if any
 * was registered.
 * If no callback was registered, nothing happens.
 *
 * This function is used internally and should not be called directly.
 *
 * \param event the SDL event.
 */
HOU_SYS_API void process(const SDL_Event& event);

}  // namespace prv

/**
 * Stops execution until an event is received, and then processes it.
 */
HOU_SYS_API void wait_next();

/**
 * Checks if the event queue is empty.
 *
 * \return true if the event queue is empty, false if at least one event is
 * currently queued.
 */
HOU_SYS_API bool queue_empty();

/**
 * Processes the next event in the queue.
 *
 * If the queue is empty, no processing takes place.
 *
 * \return true if an event was processed, or false if the queue was empty and
 * no event was processed.
 */
HOU_SYS_API bool process_next();

/**
 * Processes all events in the queue.
 */
HOU_SYS_API void process_all();

/**
 * Removes all events from the queue without processing them
 */
HOU_SYS_API void flush_all();

/**
 * Type for timestamps in events.
 *
 * The timestamp always refer to the time passed since the initialization of the
 * system module.
 */
using timestamp = std::chrono::duration<uint32_t, std::milli>;

/**
 * Callback function type for quit events.
 */
using quit_callback = std::function<void(timestamp)>;

/**
 * Callback function type for generic window events.
 */
using window_callback = std::function<void(timestamp, window::uid_type)>;

/**
 * Callback function type for window motion events.
 */
using window_motion_callback
  = std::function<void(timestamp, window::uid_type, const vec2i&)>;

/**
 * Callback function type for window resize events.
 */
using window_resize_callback
  = std::function<void(timestamp, window::uid_type, const vec2u&)>;

/**
 * Callback function type for key events.
 */
using key_callback = std::function<void(
  timestamp, window::uid_type, scan_code, key_code, modifier_keys, bool)>;

/**
 * Callback function type for mouse button events.
 */
using mouse_button_callback = std::function<void(
  timestamp, window::uid_type, mouse_button, uint, const vec2i&)>;

/**
 * Callback function type for mouse wheel events.
 */
using mouse_wheel_callback
  = std::function<void(timestamp, window::uid_type, const vec2i&, bool)>;

/**
 * Callback function type for mouse motion events.
 */
using mouse_motion_callback = std::function<void(timestamp, window::uid_type,
  mouse_buttons_state, const vec2i&, const vec2i&)>;

/**
 * Sets the callback for quit events.
 *
 * Quit events are generated when the application receives a quit request, for
 * example when the user clicks the window X button.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_quit_callback(quit_callback f);

/**
 * Generates an artificial quit event.
 */
HOU_SYS_API void generate_quit();

/**
 * Sets the callback for window closed events.
 *
 * Window closed events are generated when a window object is destroyed or
 * when the user clicks the window X button.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_closed_callback(window_callback f);

/**
 * Generates an artificial window closed event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_closed(const window& w);

/**
 * Sets the callback for window hidden events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_hidden_callback(window_callback f);

/**
 * Generates an artificial window hidden event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_hidden(const window& w);

/**
 * Sets the callback for window shown events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_shown_callback(window_callback f);

/**
 * Generates an artificial window shown event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_shown(const window& w);

/**
 * Sets the callback for window exposed events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_exposed_callback(window_callback f);

/**
 * Generates an artificial window exposed event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_exposed(const window& w);

/**
 * Sets the callback for window minimized events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_minimized_callback(window_callback f);

/**
 * Generates an artificial window minimized event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_minimized(const window& w);

/**
 * Sets the callback for window maximized events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_maximized_callback(window_callback f);

/**
 * Generates an artificial window maximized event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_maximized(const window& w);

/**
 * Sets the callback for window restored events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_restored_callback(window_callback f);

/**
 * Generates an artificial window restored event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_restored(const window& w);

/**
 * Sets the callback for window focus lost events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_focus_lost_callback(window_callback f);

/**
 * Generates an artificial window focus lost event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_focus_lost(const window& w);

/**
 * Sets the callback for window focus gained events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_focus_gained_callback(window_callback f);

/**
 * Generates an artificial window focus gained event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_focus_gained(const window& w);

/**
 * Sets the callback for window focus offered events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_focus_offered_callback(window_callback f);

/**
 * Generates an artificial window focus offered event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_window_focus_offered(const window& w);

/**
 * Sets the callback for window moved events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_moved_callback(window_motion_callback f);

/**
 * Generates an artificial window moved event.
 *
 * \param w the window.
 *
 * \param position the position.
 */
HOU_SYS_API void generate_window_moved(const window& w, const vec2i& position);

/**
 * Sets the callback for window resized events.
 *
 * Window resized events are generated when the window changes size due to
 * external input, for example due to the user dragging the window borders.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_resized_callback(window_resize_callback f);

/**
 * Generates an artificial window resized event.
 *
 * \param w the window.
 *
 * \param size the size.
 */
HOU_SYS_API void generate_window_resized(const window& w, const vec2u& size);

/**
 * Sets the callback for window size changed events.
 *
 * Window size changed events are generated when the window changes size for
 * any reason.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_window_size_changed_callback(window_resize_callback f);

/**
 * Generates an artificial window size changed event.
 *
 * \param w the window.
 *
 * \param size the size.
 */
HOU_SYS_API void generate_window_size_changed(
  const window& w, const vec2u& size);

/**
 * Sets the callback for key pressed events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_key_pressed_callback(key_callback f);

/**
 * Generates an artificial key pressed event.
 *
 * \param w the window.
 *
 * \param sc the scan code.
 *
 * \param kc the key code.
 *
 * \param mk the modifier keys state.
 *
 * \param is_repeat whether this is a key repeat event or not.
 */
HOU_SYS_API void generate_key_pressed(
  const window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat);

/**
 * Sets the callback for key released events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_key_released_callback(key_callback f);

/**
 * Generates an artificial key released event.
 *
 * \param w the window.
 *
 * \param sc the scan code.
 *
 * \param kc the key code.
 *
 * \param mk the modifier keys state.
 *
 * \param is_repeat whether this is a key repeat event or not.
 */
HOU_SYS_API void generate_key_released(
  const window& w, scan_code sc, key_code kc, modifier_keys mk, bool is_repeat);

/**
 * Sets the callback for mouse button pressed events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_mouse_button_pressed_callback(mouse_button_callback f);

/**
 * Generates an artificial mouse button pressed event.
 *
 * \param w the window.
 *
 * \param button the mouse button.
 *
 * \param clicks the number of clicks.
 *
 * \param position the position of the mouse cursor relative to w.
 */
HOU_SYS_API void generate_mouse_button_pressed(
  const window& w, mouse_button button, uint clicks, const vec2i& position);

/**
 * Sets the callback for mouse button released events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_mouse_button_released_callback(mouse_button_callback f);

/**
 * Generates an artificial mouse button released event.
 *
 * \param w the window.
 *
 * \param button the mouse button.
 *
 * \param clicks the number of clicks.
 *
 * \param position the position of the mouse cursor relative to w.
 */
HOU_SYS_API void generate_mouse_button_released(
  const window& w, mouse_button button, uint clicks, const vec2i& position);

/**
 * Sets the callback for mouse wheel moved events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_mouse_wheel_moved_callback(mouse_wheel_callback f);

/**
 * Generates an artificial mouse wheel moved event.
 *
 * \param w the window.
 *
 * \param delta the wheel delta movement. The x() component refers to the
 * horizontal wheel, the y() component to the vertical wheel.
 *
 * \param flipped wheter the values in delta are flipped.
 */
HOU_SYS_API void generate_mouse_wheel_moved(
  const window& w, const vec2i& delta, bool flipped);

/**
 * Sets the callback for mouse moved events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_mouse_moved_callback(mouse_motion_callback f);

/**
 * Generates an artificial mouse moved event.
 *
 * \param w the window.
 *
 * \param mbs the mouse button state.
 *
 * \param position the final position of the mouse cursor relative to w.
 *
 * \param position_delta the difference between the final position of the mouse
 * and the previous position of the mouse.
 */
HOU_SYS_API void generate_mouse_moved(const window& w, mouse_buttons_state mbs,
  const vec2i& position, const vec2i& position_delta);

/**
 * Sets the callback for mouse entered events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_mouse_entered_callback(window_callback f);

/**
 * Generates an artificial mouse entered event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_mouse_entered(const window& w);

/**
 * Sets the callback for mouse left events.
 *
 * \param f the callback.
 */
HOU_SYS_API void set_mouse_left_callback(window_callback f);

/**
 * Generates an artificial mouse left event.
 *
 * \param w the window.
 */
HOU_SYS_API void generate_mouse_left(const window& w);

}  // namespace event

}  // namespace hou

#endif
