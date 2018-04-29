// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/al_buffer_handle.hpp"
#include "hou/al/al_error.hpp"

using namespace hou;



namespace
{

class TestAlBufferHandle : public TestAlBase {};
class TestAlBufferHandleDeathTest : public TestAlBufferHandle {};

}



TEST_F(TestAlBufferHandle, Generation)
{
  al::buffer_handle bh = al::buffer_handle::generate();
  EXPECT_NE(0u, bh.get_name());
}



#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestAlBufferHandleDeathTest, NoContextCreation)
#else
TEST_F(TestAlBufferHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  al::context::unset_current();
  HOU_EXPECT_ERROR(al::buffer_handle::generate(), std::logic_error
    , get_text(al_error::context_existence));
}

