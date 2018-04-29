// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_AL_TEST_AL_BASE_HPP
#define TEST_HOU_AL_TEST_AL_BASE_HPP

#include <gtest/gtest.h>

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"



class TestAlBase
  : public testing::Test
{
public:
  TestAlBase();
  virtual ~TestAlBase() = 0;

  void setContextCurrent();

protected:
  hou::al::device m_device;
  hou::al::context mContext;
};

#endif

