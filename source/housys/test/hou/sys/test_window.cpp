// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/display_mode.hpp"
#include "hou/sys/event.hpp"
#include "hou/sys/window.hpp"

#include <thread>

using namespace hou;
using namespace testing;



namespace
{

class test_window : public Test
{};

class test_window_death_test : public test_window
{};

}  // namespace



TEST_F(test_window, creation)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_NE(nullptr, w.get_impl());
  EXPECT_NE(0u, w.get_uid());

  EXPECT_LT(w.get_display_index(), display::get_count());
  display_mode curr_mode = display::get_current_mode(w.get_display_index());
  display_mode w_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display_mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));
  EXPECT_EQ(w_mode, w.get_display_mode());
  EXPECT_EQ(window_mode::windowed, w.get_mode());

  EXPECT_EQ(u8"TestWindow", w.get_title());
  EXPECT_EQ(image2_rgba(), w.get_icon());

  EXPECT_EQ(vec2u(32u, 64u), w.get_size());
  EXPECT_EQ(vec2u(1u, 1u), w.get_min_size());
  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  EXPECT_EQ(vec2u(max_int, max_int), w.get_max_size());
  recti bounds = display::get_usable_bounds(w.get_display_index());
  EXPECT_EQ(bounds.get_position() + (bounds.get_size() - vec2i(32, 64)) / 2,
    w.get_position());

  EXPECT_FALSE(w.is_visible());
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());
  EXPECT_FALSE(w.get_grab());
  EXPECT_FALSE(w.is_resizable());
  EXPECT_FALSE(w.is_bordered());
}



TEST_F(test_window_death_test, null_size_creation)
{
  EXPECT_PRECOND_ERROR(window w(u8"TestWindow", vec2u(8u, 0u)));
  EXPECT_PRECOND_ERROR(window w(u8"TestWindow", vec2u(0u, 8u)));
  EXPECT_PRECOND_ERROR(window w(u8"TestWindow", vec2u(0u, 0u)));
}



TEST_F(test_window, move_constructor)
{
  window w_dummy(u8"TestWindow", vec2u(32u, 64u));
  not_null<window::impl_type*> impl = w_dummy.get_impl();
  window::uid_type uid = w_dummy.get_uid();
  window w(std::move(w_dummy));
  EXPECT_EQ(impl, w.get_impl());
  EXPECT_EQ(uid, w.get_uid());
  EXPECT_EQ(nullptr, w_dummy.get_impl());
  EXPECT_EQ(0u, w_dummy.get_uid());
}



TEST_F(test_window, move_constructor_get_from_uid)
{
  window w_dummy(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_EQ(&w_dummy, &window::get_from_uid(w_dummy.get_uid()));
  window w(std::move(w_dummy));
  EXPECT_EQ(&w, &window::get_from_uid(w.get_uid()));
}



TEST_F(test_window, move_constructor_get_from_impl)
{
  window w_dummy(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_EQ(&w_dummy, &window::get_from_impl(w_dummy.get_impl()));
  window w(std::move(w_dummy));
  EXPECT_EQ(&w, &window::get_from_impl(w.get_impl()));
}



TEST_F(test_window, display_mode)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  display_mode curr_mode = display::get_current_mode(w.get_display_index());
  display_mode default_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display_mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));

  EXPECT_EQ(default_mode, w.get_display_mode());

  display_mode custom_mode(vec2u(64u, 128u), display_format::unknown, 30u);
  w.set_display_mode(custom_mode);
  EXPECT_EQ(
    display::get_closest_supported_mode(w.get_display_index(), custom_mode),
    w.get_display_mode());

  w.set_default_display_mode();
  EXPECT_EQ(default_mode, w.get_display_mode());
}



TEST_F(test_window, default_display_mode_change_on_resize)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  display_mode curr_mode = display::get_current_mode(w.get_display_index());

  display_mode default_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display_mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));

  EXPECT_EQ(default_mode, w.get_display_mode());

  w.set_size(vec2u(800u, 600u));
  display_mode new_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display_mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));

  EXPECT_NE(default_mode, new_mode);
  EXPECT_EQ(new_mode, w.get_display_mode());
}



TEST_F(test_window, mode)
{
  window w(u8"TestWindow", vec2u(640u, 480u));
  EXPECT_EQ(window_mode::windowed, w.get_mode());

  w.set_mode(window_mode::desktop_fullscreen);
  EXPECT_EQ(window_mode::desktop_fullscreen, w.get_mode());

  w.set_mode(window_mode::windowed);
  EXPECT_EQ(window_mode::windowed, w.get_mode());

  w.set_mode(window_mode::fullscreen);
  EXPECT_EQ(window_mode::fullscreen, w.get_mode());

  w.set_mode(window_mode::windowed);
  EXPECT_EQ(window_mode::windowed, w.get_mode());

  w.set_mode(window_mode::desktop_fullscreen);
  EXPECT_EQ(window_mode::desktop_fullscreen, w.get_mode());

  w.set_mode(window_mode::fullscreen);
  EXPECT_EQ(window_mode::fullscreen, w.get_mode());

  w.set_mode(window_mode::desktop_fullscreen);
  EXPECT_EQ(window_mode::desktop_fullscreen, w.get_mode());

  w.set_mode(window_mode::windowed);
  EXPECT_EQ(window_mode::windowed, w.get_mode());
}



