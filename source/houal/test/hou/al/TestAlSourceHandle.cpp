// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/al_source_handle.hpp"
#include "hou/al/al_error.hpp"

using namespace hou;



namespace
{

class TestAlSourceHandle : public TestAlBase {};
class TestAlSourceHandleDeathTest : public TestAlSourceHandle {};

}



TEST_F(TestAlSourceHandle, Generation)
{
  al::source_handle sh = al::source_handle::generate();
  EXPECT_NE(0u, sh.get_name());
}



#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestAlSourceHandleDeathTest, NoContextCreation)
#else
TEST_F(TestAlSourceHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  al::context::unset_current();
  HOU_EXPECT_ERROR(al::source_handle::generate(), std::logic_error
    , get_text(al_error::context_existence));
}

