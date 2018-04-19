// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GL_TEST_GL_BASE_HPP
#define TEST_HOU_GL_TEST_GL_BASE_HPP

#include <gtest/gtest.h>

#include "hou/gl/GlContext.hpp"

#include "hou/sys/SystemWindow.hpp"



class TestGlBase
  : public testing::Test
{
public:
  static void SetUpTestCase();

  TestGlBase();
  virtual ~TestGlBase() = 0;

  void setContextCurrent();

protected:
  hou::SystemWindow mWindow;
  hou::gl::Context mContext;
};

#endif

