// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_base.hpp"

#include "hou/gl/gl_context_settings.hpp"



test_gl_base::test_gl_base()
  : testing::Test()
  , m_window("GlTestWindow", hou::vec2u::zero())
  , m_context(hou::gl::context_settings::get_default(), m_window)
{
  set_context_current();
}



test_gl_base::~test_gl_base()
{}



void test_gl_base::set_context_current()
{
  hou::gl::context::set_current(m_context, m_window);
}
