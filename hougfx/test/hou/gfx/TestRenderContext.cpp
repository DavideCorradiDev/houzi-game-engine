// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"

#include "hou/gfx/RenderContext.hpp"

#include "hou/gl/GlTextureHandle.hpp"

using namespace testing;
using namespace hou;



namespace
{

class TestRenderContext : public Test
{};

}  // namespace



TEST_F(TestRenderContext, Creation)
{
  RenderContext rc;
  SUCCEED();
}



TEST_F(TestRenderContext, MoveConstructor)
{
  RenderContext rcDummy;
  RenderContext::setCurrent(rcDummy);
  RenderContext rc = std::move(rcDummy);
  EXPECT_TRUE(rc.isCurrent());
}



TEST_F(TestRenderContext, SetCurrent)
{
  {
    RenderContext rc1;
    RenderContext rc2;

    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_TRUE(rc2.isCurrent());

    RenderContext::setCurrent(rc1);
    EXPECT_TRUE(rc1.isCurrent());
    EXPECT_FALSE(rc2.isCurrent());

    RenderContext::setCurrent(rc2);
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_TRUE(rc2.isCurrent());

    RenderContext::setCurrent(rc2);
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_TRUE(rc2.isCurrent());

    RenderContext::unsetCurrent();
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_FALSE(rc2.isCurrent());
  }
  EXPECT_EQ(nullptr, gl::Context::getCurrent());
}



TEST_F(TestRenderContext, UnsetCurrentOnDeletion)
{
  {
    RenderContext rc;
    EXPECT_TRUE(rc.isCurrent());
  }
  EXPECT_EQ(nullptr, gl::Context::getCurrent());
}



TEST_F(TestRenderContext, GetRenderingColorByteCount)
{
  EXPECT_EQ(4u, RenderContext::getRenderingColorByteCount());
}



TEST_F(TestRenderContext, GetRenderingDepthByteCount)
{
  EXPECT_EQ(3u, RenderContext::getRenderingDepthByteCount());
}



TEST_F(TestRenderContext, GetRenderingStencilByteCount)
{
  EXPECT_EQ(1u, RenderContext::getRenderingStencilByteCount());
}

