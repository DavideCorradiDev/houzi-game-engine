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



TEST_F(test_aud_exceptions, audio_read_error)
{
  audio_read_error ex("foo.cpp", 88u, "path/to/file.wav");
  EXPECT_STREQ(
    "foo.cpp:88 - Failed to read audio from file 'path/to/file.wav'.",
    ex.what());
}
