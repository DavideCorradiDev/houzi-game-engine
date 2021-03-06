// Houzi Game Engine
// Copyright (ctx) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_base.hpp"

#include "hou/cor/clock.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_context_exceptions.hpp"
#include "hou/gl/gl_context_settings.hpp"

#include "hou/sys/window.hpp"

#include "SDL_video.h"

#include <thread>

using namespace hou;



namespace
{

class test_gl_context : public testing::Test
{};

using test_gl_context_death_test = test_gl_context;
using test_gl_context_optimizations = test_gl_context;

}  // namespace



TEST_F(test_gl_context, constructor)
{
  window w("Test", vec2u(10u, 10u));
  gl::context ctx(get_test_default_context_settings(), w);

  EXPECT_NE(0u, ctx.get_uid());
  EXPECT_NE(0u, ctx.get_sharing_group_uid());
  EXPECT_FALSE(ctx.is_current());
  EXPECT_EQ(get_test_default_context_settings(), ctx.get_settings());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());
}



TEST_F(test_gl_context, shared_constructor)
{
  window w1("Test", vec2u(1u, 1u));
  gl::context c1(get_test_default_context_settings(), w1);

  EXPECT_NE(0u, c1.get_uid());
  EXPECT_NE(0u, c1.get_sharing_group_uid());
  EXPECT_FALSE(c1.is_current());
  EXPECT_EQ(get_test_default_context_settings(), c1.get_settings());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());

  window w2("Test", vec2u(1u, 1u));
  gl::context c2(get_test_default_context_settings(), w2, c1);

  EXPECT_NE(0u, c2.get_uid());
  EXPECT_NE(0u, c2.get_sharing_group_uid());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(get_test_default_context_settings(), c2.get_settings());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());

  EXPECT_EQ(c1.get_sharing_group_uid(), c2.get_sharing_group_uid());
}



TEST_F(test_gl_context, shared_constructor_binding_preservation)
{
  window w0("Test", vec2u(1u, 1u));
  gl::context c0(get_test_default_context_settings(), w0);
  gl::context::set_current(c0, w0);

  EXPECT_NE(0u, c0.get_uid());
  EXPECT_NE(0u, c0.get_sharing_group_uid());
  EXPECT_EQ(&c0, gl::context::get_current());
  EXPECT_EQ(&w0, gl::context::get_current_window());

  window w1("Test", vec2u(1u, 1u));
  gl::context c1(get_test_default_context_settings(), w1);

  EXPECT_NE(0u, c1.get_uid());
  EXPECT_NE(0u, c1.get_sharing_group_uid());
  EXPECT_EQ(&c0, gl::context::get_current());
  EXPECT_EQ(&w0, gl::context::get_current_window());

  window w2("Test", vec2u(1u, 1u));
  gl::context c2(get_test_default_context_settings(), w2, c1);

  EXPECT_NE(0u, c2.get_uid());
  EXPECT_NE(0u, c2.get_sharing_group_uid());
  EXPECT_EQ(&c0, gl::context::get_current());
  EXPECT_EQ(&w0, gl::context::get_current_window());

  EXPECT_EQ(c1.get_sharing_group_uid(), c2.get_sharing_group_uid());
}



TEST_F(test_gl_context, get_uid)
{
  // Various tests generate contexts. Also, initializing Gl extensions craetes
  // a context. For this reason one may not know beforehand the first
  // context id that will appear in this test, and only the relative value
  // can be tested.
  window w("Test", vec2u(1u, 1u));
  gl::context first_context(get_test_default_context_settings(), w);
  uint32_t first_id = first_context.get_uid() + 1u;

  for(size_t i = 0; i < 5u; ++i)
  {
    gl::context ctx(get_test_default_context_settings(), w);
    EXPECT_EQ(first_id + i, ctx.get_uid());
    EXPECT_EQ(first_id + i, ctx.get_sharing_group_uid());
  }
}



