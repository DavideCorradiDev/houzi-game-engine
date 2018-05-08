// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/Test.hpp"
#include "hou/aud/test_aud_base.hpp"

#include "hou/aud/audio_buffer.hpp"
#include "hou/aud/audio_source.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;



namespace
{

class test_audio_source : public test_aud_base
{
public:
  test_audio_source();

public:
  audio_buffer m_buffer;
};



class test_audio_source_death_test : public test_audio_source
{};



class concrete_audio_source : public audio_source
{
public:
  concrete_audio_source(const audio_buffer& buffer);
  concrete_audio_source(concrete_audio_source&& other) noexcept;
  virtual ~concrete_audio_source();

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
  audio_buffer_format m_format;
  int m_sample_rate;
};



test_audio_source::test_audio_source()
  : test_aud_base()
  , m_buffer(
      std::vector<uint8_t>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      audio_buffer_format::stereo16, 2)
{}



concrete_audio_source::concrete_audio_source(const audio_buffer& buffer)
  : audio_source()
  , m_sample_count(buffer.get_sample_count())
  , m_format(buffer.get_format())
  , m_sample_rate(buffer.get_sample_rate())
{
  al::set_source_buffer(get_handle(), buffer.get_handle().get_name());
}



concrete_audio_source::concrete_audio_source(
  concrete_audio_source&& other) noexcept
  : audio_source(std::move(other))
  , m_sample_count(std::move(other.m_sample_count))
  , m_format(std::move(other.m_format))
  , m_sample_rate(std::move(other.m_sample_rate))
{}



concrete_audio_source::~concrete_audio_source()
{}



audio_buffer_format concrete_audio_source::get_format() const
{
  return m_format;
}



uint concrete_audio_source::get_channel_count() const
{
  return get_audio_buffer_format_channel_count(m_format);
}



uint concrete_audio_source::get_bytes_per_sample() const
{
  return get_audio_buffer_format_bytes_per_sample(m_format);
}



uint concrete_audio_source::get_sample_rate() const
{
  return m_sample_rate;
}



uint concrete_audio_source::get_sample_count() const
{
  return m_sample_count;
}



void concrete_audio_source::set_looping(bool looping)
{
  audio_source::set_looping(looping);
}



bool concrete_audio_source::is_looping() const
{
  return audio_source::is_looping();
}



void concrete_audio_source::on_set_sample_pos(uint value)
{
  audio_source::on_set_sample_pos(value);
}



uint concrete_audio_source::on_get_sample_pos() const
{
  return audio_source::on_get_sample_pos();
}

}  // namespace



TEST_F(test_audio_source, default_constructor)
{
  concrete_audio_source as(m_buffer);
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
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(test_audio_source, move_constructor)
{
  concrete_audio_source as_dummy(m_buffer);
  concrete_audio_source as(std::move(as_dummy));
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
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
}



TEST_F(test_audio_source, set_time_pos_while_stopped)
{
  concrete_audio_source as(m_buffer);
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
}



TEST_F(test_audio_source, set_time_pos_while_playing)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.set_sample_pos(3u);
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, set_time_pos_while_paused)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.set_sample_pos(3u);
  EXPECT_EQ(3u, as.get_sample_pos());
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_audio_source, set_time_pos_overflow)
{
  concrete_audio_source as(m_buffer);
  as.set_sample_pos(6u);
  EXPECT_EQ(2u, as.get_sample_pos());
}



TEST_F(test_audio_source, set_time_pos_microseconds)
{
  concrete_audio_source as(m_buffer);
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(0u, as.get_sample_pos());
  as.set_time_pos(std::chrono::microseconds(1500000));
  EXPECT_EQ(std::chrono::microseconds(1500000), as.get_time_pos());
  EXPECT_EQ(3u, as.get_sample_pos());
  as.set_sample_pos(1u);
  EXPECT_EQ(std::chrono::microseconds(500000), as.get_time_pos());
  EXPECT_EQ(1u, as.get_sample_pos());
}



TEST_F(test_audio_source, pos_seconds)
{
  concrete_audio_source as(m_buffer);
  as.set_time_pos(std::chrono::duration<double>(1.5f));
  EXPECT_EQ(std::chrono::duration<double>(1.5f), as.get_time_pos());
  EXPECT_EQ(3u, as.get_sample_pos());
}



TEST_F(test_audio_source, looping)
{
  concrete_audio_source as(m_buffer);
  EXPECT_FALSE(as.is_looping());
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TEST_F(test_audio_source, stop_while_stopped)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_audio_source, stop_while_playing)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_audio_source, stop_while_paused)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.play();
  as.pause();
  as.stop();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_audio_source, play_while_stopped)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, play_while_playing)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, play_while_paused)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, pause_while_stopped)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.set_sample_pos(3u);
  as.pause();
  EXPECT_EQ(audio_source_state::stopped, as.get_state());
  EXPECT_EQ(0u, as.get_sample_pos());
}



