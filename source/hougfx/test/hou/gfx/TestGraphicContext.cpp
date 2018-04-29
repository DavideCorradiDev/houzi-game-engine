// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/GraphicContext.hpp"

#include "hou/gl/gl_texture_handle.hpp"
#include "hou/gl/gl_functions.hpp"

using namespace testing;
using namespace hou;



namespace
{

class TestGraphicContext : public Test
{};

}  // namespace



TEST_F(TestGraphicContext, Creation)
{
  GraphicContext rc;
  SUCCEED();
}



TEST_F(TestGraphicContext, MoveConstructor)
{
  GraphicContext rcDummy;
  GraphicContext::set_current(rcDummy);
  GraphicContext rc = std::move(rcDummy);
  EXPECT_TRUE(rc.is_current());
}



TEST_F(TestGraphicContext, SetCurrent)
{
  {
    GraphicContext rc1;
    GraphicContext rc2;

    EXPECT_FALSE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());

    GraphicContext::set_current(rc1);
    EXPECT_TRUE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());

    GraphicContext::set_current(rc2);
    EXPECT_FALSE(rc1.is_current());
    EXPECT_TRUE(rc2.is_current());

    GraphicContext::set_current(rc2);
    EXPECT_FALSE(rc1.is_current());
    EXPECT_TRUE(rc2.is_current());

    GraphicContext::unset_current();
    EXPECT_FALSE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());

    GraphicContext::unset_current();
    EXPECT_FALSE(rc1.is_current());
    EXPECT_FALSE(rc2.is_current());
  }
  EXPECT_EQ(nullptr, gl::context::getCurrent());
}



TEST_F(TestGraphicContext, UnsetCurrentOnDeletion)
{
  {
    GraphicContext rc;
    EXPECT_FALSE(rc.is_current());
    GraphicContext::set_current(rc);
    EXPECT_TRUE(rc.is_current());
  }
  EXPECT_EQ(nullptr, gl::context::getCurrent());
}



TEST_F(TestGraphicContext, DefaultContextParameters)
{
  GraphicContext rc;
  GraphicContext::set_current(rc);

  EXPECT_EQ(1, gl::get_unpack_alignment());
  EXPECT_EQ(1, gl::get_pack_alignment());

  EXPECT_FALSE(gl::is_multisampling_enabled());

  EXPECT_TRUE(gl::is_blending_enabled());
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_ALPHA), gl::get_source_blending());
  EXPECT_EQ(
    static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA), gl::get_destination_blending());
}



TEST_F(TestGraphicContext, ContextParametersWithContextSwitch)
{
  GraphicContext rc1;
  GraphicContext rc2;

  GraphicContext::set_current(rc1);
  EXPECT_EQ(1, gl::get_unpack_alignment());
  gl::set_unpack_alignment(4);
  EXPECT_EQ(4, gl::get_unpack_alignment());

  GraphicContext::set_current(rc2);
  EXPECT_EQ(1, gl::get_unpack_alignment());

  GraphicContext::set_current(rc1);
  EXPECT_EQ(4, gl::get_unpack_alignment());
}



TEST_F(TestGraphicContext, GetRenderingColorByteCount)
{
  EXPECT_EQ(4u, GraphicContext::getRenderingColorByteCount());
}



TEST_F(TestGraphicContext, GetRenderingDepthByteCount)
{
  EXPECT_EQ(3u, GraphicContext::getRenderingDepthByteCount());
}



TEST_F(TestGraphicContext, GetRenderingStencilByteCount)
{
  EXPECT_EQ(1u, GraphicContext::getRenderingStencilByteCount());
}