TEST_F(test_gl_context, get_sharing_group_uid)
{
  window w("Test", vec2u(1u, 1u));
  gl::context c1(get_test_default_context_settings(), w);
  gl::context c2(get_test_default_context_settings(), w);
  gl::context c3(get_test_default_context_settings(), w, c1);
  gl::context c4(get_test_default_context_settings(), w, c3);
  gl::context c5(get_test_default_context_settings(), w, c1);
  gl::context c6(get_test_default_context_settings(), w);
  gl::context c7(get_test_default_context_settings(), w, c2);
  gl::context c8(get_test_default_context_settings(), w, c5);

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
  window w("Test", vec2u(1u, 1u));
  gl::context ctx_dummy(get_test_default_context_settings(), w);

  gl::context::impl_type* impl_ref = ctx_dummy.get_impl();
  gl::context::uid_type uid_ref = ctx_dummy.get_uid();
  gl::context::uid_type shared_uid_ref = ctx_dummy.get_sharing_group_uid();

  gl::context ctx = std::move(ctx_dummy);

  EXPECT_EQ(nullptr, ctx_dummy.get_impl());
  EXPECT_EQ(0u, ctx_dummy.get_uid());

  EXPECT_EQ(impl_ref, ctx.get_impl());
  EXPECT_EQ(uid_ref, ctx.get_uid());
  EXPECT_EQ(shared_uid_ref, ctx.get_sharing_group_uid());
  EXPECT_EQ(get_test_default_context_settings(), ctx.get_settings());
}



TEST_F(test_gl_context, current_context_move_constructor)
{
  window w("Test", vec2u(1u, 1u));
  gl::context ctx_dummy(get_test_default_context_settings(), w);

  gl::context::set_current(ctx_dummy, w);
  EXPECT_EQ(&ctx_dummy, gl::context::get_current());
  EXPECT_EQ(&w, gl::context::get_current_window());

  gl::context ctx = std::move(ctx_dummy);
  EXPECT_NE(&ctx_dummy, gl::context::get_current());
  EXPECT_EQ(&ctx, gl::context::get_current());
  EXPECT_EQ(&ctx, gl::context::get_current());
  EXPECT_EQ(&w, gl::context::get_current_window());
}



TEST_F(test_gl_context, move_constructor_get_from_impl)
{
  window w("Test", vec2u(1u, 1u));
  gl::context ctx_dummy(get_test_default_context_settings(), w);
  gl::context ctx(std::move(ctx_dummy));
  EXPECT_EQ(&ctx, &gl::context::get_from_impl(ctx.get_impl()));
}



TEST_F(test_gl_context, get_from_impl)
{
  window w("Test", vec2u(1u, 1u));
  gl::context ctx(get_test_default_context_settings(), w);
  EXPECT_EQ(&ctx, &gl::context::get_from_impl(ctx.get_impl()));
}



TEST_F(test_gl_context_death_test, get_from_impl_after_destruction)
{
  gl::context::impl_type* impl = nullptr;
  {
    window w("Test", vec2u(1u, 1u));
    gl::context ctx(get_test_default_context_settings(), w);
    impl = ctx.get_impl();
  }
  EXPECT_POSTCOND_ERROR(gl::context::get_from_impl(impl));
}



TEST_F(test_gl_context, current_gl_context)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif

  window w1("Test1", vec2u(10u, 10u));
  gl::context c1(get_test_default_context_settings(), w1);
  window w2("Test2", vec2u(10u, 10u));
  gl::context c2(get_test_default_context_settings(), w2);

  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());

  gl::context::set_current(c1, w1);
  EXPECT_TRUE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(&c1, gl::context::get_current());
  EXPECT_EQ(&w1, gl::context::get_current_window());

  gl::context::set_current(c2, w2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, gl::context::get_current());
  EXPECT_EQ(&w2, gl::context::get_current_window());

  gl::context::set_current(c2, w2);
  EXPECT_FALSE(c1.is_current());
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&c2, gl::context::get_current());
  EXPECT_EQ(&w2, gl::context::get_current_window());

  gl::context::unset_current();
  EXPECT_FALSE(c1.is_current());
  EXPECT_FALSE(c2.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());
}



TEST_F(test_gl_context_death_test, set_current_error_multiple_threads)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multi-threading is not supported on Emscripten.");
#endif

#if defined(HOU_SYSTEM_WINDOWS)
  const char msg[] = "wglMakeCurrent(): The requested resource is in use.\r\n";
