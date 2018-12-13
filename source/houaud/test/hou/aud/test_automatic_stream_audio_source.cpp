// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"
#include "hou/test.hpp"

#include "hou/aud/automatic_stream_audio_source.hpp"
#include "hou/aud/listener.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class test_automatic_stream_audio_source : public test_aud_base
{
public:
  static void SetUpTestCase();

public:
  static const std::string audio_filename;
  static const std::string mono8_filename;
  static const std::string mono16_filename;
  static const std::string stereo8_filename;
  static const std::string stereo16_filename;
};



class test_automatic_stream_audio_source_death_testh
  : public test_automatic_stream_audio_source
{};



void test_automatic_stream_audio_source::SetUpTestCase()
{
  test_aud_base::SetUpTestCase();
  listener::set_gain(0.f);
}



const std::string test_automatic_stream_audio_source::audio_filename
  = get_data_dir() + u8"TestOgg-stereo-16-44100.ogg";
const std::string test_automatic_stream_audio_source::mono8_filename
  = get_data_dir() + u8"TestWav-mono-8-44100.wav";
const std::string test_automatic_stream_audio_source::mono16_filename
  = get_data_dir() + u8"TestWav-mono-16-44100.wav";
const std::string test_automatic_stream_audio_source::stereo8_filename
  = get_data_dir() + u8"TestWav-stereo-8-44100.wav";
const std::string test_automatic_stream_audio_source::stereo16_filename
  = get_data_dir() + u8"TestWav-stereo-16-44100.wav";

}  // namespace



TEST_F(test_automatic_stream_audio_source, default_constructor)
{
  automatic_stream_audio_source as;
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u, as.get_buffer_sample_count());
  EXPECT_EQ(nullptr, as.get_stream());
  EXPECT_FALSE(as.is_valid());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(audio_buffer_format::mono8, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
  EXPECT_EQ(1u, as.get_sample_rate());
  EXPECT_EQ(0u, as.get_sample_count());
  EXPECT_EQ(0u, as.get_sample_pos());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.get_time_pos());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.get_duration());
  EXPECT_FALSE(as.is_looping());
  EXPECT_FLOAT_EQ(1.f, as.get_pitch());
  EXPECT_FLOAT_EQ(1.f, as.get_gain());
  EXPECT_FLOAT_EQ(1.f, as.get_max_gain());
  EXPECT_FLOAT_EQ(0.f, as.get_min_gain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), as.get_max_distance());
  EXPECT_FLOAT_EQ(1.f, as.get_rolloff_factor());
  EXPECT_FLOAT_EQ(1.f, as.get_reference_distance());
  EXPECT_FALSE(as.is_relative());
  EXPECT_FLOAT_EQ(0.f, as.get_cone_outer_gain());
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_outer_angle());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(test_automatic_stream_audio_source, stream_constructor)
{
  auto str = std::make_unique<ogg_file_in>(audio_filename);
  audio_stream_in* str_ref = str.get();
  automatic_stream_audio_source as(std::move(str));
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u / 4u, as.get_buffer_sample_count());
  EXPECT_EQ(str_ref, as.get_stream());
  EXPECT_TRUE(as.is_valid());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(audio_buffer_format::stereo16, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
  EXPECT_EQ(44100u, as.get_sample_rate());
  EXPECT_EQ(21231u, as.get_sample_count());
  EXPECT_EQ(0u, as.get_sample_pos());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.get_time_pos());
  EXPECT_EQ(std::chrono::nanoseconds(481428571), as.get_duration());
  EXPECT_FALSE(as.is_looping());
  EXPECT_FLOAT_EQ(1.f, as.get_pitch());
  EXPECT_FLOAT_EQ(1.f, as.get_gain());
  EXPECT_FLOAT_EQ(1.f, as.get_max_gain());
  EXPECT_FLOAT_EQ(0.f, as.get_min_gain());
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), as.get_max_distance());
  EXPECT_FLOAT_EQ(1.f, as.get_rolloff_factor());
  EXPECT_FLOAT_EQ(1.f, as.get_reference_distance());
  EXPECT_FALSE(as.is_relative());
  EXPECT_FLOAT_EQ(0.f, as.get_cone_outer_gain());
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_outer_angle());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(test_automatic_stream_audio_source, validity_after_set_stream)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_TRUE(as.is_valid());
  as.set_stream(nullptr);
  EXPECT_FALSE(as.is_valid());
  as.set_stream(std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_TRUE(as.is_valid());
}



