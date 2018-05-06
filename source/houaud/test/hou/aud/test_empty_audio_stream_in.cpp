// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"

#include "hou/aud/empty_audio_stream_in.hpp"

#include "hou/sys/system_exceptions.hpp"

using namespace hou;
using namespace testing;



namespace
{

class test_empty_audio_stream_in : public Test
{};

class test_empty_audio_stream_in_death_test : public test_empty_audio_stream_in
{};

}  // namespace



TEST_F(test_empty_audio_stream_in, default_constructor)
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



TEST_F(test_empty_audio_stream_in, set_byte_pos)
{
  empty_audio_stream_in si;
  si.set_byte_pos(0);
  EXPECT_EQ(0, si.get_byte_pos());
}



TEST_F(test_empty_audio_stream_in_death_test, set_byte_pos_error)
{
  empty_audio_stream_in si;
  EXPECT_ERROR_0(si.set_byte_pos(-1), file_cursor_error);
  EXPECT_ERROR_0(si.set_byte_pos(1), file_cursor_error);
}



TEST_F(test_empty_audio_stream_in, move_byte_pos)
{
  empty_audio_stream_in si;
  si.move_byte_pos(0);
  EXPECT_EQ(0, si.get_byte_pos());
}



TEST_F(test_empty_audio_stream_in_death_test, move_byte_pos_error)
{
  empty_audio_stream_in si;
  EXPECT_ERROR_0(si.move_byte_pos(-1), file_cursor_error);
  EXPECT_ERROR_0(si.move_byte_pos(1), file_cursor_error);
}



TEST_F(test_empty_audio_stream_in, set_sample_pos)
{
  empty_audio_stream_in si;
  si.set_sample_pos(0);
  EXPECT_EQ(0, si.get_sample_pos());
}



TEST_F(test_empty_audio_stream_in_death_test, set_sample_pos_error)
{
  empty_audio_stream_in si;
  EXPECT_ERROR_0(si.set_sample_pos(-1), file_cursor_error);
  EXPECT_ERROR_0(si.set_sample_pos(1), file_cursor_error);
}



TEST_F(test_empty_audio_stream_in, move_sample_pos)
{
  empty_audio_stream_in si;
  si.move_sample_pos(0);
  EXPECT_EQ(0, si.get_sample_pos());
}



TEST_F(test_empty_audio_stream_in_death_test, move_sample_pos_error)
{
  empty_audio_stream_in si;
  EXPECT_ERROR_0(si.move_sample_pos(-1), file_cursor_error);
  EXPECT_ERROR_0(si.move_sample_pos(1), file_cursor_error);
}
