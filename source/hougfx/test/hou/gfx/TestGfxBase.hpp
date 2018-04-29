// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GFX_TEST_GFX_BASE_HPP
#define TEST_HOU_GFX_TEST_GFX_BASE_HPP

#include <gtest/gtest.h>

#include "hou/gfx/graphic_context.hpp"



class TestGfxBase
  : public ::testing::Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();

public:
  TestGfxBase();
  virtual ~TestGfxBase() = 0;

public:
  static std::unique_ptr<hou::graphic_context> sContext;
};

#endif

