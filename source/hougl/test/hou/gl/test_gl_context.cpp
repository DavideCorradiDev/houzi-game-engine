// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/clock.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_functions.hpp"

#include "hou/sys/video_mode.hpp"
#include "hou/sys/system_window.hpp"

#include <thread>

using namespace hou;



namespace
{

class TestGlContext : public testing::Test
{
public:
  static void SetUpTestCase();
};

class TestGlContextOptimizations : public TestGlContext
{};
class TestGlContextDeathTest : public TestGlContext
{};



void TestGlContext::SetUpTestCase()
{
  gl::init_extensions();
}

}  // namespace



TEST_F(TestGlContext, Creation)
{
  system_window w("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c(gl::context_settings::standard, w);

  EXPECT_NE(0u, c.get_uid());
  EXPECT_NE(0u, c.getSharingGroupUid());
  EXPECT_FALSE(c.is_current());
}



TEST_F(TestGlContext, SharedCreation)
{
  system_window w1("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w1);
  gl::context c2(gl::context_settings::standard, w2, c1);

  EXPECT_NE(0u, c1.get_uid());
  EXPECT_NE(0u, c1.getSharingGroupUid());
  EXPECT_FALSE(c1.is_current());

  EXPECT_NE(0u, c2.get_uid());
  EXPECT_NE(0u, c2.getSharingGroupUid());
  EXPECT_FALSE(c2.is_current());

  EXPECT_EQ(c1.getSharingGroupUid(), c2.getSharingGroupUid());
}



TEST_F(TestGlContext, GetUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);

  // Various tests generate contexts. Also, initializing Gl extensions craetes
  // a ph_context. For this reason one may not know beforehand the first ph_context
  // id that will appear in this test.
  gl::context firstContext(gl::context_settings::standard, w);
  uint32_t firstId = firstContext.get_uid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    gl::context c(gl::context_settings::standard, w);
    EXPECT_EQ(firstId + i, c.get_uid());
    EXPECT_EQ(firstId + i, c.getSharingGroupUid());
  }
}



TEST_F(TestGlContext, GetSharingGroupUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w);
  gl::context c3(gl::context_settings::standard, w, c1);
  gl::context c4(gl::context_settings::standard, w, c3);
  gl::context c5(gl::context_settings::standard, w, c1);
  gl::context c6(gl::context_settings::standard, w);
  gl::context c7(gl::context_settings::standard, w, c2);
  gl::context c8(gl::context_settings::standard, w, c5);

  EXPECT_NE(c1.getSharingGroupUid(), c2.getSharingGroupUid());
  EXPECT_EQ(c1.getSharingGroupUid(), c3.getSharingGroupUid());
  EXPECT_EQ(c1.getSharingGroupUid(), c4.getSharingGroupUid());
  EXPECT_EQ(c1.getSharingGroupUid(), c5.getSharingGroupUid());
  EXPECT_NE(c1.getSharingGroupUid(), c6.getSharingGroupUid());
  EXPECT_NE(c1.getSharingGroupUid(), c7.getSharingGroupUid());
  EXPECT_EQ(c1.getSharingGroupUid(), c8.getSharingGroupUid());

  EXPECT_NE(c2.getSharingGroupUid(), c3.getSharingGroupUid());
  EXPECT_NE(c2.getSharingGroupUid(), c4.getSharingGroupUid());
  EXPECT_NE(c2.getSharingGroupUid(), c5.getSharingGroupUid());
  EXPECT_NE(c2.getSharingGroupUid(), c6.getSharingGroupUid());
  EXPECT_EQ(c2.getSharingGroupUid(), c7.getSharingGroupUid());
  EXPECT_NE(c2.getSharingGroupUid(), c8.getSharingGroupUid());

  EXPECT_EQ(c3.getSharingGroupUid(), c4.getSharingGroupUid());
  EXPECT_EQ(c3.getSharingGroupUid(), c5.getSharingGroupUid());
  EXPECT_NE(c3.getSharingGroupUid(), c6.getSharingGroupUid());
  EXPECT_NE(c3.getSharingGroupUid(), c7.getSharingGroupUid());
  EXPECT_EQ(c3.getSharingGroupUid(), c8.getSharingGroupUid());

  EXPECT_EQ(c4.getSharingGroupUid(), c5.getSharingGroupUid());
  EXPECT_NE(c4.getSharingGroupUid(), c6.getSharingGroupUid());
  EXPECT_NE(c4.getSharingGroupUid(), c7.getSharingGroupUid());
  EXPECT_EQ(c4.getSharingGroupUid(), c8.getSharingGroupUid());

  EXPECT_NE(c5.getSharingGroupUid(), c6.getSharingGroupUid());
  EXPECT_NE(c5.getSharingGroupUid(), c7.getSharingGroupUid());
  EXPECT_EQ(c5.getSharingGroupUid(), c8.getSharingGroupUid());

  EXPECT_NE(c6.getSharingGroupUid(), c7.getSharingGroupUid());
  EXPECT_NE(c6.getSharingGroupUid(), c8.getSharingGroupUid());

  EXPECT_NE(c7.getSharingGroupUid(), c8.getSharingGroupUid());
}



