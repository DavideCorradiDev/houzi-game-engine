// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_base.hpp"

#include "hou/gl/gl_context_settings.hpp"



test_gl_base::test_gl_base()
  : testing::Test()
  , m_window("GlTestWindow", hou::vec2u(1u, 1u))
  , m_context(get_test_default_context_settings(), m_window)
{
  set_context_current();
}



test_gl_base::~test_gl_base()
{}



void test_gl_base::set_context_current()
{
  hou::gl::context::set_current(m_context, m_window);
}



hou::gl::context_settings get_test_default_context_settings()
{
// clang-format off
#if HOU_GL_CONTEXT_PROFILE == 1
  return hou::gl::context_settings::get_default_core();
#elif HOU_GL_CONTEXT_PROFILE == 2
  return hou::gl::context_settings::get_default_es();
#else
  #error                                                                         \
    "Unspecified context profile. Please define the preprocessor symbol HOU_GL_CONTEXT_PROFILE with value 1 for GL core or 2 for GLES."
#endif
  // clang-format on
}
