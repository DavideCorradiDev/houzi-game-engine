// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/sys/window_event.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_window_event : public Test
{};

class test_window_event_death_test : public test_window_event
{};

}  // namespace



TEST_F(test_window_event, empty)
{
  window_event ev = window_event::empty();
  EXPECT_EQ(window_event_type::empty, ev.get_type());
}



TEST_F(test_window_event_death_test, empty_wrong_data)
{
  window_event ev = window_event::empty();
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, closed)
{
  window_event ev = window_event::closed();
  EXPECT_EQ(window_event_type::closed, ev.get_type());
}



TEST_F(test_window_event_death_test, closed_wrong_data)
{
  window_event ev = window_event::closed();
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, focus_gained)
{
  window_event ev = window_event::focus_gained();
  EXPECT_EQ(window_event_type::focus_gained, ev.get_type());
}



TEST_F(test_window_event_death_test, focus_gained_wrong_data)
{
  window_event ev = window_event::focus_gained();
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, focus_lost)
{
  window_event ev = window_event::focus_lost();
  EXPECT_EQ(window_event_type::focus_lost, ev.get_type());
}



TEST_F(test_window_event_death_test, focus_lost_wrong_data)
{
  window_event ev = window_event::focus_lost();
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, resized)
{
  window_event ev = window_event::resized(1u, 3u);
  EXPECT_EQ(window_event_type::resized, ev.get_type());
  EXPECT_EQ(1u, ev.get_size_data().x);
  EXPECT_EQ(3u, ev.get_size_data().y);
}



TEST_F(test_window_event_death_test, resized_wrong_data)
{
  window_event ev = window_event::resized(1, 3);
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, key_pressed)
{
  window_event ev = window_event::key_pressed(
    key_code::A, scan_code::Q, modifier_keys::alt | modifier_keys::shift);
  EXPECT_EQ(window_event_type::key_pressed, ev.get_type());
  EXPECT_EQ(key_code::A, ev.get_key_data().key_code);
  EXPECT_EQ(scan_code::Q, ev.get_key_data().scan_code);
  EXPECT_EQ(
    modifier_keys::alt | modifier_keys::shift, ev.get_key_data().modifier_keys);
}



TEST_F(test_window_event_death_test, key_pressed_wrong_data)
{
  window_event ev = window_event::key_pressed(
    key_code::A, scan_code::Q, modifier_keys::alt | modifier_keys::shift);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, key_released)
{
  window_event ev = window_event::key_released(
    key_code::A, scan_code::Q, modifier_keys::alt | modifier_keys::shift);
  EXPECT_EQ(window_event_type::key_released, ev.get_type());
  EXPECT_EQ(key_code::A, ev.get_key_data().key_code);
  EXPECT_EQ(scan_code::Q, ev.get_key_data().scan_code);
  EXPECT_EQ(
    modifier_keys::alt | modifier_keys::shift, ev.get_key_data().modifier_keys);
}



TEST_F(test_window_event_death_test, key_released_wrong_data)
{
  window_event ev = window_event::key_released(
    key_code::A, scan_code::Q, modifier_keys::alt | modifier_keys::shift);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, text_entered)
{
  window_event ev = window_event::text_entered(1234u);
  EXPECT_EQ(window_event_type::text_entered, ev.get_type());
  EXPECT_EQ(1234u, ev.get_text_data().code_point);
}



TEST_F(test_window_event_death_test, text_entered_wrong_data)
{
  window_event ev = window_event::text_entered(1234u);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, mouse_moved)
{
  window_event ev = window_event::mouse_moved(1, 3);
  EXPECT_EQ(window_event_type::mouse_moved, ev.get_type());
  EXPECT_EQ(1, ev.get_mouse_move_data().x);
  EXPECT_EQ(3, ev.get_mouse_move_data().y);
}



TEST_F(test_window_event_death_test, mouse_moved_wrong_data)
{
  window_event ev = window_event::mouse_moved(1, 3);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, mouse_entered)
{
  window_event ev = window_event::mouse_entered();
  EXPECT_EQ(window_event_type::mouse_entered, ev.get_type());
}



TEST_F(test_window_event_death_test, mouse_entered_wrong_data)
{
  window_event ev = window_event::mouse_entered();
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, mouse_left)
{
  window_event ev = window_event::mouse_left();
  EXPECT_EQ(window_event_type::mouse_left, ev.get_type());
}



TEST_F(test_window_event_death_test, mouse_left_wrong_data)
{
  window_event ev = window_event::mouse_left();
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, mouse_button_pressed)
{
  window_event ev = window_event::mouse_button_pressed(mouse_button::lb, 1, 3);
  EXPECT_EQ(window_event_type::mouse_button_pressed, ev.get_type());
  EXPECT_EQ(mouse_button::lb, ev.get_mouse_button_data().button);
  EXPECT_EQ(1, ev.get_mouse_button_data().x);
  EXPECT_EQ(3, ev.get_mouse_button_data().y);
}



TEST_F(test_window_event_death_test, mouse_button_pressed_wrong_data)
{
  window_event ev = window_event::mouse_button_pressed(mouse_button::lb, 1, 3);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, mouse_button_released)
{
  window_event ev = window_event::mouse_button_released(mouse_button::lb, 1, 3);
  EXPECT_EQ(window_event_type::mouse_button_released, ev.get_type());
  EXPECT_EQ(mouse_button::lb, ev.get_mouse_button_data().button);
  EXPECT_EQ(1, ev.get_mouse_button_data().x);
  EXPECT_EQ(3, ev.get_mouse_button_data().y);
}



TEST_F(test_window_event_death_test, mouse_button_released_wrong_data)
{
  window_event ev = window_event::mouse_button_released(mouse_button::lb, 1, 3);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_wheel_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_window_event, mouse_wheel_moved)
{
  window_event ev
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 5, 1, 3);
  EXPECT_EQ(window_event_type::mouse_wheel_moved, ev.get_type());
  EXPECT_EQ(mouse_wheel::vertical, ev.get_mouse_wheel_data().wheel);
  EXPECT_EQ(5, ev.get_mouse_wheel_data().delta);
  EXPECT_EQ(1, ev.get_mouse_wheel_data().x);
  EXPECT_EQ(3, ev.get_mouse_wheel_data().y);
}



