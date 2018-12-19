// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"
#include "hou/test.hpp"

#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/buffer_audio_source.hpp"
#include "hou/aud/listener.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"

using namespace hou;



namespace
{

class test_buffer_audio_source : public test_aud_base
{
public:
  static void SetUpTestCase();
};



void test_buffer_audio_source::SetUpTestCase()
{
  test_aud_base::SetUpTestCase();
  listener::set_gain(0.f);
}



TEST_F(test_buffer_audio_source, default_constructor)
{
  buffer_audio_source as;
  EXPECT_EQ(nullptr, as.get_buffer());
}



TEST_F(test_buffer_audio_source, buffer_constructor)
{
  auto buffer
    = std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename()));
  buffer_audio_source as(buffer);
  EXPECT_EQ(buffer.get(), as.get_buffer());
}



TEST_F(test_buffer_audio_source, move_constructor)
{
  auto buffer
    = std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename()));
  buffer_audio_source as_dummy(buffer);
  buffer_audio_source as(std::move(as_dummy));
  EXPECT_EQ(buffer.get(), as.get_buffer());
}



TEST_F(test_buffer_audio_source, validity_after_set_buffer)
{
  buffer_audio_source as;
  EXPECT_FALSE(as.is_valid());
  as.set_buffer(
    std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename())));
  EXPECT_TRUE(as.is_valid());
  as.set_buffer(nullptr);
  EXPECT_FALSE(as.is_valid());
}



TEST_F(test_buffer_audio_source, set_buffer_while_playing)
{
  buffer_audio_source as(
    std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename())));
  as.set_looping(true);
  as.play();
  EXPECT_TRUE(as.is_playing());
  as.set_buffer(
    std::make_shared<audio_buffer>(wav_file_in(get_mono16_wav_filename())));
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TEST_F(test_buffer_audio_source, set_empty_buffer_while_playing)
{
  buffer_audio_source as(
    std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename())));
  as.set_looping(true);
  as.play();
  EXPECT_TRUE(as.is_playing());
  as.set_buffer(nullptr);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TEST_F(test_buffer_audio_source, set_buffer_while_paused)
{
  buffer_audio_source as(
    std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename())));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer(
    std::make_shared<audio_buffer>(wav_file_in(get_mono16_wav_filename())));
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TEST_F(test_buffer_audio_source, set_empty_buffer_while_paused)
{
  buffer_audio_source as(
    std::make_shared<audio_buffer>(wav_file_in(get_stereo16_wav_filename())));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer(nullptr);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}

}  // namespace
