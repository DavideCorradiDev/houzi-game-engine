// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/mouse_buttons_state.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_mouse_buttons_state : public Test
{};

}  // namespace



TEST_F(test_mouse_buttons_state, default_constructor)
{
  mouse_buttons_state mbs;
  EXPECT_EQ(0u, mbs.get());
}



TEST_F(test_mouse_buttons_state, constructor)
{
  mouse_buttons_state::bitfield_type state_ref = 42u;
  mouse_buttons_state mbs(state_ref);
  EXPECT_EQ(state_ref, mbs.get());
}



TEST_F(test_mouse_buttons_state, check)
{
  std::vector<mouse_button> buttons = {mouse_button::lb, mouse_button::mb,
    mouse_button::rb, mouse_button::xb1, mouse_button::xb2};

  for(auto button : buttons)
  {
    mouse_buttons_state mbs(1 << (static_cast<uint32_t>(button) - 1u));
    for(auto checked_button : buttons)
    {
      EXPECT_EQ(checked_button == button, mbs.check(checked_button));
    }
  }
}



TEST_F(test_mouse_buttons_state, comparison)
{
  mouse_buttons_state mb0(3u);
  mouse_buttons_state mb1(mb0);
  mouse_buttons_state mb2(5u);

  EXPECT_TRUE(mb0 == mb1);
  EXPECT_FALSE(mb0 == mb2);

  EXPECT_FALSE(mb0 != mb1);
  EXPECT_TRUE(mb0 != mb2);
}



TEST_F(test_mouse_buttons_state, output_stream_operator)
{
  EXPECT_OUTPUT("none", mouse_buttons_state(0));

  EXPECT_OUTPUT("lb",
    mouse_buttons_state(1 << (static_cast<uint32_t>(mouse_button::lb) - 1u)));
  EXPECT_OUTPUT("mb",
    mouse_buttons_state(1 << (static_cast<uint32_t>(mouse_button::mb) - 1u)));
  EXPECT_OUTPUT("rb",
    mouse_buttons_state(1 << (static_cast<uint32_t>(mouse_button::rb) - 1u)));
  EXPECT_OUTPUT("xb1",
    mouse_buttons_state(1 << (static_cast<uint32_t>(mouse_button::xb1) - 1u)));
  EXPECT_OUTPUT("xb2",
    mouse_buttons_state(1 << (static_cast<uint32_t>(mouse_button::xb2) - 1u)));

  EXPECT_OUTPUT("lb | rb",
    mouse_buttons_state((1 << (static_cast<uint32_t>(mouse_button::lb) - 1u))
      + (1 << (static_cast<uint32_t>(mouse_button::rb) - 1u))));
  EXPECT_OUTPUT("mb | xb1",
    mouse_buttons_state((1 << (static_cast<uint32_t>(mouse_button::mb) - 1u))
      + (1 << (static_cast<uint32_t>(mouse_button::xb1) - 1u))));
  EXPECT_OUTPUT("lb | mb | rb",
    mouse_buttons_state((1 << (static_cast<uint32_t>(mouse_button::lb) - 1u))
      + (1 << (static_cast<uint32_t>(mouse_button::mb) - 1u))
      + (1 << (static_cast<uint32_t>(mouse_button::rb) - 1u))));
}
