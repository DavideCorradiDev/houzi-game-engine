// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/GlError.hpp"
#include "hou/gl/GlTextureHandle.hpp"

using namespace hou;



namespace
{

class TestGlTextureHandle : public TestGlMultipleContexts
{};
class TestGlTextureHandleDeathTest : public TestGlTextureHandle
{};

}  // namespace



TEST_F(TestGlTextureHandle, Creation)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);
  EXPECT_NE(0u, th.getName());
  EXPECT_EQ(static_cast<GLenum>(GL_TEXTURE_2D), th.getTarget());
}



#if defined(HOU_DISABLE_GL_CONTEXT_EXISTENCE_CHECKS)
TEST_F(TestGlTextureHandleDeathTest, DISABLED_NoContextCreation)
#else
TEST_F(TestGlTextureHandleDeathTest, NoContextCreation)
#endif
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::TextureHandle::create(GL_TEXTURE_2D), std::logic_error,
    getText(GlError::ContextExistence));
}



TEST_F(TestGlTextureHandle, Tracking)
{
  gl::TextureHandle th1 = gl::TextureHandle::create(GL_TEXTURE_2D);
  gl::TextureHandle th2 = gl::TextureHandle::create(GL_TEXTURE_1D);

  gl::setActiveTexture(0u);
  EXPECT_EQ(0u, gl::getActiveTexture());
  EXPECT_EQ(0u, gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_FALSE(gl::isTextureBound(th2));

  gl::setActiveTexture(1u);
  EXPECT_EQ(1u, gl::getActiveTexture());
  EXPECT_EQ(0u, gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_FALSE(gl::isTextureBound(th2));

  gl::setActiveTexture(0u);
  gl::bindTexture(th1);
  EXPECT_EQ(0u, gl::getActiveTexture());
  EXPECT_EQ(th1.getName(), gl::getBoundTextureName());
  EXPECT_TRUE(gl::isTextureBound(th1));
  EXPECT_FALSE(gl::isTextureBound(th2));

  gl::setActiveTexture(1u);
  gl::bindTexture(th2);
  EXPECT_EQ(1u, gl::getActiveTexture());
  EXPECT_EQ(th2.getName(), gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_TRUE(gl::isTextureBound(th2));

  setSharingContextCurrent();
  EXPECT_EQ(0u, gl::getActiveTexture());
  EXPECT_EQ(0u, gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_FALSE(gl::isTextureBound(th2));

  gl::bindTexture(th2);
  EXPECT_EQ(0u, gl::getActiveTexture());
  EXPECT_EQ(th2.getName(), gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_TRUE(gl::isTextureBound(th2));

  setContextCurrent();
  EXPECT_EQ(1u, gl::getActiveTexture());
  EXPECT_EQ(th2.getName(), gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_TRUE(gl::isTextureBound(th2));

  gl::unbindTexture();
  EXPECT_EQ(1u, gl::getActiveTexture());
  EXPECT_EQ(0u, gl::getBoundTextureName());
  EXPECT_FALSE(gl::isTextureBound(th1));
  EXPECT_FALSE(gl::isTextureBound(th2));

  gl::setActiveTexture(0u);
  EXPECT_EQ(0u, gl::getActiveTexture());
  EXPECT_EQ(th1.getName(), gl::getBoundTextureName());
  EXPECT_TRUE(gl::isTextureBound(th1));
  EXPECT_FALSE(gl::isTextureBound(th2));
}



TEST_F(TestGlTextureHandle, UnitTracking)
{
  gl::TextureHandle th1 = gl::TextureHandle::create(GL_TEXTURE_2D);
  gl::TextureHandle th2 = gl::TextureHandle::create(GL_TEXTURE_1D);

  EXPECT_FALSE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_FALSE(gl::isTextureBound(th2, 2));

  gl::bindTexture(th1, 0);
  EXPECT_TRUE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_FALSE(gl::isTextureBound(th2, 2));

  gl::bindTexture(th2, 2);
  EXPECT_TRUE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_TRUE(gl::isTextureBound(th2, 2));

  setSharingContextCurrent();
  EXPECT_FALSE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_FALSE(gl::isTextureBound(th2, 2));

  gl::bindTexture(th2, 2);
  EXPECT_FALSE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_TRUE(gl::isTextureBound(th2, 2));

  setContextCurrent();
  EXPECT_TRUE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_TRUE(gl::isTextureBound(th2, 2));

  gl::bindTexture(th2, 0);
  EXPECT_FALSE(gl::isTextureBound(th1, 0));
  EXPECT_TRUE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_TRUE(gl::isTextureBound(th2, 2));

  gl::unbindTexture(0);
  EXPECT_FALSE(gl::isTextureBound(th1, 0));
  EXPECT_FALSE(gl::isTextureBound(th2, 0));
  EXPECT_FALSE(gl::isTextureBound(th1, 2));
  EXPECT_TRUE(gl::isTextureBound(th2, 2));
}



TEST_F(TestGlTextureHandle, SharingContextBinding)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_1D);
  setSharingContextCurrent();
  gl::bindTexture(th);
  EXPECT_TRUE(isTextureBound(th));
}



#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
TEST_F(TestGlTextureHandleDeathTest, DISABLED_NonSharingContextBinding)
#else
TEST_F(TestGlTextureHandleDeathTest, NonSharingContextBinding)
#endif
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_1D);
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(
    gl::bindTexture(th), std::logic_error, getText(GlError::InvalidOwnership));
  setContextCurrent();
}



#if defined(HOU_DISABLE_GL_CONTEXT_EXISTENCE_CHECKS)
TEST_F(TestGlTextureHandleDeathTest, DISABLED_NoContextBinding)
#else
TEST_F(TestGlTextureHandleDeathTest, NoContextBinding)
#endif
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_1D);
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(
    gl::bindTexture(th), std::logic_error, getText(GlError::ContextExistence));
  setContextCurrent();
}



