// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/test_gl_multiple_contexts.hpp"
#include "hou/gl/gl_context_settings.hpp"
#include "hou/sys/video_mode.hpp"



test_gl_multiple_contexts::test_gl_multiple_contexts()
  : test_gl_base()
  , mSharingContext(hou::gl::context_settings::standard, mWindow, mContext)
  , mNonSharingContext(hou::gl::context_settings::standard, mWindow)
{}



test_gl_multiple_contexts::~test_gl_multiple_contexts() {}



void test_gl_multiple_contexts::setSharingContextCurrent()
{
  hou::gl::context::set_current(mSharingContext, mWindow);
}



void test_gl_multiple_contexts::setNonSharingContextCurrent()
{
  hou::gl::context::set_current(mNonSharingContext, mWindow);
}

