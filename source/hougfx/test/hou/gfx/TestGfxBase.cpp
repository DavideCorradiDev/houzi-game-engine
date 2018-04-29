// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TestGfxBase.hpp"



std::unique_ptr<hou::GraphicContext> TestGfxBase::sContext(nullptr);



void TestGfxBase::SetUpTestCase()
{
  sContext = std::make_unique<hou::GraphicContext>();
  hou::GraphicContext::set_current(*sContext);
}



void TestGfxBase::TearDownTestCase()
{
  sContext.reset();
}



TestGfxBase::TestGfxBase()
{}



TestGfxBase::~TestGfxBase()
{}

