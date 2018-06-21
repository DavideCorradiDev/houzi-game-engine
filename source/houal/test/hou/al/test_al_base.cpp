// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/test_al_base.hpp"



test_al_base::test_al_base()
  : testing::Test()
  , m_device()
  , m_context(m_device)
{
  set_context_current();
}



void test_al_base::set_context_current()
{
  hou::al::context::set_current(m_context);
}
