// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/mouse.hpp"
#include "hou/sys/window.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_mouse : public Test
{};

}  // namespace



TEST_F(test_mouse, cursor_visibility)
{
  EXPECT_TRUE(mouse::is_cursor_visible());
  mouse::set_cursor_visible(false);
  EXPECT_FALSE(mouse::is_cursor_visible());
  mouse::set_cursor_visible(true);
  EXPECT_TRUE(mouse::is_cursor_visible());
}



TEST_F(test_mouse, relative_mode)
{
  EXPECT_FALSE(mouse::is_relative_mode());
  mouse::set_relative_mode(true);
  EXPECT_TRUE(mouse::is_relative_mode());
  mouse::set_relative_mode(false);
  EXPECT_FALSE(mouse::is_relative_mode());
}



TEST_F(test_mouse, global_and_window_position)
{
  window w("MouseTest", vec2u(32u, 16u));

  EXPECT_EQ(mouse::get_position(), w.get_position() + mouse::get_position(w));
}



TEST_F(test_mouse, set_global_position)
{
  vec2i old_pos = mouse::get_position();
  vec2i new_pos = vec2i(16, 32);
  mouse::set_position(new_pos);
  EXPECT_EQ(new_pos, mouse::get_position());
  mouse::set_position(old_pos);
}



TEST_F(test_mouse, set_window_position)
{
  window w("MouseTest", vec2u(32u, 16u));
  w.set_visible(true);
  vec2i old_pos = mouse::get_position(w);
  vec2i new_pos = vec2i(16, 32);
  mouse::set_position(new_pos, w);
  EXPECT_EQ(new_pos, mouse::get_position(w));
  mouse::set_position(old_pos, w);
}



TEST_F(test_mouse, get_position_delta)
{
  // The relative mouse position is altered only with proper physical mouse
  // movement.
  mouse::get_position_delta();
  EXPECT_EQ(vec2i::zero(), mouse::get_position_delta());
}