TEST_F(test_window, title)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(u8"TestWindow", w.get_title());
  w.set_title(u8"NewTitle");
  EXPECT_EQ(u8"NewTitle", w.get_title());
}



TEST_F(test_window, icon)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(image2_rgba(), w.get_icon());
  image2_rgba icon(vec2u(16u, 16u), pixel_rgba(color::red()));
  w.set_icon(icon);
  EXPECT_EQ(icon, w.get_icon());
}



TEST_F(test_window, size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(vec2u(32u, 64u), w.get_size());
  w.set_size(vec2u(8u, 32u));
  EXPECT_EQ(vec2u(8u, 32u), w.get_size());
}



TEST_F(test_window_death_test, set_null_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_PRECOND_ERROR(w.set_size(vec2u(0u, 8u)));
  EXPECT_PRECOND_ERROR(w.set_size(vec2u(8u, 0u)));
  EXPECT_PRECOND_ERROR(w.set_size(vec2u(0u, 0u)));
}



TEST_F(test_window, min_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(vec2u(1u, 1u), w.get_min_size());
  w.set_min_size(vec2u(6u, 10u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_min_size());
}



TEST_F(test_window, set_size_below_min_size_x)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  w.set_min_size(vec2u(6u, 10u));
  w.set_size(vec2u(5u, 11u));
  EXPECT_EQ(vec2u(6u, 11u), w.get_size());
}



TEST_F(test_window, set_size_below_min_size_y)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  w.set_min_size(vec2u(6u, 10u));
  w.set_size(vec2u(7u, 9u));
  EXPECT_EQ(vec2u(7u, 10u), w.get_size());
}



TEST_F(test_window, set_size_below_min_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  w.set_min_size(vec2u(6u, 10u));
  w.set_size(vec2u(5u, 9u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_size());
}



TEST_F(test_window, min_size_auto_resizing)
{
  window w(u8"TestWindow", vec2u(8u, 8u));

  w.set_min_size(vec2u(16u, 32u));
  EXPECT_EQ(vec2u(16u, 32u), w.get_min_size());
  EXPECT_EQ(vec2u(16u, 32u), w.get_size());

  w.set_min_size(vec2u(64u, 32u));
  EXPECT_EQ(vec2u(64u, 32u), w.get_min_size());
  EXPECT_EQ(vec2u(64u, 32u), w.get_size());

  w.set_min_size(vec2u(64u, 128u));
  EXPECT_EQ(vec2u(64u, 128u), w.get_min_size());
  EXPECT_EQ(vec2u(64u, 128u), w.get_size());
}



TEST_F(test_window, max_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  EXPECT_EQ(vec2u(max_int, max_int), w.get_max_size());
  w.set_max_size(vec2u(6u, 10u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_max_size());
}



TEST_F(test_window, set_size_above_max_size_x)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  w.set_max_size(vec2u(100u, 110u));
  w.set_size(vec2u(101u, 109u));
  EXPECT_EQ(vec2u(100u, 109u), w.get_size());
}



TEST_F(test_window, set_size_above_max_size_y)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  w.set_max_size(vec2u(100u, 110u));
  w.set_size(vec2u(99u, 111u));
  EXPECT_EQ(vec2u(99u, 110u), w.get_size());
}



TEST_F(test_window, set_size_above_max_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  w.set_max_size(vec2u(100u, 110u));
  w.set_size(vec2u(101u, 111u));
  EXPECT_EQ(vec2u(100u, 110u), w.get_size());
}



TEST_F(test_window, max_size_auto_resizing)
{
  window w(u8"TestWindow", vec2u(8u, 8u));

  w.set_max_size(vec2u(6u, 7u));
  EXPECT_EQ(vec2u(6u, 7u), w.get_max_size());
  EXPECT_EQ(vec2u(6u, 7u), w.get_size());

  w.set_max_size(vec2u(5u, 7u));
  EXPECT_EQ(vec2u(5u, 7u), w.get_max_size());
  EXPECT_EQ(vec2u(5u, 7u), w.get_size());

  w.set_max_size(vec2u(5u, 4u));
  EXPECT_EQ(vec2u(5u, 4u), w.get_max_size());
  EXPECT_EQ(vec2u(5u, 4u), w.get_size());
}



TEST_F(test_window_death_test, zero_min_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_PRECOND_ERROR(w.set_min_size(vec2u(0u, 8u)));
  EXPECT_PRECOND_ERROR(w.set_min_size(vec2u(8u, 0u)));
  EXPECT_PRECOND_ERROR(w.set_min_size(vec2u(0u, 0u)));
}



