// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/TestGlBase.hpp"

#include "hou/sys/video_mode.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlFunctions.hpp"



void TestGlBase::SetUpTestCase()
{
  hou::gl::initExtensions();
}



TestGlBase::TestGlBase()
  : testing::Test()
  , mWindow("TestGfxWindow", hou::video_mode(hou::vec2u::zero(), 4u)
    , hou::window_style::windowed)
  , mContext(hou::gl::ContextSettings::Default, mWindow)
{
  setContextCurrent();
}



TestGlBase::~TestGlBase()
{}



void TestGlBase::setContextCurrent()
{
  hou::gl::Context::setCurrent(mContext, mWindow);
}

