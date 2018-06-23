// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"



std::unique_ptr<hou::graphic_context> test_gfx_base::s_context(nullptr);



void test_gfx_base::SetUpTestCase()
{
  s_context = std::make_unique<hou::graphic_context>();
  hou::graphic_context::set_current(*s_context);
}



void test_gfx_base::TearDownTestCase()
{
  s_context.reset();
}



test_gfx_base::test_gfx_base()
{}