TEST_F(TestGlContext, MoveConstructor)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c_dummy(gl::context_settings::standard, w);
  gl::context::set_current(c_dummy, w);
  ASSERT_EQ(&c_dummy, gl::context::getCurrent());
  uint32_t uid_ref = c_dummy.get_uid();
  uint32_t sharedUid_ref = c_dummy.getSharingGroupUid();

  gl::context c = std::move(c_dummy);
  ASSERT_NE(&c_dummy, gl::context::getCurrent());
  ASSERT_EQ(&c, gl::context::getCurrent());
  ASSERT_EQ(uid_ref, c.get_uid());
  ASSERT_EQ(sharedUid_ref, c.getSharingGroupUid());
}



TEST_F(TestGlContext, CurrentGlContext)
{
  system_window w1("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w1);
  gl::context c2(gl::context_settings::standard, w2);

  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, gl::context::getCurrent());

  gl::context::set_current(c1, w1);
  EXPECT_TRUE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(&c1, gl::context::getCurrent());

  gl::context::set_current(c2, w2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, gl::context::getCurrent());

  gl::context::set_current(c2, w2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, gl::context::getCurrent());

  gl::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, gl::context::getCurrent());
}



TEST_F(TestGlContext, SingleContextMultipleWindows)
{
  system_window w1("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c(gl::context_settings::standard, w1);

  gl::context::set_current(c, w1);
  EXPECT_TRUE(c.is_current());

  gl::context::set_current(c, w2);
  EXPECT_TRUE(c.is_current());
}



TEST_F(TestGlContext, MultipleContextsSingleWindow)
{
  system_window w("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  EXPECT_TRUE(c1.is_current());

  gl::context::set_current(c2, w);
  EXPECT_TRUE(c2.is_current());
}



TEST_F(TestGlContextDeathTest, MakeCurrentError)
{
  system_window w1("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::context c(gl::context_settings::standard, w1);

  gl::context::set_current(c, w1);
  ASSERT_TRUE(c.is_current());

  std::thread t([&c]() {
    system_window w2("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
    HOU_EXPECT_ERROR(gl::context::set_current(c, w2), std::runtime_error,
      get_text(gl_error::context_make_current));
  });

  t.join();
}



TEST_F(TestGlContextOptimizations, RedundantBinding)
{
  const uint calls = 1000u;

  system_window w1("Test", video_mode(vec2u(4u, 4u), 4u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u(4u, 4u), 4u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w1);
  gl::context c2(gl::context_settings::standard, w1);

  // First binding appears to be more expensive.
  // Doing it here reduces bias in the measurements.
  gl::context::set_current(c1, w1);
  gl::context::set_current(c1, w2);
  gl::context::set_current(c2, w1);
  gl::context::set_current(c2, w2);

  // Measurement p_clock.
  hou::clock p_clock;

  // Bind to same ph_context ph_window (should not rebind).
  gl::context::unset_current();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c1, w1);
  }
  std::chrono::nanoseconds time1 = p_clock.get_elapsed_time();

  // Bind to different ph_window (should rebind).
  gl::context::unset_current();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c1, w2);
  }
  std::chrono::nanoseconds time2 = p_clock.get_elapsed_time();

  // Bind to different ph_context (should rebind).
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
