// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/TestGlMultipleContexts.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/sys/video_mode.hpp"



TestGlMultipleContexts::TestGlMultipleContexts()
  : TestGlBase()
  , mSharingContext(hou::gl::context_settings::default, mWindow, mContext)
  , mNonSharingContext(hou::gl::context_settings::default, mWindow)
{}



TestGlMultipleContexts::~TestGlMultipleContexts() {}



void TestGlMultipleContexts::setSharingContextCurrent()
{
  hou::gl::context::set_current(mSharingContext, mWindow);
}



void TestGlMultipleContexts::setNonSharingContextCurrent()
{
  hou::gl::context::set_current(mNonSharingContext, mWindow);
}

