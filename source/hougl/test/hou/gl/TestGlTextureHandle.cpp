// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlMultipleContexts.hpp"

#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_texture_handle.hpp"

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
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_NE(0u, th.get_name());
  EXPECT_EQ(static_cast<GLenum>(GL_TEXTURE_2D), th.getTarget());
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlTextureHandleDeathTest, NoContextCreation)
#else
TEST_F(TestGlTextureHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::texture_handle::create(GL_TEXTURE_2D), std::logic_error,
    get_text(gl_error::context_existence));
}



TEST_F(TestGlTextureHandle, Tracking)
{
  gl::texture_handle th1 = gl::texture_handle::create(GL_TEXTURE_2D);
  gl::texture_handle th2 = gl::texture_handle::create(GL_TEXTURE_1D);

  gl::set_active_texture(0u);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(1u);
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(0u);
  gl::bind_texture(th1);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(th1.get_name(), gl::get_bound_texture_name());
  EXPECT_TRUE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(1u);
  gl::bind_texture(th2);
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(th2.get_name(), gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_TRUE(gl::is_texture_bound(th2));

  setSharingContextCurrent();
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::bind_texture(th2);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(th2.get_name(), gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_TRUE(gl::is_texture_bound(th2));

  setContextCurrent();
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(th2.get_name(), gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_TRUE(gl::is_texture_bound(th2));

  gl::unbind_texture();
  EXPECT_EQ(1u, gl::get_active_texture());
  EXPECT_EQ(0u, gl::get_bound_texture_name());
  EXPECT_FALSE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));

  gl::set_active_texture(0u);
  EXPECT_EQ(0u, gl::get_active_texture());
  EXPECT_EQ(th1.get_name(), gl::get_bound_texture_name());
  EXPECT_TRUE(gl::is_texture_bound(th1));
  EXPECT_FALSE(gl::is_texture_bound(th2));
}



TEST_F(TestGlTextureHandle, UnitTracking)
{
  gl::texture_handle th1 = gl::texture_handle::create(GL_TEXTURE_2D);
  gl::texture_handle th2 = gl::texture_handle::create(GL_TEXTURE_1D);

  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_FALSE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th1, 0);
  EXPECT_TRUE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_FALSE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th2, 2);
  EXPECT_TRUE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  setSharingContextCurrent();
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_FALSE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th2, 2);
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  setContextCurrent();
  EXPECT_TRUE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  gl::bind_texture(th2, 0);
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_TRUE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));

  gl::unbind_texture(0);
  EXPECT_FALSE(gl::is_texture_bound(th1, 0));
  EXPECT_FALSE(gl::is_texture_bound(th2, 0));
  EXPECT_FALSE(gl::is_texture_bound(th1, 2));
  EXPECT_TRUE(gl::is_texture_bound(th2, 2));
}



TEST_F(TestGlTextureHandle, SharingContextBinding)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_1D);
  setSharingContextCurrent();
  gl::bind_texture(th);
  EXPECT_TRUE(is_texture_bound(th));
}



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
TEST_F(TestGlTextureHandleDeathTest, NonSharingContextBinding)
#else
TEST_F(TestGlTextureHandleDeathTest, DISABLED_NonSharingContextBinding)
#endif
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_1D);
  setNonSharingContextCurrent();
  HOU_EXPECT_ERROR(
    gl::bind_texture(th), std::logic_error, get_text(gl_error::invalid_ownership));
  setContextCurrent();
}



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestGlTextureHandleDeathTest, NoContextBinding)
#else
TEST_F(TestGlTextureHandleDeathTest, DISABLED_NoContextBinding)
#endif
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_1D);
  gl::context::unset_current();
  HOU_EXPECT_ERROR(
    gl::bind_texture(th), std::logic_error, get_text(gl_error::context_existence));
  setContextCurrent();
}



