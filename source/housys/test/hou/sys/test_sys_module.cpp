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
  sys_module::teardown();
}



test_sys_module::~test_sys_module()
{
  sys_module::teardown();
}

}  // namespace



TEST_F(test_sys_module, setup)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::setup());
  EXPECT_TRUE(sys_module::is_initialized());
}



TEST_F(test_sys_module, double_setup)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::setup());
  EXPECT_TRUE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::setup());
  EXPECT_TRUE(sys_module::is_initialized());
}



TEST_F(test_sys_module, teardown_before_setup)
{
  EXPECT_FALSE(sys_module::is_initialized());
  sys_module::teardown();
  EXPECT_FALSE(sys_module::is_initialized());
}



TEST_F(test_sys_module, teardown_after_setup)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::setup());
  EXPECT_TRUE(sys_module::is_initialized());
  sys_module::teardown();
  EXPECT_FALSE(sys_module::is_initialized());
}



TEST_F(test_sys_module, setup_after_teardown)
{
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::setup());
  EXPECT_TRUE(sys_module::is_initialized());
  sys_module::teardown();
  EXPECT_FALSE(sys_module::is_initialized());
  EXPECT_TRUE(sys_module::setup());
  EXPECT_TRUE(sys_module::is_initialized());
}
