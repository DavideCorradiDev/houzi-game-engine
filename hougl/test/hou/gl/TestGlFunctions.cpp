// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"

#include "hou/gl/GlError.hpp"
#include "hou/gl/GlFunctions.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/Window.hpp"

using namespace hou;



namespace
{

class TestGlFunctions : public TestGlSingleContext
{};
class TestGlFunctionsDeathTest : public TestGlFunctions
{};

}  // namespace



TEST_F(TestGlFunctions, VerticalSync)
{
  gl::setVerticalSyncMode(gl::VerticalSyncMode::Disabled);
  gl::setVerticalSyncMode(gl::VerticalSyncMode::Enabled);
  SUCCEED();
}



TEST_F(TestGlFunctions, UnpackAlignment)
{
  gl::setUnpackAlignment(1);
  EXPECT_EQ(1, gl::getUnpackAlignment());
  gl::setUnpackAlignment(4);
  EXPECT_EQ(4, gl::getUnpackAlignment());
}



TEST_F(TestGlFunctionsDeathTest, InvalidUnpackAlignment)
{
#if not defined(HOU_DISABLE_GL_ERROR_CHECKS)
  HOU_EXPECT_ERROR(gl::setUnpackAlignment(3), std::logic_error,
    getText(GlError::InvalidValue));
#endif
}



TEST_F(TestGlFunctions, PackAlignment)
{
  gl::setPackAlignment(1);
  EXPECT_EQ(1, gl::getPackAlignment());
  gl::setPackAlignment(4);
  EXPECT_EQ(4, gl::getPackAlignment());
}



TEST_F(TestGlFunctionsDeathTest, InvalidPackAlignment)
{
#if not defined(HOU_DISABLE_GL_ERROR_CHECKS)
  HOU_EXPECT_ERROR(
    gl::setPackAlignment(3), std::logic_error, getText(GlError::InvalidValue));
#endif
}



TEST_F(TestGlFunctions, getPixelSizeBytes)
{
  EXPECT_EQ(1, gl::getPixelSizeBytes(GL_RED));
  EXPECT_EQ(2, gl::getPixelSizeBytes(GL_RG));
  EXPECT_EQ(3, gl::getPixelSizeBytes(GL_RGB));
  EXPECT_EQ(3, gl::getPixelSizeBytes(GL_BGR));
  EXPECT_EQ(4, gl::getPixelSizeBytes(GL_RGBA));
  EXPECT_EQ(4, gl::getPixelSizeBytes(GL_BGRA));
}



TEST_F(TestGlFunctions, ComputeTextureSizeBytes)
{
  gl::setUnpackAlignment(4);
  EXPECT_EQ(48, gl::computeTextureSizeBytes(7, 3, 2, GL_RED));
  EXPECT_EQ(96, gl::computeTextureSizeBytes(7, 3, 2, GL_RG));
  EXPECT_EQ(144, gl::computeTextureSizeBytes(7, 3, 2, GL_RGB));
  EXPECT_EQ(144, gl::computeTextureSizeBytes(7, 3, 2, GL_BGR));
  EXPECT_EQ(168, gl::computeTextureSizeBytes(7, 3, 2, GL_RGBA));
  EXPECT_EQ(168, gl::computeTextureSizeBytes(7, 3, 2, GL_BGRA));

  gl::setUnpackAlignment(1);
  EXPECT_EQ(42, gl::computeTextureSizeBytes(7, 3, 2, GL_RED));
  EXPECT_EQ(84, gl::computeTextureSizeBytes(7, 3, 2, GL_RG));
  EXPECT_EQ(126, gl::computeTextureSizeBytes(7, 3, 2, GL_RGB));
  EXPECT_EQ(126, gl::computeTextureSizeBytes(7, 3, 2, GL_BGR));
  EXPECT_EQ(168, gl::computeTextureSizeBytes(7, 3, 2, GL_RGBA));
  EXPECT_EQ(168, gl::computeTextureSizeBytes(7, 3, 2, GL_BGRA));
}



TEST_F(TestGlFunctions, BindWindow)
{
  ASSERT_TRUE(mContext.isCurrent());
  Window w("Test", VideoMode(Vec2u(40u, 30u), 32u), WindowStyle::Windowed);
  gl::bindWindow(w);
  EXPECT_TRUE(mContext.isCurrent());
}



TEST_F(TestGlFunctions, EnableBlending)
{
  EXPECT_FALSE(gl::isBlendingEnabled());
  gl::enableBlending();
  EXPECT_TRUE(gl::isBlendingEnabled());
  gl::enableBlending();
  EXPECT_TRUE(gl::isBlendingEnabled());
  gl::disableBlending();
  EXPECT_FALSE(gl::isBlendingEnabled());
  gl::disableBlending();
  EXPECT_FALSE(gl::isBlendingEnabled());
}



TEST_F(TestGlFunctions, GetBlendingFactors)
{
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::getSourceBlending());
  EXPECT_EQ(static_cast<GLenum>(GL_ZERO), gl::getDestinationBlending());

  gl::setBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_ALPHA), gl::getSourceBlending());
  EXPECT_EQ(
    static_cast<GLenum>(GL_ONE_MINUS_SRC_ALPHA), gl::getDestinationBlending());

  gl::setBlending(GL_SRC_COLOR, GL_DST_ALPHA);
  EXPECT_EQ(static_cast<GLenum>(GL_SRC_COLOR), gl::getSourceBlending());
  EXPECT_EQ(static_cast<GLenum>(GL_DST_ALPHA), gl::getDestinationBlending());
}



TEST_F(TestGlFunctions, EnableMultisampling)
{
  EXPECT_TRUE(gl::isMultisamplingEnabled());
  gl::enableMultisampling();
  EXPECT_TRUE(gl::isMultisamplingEnabled());
  gl::enableMultisampling();
  EXPECT_TRUE(gl::isMultisamplingEnabled());
  gl::disableMultisampling();
  EXPECT_FALSE(gl::isMultisamplingEnabled());
  gl::disableMultisampling();
  EXPECT_FALSE(gl::isMultisamplingEnabled());
}
