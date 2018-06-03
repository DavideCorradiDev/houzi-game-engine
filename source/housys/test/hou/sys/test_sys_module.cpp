// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/sys_module.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_sys_module : public Test
{
public:
  test_sys_module();
  ~test_sys_module();
};



test_sys_module::test_sys_module()
{
  sys_module::terminate();
}



test_sys_module::~test_sys_module()
{
  sys_module::terminate();
}

}  // namespace



TEST_F(test_sys_module, initialize)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::initialize());
  EXPECT_TRUE(sys_module::is_initialized());
}



TEST_F(test_sys_module, double_initialize)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::initialize());
  EXPECT_TRUE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::initialize());
  EXPECT_TRUE(sys_module::is_initialized());
}



TEST_F(test_sys_module, terminate_before_initialize)
{
  EXPECT_FALSE(sys_module::is_initialized());
  sys_module::terminate();
  EXPECT_FALSE(sys_module::is_initialized());
}



TEST_F(test_sys_module, terminate_after_initialize)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::initialize());
  EXPECT_TRUE(sys_module::is_initialized());
  sys_module::terminate();
  EXPECT_FALSE(sys_module::is_initialized());
}



TEST_F(test_sys_module, initialize_after_terminate)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::initialize());
  EXPECT_TRUE(sys_module::is_initialized());
  sys_module::terminate();
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::initialize());
  EXPECT_TRUE(sys_module::is_initialized());
}
