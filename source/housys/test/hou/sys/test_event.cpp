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
  auto f = [&counter](event::timestamp) { ++counter; };
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
  auto f = [&counter](event::timestamp) { ++counter; };
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
  auto f = [&counter](event::timestamp) { ++counter; };
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
  auto f = [&](event::timestamp t_in) {
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



TEST_F(test_event, key_pressed_event)
{
  int counter = 0;
  event::timestamp t(0);
  system_window w("EventDemo", vec2u(32u, 16u));
  scan_code sc = scan_code::unknown;
  key_code kc = key_code::unknown;
  modifier_keys mk = modifier_keys::none;
  bool is_repeat = false;

  auto f = [&](event::timestamp t_in, window& w_in, scan_code sc_in,
             key_code kc_in, modifier_keys mk_in, bool is_repeat_in) {
    ++counter;
    t = t_in;
    w_in.set_title("NewTitle");
    sc = sc_in;
    kc = kc_in;
    mk = mk_in;
    is_repeat = is_repeat_in;
  };

  event::flush_all();

  event::generate_key_pressed(
    w, scan_code::w, key_code::a, modifier_keys::alt, true);
  event::process_next();
  EXPECT_EQ(0, counter);
  EXPECT_EQ(event::timestamp(0), t);
  EXPECT_EQ("EventDemo", w.get_title());
  EXPECT_EQ(scan_code::unknown, sc);
  EXPECT_EQ(key_code::unknown, kc);
  EXPECT_EQ(modifier_keys::none, mk);
  EXPECT_FALSE(is_repeat);

  event::set_key_pressed_callback(f);
  event::generate_key_pressed(
    w, scan_code::w, key_code::a, modifier_keys::alt, true);
  event::process_next();
  EXPECT_EQ(1, counter);
  EXPECT_NE(event::timestamp(0), t);
  EXPECT_EQ("NewTitle", w.get_title());
  EXPECT_EQ(scan_code::w, sc);
  EXPECT_EQ(key_code::a, kc);
  EXPECT_EQ(modifier_keys::alt, mk);
  EXPECT_TRUE(is_repeat);

  event::set_key_pressed_callback(nullptr);
  event::generate_key_pressed(
    w, scan_code::a, key_code::q, modifier_keys::ctrl, false);
  event::process_next();
  EXPECT_EQ(1, counter);
  EXPECT_NE(event::timestamp(0), t);
  EXPECT_EQ("NewTitle", w.get_title());
  EXPECT_EQ(scan_code::w, sc);
  EXPECT_EQ(key_code::a, kc);
  EXPECT_EQ(modifier_keys::alt, mk);
  EXPECT_TRUE(is_repeat);
}



TEST_F(test_event, key_released_event)
{
  int counter = 0;
  event::timestamp t(0);
  system_window w("EventDemo", vec2u(32u, 16u));
  scan_code sc = scan_code::unknown;
  key_code kc = key_code::unknown;
  modifier_keys mk = modifier_keys::none;
  bool is_repeat = false;

  auto f = [&](event::timestamp t_in, window& w_in, scan_code sc_in,
             key_code kc_in, modifier_keys mk_in, bool is_repeat_in) {
    ++counter;
    t = t_in;
    w_in.set_title("NewTitle");
    sc = sc_in;
    kc = kc_in;
    mk = mk_in;
    is_repeat = is_repeat_in;
  };

  event::flush_all();

  event::generate_key_released(
    w, scan_code::w, key_code::a, modifier_keys::alt, true);
  event::process_next();
  EXPECT_EQ(0, counter);
  EXPECT_EQ(event::timestamp(0), t);
  EXPECT_EQ("EventDemo", w.get_title());
  EXPECT_EQ(scan_code::unknown, sc);
  EXPECT_EQ(key_code::unknown, kc);
  EXPECT_EQ(modifier_keys::none, mk);
  EXPECT_FALSE(is_repeat);

  event::set_key_released_callback(f);
  event::generate_key_released(
    w, scan_code::w, key_code::a, modifier_keys::alt, true);
  event::process_next();
  EXPECT_EQ(1, counter);
  EXPECT_NE(event::timestamp(0), t);
  EXPECT_EQ("NewTitle", w.get_title());
  EXPECT_EQ(scan_code::w, sc);
  EXPECT_EQ(key_code::a, kc);
  EXPECT_EQ(modifier_keys::alt, mk);
  EXPECT_TRUE(is_repeat);

  event::set_key_released_callback(nullptr);
  event::generate_key_released(
    w, scan_code::a, key_code::q, modifier_keys::ctrl, false);
  event::process_next();
  EXPECT_EQ(1, counter);
  EXPECT_NE(event::timestamp(0), t);
  EXPECT_EQ("NewTitle", w.get_title());
  EXPECT_EQ(scan_code::w, sc);
  EXPECT_EQ(key_code::a, kc);
  EXPECT_EQ(modifier_keys::alt, mk);
  EXPECT_TRUE(is_repeat);
}
