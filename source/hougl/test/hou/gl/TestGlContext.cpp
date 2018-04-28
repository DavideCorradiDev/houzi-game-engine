// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/cor/clock.hpp"

#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/GlFunctions.hpp"

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
  gl::initExtensions();
}

}  // namespace



TEST_F(TestGlContext, Creation)
{
  system_window w("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::Context c(gl::ContextSettings::Default, w);

  EXPECT_NE(0u, c.get_uid());
  EXPECT_NE(0u, c.getSharingGroupUid());
  EXPECT_FALSE(c.isCurrent());
}



TEST_F(TestGlContext, SharedCreation)
{
  system_window w1("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w1);
  gl::Context c2(gl::ContextSettings::Default, w2, c1);

  EXPECT_NE(0u, c1.get_uid());
  EXPECT_NE(0u, c1.getSharingGroupUid());
  EXPECT_FALSE(c1.isCurrent());

  EXPECT_NE(0u, c2.get_uid());
  EXPECT_NE(0u, c2.getSharingGroupUid());
  EXPECT_FALSE(c2.isCurrent());

  EXPECT_EQ(c1.getSharingGroupUid(), c2.getSharingGroupUid());
}



TEST_F(TestGlContext, GetUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);

  // Various tests generate contexts. Also, initializing Gl extensions craetes
  // a context. For this reason one may not know beforehand the first context
  // id that will appear in this test.
  gl::Context firstContext(gl::ContextSettings::Default, w);
  uint32_t firstId = firstContext.get_uid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    gl::Context c(gl::ContextSettings::Default, w);
    EXPECT_EQ(firstId + i, c.get_uid());
    EXPECT_EQ(firstId + i, c.getSharingGroupUid());
  }
}



TEST_F(TestGlContext, GetSharingGroupUid)
{
  system_window w("Test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w);
  gl::Context c3(gl::ContextSettings::Default, w, c1);
  gl::Context c4(gl::ContextSettings::Default, w, c3);
  gl::Context c5(gl::ContextSettings::Default, w, c1);
  gl::Context c6(gl::ContextSettings::Default, w);
  gl::Context c7(gl::ContextSettings::Default, w, c2);
  gl::Context c8(gl::ContextSettings::Default, w, c5);

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
  gl::Context cDummy(gl::ContextSettings::Default, w);
  gl::Context::setCurrent(cDummy, w);
  ASSERT_EQ(&cDummy, gl::Context::getCurrent());
  uint32_t uidRef = cDummy.get_uid();
  uint32_t sharedUidRef = cDummy.getSharingGroupUid();

  gl::Context c = std::move(cDummy);
  ASSERT_NE(&cDummy, gl::Context::getCurrent());
  ASSERT_EQ(&c, gl::Context::getCurrent());
  ASSERT_EQ(uidRef, c.get_uid());
  ASSERT_EQ(sharedUidRef, c.getSharingGroupUid());
}



TEST_F(TestGlContext, CurrentGlContext)
{
  system_window w1("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w1);
  gl::Context c2(gl::ContextSettings::Default, w2);

  EXPECT_FALSE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(nullptr, gl::Context::getCurrent());

  gl::Context::setCurrent(c1, w1);
  EXPECT_TRUE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(&c1, gl::Context::getCurrent());

  gl::Context::setCurrent(c2, w2);
  EXPECT_FALSE(c1.isCurrent());
  EXPECT_TRUE(c2.isCurrent());
  EXPECT_EQ(&c2, gl::Context::getCurrent());

  gl::Context::setCurrent(c2, w2);
  EXPECT_FALSE(c1.isCurrent());
  EXPECT_TRUE(c2.isCurrent());
  EXPECT_EQ(&c2, gl::Context::getCurrent());

  gl::Context::unsetCurrent();
  EXPECT_FALSE(c1.isCurrent());
  EXPECT_FALSE(c2.isCurrent());
  EXPECT_EQ(nullptr, gl::Context::getCurrent());
}



TEST_F(TestGlContext, SingleContextMultipleWindows)
{
  system_window w1("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::Context c(gl::ContextSettings::Default, w1);

  gl::Context::setCurrent(c, w1);
  EXPECT_TRUE(c.isCurrent());

  gl::Context::setCurrent(c, w2);
  EXPECT_TRUE(c.isCurrent());
}



TEST_F(TestGlContext, MultipleContextsSingleWindow)
{
  system_window w("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  EXPECT_TRUE(c1.isCurrent());

  gl::Context::setCurrent(c2, w);
  EXPECT_TRUE(c2.isCurrent());
}



TEST_F(TestGlContextDeathTest, MakeCurrentError)
{
  system_window w1("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
  gl::Context c(gl::ContextSettings::Default, w1);

  gl::Context::setCurrent(c, w1);
  ASSERT_TRUE(c.isCurrent());

  std::thread t([&c]() {
    system_window w2("Test", video_mode(vec2u(10u, 10u), 4u), window_style::windowed);
    HOU_EXPECT_ERROR(gl::Context::setCurrent(c, w2), std::runtime_error,
      get_text(GlError::ContextMakeCurrent));
  });

  t.join();
}



TEST_F(TestGlContextOptimizations, RedundantBinding)
{
  const uint calls = 1000u;

  system_window w1("Test", video_mode(vec2u(4u, 4u), 4u), window_style::windowed);
  system_window w2("Test", video_mode(vec2u(4u, 4u), 4u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w1);
  gl::Context c2(gl::ContextSettings::Default, w1);

  // First binding appears to be more expensive.
  // Doing it here reduces bias in the measurements.
  gl::Context::setCurrent(c1, w1);
  gl::Context::setCurrent(c1, w2);
  gl::Context::setCurrent(c2, w1);
  gl::Context::setCurrent(c2, w2);

  // Measurement p_clock.
  hou::clock p_clock;

  // Bind to same context ph_window (should not rebind).
  gl::Context::unsetCurrent();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::Context::setCurrent(c1, w1);
    gl::Context::setCurrent(c1, w1);
  }
  std::chrono::nanoseconds time1 = p_clock.get_elapsed_time();

  // Bind to different ph_window (should rebind).
  gl::Context::unsetCurrent();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::Context::setCurrent(c1, w1);
    gl::Context::setCurrent(c1, w2);
  }
  std::chrono::nanoseconds time2 = p_clock.get_elapsed_time();

  // Bind to different context (should rebind).
  gl::Context::unsetCurrent();
  p_clock = hou::clock();
  for(uint i = 0; i < calls; ++i)
  {
    gl::Context::setCurrent(c1, w1);
    gl::Context::setCurrent(c2, w1);
  }
  std::chrono::nanoseconds time3 = p_clock.get_elapsed_time();

  EXPECT_LT(time1, time2);
  EXPECT_LT(time1, time3);
}

// Failing creation test.
// Failing destruction test.
