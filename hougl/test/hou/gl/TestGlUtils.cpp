// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"

#include "hou/gl/GlError.hpp"
#include "hou/gl/GlUtils.hpp"

#include "hou/sys/VideoMode.hpp"
#include "hou/sys/Window.hpp"

using namespace hou;



namespace
{

class TestGlUtils : public TestGlSingleContext
{};
class TestGlUtilsDeathTest : public TestGlUtils
{};

}  // namespace



TEST_F(TestGlUtils, VerticalSync)
{
  gl::setVerticalSyncMode(gl::VerticalSyncMode::Disabled);
  gl::setVerticalSyncMode(gl::VerticalSyncMode::Enabled);
  SUCCEED();
}



TEST_F(TestGlUtils, UnpackAlignment)
{
  gl::setUnpackAlignment(1);
  EXPECT_EQ(1, gl::getUnpackAlignment());
  gl::setUnpackAlignment(4);
  EXPECT_EQ(4, gl::getUnpackAlignment());
}



TEST_F(TestGlUtilsDeathTest, InvalidUnpackAlignment)
{
#if not defined(HOU_DISABLE_GL_ERROR_CHECKS)
  HOU_EXPECT_ERROR(gl::setUnpackAlignment(3), std::logic_error,
    getText(GlError::InvalidValue));
#endif
}



TEST_F(TestGlUtils, PackAlignment)
{
  gl::setPackAlignment(1);
  EXPECT_EQ(1, gl::getPackAlignment());
  gl::setPackAlignment(4);
  EXPECT_EQ(4, gl::getPackAlignment());
}



TEST_F(TestGlUtilsDeathTest, InvalidPackAlignment)
{
#if not defined(HOU_DISABLE_GL_ERROR_CHECKS)
  HOU_EXPECT_ERROR(
    gl::setPackAlignment(3), std::logic_error, getText(GlError::InvalidValue));
#endif
}



TEST_F(TestGlUtils, getPixelSizeBytes)
{
  EXPECT_EQ(1, gl::getPixelSizeBytes(GL_RED));
  EXPECT_EQ(2, gl::getPixelSizeBytes(GL_RG));
  EXPECT_EQ(3, gl::getPixelSizeBytes(GL_RGB));
  EXPECT_EQ(3, gl::getPixelSizeBytes(GL_BGR));
  EXPECT_EQ(4, gl::getPixelSizeBytes(GL_RGBA));
  EXPECT_EQ(4, gl::getPixelSizeBytes(GL_BGRA));
}



TEST_F(TestGlUtils, ComputeTextureSizeBytes)
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



TEST_F(TestGlUtils, BindWindow)
{
  ASSERT_TRUE(mContext.isCurrent());
  Window w("Test", VideoMode(Vec2u(40u, 30u), 32u), WindowStyle::Windowed);
  gl::bindWindow(w);
  EXPECT_TRUE(mContext.isCurrent());
}
