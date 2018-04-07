// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef TEST_HOU_GFX_TEST_GFX_RENDERING_HPP
#define TEST_HOU_GFX_TEST_GFX_RENDERING_HPP

#include "hou/gfx/TestGfxBase.hpp"



class TestGfxRendering
  : public TestGfxBase
{
public:
  TestGfxRendering();
  virtual ~TestGfxRendering() = 0;

public:
  hou::RenderTexture mRenderTexture;
};

#endif

