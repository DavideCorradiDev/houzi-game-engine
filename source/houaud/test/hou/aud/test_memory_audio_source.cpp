// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_aud_base.hpp"

#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/memory_audio_source.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class TestMemoryAudioSource
  : public test_aud_base
{
public:
  TestMemoryAudioSource();

public:
  audio_buffer mBuffer;
};



TestMemoryAudioSource::TestMemoryAudioSource()
  : test_aud_base()
  , mBuffer(std::vector<uint8_t>{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    , audio_buffer_format::stereo16, 2)
{}

}



TEST_F(TestMemoryAudioSource, DefaultConstructor)
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
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(TestMemoryAudioSource, BufferConstructor)
{
  memory_audio_source as(&mBuffer);
  EXPECT_EQ(&mBuffer, as.get_buffer());
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
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(TestMemoryAudioSource, MoveConstructor)
{
  memory_audio_source asDummy(&mBuffer);
  memory_audio_source as(std::move(asDummy));
  EXPECT_EQ(&mBuffer, as.get_buffer());
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
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  HOU_EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(TestMemoryAudioSource, SetBufferWhileStopped)
{
  memory_audio_source as;
  as.set_buffer(&mBuffer);
  EXPECT_EQ(&mBuffer, as.get_buffer());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(TestMemoryAudioSource, SetBufferWhilePlaying)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.set_buffer(nullptr);
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(TestMemoryAudioSource, SetBufferWhilePaused)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_buffer(nullptr);
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(TestMemoryAudioSource, SetTimePosWhileStopped)
{
  memory_audio_source as(&mBuffer);
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(TestMemoryAudioSource, SetTimePosWhilePlaying)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.set_sample_pos(3u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, SetTimePosWhilePaused)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(TestMemoryAudioSource, SetTimePosOverflow)
{
  memory_audio_source as(&mBuffer);
  as.set_sample_pos(6u);
  EXPECT_EQ(2u, as.get_sample_pos());
}



TEST_F(TestMemoryAudioSource, SetTimePosMicroseconds)
{
  memory_audio_source as(&mBuffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(0u, as.get_sample_pos());
  as.set_time_pos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.get_time_pos());
  EXPECT_EQ(3u, as.get_sample_pos());
  as.set_sample_pos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.get_time_pos());
  EXPECT_EQ(1u, as.get_sample_pos());
}



TEST_F(TestMemoryAudioSource, SetLooping)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TEST_F(TestMemoryAudioSource, StopWhileStopped)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestMemoryAudioSource, StopWhilePlaying)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestMemoryAudioSource, StopWhilePaused)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestMemoryAudioSource, PlayWhileStopped)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, PlayWhilePlaying)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, PlayWhilePaused)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, PauseWhileStopped)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.pause();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestMemoryAudioSource, PauseWhilePlaying)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(TestMemoryAudioSource, PauseWhilePaused)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(TestMemoryAudioSource, ReplayWhileStopped)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, ReplayWhilePlaying)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, ReplayWhilePaused)
{
  memory_audio_source as(&mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestMemoryAudioSource, PlayWithoutBuffer)
{
  memory_audio_source as;
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}

