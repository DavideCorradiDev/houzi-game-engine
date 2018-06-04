// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/test_sys_base.hpp"

#include "hou/sys/monitor.hpp"
#include "hou/sys/sys_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_monitor : public test_sys_base
{};

using test_monitor_death_test = test_monitor;

}  // namespace



TEST_F(test_monitor, get_count)
{
  EXPECT_LT(0u, monitor::get_count());
}



TEST_F(test_monitor, get_name)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    EXPECT_NE("", monitor::get_name(i));
  }
}



TEST_F(test_monitor, get_physical_size)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    EXPECT_NE(vec2u::zero(), monitor::get_physical_size(i));
  }
}



TEST_F(test_monitor, get_physical_size_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_physical_size(monitor::get_count()),
    invalid_monitor_id, monitor::get_count());
}



TEST_F(test_monitor_death_test, get_name_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_name(monitor::get_count()), invalid_monitor_id,
    monitor::get_count());
}



TEST_F(test_monitor, get_position)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    monitor::get_position(i);
    SUCCEED();
  }
}



TEST_F(test_monitor_death_test, get_position_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_position(monitor::get_count()),
    invalid_monitor_id, monitor::get_count());
}



TEST_F(test_monitor, get_size)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    EXPECT_NE(vec2u::zero(), monitor::get_size(i));
  }
}



TEST_F(test_monitor, get_size_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_size(monitor::get_count()), invalid_monitor_id,
    monitor::get_count());
}



TEST_F(test_monitor, get_depth_bit_count)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    EXPECT_NE(0u, monitor::get_depth_bit_count(i));
  }
}



TEST_F(test_monitor, get_depth_bit_count_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_depth_bit_count(monitor::get_count()),
    invalid_monitor_id, monitor::get_count());
}



TEST_F(test_monitor, get_refresh_rate)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    EXPECT_NE(0u, monitor::get_refresh_rate(i));
  }
}



TEST_F(test_monitor, get_refresh_rate_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_refresh_rate(monitor::get_count()),
    invalid_monitor_id, monitor::get_count());
}



TEST_F(test_monitor, get_video_mode)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    video_mode vm = monitor::get_video_mode(i);
    EXPECT_NE(vec2u::zero(), vm.get_size());
    EXPECT_NE(0u, vm.get_depth_bit_count());
    EXPECT_NE(0u, vm.get_refresh_rate());
  }
}



TEST_F(test_monitor, get_video_mode_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_video_mode(monitor::get_count()),
    invalid_monitor_id, monitor::get_count());
}



TEST_F(test_monitor, get_supported_video_modes)
{
  for(uint i = 0; i < monitor::get_count(); ++i)
  {
    std::set<video_mode> modes = monitor::get_supported_video_modes(i);
    for(const auto& vm : modes)
    {
      EXPECT_NE(vec2u::zero(), vm.get_size());
      EXPECT_NE(0u, vm.get_depth_bit_count());
      EXPECT_NE(0u, vm.get_refresh_rate());
    }
  }
}



TEST_F(test_monitor, get_supported_video_modes_error_invalid_id)
{
  EXPECT_ERROR_N(monitor::get_supported_video_modes(monitor::get_count()),
    invalid_monitor_id, monitor::get_count());
}
