// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

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
  graphic_context rc;
  SUCCEED();
}



TEST_F(test_graphic_context, move_constructor)
{
  graphic_context rc_dummy;
  graphic_context::set_current(rc_dummy);
  graphic_context rc = std::move(rc_dummy);
  EXPECT_TRUE(rc.is_current());
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
    graphic_context rc;
    EXPECT_FALSE(rc.is_current());
    graphic_context::set_current(rc);
    EXPECT_TRUE(rc.is_current());
  }
  EXPECT_EQ(nullptr, gl::context::get_current());
}



TEST_F(test_graphic_context, default_context_parameters)
{
  graphic_context rc;
  graphic_context::set_current(rc);

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



TEST_F(test_graphic_context, get_rendering_color_byte_count)
{
  EXPECT_EQ(4u, graphic_context::get_rendering_color_byte_count());
}



TEST_F(test_graphic_context, get_rendering_depth_byte_count)
{
  EXPECT_EQ(3u, graphic_context::get_rendering_depth_byte_count());
}



TEST_F(test_graphic_context, get_rendering_stencil_byte_count)
{
  EXPECT_EQ(1u, graphic_context::get_rendering_stencil_byte_count());
}
