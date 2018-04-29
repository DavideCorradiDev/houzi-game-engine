// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/TestAudBase.hpp"



std::unique_ptr<hou::audio_context> TestAudBase::sContext(nullptr);



void TestAudBase::SetUpTestCase()
{
  sContext = std::make_unique<hou::audio_context>();
  hou::audio_context::set_current(*sContext);
}



void TestAudBase::TearDownTestCase()
{
  sContext.reset();
}



TestAudBase::TestAudBase()
{}



TestAudBase::~TestAudBase()
{}
