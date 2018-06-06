// Houzi Multimedia Library
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include <gtest/gtest.h>

#include "hou/sys/sys_module.hpp"



int main(int argc, char** argv)
{
  hou::sys_module::initialize();
  hou::sys_module::register_terminate_callbacks();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
