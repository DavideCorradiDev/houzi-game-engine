// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/aud/AudioContext.hpp"

using namespace hou;



TEST(TestAudioContext, DefaultCreation)
{
  AudioContext ctx;
  SUCCEED();
}



TEST(TestAudioContext, DeviceNameCreation)
{
  std::vector<std::string> deviceNames = AudioContext::getDeviceNames();
  for(const auto& deviceName : deviceNames)
  {
    AudioContext ctx(deviceName);
  }
  SUCCEED();
}



TEST(TestAudioContext, MoveConstructor)
{
  AudioContext ctxDummy;
  AudioContext::set_current(ctxDummy);
  AudioContext ctx = std::move(ctxDummy);
  EXPECT_TRUE(ctx.is_current());
}



TEST(TestAudioContext, SetCurrent)
{
  {
    AudioContext ctx1;
    AudioContext ctx2;

    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    AudioContext::set_current(ctx1);
    EXPECT_TRUE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    AudioContext::set_current(ctx2);
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_TRUE(ctx2.is_current());

    AudioContext::set_current(ctx2);
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_TRUE(ctx2.is_current());

    AudioContext::unset_current();
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());

    AudioContext::unset_current();
    EXPECT_FALSE(ctx1.is_current());
    EXPECT_FALSE(ctx2.is_current());
  }
  EXPECT_EQ(nullptr, al::context::getCurrent());
}

