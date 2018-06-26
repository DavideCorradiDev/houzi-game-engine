// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/test_gfx_base.hpp"



hou::graphic_context& test_gfx_base::get_context()
{
  static hou::graphic_context ctx;
  return ctx;
}



hou::window& test_gfx_base::get_default_window()
{
  static hou::window wnd(u8"TestGfxWindow", hou::vec2u(1u, 1u));
  return wnd;
}



void test_gfx_base::SetUpTestCase()
{
  hou::graphic_context::set_current(get_context(), get_default_window());
}



test_gfx_base::test_gfx_base()
{}
