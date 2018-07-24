// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/test.hpp"
#include "hou/aud/test_aud_base.hpp"

#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/memory_audio_source.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class test_memory_audio_source : public test_aud_base
{
public:
  test_memory_audio_source();

public:
  audio_buffer m_buffer;
};



test_memory_audio_source::test_memory_audio_source()
  : test_aud_base()
  , m_buffer(
      std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      audio_buffer_format::stereo16, 2)
{}

}  // namespace



TEST_F(test_memory_audio_source, default_constructor)
{
  memory_audio_source as;
  EXPECT_EQ(nullptr, as.get_buffer());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(audio_buffer_format::mono8, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
  EXPECT_EQ(1u, as.get_sample_rate());
  EXPECT_EQ(0u, as.get_sample_count());
  EXPECT_EQ(0u, as.get_sample_pos());
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(std::chrono::microseconds(0), as.get_duration());
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



TEST_F(test_memory_audio_source, buffer_constructor)
{
  memory_audio_source as(&m_buffer);
  EXPECT_EQ(&m_buffer, as.get_buffer());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(audio_buffer_format::stereo16, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
  EXPECT_EQ(2u, as.get_sample_rate());
  EXPECT_EQ(4u, as.get_sample_count());
  EXPECT_EQ(0u, as.get_sample_pos());
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(std::chrono::microseconds(2000000), as.get_duration());
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



TEST_F(test_memory_audio_source, move_constructor)
{
  memory_audio_source as_dummy(&m_buffer);
  memory_audio_source as(std::move(as_dummy));
  EXPECT_EQ(&m_buffer, as.get_buffer());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(audio_buffer_format::stereo16, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
  EXPECT_EQ(2u, as.get_sample_rate());
  EXPECT_EQ(0u, as.get_sample_pos());
  EXPECT_EQ(4u, as.get_sample_count());
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(std::chrono::microseconds(2000000), as.get_duration());
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



TEST_F(test_memory_audio_source, set_buffer_while_stopped)
{
  memory_audio_source as;
  as.set_buffer(&m_buffer);
  EXPECT_EQ(&m_buffer, as.get_buffer());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_memory_audio_source, set_buffer_while_playing)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.set_buffer(nullptr);
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_memory_audio_source, set_buffer_while_paused)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer(nullptr);
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_memory_audio_source, set_time_pos_while_stopped)
{
  memory_audio_source as(&m_buffer);
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_memory_audio_source, set_time_pos_while_playing)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.set_sample_pos(3u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, set_time_pos_while_paused)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_memory_audio_source, set_time_pos_overflow)
{
  memory_audio_source as(&m_buffer);
  as.set_sample_pos(6u);
  EXPECT_EQ(2u, as.get_sample_pos());
}



TEST_F(test_memory_audio_source, set_time_pos_microseconds)
{
  memory_audio_source as(&m_buffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(0u, as.get_sample_pos());
  as.set_time_pos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.get_time_pos());
  EXPECT_EQ(3u, as.get_sample_pos());
  as.set_sample_pos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.get_time_pos());
  EXPECT_EQ(1u, as.get_sample_pos());
}



TEST_F(test_memory_audio_source, set_looping)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TEST_F(test_memory_audio_source, stop_while_stopped)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_memory_audio_source, stop_while_playing)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_memory_audio_source, stop_while_paused)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_memory_audio_source, play_while_stopped)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, play_while_playing)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, play_while_paused)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, pause_while_stopped)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.pause();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_memory_audio_source, pause_while_playing)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_memory_audio_source, pause_while_paused)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_memory_audio_source, replay_while_stopped)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, replay_while_playing)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, replay_while_paused)
{
  memory_audio_source as(&m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_memory_audio_source, play_without_buffer)
{
  memory_audio_source as;
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_memory_audio_source, buffer_properties_mono8)
{
  audio_buffer buf(
    std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    audio_buffer_format::mono8, 2);
  memory_audio_source as(&buf);
  EXPECT_EQ(audio_buffer_format::mono8, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
}



TEST_F(test_memory_audio_source, buffer_properties_mono16)
{
  audio_buffer buf(
    std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    audio_buffer_format::mono16, 2);
  memory_audio_source as(&buf);
  EXPECT_EQ(audio_buffer_format::mono16, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
}



TEST_F(test_memory_audio_source, buffer_properties_stereo8)
{
  audio_buffer buf(
    std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    audio_buffer_format::stereo8, 2);
  memory_audio_source as(&buf);
  EXPECT_EQ(audio_buffer_format::stereo8, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
}



TEST_F(test_memory_audio_source, buffer_properties_stereo16)
{
  audio_buffer buf(
    std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    audio_buffer_format::stereo16, 2);
  memory_audio_source as(&buf);
  EXPECT_EQ(audio_buffer_format::stereo16, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
}
