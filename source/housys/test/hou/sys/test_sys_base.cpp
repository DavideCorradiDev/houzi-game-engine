// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/test_sys_base.hpp"

#include "hou/sys/sys_module.hpp"



void test_sys_base::SetUpTestCase()
{
  HOU_ASSERT(hou::sys_module::initialize());
  hou::sys_module::register_terminate_callbacks();
}



void test_sys_base::TearDownTestCase()
{
  hou::sys_module::terminate();
}
