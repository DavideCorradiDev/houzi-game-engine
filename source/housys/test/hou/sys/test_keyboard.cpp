// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/keyboard.hpp"

using namespace hou;
using namespace testing;

namespace
{

class test_keyboard : public Test
{};

}  // namespace



TEST_F(test_keyboard, has_screen_keyboard_support)
{
#if defined(HOU_SYSTEM_WINDOWS) or defined(HOU_SYSTEM_LINUX)
  EXPECT_FALSE(keyboard::has_screen_keyboard_support());
#endif
}



TEST_F(test_keyboard, modifier_keys)
{
  modifier_keys old_state = keyboard::get_modifier_keys();
  modifier_keys new_state = modifier_keys::alt | modifier_keys::caps;
  keyboard::set_modifier_keys(new_state);
  EXPECT_EQ(new_state, keyboard::get_modifier_keys());
  keyboard::set_modifier_keys(old_state);
}
