// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GFX_TEST_GFX_MULTIPLE_CONTEXTS_HPP
#define TEST_HOU_GFX_TEST_GFX_MULTIPLE_CONTEXTS_HPP

#include "hou/gl/TestGlBase.hpp"



class TestGlMultipleContexts
  : public TestGlBase
{
public:
  TestGlMultipleContexts();
  virtual ~TestGlMultipleContexts();

  void setSharingContextCurrent();
  void setNonSharingContextCurrent();

protected:
  hou::gl::context mSharingContext;
  hou::gl::context mNonSharingContext;
};

#endif

