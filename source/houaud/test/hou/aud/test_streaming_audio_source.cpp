// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"

#include "hou/aud/empty_audio_stream_in.hpp"
#include "hou/aud/listener.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/streaming_audio_source.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class test_streaming_audio_source : public test_aud_base
{
public:
  static void SetUpTestCase();

public:
  static const std::string audio_filename;
};



class test_streaming_audio_source_death_test
  : public test_streaming_audio_source
{};



void test_streaming_audio_source::SetUpTestCase()
{
  test_aud_base::SetUpTestCase();
  listener::set_gain(0.f);
}



const std::string test_streaming_audio_source::audio_filename
  = get_data_dir() + u8"TestOgg-Stereo-16-44100.ogg";

}  // namespace



TEST_F(test_streaming_audio_source, default_constructor)
{
  streaming_audio_source as;
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
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
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(test_streaming_audio_source, stream_constructor)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_EQ(3u, as.get_buffer_count());
  EXPECT_EQ(44100u / 4u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
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
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(test_streaming_audio_source, set_stream_while_stopped)
{
  streaming_audio_source as;
  as.set_stream(std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_EQ(21231u, as.get_sample_count());
}



TEST_F(test_streaming_audio_source, set_stream_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_stream(std::make_unique<empty_audio_stream_in>());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_stream_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_stream(std::make_unique<empty_audio_stream_in>());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_time_pos_while_stopped)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_time_pos_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_sample_pos(3u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, set_time_pos_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_streaming_audio_source, set_time_pos_overflow)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_sample_pos(21432u);
  EXPECT_EQ(201u, as.get_sample_pos());
}



TEST_F(test_streaming_audio_source, set_looping)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TEST_F(test_streaming_audio_source, set_time_pos_microseconds)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
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



TEST_F(test_streaming_audio_source, stop_while_stopped)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_streaming_audio_source, stop_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_streaming_audio_source, stop_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_streaming_audio_source, play_while_stopped)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, play_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, play_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, pause_while_stopped)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.pause();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_streaming_audio_source, pause_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_streaming_audio_source, pause_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_streaming_audio_source, replay_while_stopped)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, replay_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, replay_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_streaming_audio_source, play_without_stream)
{
  streaming_audio_source as;
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_buffer_count)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  EXPECT_EQ(3u, as.get_buffer_count());
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_buffer_count_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_buffer_count_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer_count(5u);
  EXPECT_EQ(5u, as.get_buffer_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source_death_test, set_buffer_count_error)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  HOU_EXPECT_ERROR(as.set_buffer_count(0u), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(test_streaming_audio_source, set_buffer_sample_count)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_buffer_sample_count_while_playing)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source, set_buffer_sample_count_while_paused)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer_sample_count(500u);
  EXPECT_EQ(500u, as.get_buffer_sample_count());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_streaming_audio_source_death_test, set_buffer_sample_count_error)
{
  streaming_audio_source as(std::make_unique<ogg_file_in>(audio_filename));
  HOU_EXPECT_ERROR(as.set_buffer_sample_count(0u), std::logic_error,
    get_text(cor_error::pre_condition));
}
