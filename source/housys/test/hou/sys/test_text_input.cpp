// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/mth/rectangle.hpp"

#include "hou/sys/text_input.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_text_input : public Test
{};

}



TEST_F(test_text_input, is_active)
{
  EXPECT_TRUE(text_input::is_active());
  text_input::stop();
  EXPECT_FALSE(text_input::is_active());
  text_input::start();
  EXPECT_TRUE(text_input::is_active());
}



TEST_F(test_text_input, stop_multiple_times)
{
  EXPECT_TRUE(text_input::is_active());
  text_input::stop();
  EXPECT_FALSE(text_input::is_active());
  text_input::stop();
  EXPECT_FALSE(text_input::is_active());
  text_input::start();
  EXPECT_TRUE(text_input::is_active());
}



TEST_F(test_text_input, start_multiple_times)
{
  EXPECT_TRUE(text_input::is_active());
  text_input::start();
  EXPECT_TRUE(text_input::is_active());
  text_input::start();
  EXPECT_TRUE(text_input::is_active());
}



TEST_F(test_text_input, set_recT)
{
  text_input::set_rect(hou::recti(2, 3, 120, 100));
  SUCCEED();
}
