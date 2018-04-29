// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_aud_base.hpp"

#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/audio_source.hpp"

#include "hou/cor/cor_error.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class TestAudioSource : public test_aud_base
{
public:
  TestAudioSource();

public:
  audio_buffer mBuffer;
};



class TestAudioSourceDeathTest : public TestAudioSource
{};



class ConcreteAudioSource : public audio_source
{
public:
  ConcreteAudioSource(const audio_buffer& buffer);
  ConcreteAudioSource(ConcreteAudioSource&& other);
  virtual ~ConcreteAudioSource();

  audio_buffer_format get_format() const final;
  uint get_channel_count() const final;
  uint get_bytes_per_sample() const final;
  uint get_sample_rate() const final;
  uint get_sample_count() const final;

  void set_looping(bool looping) final;
  bool is_looping() const final;

private:
  void on_set_sample_pos(uint value) final;
  uint on_get_sample_pos() const final;

private:
  uint m_sample_count;
  audio_buffer_format mAudioBufferFormat;
  int m_sample_rate;
};



TestAudioSource::TestAudioSource()
  : test_aud_base()
  , mBuffer(
      std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      audio_buffer_format::stereo16, 2)
{}



ConcreteAudioSource::ConcreteAudioSource(const audio_buffer& buffer)
  : audio_source()
  , m_sample_count(buffer.get_sample_count())
  , mAudioBufferFormat(buffer.get_format())
  , m_sample_rate(buffer.get_sample_rate())
{
  al::set_source_buffer(get_handle(), buffer.get_handle().get_name());
}



ConcreteAudioSource::ConcreteAudioSource(ConcreteAudioSource&& other)
  : audio_source(std::move(other))
  , m_sample_count(std::move(other.m_sample_count))
  , mAudioBufferFormat(std::move(other.mAudioBufferFormat))
  , m_sample_rate(std::move(other.m_sample_rate))
{}



ConcreteAudioSource::~ConcreteAudioSource()
{}



audio_buffer_format ConcreteAudioSource::get_format() const
{
  return mAudioBufferFormat;
}



uint ConcreteAudioSource::get_channel_count() const
{
  return get_audio_buffer_format_channel_count(mAudioBufferFormat);
}



uint ConcreteAudioSource::get_bytes_per_sample() const
{
  return get_audio_buffer_format_bytes_per_sample(mAudioBufferFormat);
}



uint ConcreteAudioSource::get_sample_rate() const
{
  return m_sample_rate;
}



uint ConcreteAudioSource::get_sample_count() const
{
  return m_sample_count;
}



void ConcreteAudioSource::set_looping(bool looping)
{
  audio_source::set_looping(looping);
}



bool ConcreteAudioSource::is_looping() const
{
  return audio_source::is_looping();
}



void ConcreteAudioSource::on_set_sample_pos(uint value)
{
  audio_source::on_set_sample_pos(value);
}



uint ConcreteAudioSource::on_get_sample_pos() const
{
  return audio_source::on_get_sample_pos();
}

}  // namespace



