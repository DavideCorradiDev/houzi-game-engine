// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/aud/EmptyAudioStreamIn.hpp"

#include "hou/sys/SysError.hpp"

using namespace hou;
using namespace testing;



namespace
{

class TestEmptyAudioStreamIn : public Test {};
class TestEmptyAudioStreamInDeathTest : public TestEmptyAudioStreamIn {};

}



TEST_F(TestEmptyAudioStreamIn, DefaultConstructor)
{
  EmptyAudioStreamIn si;

  EXPECT_TRUE(si.eof());
  EXPECT_FALSE(si.error());
  EXPECT_EQ(0u, si.getByteCount());
  EXPECT_EQ(0u, si.getReadByteCount());
  EXPECT_EQ(0u, si.getReadElementCount());
  EXPECT_EQ(0, si.getBytePos());
  EXPECT_EQ(0u, si.getSampleCount());
  EXPECT_EQ(0, si.getSamplePos());
  EXPECT_EQ(AudioBufferFormat::Mono8, si.getFormat());
  EXPECT_EQ(1u, si.getChannelCount());
  EXPECT_EQ(1u, si.getBytesPerSample());
}



TEST_F(TestEmptyAudioStreamIn, SetBytePos)
{
  EmptyAudioStreamIn si;
  si.setBytePos(0);
  EXPECT_EQ(0, si.getBytePos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, SetBytePosError)
{
  EmptyAudioStreamIn si;
  HOU_EXPECT_ERROR(si.setBytePos(-1), std::runtime_error
    , get_text(SysError::FileSeek));
  HOU_EXPECT_ERROR(si.setBytePos(1), std::runtime_error
    , get_text(SysError::FileSeek));
}



TEST_F(TestEmptyAudioStreamIn, MoveBytePos)
{
  EmptyAudioStreamIn si;
  si.moveBytePos(0);
  EXPECT_EQ(0, si.getBytePos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, MoveBytePosError)
{
  EmptyAudioStreamIn si;
  HOU_EXPECT_ERROR(si.moveBytePos(-1), std::runtime_error
    , get_text(SysError::FileSeek));
  HOU_EXPECT_ERROR(si.moveBytePos(1), std::runtime_error
    , get_text(SysError::FileSeek));
}



TEST_F(TestEmptyAudioStreamIn, SetSamplePos)
{
  EmptyAudioStreamIn si;
  si.setSamplePos(0);
  EXPECT_EQ(0, si.getSamplePos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, SetSamplePosError)
{
  EmptyAudioStreamIn si;
  HOU_EXPECT_ERROR(si.setSamplePos(-1), std::runtime_error
    , get_text(SysError::FileSeek));
  HOU_EXPECT_ERROR(si.setSamplePos(1), std::runtime_error
    , get_text(SysError::FileSeek));
}



TEST_F(TestEmptyAudioStreamIn, MoveSamplePos)
{
  EmptyAudioStreamIn si;
  si.moveSamplePos(0);
  EXPECT_EQ(0, si.getSamplePos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, MoveSamplePosError)
{
  EmptyAudioStreamIn si;
  HOU_EXPECT_ERROR(si.moveSamplePos(-1), std::runtime_error
    , get_text(SysError::FileSeek));
  HOU_EXPECT_ERROR(si.moveSamplePos(1), std::runtime_error
    , get_text(SysError::FileSeek));
}