#elif defined(HOU_SYSTEM_LINUX)
  const char msg[] = "Unable to make GL context current";
#else
  HOU_NOT_IMPLEMENTED();
  const char msg[] = "";
#endif

  window w1("Test", vec2u(10u, 10u));
  gl::context ctx(get_test_default_context_settings(), w1);

  gl::context::set_current(ctx, w1);
  ASSERT_TRUE(ctx.is_current());

  std::thread t([&ctx, &msg]() {
    window w2("Test", vec2u(10u, 10u));
    EXPECT_ERROR_N(
      gl::context::set_current(ctx, w2), gl::context_switch_error, msg);
  });

  t.join();
}



TEST_F(test_gl_context, single_context_multiple_windows)
{
  window w1("Test", vec2u(10u, 10u));
  window w2("Test", vec2u(10u, 10u));
  gl::context ctx(get_test_default_context_settings(), w1);

  gl::context::set_current(ctx, w1);
  EXPECT_TRUE(ctx.is_current());
  EXPECT_EQ(&w1, gl::context::get_current_window());

  gl::context::set_current(ctx, w2);
  EXPECT_TRUE(ctx.is_current());
  EXPECT_EQ(&w2, gl::context::get_current_window());
}



TEST_F(test_gl_context, multiple_contexts_single_window)
{
  window w("Test", vec2u(10u, 10u));
  gl::context c1(get_test_default_context_settings(), w);
  gl::context c2(get_test_default_context_settings(), w);

  gl::context::set_current(c1, w);
  EXPECT_TRUE(c1.is_current());
  EXPECT_EQ(&w, gl::context::get_current_window());

  gl::context::set_current(c2, w);
  EXPECT_TRUE(c2.is_current());
  EXPECT_EQ(&w, gl::context::get_current_window());
}



TEST_F(test_gl_context, binding_after_window_destruction)
{
  window w1("Test", vec2u(10u, 10u));
  gl::context c(get_test_default_context_settings(), w1);
  {
    window w2("Test", vec2u(10u, 10u));
    gl::context::set_current(c, w2);
    EXPECT_TRUE(c.is_current());
    EXPECT_EQ(&c, gl::context::get_current());
    EXPECT_EQ(&w2, gl::context::get_current_window());
    EXPECT_EQ(c.get_impl(), SDL_GL_GetCurrentContext());
    EXPECT_EQ(w2.get_impl(), SDL_GL_GetCurrentWindow());
  }
  EXPECT_FALSE(c.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());
  EXPECT_EQ(nullptr, SDL_GL_GetCurrentContext());
  EXPECT_EQ(nullptr, SDL_GL_GetCurrentWindow());
}



TEST_F(test_gl_context_optimizations, redundant_binding)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif

  static constexpr uint call_count = 1000u;

  window w1("Test", vec2u(4u, 4u));
  window w2("Test", vec2u(4u, 4u));
  gl::context c1(get_test_default_context_settings(), w1);
  gl::context c2(get_test_default_context_settings(), w1);

  // First binding appears to be more expensive.
  // Doing it here reduces bias in the measurements.
  gl::context::set_current(c1, w1);
  gl::context::set_current(c1, w2);
  gl::context::set_current(c2, w1);
  gl::context::set_current(c2, w2);

  // Measurement clock.
  hou::clock clk;

  // Bind to same context window (should not rebind).
  gl::context::unset_current();
  clk = hou::clock();
  for(uint i = 0; i < call_count; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c1, w1);
  }
  std::chrono::nanoseconds time1 = clk.get_elapsed_time();

  // Bind to different window (should rebind).
  gl::context::unset_current();
  clk = hou::clock();
  for(uint i = 0; i < call_count; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c1, w2);
  }
  std::chrono::nanoseconds time2 = clk.get_elapsed_time();

  // Bind to different context (should rebind).
  gl::context::unset_current();
  clk = hou::clock();
  for(uint i = 0; i < call_count; ++i)
  {
    gl::context::set_current(c1, w1);
    gl::context::set_current(c2, w1);
  }
  std::chrono::nanoseconds time3 = clk.get_elapsed_time();

  EXPECT_LT(time1, time2);
  EXPECT_LT(time1, time3);
}
