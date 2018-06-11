// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/display_mode.hpp"
#include "hou/sys/system_window.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_system_window : public Test
{};

class test_system_window_death_test : public test_system_window
{};

}  // namespace



TEST_F(test_system_window, creation)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_NE(nullptr, w.get_impl());
  EXPECT_NE(0u, w.get_uid());

  EXPECT_LT(w.get_display_index(), display::get_count());
  display::mode curr_mode = display::get_current_mode(w.get_display_index());
  display::mode w_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display::mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));
  EXPECT_EQ(w_mode, w.get_display_mode());
  EXPECT_EQ(window_mode::windowed, w.get_mode());

  EXPECT_EQ(u8"TestWindow", w.get_title());
  EXPECT_EQ(image2_rgba(), w.get_icon());

  EXPECT_EQ(vec2u(32u, 64u), w.get_size());
  EXPECT_EQ(vec2u::zero(), w.get_min_size());
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



TEST_F(test_system_window, move_constructor)
{
  system_window w_dummy(u8"TestWindow", vec2u(32u, 64u));
  window_impl* impl = w_dummy.get_impl();
  uint32_t uid = w_dummy.get_uid();
  system_window w(std::move(w_dummy));
  EXPECT_EQ(impl, w.get_impl());
  EXPECT_EQ(uid, w.get_uid());
  EXPECT_PRECOND_ERROR(w_dummy.get_impl());
  EXPECT_EQ(0u, w_dummy.get_uid());
}



TEST_F(test_system_window, display_mode)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  display::mode curr_mode = display::get_current_mode(w.get_display_index());
  display::mode default_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display::mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));

  EXPECT_EQ(default_mode, w.get_display_mode());

  display::mode custom_mode(vec2u(64u, 128u), display::format::unknown, 30u);
  w.set_display_mode(custom_mode);
  EXPECT_EQ(
    display::get_closest_supported_mode(w.get_display_index(), custom_mode),
    w.get_display_mode());

  w.set_default_display_mode();
  EXPECT_EQ(default_mode, w.get_display_mode());
}



TEST_F(test_system_window, default_display_mode_change_on_resize)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  display::mode curr_mode = display::get_current_mode(w.get_display_index());

  display::mode default_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display::mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));

  EXPECT_EQ(default_mode, w.get_display_mode());

  w.set_size(vec2u(800u, 600u));
  display::mode new_mode
    = display::get_closest_supported_mode(w.get_display_index(),
      display::mode(
        w.get_size(), curr_mode.get_format(), curr_mode.get_refresh_rate()));

  EXPECT_NE(default_mode, new_mode);
  EXPECT_EQ(new_mode, w.get_display_mode());
}



TEST_F(test_system_window, mode)
{
  system_window w(u8"TestWindow", vec2u(640u, 480u));
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



TEST_F(test_system_window, title)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(u8"TestWindow", w.get_title());
  w.set_title(u8"NewTitle");
  EXPECT_EQ(u8"NewTitle", w.get_title());
}



TEST_F(test_system_window, icon)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(image2_rgba(), w.get_icon());
  image2_rgba icon(vec2u(16u, 16u), pixel_rgba(color::red()));
  w.set_icon(icon);
  EXPECT_EQ(icon, w.get_icon());
}



TEST_F(test_system_window, size)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(vec2u(32u, 64u), w.get_size());
  w.set_size(vec2u(8u, 32u));
  EXPECT_EQ(vec2u(8u, 32u), w.get_size());
}



TEST_F(test_system_window, min_size)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_EQ(vec2u::zero(), w.get_min_size());
  w.set_min_size(vec2u(6u, 10u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_min_size());
}



TEST_F(test_system_window, min_size_auto_resizing)
{
  system_window w(u8"TestWindow", vec2u(8u, 8u));

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



TEST_F(test_system_window, max_size)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  uint max_int = narrow_cast<uint>(std::numeric_limits<int>::max());
  EXPECT_EQ(vec2u(max_int, max_int), w.get_max_size());
  w.set_max_size(vec2u(6u, 10u));
  EXPECT_EQ(vec2u(6u, 10u), w.get_max_size());
}



TEST_F(test_system_window, max_size_auto_resizing)
{
  system_window w(u8"TestWindow", vec2u(8u, 8u));

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



TEST_F(test_system_window, position)
{
  system_window w(u8"TestWindow", vec2u(16u, 8u));

  recti bounds = display::get_usable_bounds(w.get_display_index());
  EXPECT_EQ(bounds.get_position() + (bounds.get_size() - vec2i(16, 8)) / 2,
    w.get_position());
  w.set_position(vec2i(8, 32));
  EXPECT_EQ(vec2i(8, 32), w.get_position());
}



TEST_F(test_system_window, visibility)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_visible());
  w.hide();
  EXPECT_FALSE(w.is_visible());
  w.show();
  EXPECT_TRUE(w.is_visible());
  w.show();
  EXPECT_TRUE(w.is_visible());
  w.hide();
  EXPECT_FALSE(w.is_visible());
}



TEST_F(test_system_window, maximization_on_resizable_window)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));
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



TEST_F(test_system_window, maximization_on_not_resizable_window)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));
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



TEST_F(test_system_window, minimization)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_minimized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());

  w.minimize();
  EXPECT_TRUE(w.is_minimized());

  w.restore();
  EXPECT_FALSE(w.is_minimized());
}



TEST_F(test_system_window, minimization_and_maximization)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));
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



TEST_F(test_system_window, test_grab)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  w.show();
  w.raise();

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



TEST_F(test_system_window, test_resizable)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_resizable());
  w.set_resizable(true);
  EXPECT_TRUE(w.is_resizable());
  w.set_resizable(false);
  EXPECT_FALSE(w.is_resizable());
}



TEST_F(test_system_window, test_bordered)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));

  EXPECT_FALSE(w.is_bordered());
  w.set_bordered(true);
  EXPECT_TRUE(w.is_bordered());
  w.set_bordered(false);
  EXPECT_FALSE(w.is_bordered());
}



TEST_F(test_system_window, test_raise)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));
  w.raise();
  SUCCEED();
}



TEST_F(test_system_window, impl_data)
{
  system_window w(u8"TestWindow", vec2u(32u, 64u));
  EXPECT_EQ(&w, &(window::get_impl_window(w.get_impl())));
}
