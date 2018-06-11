// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/sys/event.hpp"
#include "hou/sys/system_window.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_event : public Test
{
public:
  void TearDown() override;
};



void test_event::TearDown()
{
  EXPECT_TRUE(event::queue_empty());
}

}  // namespace



TEST_F(test_event, queue_empty)
{
  EXPECT_TRUE(event::queue_empty());

  event::generate_quit();
  event::generate_quit();
  event::generate_quit();
  EXPECT_FALSE(event::queue_empty());

  EXPECT_TRUE(event::process_next());
  EXPECT_FALSE(event::queue_empty());

  EXPECT_TRUE(event::process_next());
  EXPECT_FALSE(event::queue_empty());

  EXPECT_TRUE(event::process_next());
  EXPECT_TRUE(event::queue_empty());

  event::generate_quit();
  event::generate_quit();
  event::generate_quit();
  EXPECT_FALSE(event::queue_empty());
  event::process_all();
  EXPECT_TRUE(event::queue_empty());

  event::generate_quit();
  event::generate_quit();
  event::generate_quit();
  EXPECT_FALSE(event::queue_empty());
  event::flush_all();
  EXPECT_TRUE(event::queue_empty());
}



TEST_F(test_event, process_next)
{
  int counter = 0;
  auto f = [&counter](event::timestamp)
  {
    ++counter;
  };
  event::set_quit_callback(f);

  event::generate_quit();
  event::generate_quit();
  event::generate_quit();

  EXPECT_EQ(0, counter);

  EXPECT_TRUE(event::process_next());
  EXPECT_EQ(1, counter);

  EXPECT_TRUE(event::process_next());
  EXPECT_EQ(2, counter);

  EXPECT_TRUE(event::process_next());
  EXPECT_EQ(3, counter);

  EXPECT_FALSE(event::process_next());
}



TEST_F(test_event, process_all)
{
  int counter = 0;
  auto f = [&counter](event::timestamp)
  {
    ++counter;
  };
  event::set_quit_callback(f);

  event::generate_quit();
  event::generate_quit();
  event::generate_quit();

  EXPECT_EQ(0, counter);

  event::process_all();
  EXPECT_EQ(3, counter);
}



TEST_F(test_event, flush_all)
{
  int counter = 0;
  auto f = [&counter](event::timestamp)
  {
    ++counter;
  };
  event::set_quit_callback(f);

  event::generate_quit();
  event::generate_quit();
  event::generate_quit();

  EXPECT_EQ(0, counter);

  event::flush_all();
  EXPECT_EQ(0, counter);
}



TEST_F(test_event, quit_event)
{
  int counter = 0;
  event::timestamp t(0);
  auto f = [&](event::timestamp t_in)
  {
    ++counter;
    t = t_in;
  };

  event::generate_quit();
  event::process_next();
  EXPECT_EQ(0, counter);
  EXPECT_EQ(event::timestamp(0), t);

  event::set_quit_callback(f);
  event::generate_quit();
  event::process_next();
  EXPECT_EQ(1, counter);
  EXPECT_NE(event::timestamp(0), t);

  event::set_quit_callback(nullptr);
  event::generate_quit();
  event::process_next();
  EXPECT_EQ(1, counter);
  EXPECT_NE(event::timestamp(0), t);
}
