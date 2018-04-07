// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/TestGlBase.hpp"

#include "hou/sys/VideoMode.hpp"

#include "hou/gl/GlContextSettings.hpp"
#include "hou/gl/GlUtils.hpp"



void TestGlBase::SetUpTestCase()
{
  hou::gl::initExtensions();
}



TestGlBase::TestGlBase()
  : testing::Test()
  , mWindow("TestGfxWindow", hou::VideoMode(hou::Vec2u::zero(), 32u)
    , hou::WindowStyle::Windowed)
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

