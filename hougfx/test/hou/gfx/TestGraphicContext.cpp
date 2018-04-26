// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/gfx/GraphicContext.hpp"

#include "hou/gl/GlTextureHandle.hpp"
#include "hou/gl/GlFunctions.hpp"

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
  GraphicContext::setCurrent(rcDummy);
  GraphicContext rc = std::move(rcDummy);
  EXPECT_TRUE(rc.isCurrent());
}



TEST_F(TestGraphicContext, SetCurrent)
{
  {
    GraphicContext rc1;
    GraphicContext rc2;

    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_FALSE(rc2.isCurrent());

    GraphicContext::setCurrent(rc1);
    EXPECT_TRUE(rc1.isCurrent());
    EXPECT_FALSE(rc2.isCurrent());

    GraphicContext::setCurrent(rc2);
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_TRUE(rc2.isCurrent());

    GraphicContext::setCurrent(rc2);
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_TRUE(rc2.isCurrent());

    GraphicContext::unsetCurrent();
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_FALSE(rc2.isCurrent());

    GraphicContext::unsetCurrent();
    EXPECT_FALSE(rc1.isCurrent());
    EXPECT_FALSE(rc2.isCurrent());
  }
  EXPECT_EQ(nullptr, gl::Context::getCurrent());
}



TEST_F(TestGraphicContext, UnsetCurrentOnDeletion)
{
  {
    GraphicContext rc;
    EXPECT_FALSE(rc.isCurrent());
    GraphicContext::setCurrent(rc);
    EXPECT_TRUE(rc.isCurrent());
  }
  EXPECT_EQ(nullptr, gl::Context::getCurrent());
}



TEST_F(TestGraphicContext, DefaultContextParameters)
{
  GraphicContext rc;
  GraphicContext::setCurrent(rc);

  EXPECT_EQ(1, gl::getUnpackAlignment());
  EXPECT_EQ(1, gl::getPackAlignment());

  EXPECT_FALSE(gl::isMultisamplingEnabled());

  EXPECT_TRUE(gl::isBlendingEnabled());
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_ALPHA), gl::getSourceBlending());
  EXPECT_EQ(
    static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA), gl::getDestinationBlending());
}



TEST_F(TestGraphicContext, ContextParametersWithContextSwitch)
{
  GraphicContext rc1;
  GraphicContext rc2;

  GraphicContext::setCurrent(rc1);
  EXPECT_EQ(1, gl::getUnpackAlignment());
  gl::setUnpackAlignment(4);
  EXPECT_EQ(4, gl::getUnpackAlignment());

  GraphicContext::setCurrent(rc2);
  EXPECT_EQ(1, gl::getUnpackAlignment());

  GraphicContext::setCurrent(rc1);
  EXPECT_EQ(4, gl::getUnpackAlignment());
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
