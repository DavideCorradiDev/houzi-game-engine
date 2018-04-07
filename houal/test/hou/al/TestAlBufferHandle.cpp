// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlBufferHandle.hpp"
#include "hou/al/AlError.hpp"

using namespace hou;



namespace
{

class TestAlBufferHandle : public TestAlBase {};
class TestAlBufferHandleDeathTest : public TestAlBufferHandle {};

}



TEST_F(TestAlBufferHandle, Generation)
{
  al::BufferHandle bh = al::BufferHandle::generate();
  EXPECT_NE(0u, bh.getName());
}



#if defined(HOU_DISABLE_AL_CONTEXT_EXISTENCE_CHECKS)
TEST_F(TestAlBufferHandleDeathTest, DISABLED_NoContextCreation)
#else
TEST_F(TestAlBufferHandleDeathTest, NoContextCreation)
#endif
{
  al::Context::unsetCurrent();
  HOU_EXPECT_ERROR(al::BufferHandle::generate(), std::logic_error
    , getText(AlError::ContextExistence));
}
