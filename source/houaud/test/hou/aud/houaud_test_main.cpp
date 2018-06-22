// Houzi Multimedia Library
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include <gtest/gtest.h>

#include "hou/cor/cor_module.hpp"
#include "hou/mth/mth_module.hpp"
#include "hou/al/al_module.hpp"
#include "hou/aud/aud_module.hpp"



int main(int argc, char** argv)
{
  hou::cor_module::initialize();
  hou::cor_module::register_terminate_callbacks();
  hou::mth_module::initialize();
  hou::mth_module::register_terminate_callbacks();
  hou::al_module::initialize();
  hou::al_module::register_terminate_callbacks();
  hou::aud_module::initialize();
  hou::aud_module::register_terminate_callbacks();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