TEST_F(TestGlTextureHandle, MinFilter)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);

  gl::setTextureMinFilter(th, static_cast<GLenum>(GL_NEAREST));
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST), gl::getTextureMinFilter(th));

  gl::setTextureMinFilter(th, GL_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR), gl::getTextureMinFilter(th));

  gl::setTextureMinFilter(th, GL_NEAREST_MIPMAP_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST_MIPMAP_NEAREST),
    gl::getTextureMinFilter(th));

  gl::setTextureMinFilter(th, GL_NEAREST_MIPMAP_LINEAR);
  EXPECT_EQ(
    static_cast<GLenum>(GL_NEAREST_MIPMAP_LINEAR), gl::getTextureMinFilter(th));

  gl::setTextureMinFilter(th, GL_LINEAR_MIPMAP_NEAREST);
  EXPECT_EQ(
    static_cast<GLenum>(GL_LINEAR_MIPMAP_NEAREST), gl::getTextureMinFilter(th));

  gl::setTextureMinFilter(th, GL_LINEAR_MIPMAP_LINEAR);
  EXPECT_EQ(
    static_cast<GLenum>(GL_LINEAR_MIPMAP_LINEAR), gl::getTextureMinFilter(th));
}



TEST_F(TestGlTextureHandle, MagFilter)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);

  gl::setTextureMagFilter(th, GL_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST), gl::getTextureMagFilter(th));

  gl::setTextureMagFilter(th, GL_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR), gl::getTextureMagFilter(th));
}



TEST_F(TestGlTextureHandle, SwizzleR)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_RED), gl::getTextureSwizzleR(th));
  gl::setTextureSwizzleR(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::getTextureSwizzleR(th));
}



TEST_F(TestGlTextureHandle, SwizzleG)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_GREEN), gl::getTextureSwizzleG(th));
  gl::setTextureSwizzleG(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::getTextureSwizzleG(th));
}



TEST_F(TestGlTextureHandle, SwizzleB)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_BLUE), gl::getTextureSwizzleB(th));
  gl::setTextureSwizzleB(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::getTextureSwizzleB(th));
}



TEST_F(TestGlTextureHandle, SwizzleA)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_ALPHA), gl::getTextureSwizzleA(th));
  gl::setTextureSwizzleA(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::getTextureSwizzleA(th));
}



TEST_F(TestGlTextureHandle, SwizzleRGBA)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);
  std::array<GLenum, 4u> swizzle;
  std::array<GLenum, 4u> swizzleRef;

  swizzleRef = {
    GL_RED,
    GL_GREEN,
    GL_BLUE,
    GL_ALPHA,
  };
  gl::getTextureSwizzle(th, swizzle.data());
  EXPECT_EQ(swizzleRef, swizzle);

  swizzleRef = {
    GL_ONE,
    GL_GREEN,
    GL_ZERO,
    GL_RED,
  };
  gl::setTextureSwizzle(th, swizzleRef.data());
  gl::getTextureSwizzle(th, swizzle.data());
  EXPECT_EQ(swizzleRef, swizzle);
}



TEST_F(TestGlTextureHandle, TextureWrapModeS)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::getTextureWrapModeS(th));
  gl::setTextureWrapModeS(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::getTextureWrapModeS(th));
}



TEST_F(TestGlTextureHandle, TextureWrapModeT)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::getTextureWrapModeT(th));
  gl::setTextureWrapModeT(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::getTextureWrapModeT(th));
}



TEST_F(TestGlTextureHandle, TextureWrapModeR)
{
  gl::TextureHandle th = gl::TextureHandle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::getTextureWrapModeR(th));
  gl::setTextureWrapModeR(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::getTextureWrapModeR(th));
}
