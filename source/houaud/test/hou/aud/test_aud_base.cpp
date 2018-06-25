// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"



hou::audio_context& test_aud_base::get_context()
{
  static hou::audio_context ctx;
  return ctx;
}



void test_aud_base::SetUpTestCase()
{
  hou::audio_context::set_current(get_context());
}



test_aud_base::test_aud_base()
{}
