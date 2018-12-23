// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"
#include "hou/test.hpp"

#include "hou/aud/audio_source.hpp"
#include "hou/aud/automatic_stream_audio_source.hpp"
#include "hou/aud/listener.hpp"
#include "hou/aud/manual_stream_audio_source.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"

using namespace hou;
using namespace testing;



namespace
{

template <typename AudioSourceType>
class test_stream_audio_source : public test_aud_base
{
public:
  static void SetUpTestCase();
};



template <typename AudioSourceType>
void test_stream_audio_source<AudioSourceType>::SetUpTestCase()
{
  test_aud_base::SetUpTestCase();
  listener::set_gain(0.f);
}



using stream_audio_source_types
  = Types<automatic_stream_audio_source, manual_stream_audio_source>;
TYPED_TEST_CASE(test_stream_audio_source, stream_audio_source_types);



TYPED_TEST(test_stream_audio_source, default_constructor)
{
  TypeParam as;
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u, as.get_buffer_sample_count());
  EXPECT_EQ(nullptr, as.get_stream());
}



TYPED_TEST(test_stream_audio_source, stream_constructor)
{
  auto str = std::make_unique<ogg_file_in>(get_stereo16_ogg_filename());
  audio_stream_in* str_ref = str.get();
  TypeParam as(std::move(str));
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u / 4u, as.get_buffer_sample_count());
  EXPECT_EQ(str_ref, as.get_stream());
}



// Note: the move constructor cannot be tested here because the
// automatic_stream_audio_source does not implement it.



TYPED_TEST(test_stream_audio_source, validity_after_set_stream)
{
  TypeParam as;
  EXPECT_FALSE(as.is_valid());
  as.set_stream(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  EXPECT_TRUE(as.is_valid());
  as.set_stream(nullptr);
  EXPECT_FALSE(as.is_valid());
}



TYPED_TEST(test_stream_audio_source, set_stream_while_playing)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  EXPECT_TRUE(as.is_playing());
  as.set_stream(std::make_unique<wav_file_in>(get_stereo16_wav_filename()));
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_stream_audio_source, set_empty_stream_while_playing)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  EXPECT_TRUE(as.is_playing());
  as.set_stream(nullptr);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_stream_audio_source, set_stream_while_paused)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_stream(std::make_unique<wav_file_in>(get_stereo16_wav_filename()));
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_stream_audio_source, set_empty_stream_while_paused)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_stream(nullptr);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_stream_audio_source, set_buffer_count)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  EXPECT_EQ(3u, as.get_buffer_count());
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_stream_audio_source, set_buffer_count_while_playing)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_stream_audio_source, set_buffer_count_while_paused)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_stream_audio_source, set_buffer_count_error)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  EXPECT_PRECOND_ERROR(as.set_buffer_count(0u));
}



TYPED_TEST(test_stream_audio_source, set_buffer_sample_count)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_stream_audio_source, set_buffer_sample_count_while_playing)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_stream_audio_source, set_buffer_sample_count_while_paused)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_stream_audio_source, set_buffer_sample_count_error)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  EXPECT_PRECOND_ERROR(as.set_buffer_sample_count(0u));
}



TYPED_TEST(test_stream_audio_source, test_single_buffer)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_buffer_count(1u);
  as.play();
  as.stop();
  SUCCEED();
}



TYPED_TEST(test_stream_audio_source, test_single_sample_per_buffer)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_buffer_sample_count(1u);
  as.play();
  as.stop();
  SUCCEED();
}



TYPED_TEST(test_stream_audio_source, test_single_sample_in_queue)
{
  TypeParam as(std::make_unique<ogg_file_in>(get_stereo16_ogg_filename()));
  as.set_buffer_count(1u);
  as.set_buffer_sample_count(1u);
  as.play();
  as.stop();
  SUCCEED();
}

}  // namespace
