// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/al/TestAlBase.hpp"



TestAlBase::TestAlBase()
  : testing::Test()
  , mDevice()
  , mContext(mDevice)
{
  setContextCurrent();
}



TestAlBase::~TestAlBase()
{}



void TestAlBase::setContextCurrent()
{
  hou::al::Context::setCurrent(mContext);
}

