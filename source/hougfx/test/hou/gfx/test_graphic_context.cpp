// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gfx/graphic_context.hpp"
#include "hou/gfx/graphics_state.hpp"

#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_texture_handle.hpp"

#include "hou/sys/event.hpp"

using namespace testing;
using namespace hou;



namespace
{

class test_graphic_context : public Test
{};

using test_graphic_context_death_test = test_graphic_context;

}  // namespace



TEST_F(test_graphic_context, constructor)
{
  graphic_context ctx;
  EXPECT_NE(0u, ctx.get_impl().get_uid());
}



TEST_F(test_graphic_context, move_constructor)
{
  graphic_context ctx_dummy;
  gl::context::uid_type ctx_uid = ctx_dummy.get_impl().get_uid();
  graphic_context ctx = std::move(ctx_dummy);

  EXPECT_EQ(0u, ctx_dummy.get_impl().get_uid());
  EXPECT_EQ(ctx_uid, ctx.get_impl().get_uid());
}



TEST_F(test_graphic_context, move_constructor_current_context)
{
  window wnd("TestWindow", vec2u(1u, 1u));
  graphic_context ctx_dummy;
  graphic_context::set_current(ctx_dummy, wnd);
  graphic_context ctx = std::move(ctx_dummy);
  EXPECT_TRUE(ctx.is_current());
}



TEST_F(test_graphic_context, set_current_context_and_window)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif

  graphic_context ctx1;
  graphic_context ctx2;
  window wnd1("TestWindow", vec2u(1u, 1u));
  window wnd2("TestWindow", vec2u(1u, 1u));

  EXPECT_FALSE(ctx1.is_current());
  EXPECT_FALSE(ctx2.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());

  graphic_context::set_current(ctx1, wnd1);
  EXPECT_TRUE(ctx1.is_current());
  EXPECT_FALSE(ctx2.is_current());
  EXPECT_EQ(&ctx1.get_impl(), gl::context::get_current());
  EXPECT_EQ(&wnd1, gl::context::get_current_window());

  graphic_context::set_current(ctx2, wnd1);
  EXPECT_FALSE(ctx1.is_current());
  EXPECT_TRUE(ctx2.is_current());
  EXPECT_EQ(&ctx2.get_impl(), gl::context::get_current());
  EXPECT_EQ(&wnd1, gl::context::get_current_window());

  graphic_context::set_current(ctx1, wnd2);
  EXPECT_TRUE(ctx1.is_current());
  EXPECT_FALSE(ctx2.is_current());
  EXPECT_EQ(&ctx1.get_impl(), gl::context::get_current());
  EXPECT_EQ(&wnd2, gl::context::get_current_window());

  graphic_context::set_current(ctx2, wnd2);
  EXPECT_FALSE(ctx1.is_current());
  EXPECT_TRUE(ctx2.is_current());
  EXPECT_EQ(&ctx2.get_impl(), gl::context::get_current());
  EXPECT_EQ(&wnd2, gl::context::get_current_window());

  graphic_context::unset_current();
  EXPECT_FALSE(ctx1.is_current());
  EXPECT_FALSE(ctx2.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());
}



TEST_F(test_graphic_context, set_current_window)
{
  graphic_context ctx;
  window wnd1("TestWindow", vec2u(1u, 1u));
  window wnd2("TestWindow", vec2u(1u, 1u));

  EXPECT_FALSE(ctx.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());

  graphic_context::set_current(ctx, wnd2);
  EXPECT_TRUE(ctx.is_current());
  EXPECT_EQ(&ctx.get_impl(), gl::context::get_current());
  EXPECT_NE(&wnd1, gl::context::get_current_window());
  EXPECT_EQ(&wnd2, gl::context::get_current_window());

  graphic_context::set_current(wnd1);
  EXPECT_TRUE(ctx.is_current());
  EXPECT_EQ(&ctx.get_impl(), gl::context::get_current());
  EXPECT_EQ(&wnd1, gl::context::get_current_window());

  graphic_context::set_current(wnd2);
  EXPECT_TRUE(ctx.is_current());
  EXPECT_EQ(&ctx.get_impl(), gl::context::get_current());
  EXPECT_EQ(&wnd2, gl::context::get_current_window());

  graphic_context::unset_current();
  EXPECT_FALSE(ctx.is_current());
  EXPECT_EQ(nullptr, gl::context::get_current());
  EXPECT_EQ(nullptr, gl::context::get_current_window());
}



TEST_F(
  test_graphic_context_death_test, set_current_window_without_current_context)
{
  graphic_context ctx;
  window wnd("TestWindow", vec2u(1u, 1u));
  EXPECT_PRECOND_ERROR(graphic_context::set_current(wnd));
}



TEST_F(test_graphic_context, unset_current_on_destruction)
{
  {
    window wnd("TestWindow", vec2u(1u, 1u));
    graphic_context ctx;
    EXPECT_FALSE(ctx.is_current());
    graphic_context::set_current(ctx, wnd);
    EXPECT_TRUE(ctx.is_current());
  }
  EXPECT_EQ(nullptr, gl::context::get_current());
}



TEST_F(test_graphic_context, unset_current_on_window_destruction)
{
  graphic_context ctx;
  {
    window wnd("TestWindow", vec2u(1u, 1u));
    EXPECT_FALSE(ctx.is_current());
    graphic_context::set_current(ctx, wnd);
    EXPECT_TRUE(ctx.is_current());
  }
  EXPECT_FALSE(ctx.is_current());
}



TEST_F(test_graphic_context, default_context_parameters)
{
  window wnd("TestWindow", vec2u(1u, 1u));
  graphic_context ctx;
  graphic_context::set_current(ctx, wnd);

  EXPECT_EQ(1, gl::get_unpack_alignment());
  EXPECT_EQ(1, gl::get_pack_alignment());

  EXPECT_TRUE(is_multisampling_enabled());
  EXPECT_TRUE(is_blending_enabled());
  EXPECT_EQ(blending_factor::src_alpha, get_source_blending_factor());
  EXPECT_EQ(
    blending_factor::one_minus_src_alpha, get_destination_blending_factor());
  EXPECT_EQ(blending_equation::add, get_blending_equation());
  EXPECT_EQ(color::transparent(), get_blending_color());
}



TEST_F(test_graphic_context, context_parameters_after_context_switch)
{
#if defined(HOU_EMSCRIPTEN)
  SKIP("Multiple GL contexts are not supported on Emscripten.");
#endif

  window wnd("TestWindow", vec2u(1u, 1u));
  graphic_context ctx1;
  graphic_context ctx2;

  graphic_context::set_current(ctx1, wnd);
  EXPECT_EQ(1, gl::get_unpack_alignment());
  gl::set_unpack_alignment(4);
  EXPECT_EQ(4, gl::get_unpack_alignment());

  graphic_context::set_current(ctx2, wnd);
  EXPECT_EQ(1, gl::get_unpack_alignment());

  graphic_context::set_current(ctx1, wnd);
  EXPECT_EQ(4, gl::get_unpack_alignment());
}
