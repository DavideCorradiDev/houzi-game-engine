// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_SYS_TEST_SYS_BASE_HPP
#define TEST_HOU_SYS_TEST_SYS_BASE_HPP

#include "hou/test.hpp"

class test_sys_base : public ::testing::Test
{
public:
  static void SetUpTestCase();
  static void TearDownTestCase();
};

#endif
