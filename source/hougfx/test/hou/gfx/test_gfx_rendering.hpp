// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef TEST_HOU_GFX_TEST_GFX_RENDERING_HPP
#define TEST_HOU_GFX_TEST_GFX_RENDERING_HPP

#include "hou/gfx/test_gfx_base.hpp"



class test_gfx_rendering : public test_gfx_base
{
public:
  test_gfx_rendering();
  virtual ~test_gfx_rendering() = 0;

public:
  hou::RenderTexture m_render_texture;
};

#endif
