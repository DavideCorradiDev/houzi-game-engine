// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

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

