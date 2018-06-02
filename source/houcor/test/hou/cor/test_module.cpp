// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/module.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_impl
{
public:
  // These functions are required by hou::module.
  static bool on_setup();
  static void on_teardown() noexcept;

  // These functions just used for testing.
  static void reset();
  static void set_setup_return(bool value);

private:
  static bool s_setup_return;
};



class test_module : public Test
{
public:
  test_module();
};



bool test_impl::on_setup()
{
  if(!s_setup_return)
  {
    return false;
  }
  return true;
}



void test_impl::on_teardown() noexcept
{
}



void test_impl::reset()
{
  test_impl::set_setup_return(true);
  test_impl::on_teardown();
}



void test_impl::set_setup_return(bool value)
{
  s_setup_return = value;
}



bool test_impl::s_setup_return(true);



test_module::test_module()
{
  test_impl::reset();
  module<test_impl>::teardown();
}

}



TEST_F(test_module, starting_state)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, setup)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, double_setup)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, failed_setup)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  test_impl::set_setup_return(false);
  EXPECT_FALSE(module<test_impl>::setup());
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, failed_redundant_setup)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  test_impl::set_setup_return(false);
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, teardown_after_setup)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  module<test_impl>::teardown();
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, teardown_before_setup)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  module<test_impl>::teardown();
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, setup_after_teardown)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  module<test_impl>::teardown();
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, double_teardown)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::setup());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  module<test_impl>::teardown();
  EXPECT_FALSE(module<test_impl>::is_initialized());
  module<test_impl>::teardown();
  EXPECT_FALSE(module<test_impl>::is_initialized());
}
