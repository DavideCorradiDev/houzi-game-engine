// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/gl/TestGlSingleContext.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlCheck.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/GlObjectHandle.hpp"

#include "hou/sys/VideoMode.hpp"

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
    , getText(GlError::InvalidValue));
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
#if defined(HOU_DISABLE_GL_ERROR_CHECKS)
  HOU_GL_CHECK_ERROR();
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_ERROR(), std::logic_error
    , getText(GlError::InvalidValue));
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
    , getText(GlError::ContextExistence));
}



TEST_F(TestGlCheck, GlContextExistenceMacro)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlContextExistenceMacro)
{
  gl::Context::unsetCurrent();
#if defined(HOU_DISABLE_GL_CONTEXT_EXISTENCE_CHECKS)
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_EXISTENCE()
    , std::logic_error
    , getText(GlError::ContextExistence));
#endif
}



TEST_F(TestGlCheck, GlContextOwnershipSharedFunction)
{
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
    , getText(GlError::InvalidOwnership));

  gl::Context::setCurrent(c2, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));

  gl::Context::setCurrent(c3, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o1, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o2, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
}



TEST_F(TestGlCheck, GlContextOwnershipSharedMacro)
{
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
#endif

  gl::Context::setCurrent(c2, w);
#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
#endif

  gl::Context::setCurrent(c3, w);
#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
#endif
}



TEST_F(TestGlCheck, GlContextOwnershipNonSharedFunction)
{
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));

  gl::Context::setCurrent(c2, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o1, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o3, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));

  gl::Context::setCurrent(c3, w);
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o1, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(gl::checkContextOwnership(o2, "", 0)
    , std::logic_error
    , getText(GlError::InvalidOwnership));
}



TEST_F(TestGlCheck, GlContextOwnershipNonSharedMacro)
{
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
  Window w("test", VideoMode(Vec2u::zero(), 0u), WindowStyle::Windowed);
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
#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), std::logic_error
    , getText(GlError::InvalidOwnership));
#endif

  gl::Context::setCurrent(c2, w);
#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), std::logic_error
    , getText(GlError::InvalidOwnership));
#endif

  gl::Context::setCurrent(c3, w);
#if defined(HOU_DISABLE_GL_CONTEXT_OWNERSHIP_CHECKS)
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  SUCCEED();
#else
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , getText(GlError::InvalidOwnership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), std::logic_error
    , getText(GlError::InvalidOwnership));
#endif
}

