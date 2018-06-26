// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GFX_TEST_GFX_MULTIPLE_CONTEXTS_HPP
#define TEST_HOU_GFX_TEST_GFX_MULTIPLE_CONTEXTS_HPP

#include "hou/gl/test_gl_base.hpp"



class test_gl_multiple_contexts : public test_gl_base
{
public:
  test_gl_multiple_contexts();

  void set_sharing_context_current();

  void set_non_sharing_context_current();

protected:
  hou::gl::context m_sharing_context;
  hou::gl::context m_non_sharing_context;
};

#endif
