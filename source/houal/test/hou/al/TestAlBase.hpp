// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_AL_TEST_AL_BASE_HPP
#define TEST_HOU_AL_TEST_AL_BASE_HPP

#include <gtest/gtest.h>

#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"



class TestAlBase
  : public testing::Test
{
public:
  TestAlBase();
  virtual ~TestAlBase() = 0;

  void setContextCurrent();

protected:
  hou::al::Device mDevice;
  hou::al::context mContext;
};

#endif

