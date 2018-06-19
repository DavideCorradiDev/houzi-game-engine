// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_multiple_contexts.hpp"

#include "hou/gl/gl_context_settings.hpp"



test_gl_multiple_contexts::test_gl_multiple_contexts()
  : test_gl_base()
  , m_sharing_context(
      hou::gl::context_settings::get_default(), m_window, m_context)
  , m_non_sharing_context(hou::gl::context_settings::get_default(), m_window)
{}



void test_gl_multiple_contexts::set_sharing_context_current()
{
  hou::gl::context::set_current(m_sharing_context, m_window);
}



void test_gl_multiple_contexts::set_non_sharing_context_current()
{
  hou::gl::context::set_current(m_non_sharing_context, m_window);
}
