// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/al/TestAlBase.hpp"

#include "hou/al/AlSourceHandle.hpp"
#include "hou/al/AlError.hpp"

using namespace hou;



namespace
{

class TestAlSourceHandle : public TestAlBase {};
class TestAlSourceHandleDeathTest : public TestAlSourceHandle {};

}



TEST_F(TestAlSourceHandle, Generation)
{
  al::SourceHandle sh = al::SourceHandle::generate();
  EXPECT_NE(0u, sh.getName());
}



#ifdef HOU_ENABLE_AL_CONTEXT_EXISTENCE_CHECKS
TEST_F(TestAlSourceHandleDeathTest, NoContextCreation)
#else
TEST_F(TestAlSourceHandleDeathTest, DISABLED_NoContextCreation)
#endif
{
  al::Context::unsetCurrent();
  HOU_EXPECT_ERROR(al::SourceHandle::generate(), std::logic_error
    , getText(AlError::ContextExistence));
}