TEST_F(test_audio_source, pause_while_playing)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_audio_source, pause_while_paused)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_EQ(audio_source_state::paused, as.get_state());
}



TEST_F(test_audio_source, replay_while_stopped)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, replay_while_playing)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, replay_while_paused)
{
  concrete_audio_source as(m_buffer);
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_EQ(audio_source_state::playing, as.get_state());
}



TEST_F(test_audio_source, pitch)
{
  concrete_audio_source as(m_buffer);
  as.set_pitch(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_pitch());
}



TEST_F(test_audio_source, gain)
{
  concrete_audio_source as(m_buffer);
  as.set_gain(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_gain());
}



TEST_F(test_audio_source_death_test, invalid_gain)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_gain(-3.f));
}



TEST_F(test_audio_source, max_gain)
{
  concrete_audio_source as(m_buffer);
  as.set_max_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.get_max_gain());
}



TEST_F(test_audio_source_death_test, invalid_max_gain)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_max_gain(-3.f));
}



TEST_F(test_audio_source, min_gain)
{
  concrete_audio_source as(m_buffer);
  as.set_min_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.get_min_gain());
}



TEST_F(test_audio_source_death_test, invalid_min_gain)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_min_gain(-3.f));
}



TEST_F(test_audio_source, max_distance)
{
  concrete_audio_source as(m_buffer);
  as.set_max_distance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_max_distance());
}



TEST_F(test_audio_source_death_test, invalid_max_distance)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_max_distance(-3.f));
}



TEST_F(test_audio_source, rolloff_factor)
{
  concrete_audio_source as(m_buffer);
  as.set_rolloff_factor(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_rolloff_factor());
}



TEST_F(test_audio_source_death_test, invalid_rolloff_factor)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_rolloff_factor(-3.f));
}



TEST_F(test_audio_source, reference_distance)
{
  concrete_audio_source as(m_buffer);
  as.set_reference_distance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_reference_distance());
}



TEST_F(test_audio_source_death_test, invalid_reference_distance)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_reference_distance(-3.f));
}



TEST_F(test_audio_source, relative)
{
  concrete_audio_source as(m_buffer);
  as.set_relative(true);
  EXPECT_TRUE(as.is_relative());
}



TEST_F(test_audio_source, cone_outer_gain)
{
  concrete_audio_source as(m_buffer);
  as.set_cone_outer_gain(1.f);
  EXPECT_FLOAT_EQ(1.f, as.get_cone_outer_gain());
}



TEST_F(test_audio_source_death_test, invalid_cone_outer_gain)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_cone_outer_gain(-3.f));
}



TEST_F(test_audio_source, cone_inner_angle)
{
  concrete_audio_source as(m_buffer);
  as.set_cone_inner_angle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.get_cone_inner_angle());
  as.set_cone_inner_angle(pi_f);
  EXPECT_FLOAT_EQ(pi_f, as.get_cone_inner_angle());
  as.set_cone_inner_angle(2 * pi_f);
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_inner_angle());
}



TEST_F(test_audio_source_death_test, invalid_cone_inner_angle)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_cone_inner_angle(-pi_f));
  EXPECT_PRECOND_ERROR(as.set_cone_inner_angle(3 * pi_f));
}



TEST_F(test_audio_source, cone_outer_angle)
{
  concrete_audio_source as(m_buffer);
  as.set_cone_outer_angle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.get_cone_outer_angle());
  as.set_cone_outer_angle(pi_f);
  EXPECT_FLOAT_EQ(pi_f, as.get_cone_outer_angle());
  as.set_cone_outer_angle(2 * pi_f);
  EXPECT_FLOAT_EQ(2 * pi_f, as.get_cone_outer_angle());
}



TEST_F(test_audio_source_death_test, invalid_cone_outer_angle)
{
  concrete_audio_source as(m_buffer);
  EXPECT_PRECOND_ERROR(as.set_cone_outer_angle(-pi_f));
  EXPECT_PRECOND_ERROR(as.set_cone_outer_angle(3 * pi_f));
}



TEST_F(test_audio_source, position)
{
  concrete_audio_source as(m_buffer);
  vec3f pos_ref(1.f, -2.f, 3.f);
  as.set_position(pos_ref);
  EXPECT_FLOAT_CLOSE(pos_ref, as.get_position());
}



TEST_F(test_audio_source, velocity)
{
  concrete_audio_source as(m_buffer);
  vec3f vel_ref(1.f, -2.f, 3.f);
  as.set_velocity(vel_ref);
  EXPECT_FLOAT_CLOSE(vel_ref, as.get_velocity());
}



TEST_F(test_audio_source, direction)
{
  concrete_audio_source as(m_buffer);
  vec3f dir_ref(1.f, -2.f, 3.f);
  as.set_direction(dir_ref);
  EXPECT_FLOAT_CLOSE(dir_ref, as.get_direction());
}
