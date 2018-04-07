// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef TEST_HOU_GFX_TEST_GFX_BASE_HPP
#define TEST_HOU_GFX_TEST_GFX_BASE_HPP

#include <gtest/gtest.h>

#include "hou/gfx/RenderContext.hpp"



class TestGfxBase
  : public ::testing::Test
{
public:
  TestGfxBase();
  virtual ~TestGfxBase() = 0;

public:
  hou::RenderContext mContext;
};

#endif