TEST_F(test_window_death_test, set_max_size_error_less_than_min_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.set_min_size(vec2u(16u, 16u));

  EXPECT_PRECOND_ERROR(w.set_max_size(vec2u(8u, 32u)));
  EXPECT_PRECOND_ERROR(w.set_max_size(vec2u(32u, 8u)));
  EXPECT_PRECOND_ERROR(w.set_max_size(vec2u(8u, 8u)));
}



TEST_F(test_window_death_test, set_min_size_error_greater_than_max_size)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.set_max_size(vec2u(8u, 8u));

  EXPECT_PRECOND_ERROR(w.set_min_size(vec2u(16u, 8u)));
  EXPECT_PRECOND_ERROR(w.set_min_size(vec2u(8u, 16u)));
  EXPECT_PRECOND_ERROR(w.set_min_size(vec2u(16u, 16u)));
}



TEST_F(test_window, position)
{
  window w(u8"TestWindow", vec2u(16u, 8u));

  recti bounds = display::get_usable_bounds(w.get_display_index());
  EXPECT_EQ(bounds.get_position() + (bounds.get_size() - vec2i(16, 8)) / 2,
    w.get_position());
  w.set_position(vec2i(8, 32));
  EXPECT_EQ(vec2i(8, 32), w.get_position());
}



TEST_F(test_window, visibility)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_visible());
  w.set_visible(false);
  EXPECT_FALSE(w.is_visible());
  w.set_visible(true);
  EXPECT_TRUE(w.is_visible());
  w.set_visible(true);
  EXPECT_TRUE(w.is_visible());
  w.set_visible(false);
  EXPECT_FALSE(w.is_visible());
}



TEST_F(test_window, maximization_on_resizable_window)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.set_resizable(true);

  EXPECT_TRUE(w.is_resizable());
  EXPECT_FALSE(w.is_maximized());

  w.maximize();
  EXPECT_TRUE(w.is_maximized());

  w.maximize();
  EXPECT_TRUE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_maximized());
}



TEST_F(test_window, maximization_on_not_resizable_window)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.set_resizable(false);

  EXPECT_FALSE(w.is_resizable());
  EXPECT_FALSE(w.is_maximized());

  w.maximize();
  EXPECT_FALSE(w.is_maximized());

  w.maximize();
  EXPECT_FALSE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_maximized());
}



TEST_F(test_window, DISABLED_minimization)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_minimized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
}



TEST_F(test_window, DISABLED_minimization_and_maximization)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.set_resizable(true);

  EXPECT_TRUE(w.is_resizable());
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.maximize();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_TRUE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());

  w.minimize();

  w.maximize();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_TRUE(w.is_maximized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());
  EXPECT_TRUE(w.is_maximized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
  EXPECT_FALSE(w.is_maximized());
}



TEST_F(test_window, grab)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  // After showing the window, all events need to be processed to correctly
  // update the window.
  w.set_visible(true);
  event::process_all();

  // The window needs focus to be able to grab the input.
  w.raise();
  w.focus();

  EXPECT_FALSE(w.get_grab());
  w.set_grab(false);
  EXPECT_FALSE(w.get_grab());
  w.set_grab(true);
  EXPECT_TRUE(w.get_grab());
  w.set_grab(true);
  EXPECT_TRUE(w.get_grab());
  w.set_grab(false);
  EXPECT_FALSE(w.get_grab());
}



TEST_F(test_window, resizable)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_resizable());
  w.set_resizable(true);
  EXPECT_TRUE(w.is_resizable());
  w.set_resizable(false);
  EXPECT_FALSE(w.is_resizable());
}



TEST_F(test_window, bordered)
{
  window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_bordered());
  w.set_bordered(true);
  EXPECT_TRUE(w.is_bordered());
  w.set_bordered(false);
  EXPECT_FALSE(w.is_bordered());
}



TEST_F(test_window, focus_success)
{
  // The window is visible, focusing it will succeed.
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.set_visible(true);
  event::process_all();
  EXPECT_TRUE(w.focus());
  EXPECT_TRUE(w.has_keyboard_focus());
  EXPECT_TRUE(w.has_mouse_focus());
}



TEST_F(test_window, focus_failure)
{
  // The window is not visible, focusing it will fail.
  window w(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_FALSE(w.focus());
  EXPECT_FALSE(w.has_keyboard_focus());
  EXPECT_FALSE(w.has_mouse_focus());
}



TEST_F(test_window, raise)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.raise();
  SUCCEED();
}



TEST_F(test_window, get_from_impl)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_EQ(&w, &(window::get_from_impl(w.get_impl())));
}



TEST_F(test_window, get_from_uid)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_EQ(&w, &(window::get_from_uid(w.get_uid())));
}



TEST_F(test_window, clear)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.clear(color::black());
}



TEST_F(test_window, swap_buffers)
{
  window w(u8"TestWindow", vec2u(32u, 64u));
  w.swap_buffers();
}
