// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/aud/audio_context.hpp"

using namespace hou;



TEST(TestAudioContext, DefaultCreation)
{
  audio_context ctx;
  SUCCEED();
}



TEST(TestAudioContext, DeviceNameCreation)
{
  std::vector<std::string> deviceNames = audio_context::get_device_names();
  for(const auto& dev_name : deviceNames)
  {
    audio_context ctx(dev_name);
  }
  SUCCEED();
}



TEST(TestAudioContext, MoveConstructor)
{
  audio_context ctx_dummy;
  audio_context::set_current(ctx_dummy);
  audio_context ctx = std::move(ctx_dummy);
  EXPECT_TRUE(ctx.is_current());
}



TEST(TestAudioContext, SetCurrent)
{
  {
    audio_context ctx1;
    audio_context ctx2;

    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    audio_context::set_current(ctx1);
    EXPECT_TRUE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    audio_context::set_current(ctx2);
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_TRUE(ctx2.is_current());

    audio_context::set_current(ctx2);
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_TRUE(ctx2.is_current());

    audio_context::unset_current();
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    audio_context::unset_current();
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());
  }
  EXPECT_EQ(nullptr, al::context::get_current());
}