TEST_F(TestAudioSource, DefaultConstructor)
{
  ConcreteAudioSource as(mBuffer);
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



TEST_F(TestAudioSource, MoveConstructor)
{
  ConcreteAudioSource asDummy(mBuffer);
  ConcreteAudioSource as(std::move(asDummy));
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
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



TEST_F(TestAudioSource, SetTimePosWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(TestAudioSource, SetTimePosWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.set_sample_pos(3u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, SetTimePosWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(TestAudioSource, SetTimePosOverflow)
{
  ConcreteAudioSource as(mBuffer);
  as.set_sample_pos(6u);
  EXPECT_EQ(2u, as.get_sample_pos());
}



TEST_F(TestAudioSource, SetTimePosMicroseconds)
{
  ConcreteAudioSource as(mBuffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(0u, as.get_sample_pos());
  as.set_time_pos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.get_time_pos());
  EXPECT_EQ(3u, as.get_sample_pos());
  as.set_sample_pos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.get_time_pos());
  EXPECT_EQ(1u, as.get_sample_pos());
}



TEST_F(TestAudioSource, PosSeconds)
{
  ConcreteAudioSource as(mBuffer);
  as.set_time_pos(std::chrono::duration<double>(1.5f));
  EXPECT_EQ(std::chrono::duration<double>(1.5f), as.get_time_pos());
  EXPECT_EQ(3u, as.get_sample_pos());
}



TEST_F(TestAudioSource, Looping)
{
  ConcreteAudioSource as(mBuffer);
  EXPECT_FALSE(as.is_looping());
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TEST_F(TestAudioSource, StopWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestAudioSource, StopWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestAudioSource, StopWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestAudioSource, PlayWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, PlayWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, PlayWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, PauseWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.pause();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(TestAudioSource, PauseWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(TestAudioSource, PauseWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(TestAudioSource, ReplayWhileStopped)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, ReplayWhilePlaying)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, ReplayWhilePaused)
{
  ConcreteAudioSource as(mBuffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(TestAudioSource, Pitch)
{
  ConcreteAudioSource as(mBuffer);
  as.set_pitch(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_pitch());
}



TEST_F(TestAudioSource, Gain)
{
  ConcreteAudioSource as(mBuffer);
  as.set_gain(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_gain());
}



TEST_F(TestAudioSourceDeathTest, InvalidGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.set_gain(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, MaxGain)
{
  ConcreteAudioSource as(mBuffer);
  as.set_max_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.get_max_gain());
}



TEST_F(TestAudioSourceDeathTest, InvalidMaxGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.set_max_gain(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, MinGain)
{
  ConcreteAudioSource as(mBuffer);
  as.set_min_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.get_min_gain());
}



TEST_F(TestAudioSourceDeathTest, InvalidMinGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.set_min_gain(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, MaxDistance)
{
  ConcreteAudioSource as(mBuffer);
  as.set_max_distance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_max_distance());
}



TEST_F(TestAudioSourceDeathTest, InvalidMaxDistance)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(
    as.set_max_distance(-3.f), std::logic_error, get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, RolloffFactor)
{
  ConcreteAudioSource as(mBuffer);
  as.set_rolloff_factor(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_rolloff_factor());
}



TEST_F(TestAudioSourceDeathTest, InvalidRolloffFactor)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.set_rolloff_factor(-3.f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, ReferenceDistance)
{
  ConcreteAudioSource as(mBuffer);
  as.set_reference_distance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_reference_distance());
}



TEST_F(TestAudioSourceDeathTest, InvalidReferenceDistance)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.set_reference_distance(-3.f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, Relative)
{
  ConcreteAudioSource as(mBuffer);
  as.set_relative(true);
  EXPECT_TRUE(as.is_relative());
}



TEST_F(TestAudioSource, ConeOuterGain)
{
  ConcreteAudioSource as(mBuffer);
  as.set_cone_outer_gain(1.f);
  EXPECT_FLOAT_EQ(1.f, as.get_cone_outer_gain());
}



TEST_F(TestAudioSourceDeathTest, InvalidConeOuterGain)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.set_cone_outer_gain(-3.f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, ConeInnerAngle)
{
  ConcreteAudioSource as(mBuffer);
  as.set_cone_inner_angle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.get_cone_inner_angle());
  as.set_cone_inner_angle(pi_f);
  EXPECT_FLOAT_EQ(pi_f, as.get_cone_inner_angle());
  as.set_cone_inner_angle(2 * pi_f);
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
}



TEST_F(TestAudioSourceDeathTest, InvalidConeInnerAngle)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.set_cone_inner_angle(-pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(as.set_cone_inner_angle(3 * pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, ConeOuterAngle)
{
  ConcreteAudioSource as(mBuffer);
  as.set_cone_outer_angle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.get_cone_outer_angle());
  as.set_cone_outer_angle(pi_f);
  EXPECT_FLOAT_EQ(pi_f, as.get_cone_outer_angle());
  as.set_cone_outer_angle(2 * pi_f);
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
}



TEST_F(TestAudioSourceDeathTest, InvalidConeOuterAngle)
{
  ConcreteAudioSource as(mBuffer);
  HOU_EXPECT_ERROR(as.set_cone_outer_angle(-pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
  HOU_EXPECT_ERROR(as.set_cone_outer_angle(3 * pi_f), std::logic_error,
    get_text(cor_error::pre_condition));
}



TEST_F(TestAudioSource, Position)
{
  ConcreteAudioSource as(mBuffer);
  vec3f posRef(1.f, -2.f, 3.f);
  as.set_position(posRef);
  HOU_EXPECT_FLOAT_CLOSE(posRef, as.get_position());
}



TEST_F(TestAudioSource, Velocity)
{
  ConcreteAudioSource as(mBuffer);
  vec3f velRef(1.f, -2.f, 3.f);
  as.set_velocity(velRef);
  HOU_EXPECT_FLOAT_CLOSE(velRef, as.get_velocity());
}



TEST_F(TestAudioSource, Direction)
{
  ConcreteAudioSource as(mBuffer);
  vec3f dirRef(1.f, -2.f, 3.f);
  as.set_direction(dirRef);
  HOU_EXPECT_FLOAT_CLOSE(dirRef, as.get_direction());
}