TEST_F(TestGlTextureHandle, MinFilter)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  gl::set_texture_min_filter(th, static_cast<GLenum>(GL_NEAREST));
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST), gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR), gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_NEAREST_MIPMAP_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST_MIPMAP_NEAREST),
    gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_NEAREST_MIPMAP_LINEAR);
  EXPECT_EQ(
    static_cast<GLenum>(GL_NEAREST_MIPMAP_LINEAR), gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_LINEAR_MIPMAP_NEAREST);
  EXPECT_EQ(
    static_cast<GLenum>(GL_LINEAR_MIPMAP_NEAREST), gl::get_texture_min_filter(th));

  gl::set_texture_min_filter(th, GL_LINEAR_MIPMAP_LINEAR);
  EXPECT_EQ(
    static_cast<GLenum>(GL_LINEAR_MIPMAP_LINEAR), gl::get_texture_min_filter(th));
}



TEST_F(TestGlTextureHandle, MagFilter)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  gl::set_texture_mag_filter(th, GL_NEAREST);
  EXPECT_EQ(static_cast<GLenum>(GL_NEAREST), gl::get_texture_mag_filter(th));

  gl::set_texture_mag_filter(th, GL_LINEAR);
  EXPECT_EQ(static_cast<GLenum>(GL_LINEAR), gl::get_texture_mag_filter(th));
}



TEST_F(TestGlTextureHandle, SwizzleR)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_RED), gl::get_texture_swizzle_r(th));
  gl::set_texture_swizzle_r(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_r(th));
}



TEST_F(TestGlTextureHandle, SwizzleG)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_GREEN), gl::get_texture_swizzle_g(th));
  gl::set_texture_swizzle_g(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_g(th));
}



TEST_F(TestGlTextureHandle, SwizzleB)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_BLUE), gl::get_texture_swizzle_b(th));
  gl::set_texture_swizzle_b(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_b(th));
}



TEST_F(TestGlTextureHandle, SwizzleA)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);

  EXPECT_EQ(static_cast<GLenum>(GL_ALPHA), gl::get_texture_swizzle_a(th));
  gl::set_texture_swizzle_a(th, GL_ONE);
  EXPECT_EQ(static_cast<GLenum>(GL_ONE), gl::get_texture_swizzle_a(th));
}



TEST_F(TestGlTextureHandle, SwizzleRGBA)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  std::array<GLenum, 4u> swizzle;
  std::array<GLenum, 4u> swizzleRef;

  swizzleRef = {
    GL_RED,
    GL_GREEN,
    GL_BLUE,
    GL_ALPHA,
  };
  gl::get_texture_swizzle(th, swizzle.data());
  EXPECT_EQ(swizzleRef, swizzle);

  swizzleRef = {
    GL_ONE,
    GL_GREEN,
    GL_ZERO,
    GL_RED,
  };
  gl::set_texture_swizzle(th, swizzleRef.data());
  gl::get_texture_swizzle(th, swizzle.data());
  EXPECT_EQ(swizzleRef, swizzle);
}



TEST_F(TestGlTextureHandle, TextureWrapModeS)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::get_texture_wrap_mode_s(th));
  gl::set_texture_wrap_mode_s(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::get_texture_wrap_mode_s(th));
}



TEST_F(TestGlTextureHandle, TextureWrapModeT)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::get_texture_wrap_mode_t(th));
  gl::set_texture_wrap_mode_t(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::get_texture_wrap_mode_t(th));
}



TEST_F(TestGlTextureHandle, TextureWrapModeR)
{
  gl::texture_handle th = gl::texture_handle::create(GL_TEXTURE_2D);
  EXPECT_EQ(static_cast<GLenum>(GL_REPEAT), gl::get_texture_wrap_mode_r(th));
  gl::set_texture_wrap_mode_r(th, GL_CLAMP_TO_EDGE);
  EXPECT_EQ(static_cast<GLenum>(GL_CLAMP_TO_EDGE), gl::get_texture_wrap_mode_r(th));
}
