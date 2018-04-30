// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_AL_TEST_AL_BASE_HPP
#define TEST_HOU_AL_TEST_AL_BASE_HPP

#include <gtest/gtest.h>

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"



class test_al_base
  : public testing::Test
{
public:
  test_al_base();
  virtual ~test_al_base() = 0;

  void set_context_current();

protected:
  hou::al::device m_device;
  hou::al::context m_context;
};

#endif