TEST_F(test_automatic_stream_audio_source, set_stream_while_playing)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_stream(nullptr);
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_stream_while_paused)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_stream(nullptr);
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_sample_pos_while_stopped)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_sample_pos_while_playing)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_sample_pos(3u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_sample_pos_while_paused)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_sample_pos_overflow_not_looping)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.play();
  as.set_sample_pos(as.get_sample_count() + 1u);
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, set_sample_pos_overflow_looping)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_sample_pos(as.get_sample_count() + 1u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_looping)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TEST_F(test_automatic_stream_audio_source, set_time_pos_microseconds)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  ogg_file_in fi(audio_filename);
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(0u, as.get_sample_pos());
  as.set_time_pos(std::chrono::microseconds(30000));
  EXPECT_EQ(std::chrono::microseconds(30000), as.get_time_pos());
  EXPECT_EQ(1323u, as.get_sample_pos());
  as.set_sample_pos(11025u);
  EXPECT_EQ(std::chrono::microseconds(250000), as.get_time_pos());
  EXPECT_EQ(11025u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, stop_at_initial_state)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.stop();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, stop_after_play)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, stop_after_pause)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, stop_after_stop)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  as.stop();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, play_at_initial_state)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, play_after_play)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, play_after_pause)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, play_after_stop)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.stop();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, pause_at_initial_state)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
  EXPECT_EQ(3u, as.get_sample_pos());
}



TEST_F(test_automatic_stream_audio_source, pause_after_play)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, pause_after_pause)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, pause_after_stop)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.stop();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, replay_at_intial_state)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, replay_after_play)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, replay_after_pause)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, replay_after_stop)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.stop();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, play_without_stream)
{
  automatic_stream_audio_source as;
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_buffer_count)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_EQ(3u, as.get_buffer_count());
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_buffer_count_while_playing)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_buffer_count_while_paused)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source_death_testh, set_buffer_count_error)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_PRECOND_ERROR(as.set_buffer_count(0u));
}



TEST_F(test_automatic_stream_audio_source, set_buffer_sample_count)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(
  test_automatic_stream_audio_source, set_buffer_sample_count_while_playing)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_automatic_stream_audio_source, set_buffer_sample_count_while_paused)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(
  test_automatic_stream_audio_source_death_testh, set_buffer_sample_count_error)
{
  automatic_stream_audio_source as(
    std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_PRECOND_ERROR(as.set_buffer_sample_count(0u));
}



TEST_F(test_automatic_stream_audio_source, buffer_properties_mono8)
{
  automatic_stream_audio_source as(
    std::make_unique<wav_file_in>(mono8_filename));
  EXPECT_EQ(audio_buffer_format::mono8, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
}



TEST_F(test_automatic_stream_audio_source, buffer_properties_mono16)
{
  automatic_stream_audio_source as(
    std::make_unique<wav_file_in>(mono16_filename));
  EXPECT_EQ(audio_buffer_format::mono16, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
}



TEST_F(test_automatic_stream_audio_source, buffer_properties_stereo8)
{
  automatic_stream_audio_source as(
    std::make_unique<wav_file_in>(stereo8_filename));
  EXPECT_EQ(audio_buffer_format::stereo8, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
}



TEST_F(test_automatic_stream_audio_source, buffer_properties_stereo16)
{
  automatic_stream_audio_source as(
    std::make_unique<wav_file_in>(stereo16_filename));
  EXPECT_EQ(audio_buffer_format::stereo16, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
}
