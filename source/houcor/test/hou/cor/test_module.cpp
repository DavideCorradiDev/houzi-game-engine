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
  static bool on_initialize();
  static void on_terminate() noexcept;

  // These functions just used for testing.
  static void reset();
  static void set_initialize_return(bool value);

private:
  static bool s_initialize_return;
};



class test_module : public Test
{
public:
  test_module();
  ~test_module();
};



bool test_impl::on_initialize()
{
  if(!s_initialize_return)
  {
    return false;
  }
  return true;
}



void test_impl::on_terminate() noexcept
{}



void test_impl::reset()
{
  test_impl::set_initialize_return(true);
  test_impl::on_terminate();
}



void test_impl::set_initialize_return(bool value)
{
  s_initialize_return = value;
}



bool test_impl::s_initialize_return(true);



test_module::test_module()
{
  test_impl::reset();
  module<test_impl>::terminate();
}



test_module::~test_module()
{
  test_impl::reset();
  module<test_impl>::terminate();
}

}  // namespace



TEST_F(test_module, starting_state)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, initialize)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, double_initialize)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, failed_initialize)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  test_impl::set_initialize_return(false);
  EXPECT_FALSE(module<test_impl>::initialize());
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, failed_redundant_initialize)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  test_impl::set_initialize_return(false);
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, terminate_after_initialize)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  module<test_impl>::terminate();
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, terminate_before_initialize)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  module<test_impl>::terminate();
  EXPECT_FALSE(module<test_impl>::is_initialized());
}



TEST_F(test_module, initialize_after_terminate)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  module<test_impl>::terminate();
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
}



TEST_F(test_module, double_terminate)
{
  EXPECT_FALSE(module<test_impl>::is_initialized());
  EXPECT_TRUE(module<test_impl>::initialize());
  EXPECT_TRUE(module<test_impl>::is_initialized());
  module<test_impl>::terminate();
  EXPECT_FALSE(module<test_impl>::is_initialized());
  module<test_impl>::terminate();
  EXPECT_FALSE(module<test_impl>::is_initialized());
}
