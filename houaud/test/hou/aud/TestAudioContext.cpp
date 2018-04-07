// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

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
  AudioContext::setCurrent(ctxDummy);
  AudioContext ctx = std::move(ctxDummy);
  EXPECT_TRUE(ctx.isCurrent());
}



TEST(TestAudioContext, SetCurrent)
{
  {
    AudioContext ctx1;
    AudioContext ctx2;

    EXPECT_FALSE(ctx1.isCurrent());
    EXPECT_TRUE(ctx2.isCurrent());

    AudioContext::setCurrent(ctx1);
    EXPECT_TRUE(ctx1.isCurrent());
    EXPECT_FALSE(ctx2.isCurrent());

    AudioContext::setCurrent(ctx2);
    EXPECT_FALSE(ctx1.isCurrent());
    EXPECT_TRUE(ctx2.isCurrent());

    AudioContext::setCurrent(ctx2);
    EXPECT_FALSE(ctx1.isCurrent());
    EXPECT_TRUE(ctx2.isCurrent());
  }
  EXPECT_EQ(nullptr, al::Context::getCurrent());
}

