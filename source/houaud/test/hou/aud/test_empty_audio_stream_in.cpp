// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/aud/empty_audio_stream_in.hpp"

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
  empty_audio_stream_in si;

  EXPECT_TRUE(si.eof());
  EXPECT_FALSE(si.error());
  EXPECT_EQ(0u, si.get_byte_count());
  EXPECT_EQ(0u, si.get_read_byte_count());
  EXPECT_EQ(0u, si.get_read_element_count());
  EXPECT_EQ(0, si.get_byte_pos());
  EXPECT_EQ(0u, si.get_sample_count());
  EXPECT_EQ(0, si.get_sample_pos());
  EXPECT_EQ(audio_buffer_format::mono8, si.get_format());
  EXPECT_EQ(1u, si.get_channel_count());
  EXPECT_EQ(1u, si.get_bytes_per_sample());
}



TEST_F(TestEmptyAudioStreamIn, SetBytePos)
{
  empty_audio_stream_in si;
  si.set_byte_pos(0);
  EXPECT_EQ(0, si.get_byte_pos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, SetBytePosError)
{
  empty_audio_stream_in si;
  HOU_EXPECT_ERROR(si.set_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.set_byte_pos(1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestEmptyAudioStreamIn, MoveBytePos)
{
  empty_audio_stream_in si;
  si.move_byte_pos(0);
  EXPECT_EQ(0, si.get_byte_pos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, MoveBytePosError)
{
  empty_audio_stream_in si;
  HOU_EXPECT_ERROR(si.move_byte_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.move_byte_pos(1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestEmptyAudioStreamIn, SetSamplePos)
{
  empty_audio_stream_in si;
  si.set_sample_pos(0);
  EXPECT_EQ(0, si.get_sample_pos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, SetSamplePosError)
{
  empty_audio_stream_in si;
  HOU_EXPECT_ERROR(si.set_sample_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.set_sample_pos(1), std::runtime_error
    , get_text(sys_error::file_seek));
}



TEST_F(TestEmptyAudioStreamIn, move_sample_pos)
{
  empty_audio_stream_in si;
  si.move_sample_pos(0);
  EXPECT_EQ(0, si.get_sample_pos());
}



TEST_F(TestEmptyAudioStreamInDeathTest, MoveSamplePosError)
{
  empty_audio_stream_in si;
  HOU_EXPECT_ERROR(si.move_sample_pos(-1), std::runtime_error
    , get_text(sys_error::file_seek));
  HOU_EXPECT_ERROR(si.move_sample_pos(1), std::runtime_error
    , get_text(sys_error::file_seek));
}


