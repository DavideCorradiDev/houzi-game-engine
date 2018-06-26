// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GFX_TEST_GFX_BASE_HPP
#define TEST_HOU_GFX_TEST_GFX_BASE_HPP

#include <gtest/gtest.h>

#include "hou/gfx/graphic_context.hpp"

#include "hou/sys/window.hpp"



class test_gfx_base : public ::testing::Test
{
public:
  static hou::graphic_context& get_context();
  static hou::window& get_default_window();
  static void SetUpTestCase();

public:
  test_gfx_base();
};

#endif
