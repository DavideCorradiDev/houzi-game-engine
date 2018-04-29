// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GFX_TEST_GFX_MULTIPLE_CONTEXTS_HPP
#define TEST_HOU_GFX_TEST_GFX_MULTIPLE_CONTEXTS_HPP

#include "hou/gl/test_gl_base.hpp"



class test_gl_multiple_contexts
  : public test_gl_base
{
public:
  test_gl_multiple_contexts();
  virtual ~test_gl_multiple_contexts();

  void setSharingContextCurrent();
  void setNonSharingContextCurrent();

protected:
  hou::gl::context mSharingContext;
  hou::gl::context mNonSharingContext;
};

#endif

