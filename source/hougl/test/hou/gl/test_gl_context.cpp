// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/cor/clock.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_exceptions.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/system_window.hpp"
#include "hou/sys/video_mode.hpp"

#include <thread>

using namespace hou;



namespace
{

class test_gl_context : public testing::Test
{
public:
  static void SetUpTestCase();
};

class test_gl_context_optimizations : public test_gl_context
{};

class test_gl_context_death_test : public test_gl_context
{};



void test_gl_context::SetUpTestCase()
{
  gl::init_extensions();
}

}  // namespace



TEST_F(test_gl_context, creation)
{
  system_window w(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c(gl::context_settings::get_default(), w);

  EXPECT_NE(0u, c.get_uid());
  EXPECT_NE(0u, c.get_sharing_group_uid());
  EXPECT_FALSE(c.is_current());
}



TEST_F(test_gl_context_death_test, creation_error_unsupported_version)
{
  system_window w(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::version v(8u, 9u);
  gl::context_settings settings = gl::context_settings::get_default();
  settings.set_version(v);

  EXPECT_ERROR_N(gl::context c(settings, w), gl::unsupported_version, v);
}



// TEST_F(test_gl_context, shared_creation)
// {
//   system_window w1(
//     "Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
//   system_window w2(
//     "Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
//   gl::context c1(gl::context_settings::get_default(), w1);
//   gl::context c2(gl::context_settings::get_default(), w2, c1);
// 
//   EXPECT_NE(0u, c1.get_uid());
//   EXPECT_NE(0u, c1.get_sharing_group_uid());
//   EXPECT_FALSE(c1.is_current());
// 
//   EXPECT_NE(0u, c2.get_uid());
//   EXPECT_NE(0u, c2.get_sharing_group_uid());
//   EXPECT_FALSE(c2.is_current());
// 
//   EXPECT_EQ(c1.get_sharing_group_uid(), c2.get_sharing_group_uid());
// }



TEST_F(test_gl_context, get_uid)
{
  system_window w(
    "Test", video_mode(vec2u::zero(), 0u), window_style::windowed);

  // Various tests generate contexts. Also, initializing Gl extensions craetes
  // a context. For this reason one may not know beforehand the first
  // context id that will appear in this test.
  gl::context first_context(gl::context_settings::get_default(), w);
  uint32_t first_id = first_context.get_uid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    gl::context c(gl::context_settings::get_default(), w);
    EXPECT_EQ(first_id + i, c.get_uid());
    EXPECT_EQ(first_id + i, c.get_sharing_group_uid());
  }
}



TEST_F(test_gl_context, get_sharing_group_uid)
{
  system_window w(
    "Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w);
  gl::context c3(gl::context_settings::get_default(), w, c1);
  gl::context c4(gl::context_settings::get_default(), w, c3);
  gl::context c5(gl::context_settings::get_default(), w, c1);
  gl::context c6(gl::context_settings::get_default(), w);
  gl::context c7(gl::context_settings::get_default(), w, c2);
  gl::context c8(gl::context_settings::get_default(), w, c5);

  EXPECT_NE(c1.get_sharing_group_uid(), c2.get_sharing_group_uid());
  EXPECT_EQ(c1.get_sharing_group_uid(), c3.get_sharing_group_uid());
  EXPECT_EQ(c1.get_sharing_group_uid(), c4.get_sharing_group_uid());
  EXPECT_EQ(c1.get_sharing_group_uid(), c5.get_sharing_group_uid());
  EXPECT_NE(c1.get_sharing_group_uid(), c6.get_sharing_group_uid());
  EXPECT_NE(c1.get_sharing_group_uid(), c7.get_sharing_group_uid());
  EXPECT_EQ(c1.get_sharing_group_uid(), c8.get_sharing_group_uid());

  EXPECT_NE(c2.get_sharing_group_uid(), c3.get_sharing_group_uid());
  EXPECT_NE(c2.get_sharing_group_uid(), c4.get_sharing_group_uid());
  EXPECT_NE(c2.get_sharing_group_uid(), c5.get_sharing_group_uid());
  EXPECT_NE(c2.get_sharing_group_uid(), c6.get_sharing_group_uid());
  EXPECT_EQ(c2.get_sharing_group_uid(), c7.get_sharing_group_uid());
  EXPECT_NE(c2.get_sharing_group_uid(), c8.get_sharing_group_uid());

  EXPECT_EQ(c3.get_sharing_group_uid(), c4.get_sharing_group_uid());
  EXPECT_EQ(c3.get_sharing_group_uid(), c5.get_sharing_group_uid());
  EXPECT_NE(c3.get_sharing_group_uid(), c6.get_sharing_group_uid());
  EXPECT_NE(c3.get_sharing_group_uid(), c7.get_sharing_group_uid());
  EXPECT_EQ(c3.get_sharing_group_uid(), c8.get_sharing_group_uid());

  EXPECT_EQ(c4.get_sharing_group_uid(), c5.get_sharing_group_uid());
  EXPECT_NE(c4.get_sharing_group_uid(), c6.get_sharing_group_uid());
  EXPECT_NE(c4.get_sharing_group_uid(), c7.get_sharing_group_uid());
  EXPECT_EQ(c4.get_sharing_group_uid(), c8.get_sharing_group_uid());

  EXPECT_NE(c5.get_sharing_group_uid(), c6.get_sharing_group_uid());
  EXPECT_NE(c5.get_sharing_group_uid(), c7.get_sharing_group_uid());
  EXPECT_EQ(c5.get_sharing_group_uid(), c8.get_sharing_group_uid());

  EXPECT_NE(c6.get_sharing_group_uid(), c7.get_sharing_group_uid());
  EXPECT_NE(c6.get_sharing_group_uid(), c8.get_sharing_group_uid());

  EXPECT_NE(c7.get_sharing_group_uid(), c8.get_sharing_group_uid());
}



TEST_F(test_gl_context, move_constructor)
{
  system_window w(
    "Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c_dummy(gl::context_settings::get_default(), w);
  gl::context::set_current(c_dummy, w);
  ASSERT_EQ(&c_dummy, gl::context::get_current());
  uint32_t uid_ref = c_dummy.get_uid();
  uint32_t shared_uid_ref = c_dummy.get_sharing_group_uid();

  gl::context c = std::move(c_dummy);
  ASSERT_NE(&c_dummy, gl::context::get_current());
  ASSERT_EQ(&c, gl::context::get_current());
  ASSERT_EQ(uid_ref, c.get_uid());
  ASSERT_EQ(shared_uid_ref, c.get_sharing_group_uid());
}



TEST_F(test_gl_context, current_gl_context)
{
  system_window w1(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  system_window w2(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c1(gl::context_settings::get_default(), w1);
  gl::context c2(gl::context_settings::get_default(), w2);

  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());

  gl::context::set_current(c1, w1);
  EXPECT_TRUE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(&c1, gl::context::get_current());

  gl::context::set_current(c2, w2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, gl::context::get_current());

  gl::context::set_current(c2, w2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, gl::context::get_current());

  gl::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
}



TEST_F(test_gl_context, single_context_multiple_windows)
{
  system_window w1(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  system_window w2(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c(gl::context_settings::get_default(), w1);

  gl::context::set_current(c, w1);
  EXPECT_TRUE(c.is_current());

  gl::context::set_current(c, w2);
  EXPECT_TRUE(c.is_current());
}



TEST_F(test_gl_context, multiple_contexts_single_window)
{
  system_window w(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c1(gl::context_settings::get_default(), w);
  gl::context c2(gl::context_settings::get_default(), w);

  gl::context::set_current(c1, w);
  EXPECT_TRUE(c1.is_current());

  gl::context::set_current(c2, w);
  EXPECT_TRUE(c2.is_current());
}



TEST_F(test_gl_context_death_test, make_current_error)
{
  system_window w1(
    "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c(gl::context_settings::get_default(), w1);

  gl::context::set_current(c, w1);
  ASSERT_TRUE(c.is_current());

  std::thread t([&c]() {
    system_window w2(
      "Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
    EXPECT_ERROR_0(gl::context::set_current(c, w2), gl::context_switch_error);
  });

  t.join();
}



TEST_F(test_gl_context_optimizations, redundant_binding)
{
  const uint calls = 1000u;

  system_window w1(
    "Test", video_mode(vec2u(4u, 4u), 4u), window_style::windowed);
  system_window w2(
    "Test", video_mode(vec2u(4u, 4u), 4u), window_style::windowed);
  gl::context c1(gl::context_settings::get_default(), w1);
  gl::context c2(gl::context_settings::get_default(), w1);

  // First binding appears to be more expensive.
  // Doing it here reduces bias in the measurements.
  gl::context::set_current(c1, w1);
  gl::context::set_current(c1, w2);
  gl::context::set_current(c2, w1);
  gl::context::set_current(c2, w2);

  // Measurement p_clock.
  hou::clock p_clock;

  // Bind to same context window (should not rebind).
  gl::context::unset_current();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c1, w1);
  }
  std::chrono::nanoseconds time1 = p_clock.get_elapsed_time();

  // Bind to different window (should rebind).
  gl::context::unset_current();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c1, w2);
  }
  std::chrono::nanoseconds time2 = p_clock.get_elapsed_time();

  // Bind to different context (should rebind).
  gl::context::unset_current();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c2, w1);
  }
  std::chrono::nanoseconds time3 = p_clock.get_elapsed_time();

  EXPECT_LT(time1, time2);
  EXPECT_LT(time1, time3);
}

// Failing creation test.
// Failing destruction test.
