// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/TestGlBase.hpp"

#include "hou/sys/video_mode.hpp"

#include "hou/gl/gl_context_settings.hpp"
#include "hou/gl/gl_functions.hpp"



void TestGlBase::SetUpTestCase()
{
  hou::gl::init_extensions();
}



TestGlBase::TestGlBase()
  : testing::Test()
  , mWindow("TestGfxWindow", hou::video_mode(hou::vec2u::zero(), 4u)
    , hou::window_style::windowed)
  , mContext(hou::gl::context_settings::default, mWindow)
{
  setContextCurrent();
}



TestGlBase::~TestGlBase()
{}



void TestGlBase::setContextCurrent()
{
  hou::gl::context::set_current(mContext, mWindow);
}

