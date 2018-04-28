// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/aud/EmptyAudioStreamIn.hpp"

#include "hou/sys/sys_error.hpp"

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
  EXPECT_EQ(0u, si.get_byte_count());
  EXPECT_EQ(0u, si.get_read_byte_count());
  EXPECT_EQ(0u, si.get_read_element_count());
  EXPECT_EQ(0, si.get_byte_pos());
  EXPECT_EQ(0u, si.getSampleCount());
  EXPECT_EQ(0, si.getSamplePos());
  EXPECT_EQ(AudioBufferFormat::Mono8, si.get_format());
  EXPECT_EQ(1u, si.getChannelCount());
  EXPECT_EQ(1u, si.getBytesPerSample());
}



TEST_F(TestEmptyAudioStreamIn, SetBytePos)
{
  EmptyAudioStreamIn si;
  si.set_byte_pos(0);
  EXPECT_EQ(0, si.get_byte_pos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, SetBytePosError)
{
  EmptyAudioStreamIn si;
  HOU_EXPECT_ERROR(si.set_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.set_byte_pos(1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestEmptyAudioStreamIn, MoveBytePos)
{
  EmptyAudioStreamIn si;
  si.move_byte_pos(0);
  EXPECT_EQ(0, si.get_byte_pos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, MoveBytePosError)
{
  EmptyAudioStreamIn si;
  HOU_EXPECT_ERROR(si.move_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.move_byte_pos(1), std::runtime_error
    , get_text(sys_error::file_seek));
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
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.setSamplePos(1), std::runtime_error
    , get_text(sys_error::file_seek));
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
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.moveSamplePos(1), std::runtime_error
    , get_text(sys_error::file_seek));
}


