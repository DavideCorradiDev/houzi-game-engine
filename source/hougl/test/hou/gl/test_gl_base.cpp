// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_base.hpp"

#include "hou/sys/video_mode.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_functions.hpp"



void test_gl_base::SetUpTestCase()
{
  hou::gl::init_extensions();
}



test_gl_base::test_gl_base()
  : testing::Test()
  , mWindow("TestGfxWindow", hou::video_mode(hou::vec2u::zero(), 4u)
    , hou::window_style::windowed)
  , mContext(hou::gl::context_settings::standard, mWindow)
{
  setContextCurrent();
}



test_gl_base::~test_gl_base()
{}



void test_gl_base::setContextCurrent()
{
  hou::gl::context::set_current(mContext, mWindow);
}

