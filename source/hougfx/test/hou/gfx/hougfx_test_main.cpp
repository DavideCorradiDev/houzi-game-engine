// Houzi Multimedia Library
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include <gtest/gtest.h>

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/sys/sys_module.hpp"
#include "hou/gl/gl_module.hpp"
#include "hou/gfx/gfx_module.hpp"



int main(int argc, char** argv)
{
  hou::cor_module::initialize();
  hou::mth_module::initialize();
  hou::sys_module::initialize();
  hou::gl_module::initialize();
  hou::gfx_module::initialize();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
