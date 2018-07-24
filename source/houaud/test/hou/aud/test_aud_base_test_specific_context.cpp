// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base_test_specific_context.hpp"



test_aud_base_test_specific_context::test_aud_base_test_specific_context()
  : m_context()
{
  hou::audio_context::set_current(m_context);
}



test_aud_base_test_specific_context::~test_aud_base_test_specific_context()
{}
