// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/TestAudBase.hpp"



std::unique_ptr<hou::AudioContext> TestAudBase::sContext(nullptr);



void TestAudBase::SetUpTestCase()
{
  sContext = std::make_unique<hou::AudioContext>();
  hou::AudioContext::setCurrent(*sContext);
}



void TestAudBase::TearDownTestCase()
{
  sContext.reset();
}



TestAudBase::TestAudBase()
{}



TestAudBase::~TestAudBase()
{}

