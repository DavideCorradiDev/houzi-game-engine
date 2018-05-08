// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"

#include "hou/aud/aud_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_aud_exceptions : public Test
{};

}  // namespace



TEST_F(test_aud_exceptions, invalid_audio_data)
{
  invalid_audio_data ex("foo.cpp", 88u);
  EXPECT_STREQ("foo.cpp:88 - Invalid or corrupted audio data.", ex.what());
}
