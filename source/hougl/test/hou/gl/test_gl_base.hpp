// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GL_TEST_GL_BASE_HPP
#define TEST_HOU_GL_TEST_GL_BASE_HPP

#include <gtest/gtest.h>

#include "hou/gl/gl_context.hpp"

#include "hou/sys/system_window.hpp"



class test_gl_base
  : public testing::Test
{
public:
  static void SetUpTestCase();

  test_gl_base();
  virtual ~test_gl_base() = 0;

  void setContextCurrent();

protected:
  hou::system_window mWindow;
  hou::gl::context mContext;
};

#endif

