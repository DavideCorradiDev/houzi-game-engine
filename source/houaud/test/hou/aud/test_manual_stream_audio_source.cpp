// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"
#include "hou/test.hpp"

#include "hou/aud/listener.hpp"
#include "hou/aud/manual_stream_audio_source.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"

#include <thread>

using namespace hou;



namespace
{

class test_manual_stream_audio_source : public test_aud_base
{
public:
  static void SetUpTestCase();
};



void test_manual_stream_audio_source::SetUpTestCase()
{
  test_aud_base::SetUpTestCase();
  listener::set_gain(0.f);
}



TEST_F(test_manual_stream_audio_source, move_constructor)
{
  auto str = std::make_unique<ogg_file_in>(get_stereo16_ogg_filename());
  audio_stream_in* str_ref = str.get();
  manual_stream_audio_source as_dummy(std::move(str));
  manual_stream_audio_source as(std::move(as_dummy));
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u / 4u, as.get_buffer_sample_count());
  EXPECT_EQ(str_ref, as.get_stream());
}



TEST_F(test_manual_stream_audio_source, slow_buffer_queueing)
{
  manual_stream_audio_source as;
  as.set_buffer_count(3u);
  as.set_buffer_sample_count(4u);
  as.set_stream(std::make_unique<wav_file_in>(get_stereo16_wav_filename()));
  ASSERT_GT(as.get_sample_count(),
    as.get_buffer_count() * as.get_buffer_sample_count());
  as.play();
  // Sleep a short time to make sure the buffer has been completely processed.
  std::this_thread::sleep_for(std::chrono::milliseconds(20u));
  as.update();
  EXPECT_TRUE(as.is_playing());
}



TEST_F(test_manual_stream_audio_source, streaming_end)
{
  manual_stream_audio_source as(
    std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.play();
  while(as.is_playing())
  {
    as.update();
  }
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}

}  // namespace
