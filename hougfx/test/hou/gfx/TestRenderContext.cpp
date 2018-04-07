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

class TestRenderContext : public Test {};

}



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
  }
  EXPECT_EQ(nullptr, gl::Context::getCurrent());
}



TEST_F(TestRenderContext, GetMaxTextureSampleCount)
{
  RenderContext rc;
  EXPECT_NE(0u, RenderContext::getMaxTextureSampleCount());
  EXPECT_EQ(static_cast<uint>(gl::getMaxTextureSamples())
    , RenderContext::getMaxTextureSampleCount());
}



TEST_F(TestRenderContext, GetMaxTextureSize)
{
  RenderContext rc;
  EXPECT_NE(0u, RenderContext::getMaxTextureSize());
  EXPECT_EQ(static_cast<uint>(gl::getMaxTextureSize())
    , RenderContext::getMaxTextureSize());
}



TEST_F(TestRenderContext, GetTextureUnitCount)
{
  RenderContext rc;
  EXPECT_NE(0u, RenderContext::getTextureUnitCount());
  EXPECT_EQ(static_cast<uint>(gl::getMaxTextureImageUnits())
    , RenderContext::getTextureUnitCount());
}

