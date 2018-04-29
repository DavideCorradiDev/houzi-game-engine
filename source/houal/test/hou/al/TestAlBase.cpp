// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/TestAlBase.hpp"



TestAlBase::TestAlBase()
  : testing::Test()
  , m_device()
  , mContext(m_device)
{
  setContextCurrent();
}



TestAlBase::~TestAlBase()
{}



void TestAlBase::setContextCurrent()
{
  hou::al::context::set_current(mContext);
}