TEST_F(test_window_event_death_test, mouse_wheel_moved_wrong_data)
{
  window_event ev
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 5, 1, 3);
  HOU_EXPECT_ERROR(
    ev.get_size_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_key_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(
    ev.get_text_data(), std::logic_error, get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_move_data(), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(ev.get_mouse_button_data(), std::logic_error,
    get_text(cor_error::pre_condition));
}


TEST_F(test_window_event, comparison)
{
  window_event em0 = window_event::empty();
  window_event em1 = window_event::empty();
  window_event cl0 = window_event::closed();
  window_event cl1 = window_event::closed();
  window_event fg0 = window_event::focus_gained();
  window_event fg1 = window_event::focus_gained();
  window_event fl0 = window_event::focus_lost();
  window_event fl1 = window_event::focus_lost();
  window_event rs0 = window_event::resized(1, 2);
  window_event rs1 = window_event::resized(1, 2);
  window_event rs2 = window_event::resized(3, 2);
  window_event rs3 = window_event::resized(1, 4);
  window_event kp0 = window_event::key_pressed(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kp1 = window_event::key_pressed(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kp2 = window_event::key_pressed(key_code::B, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kp3 = window_event::key_pressed(key_code::A, scan_code::B,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kp4 = window_event::key_pressed(key_code::A, scan_code::A,
    modifier_keys::ctrl | modifier_keys::shift | modifier_keys::system);
  window_event kp5 = window_event::key_pressed(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::shift | modifier_keys::system);
  window_event kp6 = window_event::key_pressed(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::system);
  window_event kp7 = window_event::key_pressed(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift);
  window_event kr0 = window_event::key_released(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kr1 = window_event::key_released(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kr2 = window_event::key_released(key_code::B, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kr3 = window_event::key_released(key_code::A, scan_code::B,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift
      | modifier_keys::system);
  window_event kr4 = window_event::key_released(key_code::A, scan_code::A,
    modifier_keys::ctrl | modifier_keys::shift | modifier_keys::system);
  window_event kr5 = window_event::key_released(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::shift | modifier_keys::system);
  window_event kr6 = window_event::key_released(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::system);
  window_event kr7 = window_event::key_released(key_code::A, scan_code::A,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::shift);
  window_event te0 = window_event::text_entered(12);
  window_event te1 = window_event::text_entered(12);
  window_event te2 = window_event::text_entered(24);
  window_event mm0 = window_event::mouse_moved(3, 5);
  window_event mm1 = window_event::mouse_moved(3, 5);
  window_event mm2 = window_event::mouse_moved(6, 5);
  window_event mm3 = window_event::mouse_moved(3, 8);
  window_event me0 = window_event::mouse_entered();
  window_event me1 = window_event::mouse_entered();
  window_event ml0 = window_event::mouse_left();
  window_event ml1 = window_event::mouse_left();
  window_event mp0 = window_event::mouse_button_pressed(mouse_button::lb, 3, 5);
  window_event mp1 = window_event::mouse_button_pressed(mouse_button::lb, 3, 5);
  window_event mp2 = window_event::mouse_button_pressed(mouse_button::rb, 3, 5);
  window_event mp3 = window_event::mouse_button_pressed(mouse_button::lb, 6, 5);
  window_event mp4 = window_event::mouse_button_pressed(mouse_button::lb, 3, 8);
  window_event mr0
    = window_event::mouse_button_released(mouse_button::lb, 3, 5);
  window_event mr1
    = window_event::mouse_button_released(mouse_button::lb, 3, 5);
  window_event mr2
    = window_event::mouse_button_released(mouse_button::rb, 3, 5);
  window_event mr3
    = window_event::mouse_button_released(mouse_button::lb, 6, 5);
  window_event mr4
    = window_event::mouse_button_released(mouse_button::lb, 3, 8);
  window_event mw0
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 7, 3, 5);
  window_event mw1
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 7, 3, 5);
  window_event mw2
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 9, 3, 5);
  window_event mw3
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 7, 6, 5);
  window_event mw4
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 7, 3, 8);
  window_event mw5
    = window_event::mouse_wheel_moved(mouse_wheel::horizontal, 7, 3, 5);

  EXPECT_TRUE(em0 == em1);
  EXPECT_FALSE(em0 == cl1);
  EXPECT_FALSE(em0 == fg1);
  EXPECT_FALSE(em0 == fl1);
  EXPECT_FALSE(em0 == rs1);
  EXPECT_FALSE(em0 == rs2);
  EXPECT_FALSE(em0 == rs3);
  EXPECT_FALSE(em0 == kp1);
  EXPECT_FALSE(em0 == kp2);
  EXPECT_FALSE(em0 == kp3);
  EXPECT_FALSE(em0 == kp4);
  EXPECT_FALSE(em0 == kp5);
  EXPECT_FALSE(em0 == kp6);
  EXPECT_FALSE(em0 == kp7);
  EXPECT_FALSE(em0 == kr1);
  EXPECT_FALSE(em0 == kr2);
  EXPECT_FALSE(em0 == kr3);
  EXPECT_FALSE(em0 == kr4);
  EXPECT_FALSE(em0 == kr5);
  EXPECT_FALSE(em0 == kr6);
  EXPECT_FALSE(em0 == kr7);
  EXPECT_FALSE(em0 == te1);
  EXPECT_FALSE(em0 == te2);
  EXPECT_FALSE(em0 == mm1);
  EXPECT_FALSE(em0 == mm2);
  EXPECT_FALSE(em0 == mm3);
  EXPECT_FALSE(em0 == me1);
  EXPECT_FALSE(em0 == ml1);
  EXPECT_FALSE(em0 == mp1);
  EXPECT_FALSE(em0 == mp2);
  EXPECT_FALSE(em0 == mp3);
  EXPECT_FALSE(em0 == mp4);
  EXPECT_FALSE(em0 == mr1);
  EXPECT_FALSE(em0 == mr2);
  EXPECT_FALSE(em0 == mr3);
  EXPECT_FALSE(em0 == mr4);
  EXPECT_FALSE(em0 == mw1);
  EXPECT_FALSE(em0 == mw2);
  EXPECT_FALSE(em0 == mw3);
  EXPECT_FALSE(em0 == mw4);
  EXPECT_FALSE(em0 == mw5);

  EXPECT_FALSE(cl0 == em1);
  EXPECT_TRUE(cl0 == cl1);
  EXPECT_FALSE(cl0 == fg1);
  EXPECT_FALSE(cl0 == fl1);
  EXPECT_FALSE(cl0 == rs1);
  EXPECT_FALSE(cl0 == rs2);
  EXPECT_FALSE(cl0 == rs3);
  EXPECT_FALSE(cl0 == kp1);
  EXPECT_FALSE(cl0 == kp2);
  EXPECT_FALSE(cl0 == kp3);
  EXPECT_FALSE(cl0 == kp4);
  EXPECT_FALSE(cl0 == kp5);
  EXPECT_FALSE(cl0 == kp6);
  EXPECT_FALSE(cl0 == kp7);
  EXPECT_FALSE(cl0 == kr1);
  EXPECT_FALSE(cl0 == kr2);
  EXPECT_FALSE(cl0 == kr3);
  EXPECT_FALSE(cl0 == kr4);
  EXPECT_FALSE(cl0 == kr5);
  EXPECT_FALSE(cl0 == kr6);
  EXPECT_FALSE(cl0 == kr7);
  EXPECT_FALSE(cl0 == te1);
  EXPECT_FALSE(cl0 == te2);
  EXPECT_FALSE(cl0 == mm1);
  EXPECT_FALSE(cl0 == mm2);
  EXPECT_FALSE(cl0 == mm3);
  EXPECT_FALSE(cl0 == me1);
  EXPECT_FALSE(cl0 == ml1);
  EXPECT_FALSE(cl0 == mp1);
  EXPECT_FALSE(cl0 == mp2);
  EXPECT_FALSE(cl0 == mp3);
  EXPECT_FALSE(cl0 == mp4);
  EXPECT_FALSE(cl0 == mr1);
  EXPECT_FALSE(cl0 == mr2);
  EXPECT_FALSE(cl0 == mr3);
  EXPECT_FALSE(cl0 == mr4);
  EXPECT_FALSE(cl0 == mw1);
  EXPECT_FALSE(cl0 == mw2);
  EXPECT_FALSE(cl0 == mw3);
  EXPECT_FALSE(cl0 == mw4);
  EXPECT_FALSE(cl0 == mw5);

  EXPECT_FALSE(fg0 == em1);
  EXPECT_FALSE(fg0 == cl1);
  EXPECT_TRUE(fg0 == fg1);
  EXPECT_FALSE(fg0 == fl1);
  EXPECT_FALSE(fg0 == rs1);
  EXPECT_FALSE(fg0 == rs2);
  EXPECT_FALSE(fg0 == rs3);
  EXPECT_FALSE(fg0 == kp1);
  EXPECT_FALSE(fg0 == kp2);
  EXPECT_FALSE(fg0 == kp3);
  EXPECT_FALSE(fg0 == kp4);
  EXPECT_FALSE(fg0 == kp5);
  EXPECT_FALSE(fg0 == kp6);
  EXPECT_FALSE(fg0 == kp7);
  EXPECT_FALSE(fg0 == kr1);
  EXPECT_FALSE(fg0 == kr2);
  EXPECT_FALSE(fg0 == kr3);
  EXPECT_FALSE(fg0 == kr4);
  EXPECT_FALSE(fg0 == kr5);
  EXPECT_FALSE(fg0 == kr6);
  EXPECT_FALSE(fg0 == kr7);
  EXPECT_FALSE(fg0 == te1);
  EXPECT_FALSE(fg0 == te2);
  EXPECT_FALSE(fg0 == mm1);
  EXPECT_FALSE(fg0 == mm2);
  EXPECT_FALSE(fg0 == mm3);
  EXPECT_FALSE(fg0 == me1);
  EXPECT_FALSE(fg0 == ml1);
  EXPECT_FALSE(fg0 == mp1);
  EXPECT_FALSE(fg0 == mp2);
  EXPECT_FALSE(fg0 == mp3);
  EXPECT_FALSE(fg0 == mp4);
  EXPECT_FALSE(fg0 == mr1);
  EXPECT_FALSE(fg0 == mr2);
  EXPECT_FALSE(fg0 == mr3);
  EXPECT_FALSE(fg0 == mr4);
  EXPECT_FALSE(fg0 == mw1);
  EXPECT_FALSE(fg0 == mw2);
  EXPECT_FALSE(fg0 == mw3);
  EXPECT_FALSE(fg0 == mw4);
  EXPECT_FALSE(fg0 == mw5);

  EXPECT_FALSE(fl0 == em1);
  EXPECT_FALSE(fl0 == cl1);
  EXPECT_FALSE(fl0 == fg1);
  EXPECT_TRUE(fl0 == fl1);
  EXPECT_FALSE(fl0 == rs1);
  EXPECT_FALSE(fl0 == rs2);
  EXPECT_FALSE(fl0 == rs3);
  EXPECT_FALSE(fl0 == kp1);
  EXPECT_FALSE(fl0 == kp2);
  EXPECT_FALSE(fl0 == kp3);
  EXPECT_FALSE(fl0 == kp4);
  EXPECT_FALSE(fl0 == kp5);
  EXPECT_FALSE(fl0 == kp6);
  EXPECT_FALSE(fl0 == kp7);
  EXPECT_FALSE(fl0 == kr1);
  EXPECT_FALSE(fl0 == kr2);
  EXPECT_FALSE(fl0 == kr3);
  EXPECT_FALSE(fl0 == kr4);
  EXPECT_FALSE(fl0 == kr5);
  EXPECT_FALSE(fl0 == kr6);
  EXPECT_FALSE(fl0 == kr7);
  EXPECT_FALSE(fl0 == te1);
  EXPECT_FALSE(fl0 == te2);
  EXPECT_FALSE(fl0 == mm1);
  EXPECT_FALSE(fl0 == mm2);
  EXPECT_FALSE(fl0 == mm3);
  EXPECT_FALSE(fl0 == me1);
  EXPECT_FALSE(fl0 == ml1);
  EXPECT_FALSE(fl0 == mp1);
  EXPECT_FALSE(fl0 == mp2);
  EXPECT_FALSE(fl0 == mp3);
  EXPECT_FALSE(fl0 == mp4);
  EXPECT_FALSE(fl0 == mr1);
  EXPECT_FALSE(fl0 == mr2);
  EXPECT_FALSE(fl0 == mr3);
  EXPECT_FALSE(fl0 == mr4);
  EXPECT_FALSE(fl0 == mw1);
  EXPECT_FALSE(fl0 == mw2);
  EXPECT_FALSE(fl0 == mw3);
  EXPECT_FALSE(fl0 == mw4);
  EXPECT_FALSE(fl0 == mw5);

  EXPECT_FALSE(rs0 == em1);
  EXPECT_FALSE(rs0 == cl1);
  EXPECT_FALSE(rs0 == fg1);
  EXPECT_FALSE(rs0 == fl1);
  EXPECT_TRUE(rs0 == rs1);
  EXPECT_FALSE(rs0 == rs2);
  EXPECT_FALSE(rs0 == rs3);
  EXPECT_FALSE(rs0 == kp1);
  EXPECT_FALSE(rs0 == kp2);
  EXPECT_FALSE(rs0 == kp3);
  EXPECT_FALSE(rs0 == kp4);
  EXPECT_FALSE(rs0 == kp5);
  EXPECT_FALSE(rs0 == kp6);
  EXPECT_FALSE(rs0 == kp7);
  EXPECT_FALSE(rs0 == kr1);
  EXPECT_FALSE(rs0 == kr2);
  EXPECT_FALSE(rs0 == kr3);
  EXPECT_FALSE(rs0 == kr4);
  EXPECT_FALSE(rs0 == kr5);
  EXPECT_FALSE(rs0 == kr6);
  EXPECT_FALSE(rs0 == kr7);
  EXPECT_FALSE(rs0 == te1);
  EXPECT_FALSE(rs0 == te2);
  EXPECT_FALSE(rs0 == mm1);
  EXPECT_FALSE(rs0 == mm2);
  EXPECT_FALSE(rs0 == mm3);
  EXPECT_FALSE(rs0 == me1);
  EXPECT_FALSE(rs0 == ml1);
  EXPECT_FALSE(rs0 == mp1);
  EXPECT_FALSE(rs0 == mp2);
  EXPECT_FALSE(rs0 == mp3);
  EXPECT_FALSE(rs0 == mp4);
  EXPECT_FALSE(rs0 == mr1);
  EXPECT_FALSE(rs0 == mr2);
  EXPECT_FALSE(rs0 == mr3);
  EXPECT_FALSE(rs0 == mr4);
  EXPECT_FALSE(rs0 == mw1);
  EXPECT_FALSE(rs0 == mw2);
  EXPECT_FALSE(rs0 == mw3);
  EXPECT_FALSE(rs0 == mw4);
  EXPECT_FALSE(rs0 == mw5);

  EXPECT_FALSE(kp0 == em1);
  EXPECT_FALSE(kp0 == cl1);
  EXPECT_FALSE(kp0 == fg1);
  EXPECT_FALSE(kp0 == fl1);
  EXPECT_FALSE(kp0 == rs1);
  EXPECT_FALSE(kp0 == rs2);
  EXPECT_FALSE(kp0 == rs3);
  EXPECT_TRUE(kp0 == kp1);
  EXPECT_FALSE(kp0 == kp2);
  EXPECT_FALSE(kp0 == kp3);
  EXPECT_FALSE(kp0 == kp4);
  EXPECT_FALSE(kp0 == kp5);
  EXPECT_FALSE(kp0 == kp6);
  EXPECT_FALSE(kp0 == kp7);
  EXPECT_FALSE(kp0 == kr1);
  EXPECT_FALSE(kp0 == kr2);
  EXPECT_FALSE(kp0 == kr3);
  EXPECT_FALSE(kp0 == kr4);
  EXPECT_FALSE(kp0 == kr5);
  EXPECT_FALSE(kp0 == kr6);
  EXPECT_FALSE(kp0 == kr7);
  EXPECT_FALSE(kp0 == te1);
  EXPECT_FALSE(kp0 == te2);
  EXPECT_FALSE(kp0 == mm1);
  EXPECT_FALSE(kp0 == mm2);
  EXPECT_FALSE(kp0 == mm3);
  EXPECT_FALSE(kp0 == me1);
  EXPECT_FALSE(kp0 == ml1);
  EXPECT_FALSE(kp0 == mp1);
  EXPECT_FALSE(kp0 == mp2);
  EXPECT_FALSE(kp0 == mp3);
  EXPECT_FALSE(kp0 == mp4);
  EXPECT_FALSE(kp0 == mr1);
  EXPECT_FALSE(kp0 == mr2);
  EXPECT_FALSE(kp0 == mr3);
  EXPECT_FALSE(kp0 == mr4);
  EXPECT_FALSE(kp0 == mw1);
  EXPECT_FALSE(kp0 == mw2);
  EXPECT_FALSE(kp0 == mw3);
  EXPECT_FALSE(kp0 == mw4);
  EXPECT_FALSE(kp0 == mw5);

  EXPECT_FALSE(kr0 == em1);
  EXPECT_FALSE(kr0 == cl1);
  EXPECT_FALSE(kr0 == fg1);
  EXPECT_FALSE(kr0 == fl1);
  EXPECT_FALSE(kr0 == rs1);
  EXPECT_FALSE(kr0 == rs2);
  EXPECT_FALSE(kr0 == rs3);
  EXPECT_FALSE(kr0 == kp1);
  EXPECT_FALSE(kr0 == kp2);
  EXPECT_FALSE(kr0 == kp3);
  EXPECT_FALSE(kr0 == kp4);
  EXPECT_FALSE(kr0 == kp5);
  EXPECT_FALSE(kr0 == kp6);
  EXPECT_FALSE(kr0 == kp7);
  EXPECT_TRUE(kr0 == kr1);
  EXPECT_FALSE(kr0 == kr2);
  EXPECT_FALSE(kr0 == kr3);
  EXPECT_FALSE(kr0 == kr4);
  EXPECT_FALSE(kr0 == kr5);
  EXPECT_FALSE(kr0 == kr6);
  EXPECT_FALSE(kr0 == kr7);
  EXPECT_FALSE(kr0 == te1);
  EXPECT_FALSE(kr0 == te2);
  EXPECT_FALSE(kr0 == mm1);
  EXPECT_FALSE(kr0 == mm2);
  EXPECT_FALSE(kr0 == mm3);
  EXPECT_FALSE(kr0 == me1);
  EXPECT_FALSE(kr0 == ml1);
  EXPECT_FALSE(kr0 == mp1);
  EXPECT_FALSE(kr0 == mp2);
  EXPECT_FALSE(kr0 == mp3);
  EXPECT_FALSE(kr0 == mp4);
  EXPECT_FALSE(kr0 == mr1);
  EXPECT_FALSE(kr0 == mr2);
  EXPECT_FALSE(kr0 == mr3);
  EXPECT_FALSE(kr0 == mr4);
  EXPECT_FALSE(kr0 == mw1);
  EXPECT_FALSE(kr0 == mw2);
  EXPECT_FALSE(kr0 == mw3);
  EXPECT_FALSE(kr0 == mw4);
  EXPECT_FALSE(kr0 == mw5);

  EXPECT_FALSE(te0 == em1);
  EXPECT_FALSE(te0 == cl1);
  EXPECT_FALSE(te0 == fg1);
  EXPECT_FALSE(te0 == fl1);
  EXPECT_FALSE(te0 == rs1);
  EXPECT_FALSE(te0 == rs2);
  EXPECT_FALSE(te0 == rs3);
  EXPECT_FALSE(te0 == kp1);
  EXPECT_FALSE(te0 == kp2);
  EXPECT_FALSE(te0 == kp3);
  EXPECT_FALSE(te0 == kp4);
  EXPECT_FALSE(te0 == kp5);
  EXPECT_FALSE(te0 == kp6);
  EXPECT_FALSE(te0 == kp7);
  EXPECT_FALSE(te0 == kr1);
  EXPECT_FALSE(te0 == kr2);
  EXPECT_FALSE(te0 == kr3);
  EXPECT_FALSE(te0 == kr4);
  EXPECT_FALSE(te0 == kr5);
  EXPECT_FALSE(te0 == kr6);
  EXPECT_FALSE(te0 == kr7);
  EXPECT_TRUE(te0 == te1);
  EXPECT_FALSE(te0 == te2);
  EXPECT_FALSE(te0 == mm1);
  EXPECT_FALSE(te0 == mm2);
  EXPECT_FALSE(te0 == mm3);
  EXPECT_FALSE(te0 == me1);
  EXPECT_FALSE(te0 == ml1);
  EXPECT_FALSE(te0 == mp1);
  EXPECT_FALSE(te0 == mp2);
  EXPECT_FALSE(te0 == mp3);
  EXPECT_FALSE(te0 == mp4);
  EXPECT_FALSE(te0 == mr1);
  EXPECT_FALSE(te0 == mr2);
  EXPECT_FALSE(te0 == mr3);
  EXPECT_FALSE(te0 == mr4);
  EXPECT_FALSE(te0 == mw1);
  EXPECT_FALSE(te0 == mw2);
  EXPECT_FALSE(te0 == mw3);
  EXPECT_FALSE(te0 == mw4);
  EXPECT_FALSE(te0 == mw5);

  EXPECT_FALSE(mm0 == em1);
  EXPECT_FALSE(mm0 == cl1);
  EXPECT_FALSE(mm0 == fg1);
  EXPECT_FALSE(mm0 == fl1);
  EXPECT_FALSE(mm0 == rs1);
  EXPECT_FALSE(mm0 == rs2);
  EXPECT_FALSE(mm0 == rs3);
  EXPECT_FALSE(mm0 == kp1);
  EXPECT_FALSE(mm0 == kp2);
  EXPECT_FALSE(mm0 == kp3);
  EXPECT_FALSE(mm0 == kp4);
  EXPECT_FALSE(mm0 == kp5);
  EXPECT_FALSE(mm0 == kp6);
  EXPECT_FALSE(mm0 == kp7);
  EXPECT_FALSE(mm0 == kr1);
  EXPECT_FALSE(mm0 == kr2);
  EXPECT_FALSE(mm0 == kr3);
  EXPECT_FALSE(mm0 == kr4);
  EXPECT_FALSE(mm0 == kr5);
  EXPECT_FALSE(mm0 == kr6);
  EXPECT_FALSE(mm0 == kr7);
  EXPECT_FALSE(mm0 == te1);
  EXPECT_FALSE(mm0 == te2);
  EXPECT_TRUE(mm0 == mm1);
  EXPECT_FALSE(mm0 == mm2);
  EXPECT_FALSE(mm0 == mm3);
  EXPECT_FALSE(mm0 == me1);
  EXPECT_FALSE(mm0 == ml1);
  EXPECT_FALSE(mm0 == mp1);
  EXPECT_FALSE(mm0 == mp2);
  EXPECT_FALSE(mm0 == mp3);
  EXPECT_FALSE(mm0 == mp4);
  EXPECT_FALSE(mm0 == mr1);
  EXPECT_FALSE(mm0 == mr2);
  EXPECT_FALSE(mm0 == mr3);
  EXPECT_FALSE(mm0 == mr4);
  EXPECT_FALSE(mm0 == mw1);
  EXPECT_FALSE(mm0 == mw2);
  EXPECT_FALSE(mm0 == mw3);
  EXPECT_FALSE(mm0 == mw4);
  EXPECT_FALSE(mm0 == mw5);

  EXPECT_FALSE(me0 == em1);
  EXPECT_FALSE(me0 == cl1);
  EXPECT_FALSE(me0 == fg1);
  EXPECT_FALSE(me0 == fl1);
  EXPECT_FALSE(me0 == rs1);
  EXPECT_FALSE(me0 == rs2);
  EXPECT_FALSE(me0 == rs3);
  EXPECT_FALSE(me0 == kp1);
  EXPECT_FALSE(me0 == kp2);
  EXPECT_FALSE(me0 == kp3);
  EXPECT_FALSE(me0 == kp4);
  EXPECT_FALSE(me0 == kp5);
  EXPECT_FALSE(me0 == kp6);
  EXPECT_FALSE(me0 == kp7);
  EXPECT_FALSE(me0 == kr1);
  EXPECT_FALSE(me0 == kr2);
  EXPECT_FALSE(me0 == kr3);
  EXPECT_FALSE(me0 == kr4);
  EXPECT_FALSE(me0 == kr5);
  EXPECT_FALSE(me0 == kr6);
  EXPECT_FALSE(me0 == kr7);
  EXPECT_FALSE(me0 == te1);
  EXPECT_FALSE(me0 == te2);
  EXPECT_FALSE(me0 == mm1);
  EXPECT_FALSE(me0 == mm2);
  EXPECT_FALSE(me0 == mm3);
  EXPECT_TRUE(me0 == me1);
  EXPECT_FALSE(me0 == ml1);
  EXPECT_FALSE(me0 == mp1);
  EXPECT_FALSE(me0 == mp2);
  EXPECT_FALSE(me0 == mp3);
  EXPECT_FALSE(me0 == mp4);
  EXPECT_FALSE(me0 == mr1);
  EXPECT_FALSE(me0 == mr2);
  EXPECT_FALSE(me0 == mr3);
  EXPECT_FALSE(me0 == mr4);
  EXPECT_FALSE(me0 == mw1);
  EXPECT_FALSE(me0 == mw2);
  EXPECT_FALSE(me0 == mw3);
  EXPECT_FALSE(me0 == mw4);
  EXPECT_FALSE(me0 == mw5);

  EXPECT_FALSE(ml0 == em1);
  EXPECT_FALSE(ml0 == cl1);
  EXPECT_FALSE(ml0 == fg1);
  EXPECT_FALSE(ml0 == fl1);
  EXPECT_FALSE(ml0 == rs1);
  EXPECT_FALSE(ml0 == rs2);
  EXPECT_FALSE(ml0 == rs3);
  EXPECT_FALSE(ml0 == kp1);
  EXPECT_FALSE(ml0 == kp2);
  EXPECT_FALSE(ml0 == kp3);
  EXPECT_FALSE(ml0 == kp4);
  EXPECT_FALSE(ml0 == kp5);
  EXPECT_FALSE(ml0 == kp6);
  EXPECT_FALSE(ml0 == kp7);
  EXPECT_FALSE(ml0 == kr1);
  EXPECT_FALSE(ml0 == kr2);
  EXPECT_FALSE(ml0 == kr3);
  EXPECT_FALSE(ml0 == kr4);
  EXPECT_FALSE(ml0 == kr5);
  EXPECT_FALSE(ml0 == kr6);
  EXPECT_FALSE(ml0 == kr7);
  EXPECT_FALSE(ml0 == te1);
  EXPECT_FALSE(ml0 == te2);
  EXPECT_FALSE(ml0 == mm1);
  EXPECT_FALSE(ml0 == mm2);
  EXPECT_FALSE(ml0 == mm3);
  EXPECT_FALSE(ml0 == me1);
  EXPECT_TRUE(ml0 == ml1);
  EXPECT_FALSE(ml0 == mp1);
  EXPECT_FALSE(ml0 == mp2);
  EXPECT_FALSE(ml0 == mp3);
  EXPECT_FALSE(ml0 == mp4);
  EXPECT_FALSE(ml0 == mr1);
  EXPECT_FALSE(ml0 == mr2);
  EXPECT_FALSE(ml0 == mr3);
  EXPECT_FALSE(ml0 == mr4);
  EXPECT_FALSE(ml0 == mw1);
  EXPECT_FALSE(ml0 == mw2);
  EXPECT_FALSE(ml0 == mw3);
  EXPECT_FALSE(ml0 == mw4);
  EXPECT_FALSE(ml0 == mw5);

  EXPECT_FALSE(mp0 == em1);
  EXPECT_FALSE(mp0 == cl1);
  EXPECT_FALSE(mp0 == fg1);
  EXPECT_FALSE(mp0 == fl1);
  EXPECT_FALSE(mp0 == rs1);
  EXPECT_FALSE(mp0 == rs2);
  EXPECT_FALSE(mp0 == rs3);
  EXPECT_FALSE(mp0 == kp1);
  EXPECT_FALSE(mp0 == kp2);
  EXPECT_FALSE(mp0 == kp3);
  EXPECT_FALSE(mp0 == kp4);
  EXPECT_FALSE(mp0 == kp5);
  EXPECT_FALSE(mp0 == kp6);
  EXPECT_FALSE(mp0 == kp7);
  EXPECT_FALSE(mp0 == kr1);
  EXPECT_FALSE(mp0 == kr2);
  EXPECT_FALSE(mp0 == kr3);
  EXPECT_FALSE(mp0 == kr4);
  EXPECT_FALSE(mp0 == kr5);
  EXPECT_FALSE(mp0 == kr6);
  EXPECT_FALSE(mp0 == kr7);
  EXPECT_FALSE(mp0 == te1);
  EXPECT_FALSE(mp0 == te2);
  EXPECT_FALSE(mp0 == mm1);
  EXPECT_FALSE(mp0 == mm2);
  EXPECT_FALSE(mp0 == mm3);
  EXPECT_FALSE(mp0 == me1);
  EXPECT_FALSE(mp0 == ml1);
  EXPECT_TRUE(mp0 == mp1);
  EXPECT_FALSE(mp0 == mp2);
  EXPECT_FALSE(mp0 == mp3);
  EXPECT_FALSE(mp0 == mp4);
  EXPECT_FALSE(mp0 == mr1);
  EXPECT_FALSE(mp0 == mr2);
  EXPECT_FALSE(mp0 == mr3);
  EXPECT_FALSE(mp0 == mr4);
  EXPECT_FALSE(mp0 == mw1);
  EXPECT_FALSE(mp0 == mw2);
  EXPECT_FALSE(mp0 == mw3);
  EXPECT_FALSE(mp0 == mw4);
  EXPECT_FALSE(mp0 == mw5);

  EXPECT_FALSE(mr0 == em1);
  EXPECT_FALSE(mr0 == cl1);
  EXPECT_FALSE(mr0 == fg1);
  EXPECT_FALSE(mr0 == fl1);
  EXPECT_FALSE(mr0 == rs1);
  EXPECT_FALSE(mr0 == rs2);
  EXPECT_FALSE(mr0 == rs3);
  EXPECT_FALSE(mr0 == kp1);
  EXPECT_FALSE(mr0 == kp2);
  EXPECT_FALSE(mr0 == kp3);
  EXPECT_FALSE(mr0 == kp4);
  EXPECT_FALSE(mr0 == kp5);
  EXPECT_FALSE(mr0 == kp6);
  EXPECT_FALSE(mr0 == kp7);
  EXPECT_FALSE(mr0 == kr1);
  EXPECT_FALSE(mr0 == kr2);
  EXPECT_FALSE(mr0 == kr3);
  EXPECT_FALSE(mr0 == kr4);
  EXPECT_FALSE(mr0 == kr5);
  EXPECT_FALSE(mr0 == kr6);
  EXPECT_FALSE(mr0 == kr7);
  EXPECT_FALSE(mr0 == te1);
  EXPECT_FALSE(mr0 == te2);
  EXPECT_FALSE(mr0 == mm1);
  EXPECT_FALSE(mr0 == mm2);
  EXPECT_FALSE(mr0 == mm3);
  EXPECT_FALSE(mr0 == me1);
  EXPECT_FALSE(mr0 == ml1);
  EXPECT_FALSE(mr0 == mp1);
  EXPECT_FALSE(mr0 == mp2);
  EXPECT_FALSE(mr0 == mp3);
  EXPECT_FALSE(mr0 == mp4);
  EXPECT_TRUE(mr0 == mr1);
  EXPECT_FALSE(mr0 == mr2);
  EXPECT_FALSE(mr0 == mr3);
  EXPECT_FALSE(mr0 == mr4);
  EXPECT_FALSE(mr0 == mw1);
  EXPECT_FALSE(mr0 == mw2);
  EXPECT_FALSE(mr0 == mw3);
  EXPECT_FALSE(mr0 == mw4);
  EXPECT_FALSE(mr0 == mw5);

  EXPECT_FALSE(mw0 == em1);
  EXPECT_FALSE(mw0 == cl1);
  EXPECT_FALSE(mw0 == fg1);
  EXPECT_FALSE(mw0 == fl1);
  EXPECT_FALSE(mw0 == rs1);
  EXPECT_FALSE(mw0 == rs2);
  EXPECT_FALSE(mw0 == rs3);
  EXPECT_FALSE(mw0 == kp1);
  EXPECT_FALSE(mw0 == kp2);
  EXPECT_FALSE(mw0 == kp3);
  EXPECT_FALSE(mw0 == kp4);
  EXPECT_FALSE(mw0 == kp5);
  EXPECT_FALSE(mw0 == kp6);
  EXPECT_FALSE(mw0 == kp7);
  EXPECT_FALSE(mw0 == kr1);
  EXPECT_FALSE(mw0 == kr2);
  EXPECT_FALSE(mw0 == kr3);
  EXPECT_FALSE(mw0 == kr4);
  EXPECT_FALSE(mw0 == kr5);
  EXPECT_FALSE(mw0 == kr6);
  EXPECT_FALSE(mw0 == kr7);
  EXPECT_FALSE(mw0 == te1);
  EXPECT_FALSE(mw0 == te2);
  EXPECT_FALSE(mw0 == mm1);
  EXPECT_FALSE(mw0 == mm2);
  EXPECT_FALSE(mw0 == mm3);
  EXPECT_FALSE(mw0 == me1);
  EXPECT_FALSE(mw0 == ml1);
  EXPECT_FALSE(mw0 == mp1);
  EXPECT_FALSE(mw0 == mp2);
  EXPECT_FALSE(mw0 == mp3);
  EXPECT_FALSE(mw0 == mp4);
  EXPECT_FALSE(mw0 == mr1);
  EXPECT_FALSE(mw0 == mr2);
  EXPECT_FALSE(mw0 == mr3);
  EXPECT_FALSE(mw0 == mr4);
  EXPECT_TRUE(mw0 == mw1);
  EXPECT_FALSE(mw0 == mw2);
  EXPECT_FALSE(mw0 == mw3);
  EXPECT_FALSE(mw0 == mw4);
  EXPECT_FALSE(mw0 == mw5);

  EXPECT_FALSE(em0 != em1);
  EXPECT_TRUE(em0 != cl1);
  EXPECT_TRUE(em0 != fg1);
  EXPECT_TRUE(em0 != fl1);
  EXPECT_TRUE(em0 != rs1);
  EXPECT_TRUE(em0 != rs2);
  EXPECT_TRUE(em0 != rs3);
  EXPECT_TRUE(em0 != kp1);
  EXPECT_TRUE(em0 != kp2);
  EXPECT_TRUE(em0 != kp3);
  EXPECT_TRUE(em0 != kp4);
  EXPECT_TRUE(em0 != kp5);
  EXPECT_TRUE(em0 != kp6);
  EXPECT_TRUE(em0 != kp7);
  EXPECT_TRUE(em0 != kr1);
  EXPECT_TRUE(em0 != kr2);
  EXPECT_TRUE(em0 != kr3);
  EXPECT_TRUE(em0 != kr4);
  EXPECT_TRUE(em0 != kr5);
  EXPECT_TRUE(em0 != kr6);
  EXPECT_TRUE(em0 != kr7);
  EXPECT_TRUE(em0 != te1);
  EXPECT_TRUE(em0 != te2);
  EXPECT_TRUE(em0 != mm1);
  EXPECT_TRUE(em0 != mm2);
  EXPECT_TRUE(em0 != mm3);
  EXPECT_TRUE(em0 != me1);
  EXPECT_TRUE(em0 != ml1);
  EXPECT_TRUE(em0 != mp1);
  EXPECT_TRUE(em0 != mp2);
  EXPECT_TRUE(em0 != mp3);
  EXPECT_TRUE(em0 != mp4);
  EXPECT_TRUE(em0 != mr1);
  EXPECT_TRUE(em0 != mr2);
  EXPECT_TRUE(em0 != mr3);
  EXPECT_TRUE(em0 != mr4);
  EXPECT_TRUE(em0 != mw1);
  EXPECT_TRUE(em0 != mw2);
  EXPECT_TRUE(em0 != mw3);
  EXPECT_TRUE(em0 != mw4);
  EXPECT_TRUE(em0 != mw5);

  EXPECT_TRUE(cl0 != em1);
  EXPECT_FALSE(cl0 != cl1);
  EXPECT_TRUE(cl0 != fg1);
  EXPECT_TRUE(cl0 != fl1);
  EXPECT_TRUE(cl0 != rs1);
  EXPECT_TRUE(cl0 != rs2);
  EXPECT_TRUE(cl0 != rs3);
  EXPECT_TRUE(cl0 != kp1);
  EXPECT_TRUE(cl0 != kp2);
  EXPECT_TRUE(cl0 != kp3);
  EXPECT_TRUE(cl0 != kp4);
  EXPECT_TRUE(cl0 != kp5);
  EXPECT_TRUE(cl0 != kp6);
  EXPECT_TRUE(cl0 != kp7);
  EXPECT_TRUE(cl0 != kr1);
  EXPECT_TRUE(cl0 != kr2);
  EXPECT_TRUE(cl0 != kr3);
  EXPECT_TRUE(cl0 != kr4);
  EXPECT_TRUE(cl0 != kr5);
  EXPECT_TRUE(cl0 != kr6);
  EXPECT_TRUE(cl0 != kr7);
  EXPECT_TRUE(cl0 != te1);
  EXPECT_TRUE(cl0 != te2);
  EXPECT_TRUE(cl0 != mm1);
  EXPECT_TRUE(cl0 != mm2);
  EXPECT_TRUE(cl0 != mm3);
  EXPECT_TRUE(cl0 != me1);
  EXPECT_TRUE(cl0 != ml1);
  EXPECT_TRUE(cl0 != mp1);
  EXPECT_TRUE(cl0 != mp2);
  EXPECT_TRUE(cl0 != mp3);
  EXPECT_TRUE(cl0 != mp4);
  EXPECT_TRUE(cl0 != mr1);
  EXPECT_TRUE(cl0 != mr2);
  EXPECT_TRUE(cl0 != mr3);
  EXPECT_TRUE(cl0 != mr4);
  EXPECT_TRUE(cl0 != mw1);
  EXPECT_TRUE(cl0 != mw2);
  EXPECT_TRUE(cl0 != mw3);
  EXPECT_TRUE(cl0 != mw4);
  EXPECT_TRUE(cl0 != mw5);

  EXPECT_TRUE(fg0 != em1);
  EXPECT_TRUE(fg0 != cl1);
  EXPECT_FALSE(fg0 != fg1);
  EXPECT_TRUE(fg0 != fl1);
  EXPECT_TRUE(fg0 != rs1);
  EXPECT_TRUE(fg0 != rs2);
  EXPECT_TRUE(fg0 != rs3);
  EXPECT_TRUE(fg0 != kp1);
  EXPECT_TRUE(fg0 != kp2);
  EXPECT_TRUE(fg0 != kp3);
  EXPECT_TRUE(fg0 != kp4);
  EXPECT_TRUE(fg0 != kp5);
  EXPECT_TRUE(fg0 != kp6);
  EXPECT_TRUE(fg0 != kp7);
  EXPECT_TRUE(fg0 != kr1);
  EXPECT_TRUE(fg0 != kr2);
  EXPECT_TRUE(fg0 != kr3);
  EXPECT_TRUE(fg0 != kr4);
  EXPECT_TRUE(fg0 != kr5);
  EXPECT_TRUE(fg0 != kr6);
  EXPECT_TRUE(fg0 != kr7);
  EXPECT_TRUE(fg0 != te1);
  EXPECT_TRUE(fg0 != te2);
  EXPECT_TRUE(fg0 != mm1);
  EXPECT_TRUE(fg0 != mm2);
  EXPECT_TRUE(fg0 != mm3);
  EXPECT_TRUE(fg0 != me1);
  EXPECT_TRUE(fg0 != ml1);
  EXPECT_TRUE(fg0 != mp1);
  EXPECT_TRUE(fg0 != mp2);
  EXPECT_TRUE(fg0 != mp3);
  EXPECT_TRUE(fg0 != mp4);
  EXPECT_TRUE(fg0 != mr1);
  EXPECT_TRUE(fg0 != mr2);
  EXPECT_TRUE(fg0 != mr3);
  EXPECT_TRUE(fg0 != mr4);
  EXPECT_TRUE(fg0 != mw1);
  EXPECT_TRUE(fg0 != mw2);
  EXPECT_TRUE(fg0 != mw3);
  EXPECT_TRUE(fg0 != mw4);
  EXPECT_TRUE(fg0 != mw5);

  EXPECT_TRUE(fl0 != em1);
  EXPECT_TRUE(fl0 != cl1);
  EXPECT_TRUE(fl0 != fg1);
  EXPECT_FALSE(fl0 != fl1);
  EXPECT_TRUE(fl0 != rs1);
  EXPECT_TRUE(fl0 != rs2);
  EXPECT_TRUE(fl0 != rs3);
  EXPECT_TRUE(fl0 != kp1);
  EXPECT_TRUE(fl0 != kp2);
  EXPECT_TRUE(fl0 != kp3);
  EXPECT_TRUE(fl0 != kp4);
  EXPECT_TRUE(fl0 != kp5);
  EXPECT_TRUE(fl0 != kp6);
  EXPECT_TRUE(fl0 != kp7);
  EXPECT_TRUE(fl0 != kr1);
  EXPECT_TRUE(fl0 != kr2);
  EXPECT_TRUE(fl0 != kr3);
  EXPECT_TRUE(fl0 != kr4);
  EXPECT_TRUE(fl0 != kr5);
  EXPECT_TRUE(fl0 != kr6);
  EXPECT_TRUE(fl0 != kr7);
  EXPECT_TRUE(fl0 != te1);
  EXPECT_TRUE(fl0 != te2);
  EXPECT_TRUE(fl0 != mm1);
  EXPECT_TRUE(fl0 != mm2);
  EXPECT_TRUE(fl0 != mm3);
  EXPECT_TRUE(fl0 != me1);
  EXPECT_TRUE(fl0 != ml1);
  EXPECT_TRUE(fl0 != mp1);
  EXPECT_TRUE(fl0 != mp2);
  EXPECT_TRUE(fl0 != mp3);
  EXPECT_TRUE(fl0 != mp4);
  EXPECT_TRUE(fl0 != mr1);
  EXPECT_TRUE(fl0 != mr2);
  EXPECT_TRUE(fl0 != mr3);
  EXPECT_TRUE(fl0 != mr4);
  EXPECT_TRUE(fl0 != mw1);
  EXPECT_TRUE(fl0 != mw2);
  EXPECT_TRUE(fl0 != mw3);
  EXPECT_TRUE(fl0 != mw4);
  EXPECT_TRUE(fl0 != mw5);

  EXPECT_TRUE(rs0 != em1);
  EXPECT_TRUE(rs0 != cl1);
  EXPECT_TRUE(rs0 != fg1);
  EXPECT_TRUE(rs0 != fl1);
  EXPECT_FALSE(rs0 != rs1);
  EXPECT_TRUE(rs0 != rs2);
  EXPECT_TRUE(rs0 != rs3);
  EXPECT_TRUE(rs0 != kp1);
  EXPECT_TRUE(rs0 != kp2);
  EXPECT_TRUE(rs0 != kp3);
  EXPECT_TRUE(rs0 != kp4);
  EXPECT_TRUE(rs0 != kp5);
  EXPECT_TRUE(rs0 != kp6);
  EXPECT_TRUE(rs0 != kp7);
  EXPECT_TRUE(rs0 != kr1);
  EXPECT_TRUE(rs0 != kr2);
  EXPECT_TRUE(rs0 != kr3);
  EXPECT_TRUE(rs0 != kr4);
  EXPECT_TRUE(rs0 != kr5);
  EXPECT_TRUE(rs0 != kr6);
  EXPECT_TRUE(rs0 != kr7);
  EXPECT_TRUE(rs0 != te1);
  EXPECT_TRUE(rs0 != te2);
  EXPECT_TRUE(rs0 != mm1);
  EXPECT_TRUE(rs0 != mm2);
  EXPECT_TRUE(rs0 != mm3);
  EXPECT_TRUE(rs0 != me1);
  EXPECT_TRUE(rs0 != ml1);
  EXPECT_TRUE(rs0 != mp1);
  EXPECT_TRUE(rs0 != mp2);
  EXPECT_TRUE(rs0 != mp3);
  EXPECT_TRUE(rs0 != mp4);
  EXPECT_TRUE(rs0 != mr1);
  EXPECT_TRUE(rs0 != mr2);
  EXPECT_TRUE(rs0 != mr3);
  EXPECT_TRUE(rs0 != mr4);
  EXPECT_TRUE(rs0 != mw1);
  EXPECT_TRUE(rs0 != mw2);
  EXPECT_TRUE(rs0 != mw3);
  EXPECT_TRUE(rs0 != mw4);
  EXPECT_TRUE(rs0 != mw5);

  EXPECT_TRUE(kp0 != em1);
  EXPECT_TRUE(kp0 != cl1);
  EXPECT_TRUE(kp0 != fg1);
  EXPECT_TRUE(kp0 != fl1);
  EXPECT_TRUE(kp0 != rs1);
  EXPECT_TRUE(kp0 != rs2);
  EXPECT_TRUE(kp0 != rs3);
  EXPECT_FALSE(kp0 != kp1);
  EXPECT_TRUE(kp0 != kp2);
  EXPECT_TRUE(kp0 != kp3);
  EXPECT_TRUE(kp0 != kp4);
  EXPECT_TRUE(kp0 != kp5);
  EXPECT_TRUE(kp0 != kp6);
  EXPECT_TRUE(kp0 != kp7);
  EXPECT_TRUE(kp0 != kr1);
  EXPECT_TRUE(kp0 != kr2);
  EXPECT_TRUE(kp0 != kr3);
  EXPECT_TRUE(kp0 != kr4);
  EXPECT_TRUE(kp0 != kr5);
  EXPECT_TRUE(kp0 != kr6);
  EXPECT_TRUE(kp0 != kr7);
  EXPECT_TRUE(kp0 != te1);
  EXPECT_TRUE(kp0 != te2);
  EXPECT_TRUE(kp0 != mm1);
  EXPECT_TRUE(kp0 != mm2);
  EXPECT_TRUE(kp0 != mm3);
  EXPECT_TRUE(kp0 != me1);
  EXPECT_TRUE(kp0 != ml1);
  EXPECT_TRUE(kp0 != mp1);
  EXPECT_TRUE(kp0 != mp2);
  EXPECT_TRUE(kp0 != mp3);
  EXPECT_TRUE(kp0 != mp4);
  EXPECT_TRUE(kp0 != mr1);
  EXPECT_TRUE(kp0 != mr2);
  EXPECT_TRUE(kp0 != mr3);
  EXPECT_TRUE(kp0 != mr4);
  EXPECT_TRUE(kp0 != mw1);
  EXPECT_TRUE(kp0 != mw2);
  EXPECT_TRUE(kp0 != mw3);
  EXPECT_TRUE(kp0 != mw4);
  EXPECT_TRUE(kp0 != mw5);

  EXPECT_TRUE(kr0 != em1);
  EXPECT_TRUE(kr0 != cl1);
  EXPECT_TRUE(kr0 != fg1);
  EXPECT_TRUE(kr0 != fl1);
  EXPECT_TRUE(kr0 != rs1);
  EXPECT_TRUE(kr0 != rs2);
  EXPECT_TRUE(kr0 != rs3);
  EXPECT_TRUE(kr0 != kp1);
  EXPECT_TRUE(kr0 != kp2);
  EXPECT_TRUE(kr0 != kp3);
  EXPECT_TRUE(kr0 != kp4);
  EXPECT_TRUE(kr0 != kp5);
  EXPECT_TRUE(kr0 != kp6);
  EXPECT_TRUE(kr0 != kp7);
  EXPECT_FALSE(kr0 != kr1);
  EXPECT_TRUE(kr0 != kr2);
  EXPECT_TRUE(kr0 != kr3);
  EXPECT_TRUE(kr0 != kr4);
  EXPECT_TRUE(kr0 != kr5);
  EXPECT_TRUE(kr0 != kr6);
  EXPECT_TRUE(kr0 != kr7);
  EXPECT_TRUE(kr0 != te1);
  EXPECT_TRUE(kr0 != te2);
  EXPECT_TRUE(kr0 != mm1);
  EXPECT_TRUE(kr0 != mm2);
  EXPECT_TRUE(kr0 != mm3);
  EXPECT_TRUE(kr0 != me1);
  EXPECT_TRUE(kr0 != ml1);
  EXPECT_TRUE(kr0 != mp1);
  EXPECT_TRUE(kr0 != mp2);
  EXPECT_TRUE(kr0 != mp3);
  EXPECT_TRUE(kr0 != mp4);
  EXPECT_TRUE(kr0 != mr1);
  EXPECT_TRUE(kr0 != mr2);
  EXPECT_TRUE(kr0 != mr3);
  EXPECT_TRUE(kr0 != mr4);
  EXPECT_TRUE(kr0 != mw1);
  EXPECT_TRUE(kr0 != mw2);
  EXPECT_TRUE(kr0 != mw3);
  EXPECT_TRUE(kr0 != mw4);
  EXPECT_TRUE(kr0 != mw5);

  EXPECT_TRUE(te0 != em1);
  EXPECT_TRUE(te0 != cl1);
  EXPECT_TRUE(te0 != fg1);
  EXPECT_TRUE(te0 != fl1);
  EXPECT_TRUE(te0 != rs1);
  EXPECT_TRUE(te0 != rs2);
  EXPECT_TRUE(te0 != rs3);
  EXPECT_TRUE(te0 != kp1);
  EXPECT_TRUE(te0 != kp2);
  EXPECT_TRUE(te0 != kp3);
  EXPECT_TRUE(te0 != kp4);
  EXPECT_TRUE(te0 != kp5);
  EXPECT_TRUE(te0 != kp6);
  EXPECT_TRUE(te0 != kp7);
  EXPECT_TRUE(te0 != kr1);
  EXPECT_TRUE(te0 != kr2);
  EXPECT_TRUE(te0 != kr3);
  EXPECT_TRUE(te0 != kr4);
  EXPECT_TRUE(te0 != kr5);
  EXPECT_TRUE(te0 != kr6);
  EXPECT_TRUE(te0 != kr7);
  EXPECT_FALSE(te0 != te1);
  EXPECT_TRUE(te0 != te2);
  EXPECT_TRUE(te0 != mm1);
  EXPECT_TRUE(te0 != mm2);
  EXPECT_TRUE(te0 != mm3);
  EXPECT_TRUE(te0 != me1);
  EXPECT_TRUE(te0 != ml1);
  EXPECT_TRUE(te0 != mp1);
  EXPECT_TRUE(te0 != mp2);
  EXPECT_TRUE(te0 != mp3);
  EXPECT_TRUE(te0 != mp4);
  EXPECT_TRUE(te0 != mr1);
  EXPECT_TRUE(te0 != mr2);
  EXPECT_TRUE(te0 != mr3);
  EXPECT_TRUE(te0 != mr4);
  EXPECT_TRUE(te0 != mw1);
  EXPECT_TRUE(te0 != mw2);
  EXPECT_TRUE(te0 != mw3);
  EXPECT_TRUE(te0 != mw4);
  EXPECT_TRUE(te0 != mw5);

  EXPECT_TRUE(mm0 != em1);
  EXPECT_TRUE(mm0 != cl1);
  EXPECT_TRUE(mm0 != fg1);
  EXPECT_TRUE(mm0 != fl1);
  EXPECT_TRUE(mm0 != rs1);
  EXPECT_TRUE(mm0 != rs2);
  EXPECT_TRUE(mm0 != rs3);
  EXPECT_TRUE(mm0 != kp1);
  EXPECT_TRUE(mm0 != kp2);
  EXPECT_TRUE(mm0 != kp3);
  EXPECT_TRUE(mm0 != kp4);
  EXPECT_TRUE(mm0 != kp5);
  EXPECT_TRUE(mm0 != kp6);
  EXPECT_TRUE(mm0 != kp7);
  EXPECT_TRUE(mm0 != kr1);
  EXPECT_TRUE(mm0 != kr2);
  EXPECT_TRUE(mm0 != kr3);
  EXPECT_TRUE(mm0 != kr4);
  EXPECT_TRUE(mm0 != kr5);
  EXPECT_TRUE(mm0 != kr6);
  EXPECT_TRUE(mm0 != kr7);
  EXPECT_TRUE(mm0 != te1);
  EXPECT_TRUE(mm0 != te2);
  EXPECT_FALSE(mm0 != mm1);
  EXPECT_TRUE(mm0 != mm2);
  EXPECT_TRUE(mm0 != mm3);
  EXPECT_TRUE(mm0 != me1);
  EXPECT_TRUE(mm0 != ml1);
  EXPECT_TRUE(mm0 != mp1);
  EXPECT_TRUE(mm0 != mp2);
  EXPECT_TRUE(mm0 != mp3);
  EXPECT_TRUE(mm0 != mp4);
  EXPECT_TRUE(mm0 != mr1);
  EXPECT_TRUE(mm0 != mr2);
  EXPECT_TRUE(mm0 != mr3);
  EXPECT_TRUE(mm0 != mr4);
  EXPECT_TRUE(mm0 != mw1);
  EXPECT_TRUE(mm0 != mw2);
  EXPECT_TRUE(mm0 != mw3);
  EXPECT_TRUE(mm0 != mw4);
  EXPECT_TRUE(mm0 != mw5);

  EXPECT_TRUE(me0 != em1);
  EXPECT_TRUE(me0 != cl1);
  EXPECT_TRUE(me0 != fg1);
  EXPECT_TRUE(me0 != fl1);
  EXPECT_TRUE(me0 != rs1);
  EXPECT_TRUE(me0 != rs2);
  EXPECT_TRUE(me0 != rs3);
  EXPECT_TRUE(me0 != kp1);
  EXPECT_TRUE(me0 != kp2);
  EXPECT_TRUE(me0 != kp3);
  EXPECT_TRUE(me0 != kp4);
  EXPECT_TRUE(me0 != kp5);
  EXPECT_TRUE(me0 != kp6);
  EXPECT_TRUE(me0 != kp7);
  EXPECT_TRUE(me0 != kr1);
  EXPECT_TRUE(me0 != kr2);
  EXPECT_TRUE(me0 != kr3);
  EXPECT_TRUE(me0 != kr4);
  EXPECT_TRUE(me0 != kr5);
  EXPECT_TRUE(me0 != kr6);
  EXPECT_TRUE(me0 != kr7);
  EXPECT_TRUE(me0 != te1);
  EXPECT_TRUE(me0 != te2);
  EXPECT_TRUE(me0 != mm1);
  EXPECT_TRUE(me0 != mm2);
  EXPECT_TRUE(me0 != mm3);
  EXPECT_FALSE(me0 != me1);
  EXPECT_TRUE(me0 != ml1);
  EXPECT_TRUE(me0 != mp1);
  EXPECT_TRUE(me0 != mp2);
  EXPECT_TRUE(me0 != mp3);
  EXPECT_TRUE(me0 != mp4);
  EXPECT_TRUE(me0 != mr1);
  EXPECT_TRUE(me0 != mr2);
  EXPECT_TRUE(me0 != mr3);
  EXPECT_TRUE(me0 != mr4);
  EXPECT_TRUE(me0 != mw1);
  EXPECT_TRUE(me0 != mw2);
  EXPECT_TRUE(me0 != mw3);
  EXPECT_TRUE(me0 != mw4);
  EXPECT_TRUE(me0 != mw5);

  EXPECT_TRUE(ml0 != em1);
  EXPECT_TRUE(ml0 != cl1);
  EXPECT_TRUE(ml0 != fg1);
  EXPECT_TRUE(ml0 != fl1);
  EXPECT_TRUE(ml0 != rs1);
  EXPECT_TRUE(ml0 != rs2);
  EXPECT_TRUE(ml0 != rs3);
  EXPECT_TRUE(ml0 != kp1);
  EXPECT_TRUE(ml0 != kp2);
  EXPECT_TRUE(ml0 != kp3);
  EXPECT_TRUE(ml0 != kp4);
  EXPECT_TRUE(ml0 != kp5);
  EXPECT_TRUE(ml0 != kp6);
  EXPECT_TRUE(ml0 != kp7);
  EXPECT_TRUE(ml0 != kr1);
  EXPECT_TRUE(ml0 != kr2);
  EXPECT_TRUE(ml0 != kr3);
  EXPECT_TRUE(ml0 != kr4);
  EXPECT_TRUE(ml0 != kr5);
  EXPECT_TRUE(ml0 != kr6);
  EXPECT_TRUE(ml0 != kr7);
  EXPECT_TRUE(ml0 != te1);
  EXPECT_TRUE(ml0 != te2);
  EXPECT_TRUE(ml0 != mm1);
  EXPECT_TRUE(ml0 != mm2);
  EXPECT_TRUE(ml0 != mm3);
  EXPECT_TRUE(ml0 != me1);
  EXPECT_FALSE(ml0 != ml1);
  EXPECT_TRUE(ml0 != mp1);
  EXPECT_TRUE(ml0 != mp2);
  EXPECT_TRUE(ml0 != mp3);
  EXPECT_TRUE(ml0 != mp4);
  EXPECT_TRUE(ml0 != mr1);
  EXPECT_TRUE(ml0 != mr2);
  EXPECT_TRUE(ml0 != mr3);
  EXPECT_TRUE(ml0 != mr4);
  EXPECT_TRUE(ml0 != mw1);
  EXPECT_TRUE(ml0 != mw2);
  EXPECT_TRUE(ml0 != mw3);
  EXPECT_TRUE(ml0 != mw4);
  EXPECT_TRUE(ml0 != mw5);

  EXPECT_TRUE(mp0 != em1);
  EXPECT_TRUE(mp0 != cl1);
  EXPECT_TRUE(mp0 != fg1);
  EXPECT_TRUE(mp0 != fl1);
  EXPECT_TRUE(mp0 != rs1);
  EXPECT_TRUE(mp0 != rs2);
  EXPECT_TRUE(mp0 != rs3);
  EXPECT_TRUE(mp0 != kp1);
  EXPECT_TRUE(mp0 != kp2);
  EXPECT_TRUE(mp0 != kp3);
  EXPECT_TRUE(mp0 != kp4);
  EXPECT_TRUE(mp0 != kp5);
  EXPECT_TRUE(mp0 != kp6);
  EXPECT_TRUE(mp0 != kp7);
  EXPECT_TRUE(mp0 != kr1);
  EXPECT_TRUE(mp0 != kr2);
  EXPECT_TRUE(mp0 != kr3);
  EXPECT_TRUE(mp0 != kr4);
  EXPECT_TRUE(mp0 != kr5);
  EXPECT_TRUE(mp0 != kr6);
  EXPECT_TRUE(mp0 != kr7);
  EXPECT_TRUE(mp0 != te1);
  EXPECT_TRUE(mp0 != te2);
  EXPECT_TRUE(mp0 != mm1);
  EXPECT_TRUE(mp0 != mm2);
  EXPECT_TRUE(mp0 != mm3);
  EXPECT_TRUE(mp0 != me1);
  EXPECT_TRUE(mp0 != ml1);
  EXPECT_FALSE(mp0 != mp1);
  EXPECT_TRUE(mp0 != mp2);
  EXPECT_TRUE(mp0 != mp3);
  EXPECT_TRUE(mp0 != mp4);
  EXPECT_TRUE(mp0 != mr1);
  EXPECT_TRUE(mp0 != mr2);
  EXPECT_TRUE(mp0 != mr3);
  EXPECT_TRUE(mp0 != mr4);
  EXPECT_TRUE(mp0 != mw1);
  EXPECT_TRUE(mp0 != mw2);
  EXPECT_TRUE(mp0 != mw3);
  EXPECT_TRUE(mp0 != mw4);
  EXPECT_TRUE(mp0 != mw5);

  EXPECT_TRUE(mr0 != em1);
  EXPECT_TRUE(mr0 != cl1);
  EXPECT_TRUE(mr0 != fg1);
  EXPECT_TRUE(mr0 != fl1);
  EXPECT_TRUE(mr0 != rs1);
  EXPECT_TRUE(mr0 != rs2);
  EXPECT_TRUE(mr0 != rs3);
  EXPECT_TRUE(mr0 != kp1);
  EXPECT_TRUE(mr0 != kp2);
  EXPECT_TRUE(mr0 != kp3);
  EXPECT_TRUE(mr0 != kp4);
  EXPECT_TRUE(mr0 != kp5);
  EXPECT_TRUE(mr0 != kp6);
  EXPECT_TRUE(mr0 != kp7);
  EXPECT_TRUE(mr0 != kr1);
  EXPECT_TRUE(mr0 != kr2);
  EXPECT_TRUE(mr0 != kr3);
  EXPECT_TRUE(mr0 != kr4);
  EXPECT_TRUE(mr0 != kr5);
  EXPECT_TRUE(mr0 != kr6);
  EXPECT_TRUE(mr0 != kr7);
  EXPECT_TRUE(mr0 != te1);
  EXPECT_TRUE(mr0 != te2);
  EXPECT_TRUE(mr0 != mm1);
  EXPECT_TRUE(mr0 != mm2);
  EXPECT_TRUE(mr0 != mm3);
  EXPECT_TRUE(mr0 != me1);
  EXPECT_TRUE(mr0 != ml1);
  EXPECT_TRUE(mr0 != mp1);
  EXPECT_TRUE(mr0 != mp2);
  EXPECT_TRUE(mr0 != mp3);
  EXPECT_TRUE(mr0 != mp4);
  EXPECT_FALSE(mr0 != mr1);
  EXPECT_TRUE(mr0 != mr2);
  EXPECT_TRUE(mr0 != mr3);
  EXPECT_TRUE(mr0 != mr4);
  EXPECT_TRUE(mr0 != mw1);
  EXPECT_TRUE(mr0 != mw2);
  EXPECT_TRUE(mr0 != mw3);
  EXPECT_TRUE(mr0 != mw4);
  EXPECT_TRUE(mr0 != mw5);

  EXPECT_TRUE(mw0 != em1);
  EXPECT_TRUE(mw0 != cl1);
  EXPECT_TRUE(mw0 != fg1);
  EXPECT_TRUE(mw0 != fl1);
  EXPECT_TRUE(mw0 != rs1);
  EXPECT_TRUE(mw0 != rs2);
  EXPECT_TRUE(mw0 != rs3);
  EXPECT_TRUE(mw0 != kp1);
  EXPECT_TRUE(mw0 != kp2);
  EXPECT_TRUE(mw0 != kp3);
  EXPECT_TRUE(mw0 != kp4);
  EXPECT_TRUE(mw0 != kp5);
  EXPECT_TRUE(mw0 != kp6);
  EXPECT_TRUE(mw0 != kp7);
  EXPECT_TRUE(mw0 != kr1);
  EXPECT_TRUE(mw0 != kr2);
  EXPECT_TRUE(mw0 != kr3);
  EXPECT_TRUE(mw0 != kr4);
  EXPECT_TRUE(mw0 != kr5);
  EXPECT_TRUE(mw0 != kr6);
  EXPECT_TRUE(mw0 != kr7);
  EXPECT_TRUE(mw0 != te1);
  EXPECT_TRUE(mw0 != te2);
  EXPECT_TRUE(mw0 != mm1);
  EXPECT_TRUE(mw0 != mm2);
  EXPECT_TRUE(mw0 != mm3);
  EXPECT_TRUE(mw0 != me1);
  EXPECT_TRUE(mw0 != ml1);
  EXPECT_TRUE(mw0 != mp1);
  EXPECT_TRUE(mw0 != mp2);
  EXPECT_TRUE(mw0 != mp3);
  EXPECT_TRUE(mw0 != mp4);
  EXPECT_TRUE(mw0 != mr1);
  EXPECT_TRUE(mw0 != mr2);
  EXPECT_TRUE(mw0 != mr3);
  EXPECT_TRUE(mw0 != mr4);
  EXPECT_FALSE(mw0 != mw1);
  EXPECT_TRUE(mw0 != mw2);
  EXPECT_TRUE(mw0 != mw3);
  EXPECT_TRUE(mw0 != mw4);
  EXPECT_TRUE(mw0 != mw5);
}



TEST_F(test_window_event, empty_output_stream_operator)
{
  window_event ev = window_event::empty();
  const char* os_ref = "{type = empty, data = {}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, closed_output_stream_operator)
{
  window_event ev = window_event::closed();
  const char* os_ref = "{type = closed, data = {}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, focus_gained_output_stream_operator)
{
  window_event ev = window_event::focus_gained();
  const char* os_ref = "{type = focus_gained, data = {}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, focus_lost_output_stream_operator)
{
  window_event ev = window_event::focus_lost();
  const char* os_ref = "{type = focus_lost, data = {}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, resized_output_stream_operator)
{
  window_event ev = window_event::resized(1u, 3u);
  const char* os_ref = "{type = resized, data = {size_type = (1, 3)}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, key_pressed_output_stream_operator)
{
  window_event ev = window_event::key_pressed(
    key_code::A, scan_code::Q, modifier_keys::alt | modifier_keys::shift);
  const char* os_ref
    = "{type = key_pressed, data = {key_code = A, scan_code = Q, "
      "modifier_keys = alt | 0 | shift | 0}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, key_released_output_stream_operator)
{
  window_event ev = window_event::key_released(key_code::A, scan_code::Q,
    modifier_keys::alt | modifier_keys::ctrl | modifier_keys::system);
  const char* os_ref
    = "{type = key_released, data = {key_code = A, scan_code = Q, "
      "modifier_keys = alt | ctrl | 0 | system}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, text_entered_output_stream_operator)
{
  window_event ev = window_event::text_entered(0x13fa);
  const char* os_ref = "{type = text_entered, data = {code_point = 0x000013fa}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, mouse_moved_output_stream_operator)
{
  window_event ev = window_event::mouse_moved(1, 3);
  const char* os_ref = "{type = mouse_moved, data = {position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, mouse_entered_output_stream_operator)
{
  window_event ev = window_event::mouse_entered();
  const char* os_ref = "{type = mouse_entered, data = {}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, mouse_left_output_stream_operator)
{
  window_event ev = window_event::mouse_left();
  const char* os_ref = "{type = mouse_left, data = {}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, mouse_button_pressed_output_stream_operator)
{
  window_event ev = window_event::mouse_button_pressed(mouse_button::lb, 1, 3);
  const char* os_ref
    = "{type = mouse_button_pressed, data = {button = lb, "
      "position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, mouse_button_released_output_stream_operator)
{
  window_event ev = window_event::mouse_button_released(mouse_button::lb, 1, 3);
  const char* os_ref
    = "{type = mouse_button_released, data = {button = lb, "
      "position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}



TEST_F(test_window_event, mouse_wheel_moved_output_stream_operator)
{
  window_event ev
    = window_event::mouse_wheel_moved(mouse_wheel::vertical, 5, 1, 3);
  const char* os_ref
    = "{type = mouse_wheel_moved, data = {wheel = vertical, "
      "delta = 5, position = (1, 3)}}";
  HOU_EXPECT_OUTPUT(os_ref, ev);
}
