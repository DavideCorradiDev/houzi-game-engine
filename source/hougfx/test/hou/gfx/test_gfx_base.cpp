// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"



std::unique_ptr<hou::graphic_context> test_gfx_base::sContext(nullptr);



void test_gfx_base::SetUpTestCase()
{
  sContext = std::make_unique<hou::graphic_context>();
  hou::graphic_context::set_current(*sContext);
}



void test_gfx_base::TearDownTestCase()
{
  sContext.reset();
}



test_gfx_base::test_gfx_base()
{}



test_gfx_base::~test_gfx_base()
{}

