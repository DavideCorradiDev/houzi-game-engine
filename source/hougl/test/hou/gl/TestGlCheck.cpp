// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/GlObjectHandle.hpp"

#include "hou/sys/video_mode.hpp"

using namespace hou;



namespace
{

class TestGlCheck: public TestGlSingleContext {};
class TestGlCheckDeathTest : public TestGlCheck {};

class ConcreteGlSharedObjectHandle
  : public gl::SharedObjectHandle
{
public:
  ConcreteGlSharedObjectHandle(GLuint name)
    : gl::SharedObjectHandle(name)
  {}
};



class ConcreteGlNonSharedObjectHandle
  : public gl::NonSharedObjectHandle
{
public:
  ConcreteGlNonSharedObjectHandle(GLuint name)
    : gl::NonSharedObjectHandle(name)
  {}
};

}



TEST_F(TestGlCheck, GlCheckErrorFunction)
{
  glClear(GL_COLOR_BUFFER_BIT);
  gl::checkError("", 0);
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlCheckErrorFunction)
{
  glClear(GL_COLOR); 
  HOU_EXPECT_ERROR(gl::checkError("", 0), std::logic_error
    , get_text(GlError::InvalidValue));
}



TEST_F(TestGlCheck, GlCheckErrorMacro)
{
  glClear(GL_COLOR_BUFFER_BIT);
  HOU_GL_CHECK_ERROR();
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlCheckErrorMacro)
{
  glClear(GL_COLOR);
#ifdef HOU_ENABLE_GL_ERROR_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_ERROR(), std::logic_error
    , get_text(GlError::InvalidValue));
#else
  HOU_GL_CHECK_ERROR();
  SUCCEED();
#endif
}



TEST_F(TestGlCheck, GlContextExistenceFunction)
{
  gl::checkContextExistence("", 0);
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlContextExistenceFunction)
{
  gl::Context::unsetCurrent();
  HOU_EXPECT_ERROR(gl::checkContextExistence("", 0)
    , std::logic_error
    , get_text(GlError::ContextExistence));
}



TEST_F(TestGlCheck, GlContextExistenceMacro)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlContextExistenceMacro)
{
  gl::Context::unsetCurrent();
#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_EXISTENCE()
    , std::logic_error
    , get_text(GlError::ContextExistence));
#else
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
#endif
}



TEST_F(TestGlCheck, GlContextOwnershipSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
  gl::checkContextOwnership(o1, "", 0);
  gl::checkContextOwnership(o2, "", 0);

  gl::Context::setCurrent(c2, w);
  gl::checkContextOwnership(o1, "", 0);
  gl::checkContextOwnership(o2, "", 0);

  gl::Context::setCurrent(c3, w);
  gl::checkContextOwnership(o3, "", 0);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));

  gl::Context::setCurrent(c2, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));

  gl::Context::setCurrent(c3, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o1, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o2, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
}



TEST_F(TestGlCheck, GlContextOwnershipSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);

  gl::Context::setCurrent(c2, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);

  gl::Context::setCurrent(c3, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::Context::setCurrent(c2, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::Context::setCurrent(c3, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  SUCCEED();
#endif
}



TEST_F(TestGlCheck, GlContextOwnershipNonSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
  gl::checkContextOwnership(o1, "", 0);

  gl::Context::setCurrent(c2, w);
  gl::checkContextOwnership(o2, "", 0);

  gl::Context::setCurrent(c3, w);
  gl::checkContextOwnership(o3, "", 0);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipNonSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o2, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));

  gl::Context::setCurrent(c2, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o1, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));

  gl::Context::setCurrent(c3, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o1, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o2, "", 0)
    , std::logic_error
    , get_text(GlError::InvalidOwnership));
}



TEST_F(TestGlCheck, GlContextOwnershipNonSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);

  gl::Context::setCurrent(c2, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);

  gl::Context::setCurrent(c3, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipNonSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::Context c1(gl::ContextSettings::Default, w);
  gl::Context c2(gl::ContextSettings::Default, w, c1);
  gl::Context c3(gl::ContextSettings::Default, w);

  gl::Context::setCurrent(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::Context::setCurrent(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::Context::setCurrent(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::Context::setCurrent(c1, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), std::logic_error
    , get_text(GlError::InvalidOwnership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::Context::setCurrent(c2, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), std::logic_error
    , get_text(GlError::InvalidOwnership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::Context::setCurrent(c3, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , get_text(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), std::logic_error
    , get_text(GlError::InvalidOwnership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  SUCCEED();
#endif
}

