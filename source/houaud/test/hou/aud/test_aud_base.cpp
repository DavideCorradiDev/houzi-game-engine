// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"



std::unique_ptr<hou::audio_context> test_aud_base::sContext(nullptr);



void test_aud_base::SetUpTestCase()
{
  sContext = std::make_unique<hou::audio_context>();
  hou::audio_context::set_current(*sContext);
}



void test_aud_base::TearDownTestCase()
{
  sContext.reset();
}



test_aud_base::test_aud_base()
{}



test_aud_base::~test_aud_base()
{}
