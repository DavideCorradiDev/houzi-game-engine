// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef TEST_HOU_GL_TEST_GL_BASE_HPP
#define TEST_HOU_GL_TEST_GL_BASE_HPP

#include <gtest/gtest.h>

#include "hou/gl/GlContext.hpp"

#include "hou/sys/Window.hpp"



class TestGlBase
  : public testing::Test
{
public:
  static void SetUpTestCase();

  TestGlBase();
  virtual ~TestGlBase() = 0;

  void setContextCurrent();

protected:
  hou::Window mWindow;
  hou::gl::Context mContext;
};

#endif
