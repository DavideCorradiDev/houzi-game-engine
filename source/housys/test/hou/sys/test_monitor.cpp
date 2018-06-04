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
