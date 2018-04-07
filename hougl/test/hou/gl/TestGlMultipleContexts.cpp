// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/TestGlMultipleContexts.hpp"
#include "hou/gl/GlContextSettings.hpp"
#include "hou/sys/VideoMode.hpp"



TestGlMultipleContexts::TestGlMultipleContexts()
  : TestGlBase()
  , mSharingContext(hou::gl::ContextSettings::Default, mWindow, mContext)
  , mNonSharingContext(hou::gl::ContextSettings::Default, mWindow)
{}



TestGlMultipleContexts::~TestGlMultipleContexts() {}



void TestGlMultipleContexts::setSharingContextCurrent()
{
  hou::gl::Context::setCurrent(mSharingContext, mWindow);
}



void TestGlMultipleContexts::setNonSharingContextCurrent()
{
  hou::gl::Context::setCurrent(mNonSharingContext, mWindow);
}

