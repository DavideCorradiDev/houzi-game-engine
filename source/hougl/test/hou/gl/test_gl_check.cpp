// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/gl/test_gl_single_context.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_check.hpp"
#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_object_handle.hpp"

#include "hou/sys/video_mode.hpp"

using namespace hou;



namespace
{

class TestGlCheck: public test_gl_single_context {};
class TestGlCheckDeathTest : public TestGlCheck {};

class ConcreteGlSharedObjectHandle
  : public gl::shared_object_handle
{
public:
  ConcreteGlSharedObjectHandle(GLuint name)
    : gl::shared_object_handle(name)
  {}
};



class ConcreteGlNonSharedObjectHandle
  : public gl::non_shared_object_handle
{
public:
  ConcreteGlNonSharedObjectHandle(GLuint name)
    : gl::non_shared_object_handle(name)
  {}
};

}



TEST_F(TestGlCheck, GlCheckErrorFunction)
{
  glClear(GL_COLOR_BUFFER_BIT);
  gl::check_error("", 0);
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlCheckErrorFunction)
{
  glClear(GL_COLOR); 
  HOU_EXPECT_ERROR(gl::check_error("", 0), std::logic_error
    , get_text(gl_error::invalid_value));
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
    , get_text(gl_error::invalid_value));
#else
  HOU_GL_CHECK_ERROR();
  SUCCEED();
#endif
}



TEST_F(TestGlCheck, GlContextExistenceFunction)
{
  gl::check_context_existence("", 0);
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlContextExistenceFunction)
{
  gl::context::unset_current();
  HOU_EXPECT_ERROR(gl::check_context_existence("", 0)
    , std::logic_error
    , get_text(gl_error::context_existence));
}



TEST_F(TestGlCheck, GlContextExistenceMacro)
{
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
}



TEST_F(TestGlCheckDeathTest, GlContextExistenceMacro)
{
  gl::context::unset_current();
#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_EXISTENCE()
    , std::logic_error
    , get_text(gl_error::context_existence));
#else
  HOU_GL_CHECK_CONTEXT_EXISTENCE();
  SUCCEED();
#endif
}



TEST_F(TestGlCheck, GlContextOwnershipSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
  gl::check_context_ownership(o1, "", 0);
  gl::check_context_ownership(o2, "", 0);

  gl::context::set_current(c2, w);
  gl::check_context_ownership(o1, "", 0);
  gl::check_context_ownership(o2, "", 0);

  gl::context::set_current(c3, w);
  gl::check_context_ownership(o3, "", 0);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
  HOU_EXPECT_ERROR(gl::check_context_ownership(o3, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));

  gl::context::set_current(c2, w);
  HOU_EXPECT_ERROR(gl::check_context_ownership(o3, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));

  gl::context::set_current(c3, w);
  HOU_EXPECT_ERROR(gl::check_context_ownership(o1, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(gl::check_context_ownership(o2, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
}



TEST_F(TestGlCheck, GlContextOwnershipSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);

  gl::context::set_current(c2, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);

  gl::context::set_current(c3, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::context::set_current(c2, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::context::set_current(c3, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  SUCCEED();
#endif
}



TEST_F(TestGlCheck, GlContextOwnershipNonSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
  gl::check_context_ownership(o1, "", 0);

  gl::context::set_current(c2, w);
  gl::check_context_ownership(o2, "", 0);

  gl::context::set_current(c3, w);
  gl::check_context_ownership(o3, "", 0);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipNonSharedFunction)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
  HOU_EXPECT_ERROR(gl::check_context_ownership(o2, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(gl::check_context_ownership(o3, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));

  gl::context::set_current(c2, w);
  HOU_EXPECT_ERROR(gl::check_context_ownership(o1, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(gl::check_context_ownership(o3, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));

  gl::context::set_current(c3, w);
  HOU_EXPECT_ERROR(gl::check_context_ownership(o1, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(gl::check_context_ownership(o2, "", 0)
    , std::logic_error
    , get_text(gl_error::invalid_ownership));
}



TEST_F(TestGlCheck, GlContextOwnershipNonSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);

  gl::context::set_current(c2, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);

  gl::context::set_current(c3, w);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
}



TEST_F(TestGlCheckDeathTest, GlContextOwnershipNonSharedMacro)
{
  system_window w("test", video_mode(vec2u::zero(), 0u), window_style::windowed);
  gl::context c1(gl::context_settings::standard, w);
  gl::context c2(gl::context_settings::standard, w, c1);
  gl::context c3(gl::context_settings::standard, w);

  gl::context::set_current(c1, w);
  ConcreteGlNonSharedObjectHandle o1(0u);

  gl::context::set_current(c2, w);
  ConcreteGlNonSharedObjectHandle o2(0u);

  gl::context::set_current(c3, w);
  ConcreteGlNonSharedObjectHandle o3(0u);

  gl::context::set_current(c1, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), std::logic_error
    , get_text(gl_error::invalid_ownership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::context::set_current(c2, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3), std::logic_error
    , get_text(gl_error::invalid_ownership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o3);
  SUCCEED();
#endif

  gl::context::set_current(c3, w);
#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1), std::logic_error
    , get_text(gl_error::invalid_ownership));
  HOU_EXPECT_ERROR(HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2), std::logic_error
    , get_text(gl_error::invalid_ownership));
#else
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o1);
  HOU_GL_CHECK_CONTEXT_OWNERSHIP(o2);
  SUCCEED();
#endif
}

