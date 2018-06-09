// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/display.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_display : public Test
{};

using test_display_death_test = test_display;

}  // namespace



TEST_F(test_display, get_current_video_driver)
{
  EXPECT_NE("", display::get_current_video_driver());
}



TEST_F(test_display, get_available_video_drivers)
{
  std::set<std::string> video_drivers = display::get_available_video_drivers();
  EXPECT_GE(video_drivers.size(), 1u);
  for(const auto& video_driver : video_drivers)
  {
    EXPECT_NE("", video_driver);
  }
}



TEST_F(test_display, get_count)
{
  EXPECT_GE(display::get_count(), 1u);
}



TEST_F(test_display, get_name)
{
  for(uint i = 0u; i < display::get_count(); ++i)
  {
    EXPECT_NE("", display::get_name(i));
  }
}



TEST_F(test_display_death_test, get_name_error)
{
  std::stringstream err_msg;
  err_msg << "displayIndex must be in the range 0 - "
          << display::get_count() - 1;
  EXPECT_ERROR_N(
    display::get_name(display::get_count()), platform_error, err_msg.str());
}



TEST_F(test_display, get_bounds)
{
  for(uint i = 0u; i < display::get_count(); ++i)
  {
    EXPECT_NE(recti(), display::get_bounds(i));
  }
}



TEST_F(test_display_death_test, get_bounds_error)
{
  std::stringstream err_msg;
  err_msg << "displayIndex must be in the range 0 - "
          << display::get_count() - 1;
  EXPECT_ERROR_N(
    display::get_bounds(display::get_count()), platform_error, err_msg.str());
}



TEST_F(test_display, get_usable_bounds)
{
  for(uint i = 0u; i < display::get_count(); ++i)
  {
    EXPECT_NE(recti(), display::get_usable_bounds(i));
  }
}



TEST_F(test_display_death_test, get_usable_bounds_error)
{
  std::stringstream err_msg;
  err_msg << "displayIndex must be in the range 0 - "
          << display::get_count() - 1;
  EXPECT_ERROR_N(display::get_usable_bounds(display::get_count()),
    platform_error, err_msg.str());
}



TEST_F(test_display, get_current_mode)
{
  for(uint i = 0u; i < display::get_count(); ++i)
  {
    EXPECT_NE(display::mode(), display::get_current_mode(i));
  }
}



TEST_F(test_display_death_test, get_current_mode_error)
{
  std::stringstream err_msg;
  err_msg << "displayIndex must be in the range 0 - "
          << display::get_count() - 1;
  EXPECT_ERROR_N(display::get_current_mode(display::get_count()),
    platform_error, err_msg.str());
}



TEST_F(test_display, get_supported_modes)
{
  for(uint i = 0u; i < display::get_count(); ++i)
  {
    std::set<display::mode> modes = display::get_supported_modes(i);
    for(const auto& mode : modes)
    {
      EXPECT_NE(display::mode(), mode);
    }
  }
}



TEST_F(test_display, get_closest_supported_mode)
{
  display::mode invalid_mode(vec2u(33u, 88u), display::pixel_format(), 23u);
  for(uint i = 0; i < display::get_count(); ++i)
  {
    display::mode valid_mode
      = display::get_closest_supported_mode(i, invalid_mode);
    EXPECT_THAT(display::get_supported_modes(i), Contains(valid_mode));
  }
}



TEST_F(test_display_death_test, get_supported_modes)
{
  std::stringstream err_msg;
  err_msg << "displayIndex must be in the range 0 - "
          << display::get_count() - 1;
  EXPECT_ERROR_N(display::get_supported_modes(display::get_count()),
    platform_error, err_msg.str());
}
