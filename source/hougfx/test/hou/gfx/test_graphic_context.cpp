// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/gfx/graphic_context.hpp"

#include "hou/gl/gl_functions.hpp"
#include "hou/gl/gl_texture_handle.hpp"

using namespace testing;
using namespace hou;



namespace
{

class test_graphic_context : public Test
{};

}  // namespace



TEST_F(test_graphic_context, creation)
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
  graphic_context ctx_dummy;
  graphic_context::set_current(ctx_dummy);
  graphic_context ctx = std::move(ctx_dummy);
  EXPECT_TRUE(ctx.is_current());
}



TEST_F(test_graphic_context, set_current)
{
  {
    graphic_context rc1;
    graphic_context rc2;

    EXPECT_FALSE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());

    graphic_context::set_current(rc1);
    EXPECT_TRUE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());

    graphic_context::set_current(rc2);
    EXPECT_FALSE(rc1.is_current());
    EXPECT_TRUE(rc2.is_current());

    graphic_context::set_current(rc2);
    EXPECT_FALSE(rc1.is_current());
    EXPECT_TRUE(rc2.is_current());

    graphic_context::unset_current();
    EXPECT_FALSE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());

    graphic_context::unset_current();
    EXPECT_FALSE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());
  }
  EXPECT_EQ(nullptr, gl::context::get_current());
}



TEST_F(test_graphic_context, unset_current_on_deletion)
{
  {
    graphic_context ctx;
    EXPECT_FALSE(ctx.is_current());
    graphic_context::set_current(ctx);
    EXPECT_TRUE(ctx.is_current());
  }
  EXPECT_EQ(nullptr, gl::context::get_current());
}



TEST_F(test_graphic_context, default_context_parameters)
{
  graphic_context ctx;
  graphic_context::set_current(ctx);

  EXPECT_EQ(1, gl::get_unpack_alignment());
  EXPECT_EQ(1, gl::get_pack_alignment());

  EXPECT_FALSE(gl::is_multisampling_enabled());

  EXPECT_TRUE(gl::is_blending_enabled());
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_ALPHA), gl::get_source_blending());
  EXPECT_EQ(static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA),
    gl::get_destination_blending());
}



TEST_F(test_graphic_context, context_parameters_with_context_switch)
{
  graphic_context rc1;
  graphic_context rc2;

  graphic_context::set_current(rc1);
  EXPECT_EQ(1, gl::get_unpack_alignment());
  gl::set_unpack_alignment(4);
  EXPECT_EQ(4, gl::get_unpack_alignment());

  graphic_context::set_current(rc2);
  EXPECT_EQ(1, gl::get_unpack_alignment());

  graphic_context::set_current(rc1);
  EXPECT_EQ(4, gl::get_unpack_alignment());
}
