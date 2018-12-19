// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/test_aud_base.hpp"
#include "hou/aud/test_data.hpp"
#include "hou/test.hpp"

#include "hou/aud/audio_source.hpp"
#include "hou/aud/automatic_stream_audio_source.hpp"
#include "hou/aud/buffer_audio_source.hpp"
#include "hou/aud/manual_stream_audio_source.hpp"
#include "hou/aud/listener.hpp"
#include "hou/aud/ogg_file_in.hpp"
#include "hou/aud/wav_file_in.hpp"

#include "hou/mth/math_functions.hpp"

using namespace hou;
using namespace testing;



namespace
{

template <typename AudioSourceType>
class test_audio_source : public test_aud_base
{
public:
  static void SetUpTestCase();

public:
  test_audio_source();

  audio_source& get_audio_source();
  void unload_audio();
  void load_wav(const std::string& filename);

private:
  AudioSourceType& get_original_audio_source();

private:
  std::unique_ptr<audio_source> m_as;
};



template <typename AudioSourceType>
void test_audio_source<AudioSourceType>::SetUpTestCase()
{
  test_aud_base::SetUpTestCase();
  listener::set_gain(0.f);
}




template <>
test_audio_source<buffer_audio_source>::test_audio_source()
  : test_aud_base()
  , m_as(std::make_unique<buffer_audio_source>(
      std::make_shared<audio_buffer>(ogg_file_in(get_stereo16_ogg_filename()))))
{}



template <>
test_audio_source<manual_stream_audio_source>::test_audio_source()
  : test_aud_base()
  , m_as(std::make_unique<manual_stream_audio_source>(
      std::make_unique<ogg_file_in>(get_stereo16_ogg_filename())))
{}



template <>
test_audio_source<automatic_stream_audio_source>::test_audio_source()
  : test_aud_base()
  , m_as(std::make_unique<automatic_stream_audio_source>(
      std::make_unique<ogg_file_in>(get_stereo16_ogg_filename())))
{}



template <typename AudioSourceType>
audio_source& test_audio_source<AudioSourceType>::get_audio_source()
{
  HOU_ASSERT(m_as != nullptr);
  return *m_as;
}



template <typename AudioSourceType>
AudioSourceType& test_audio_source<AudioSourceType>::get_original_audio_source()
{
  return dynamic_cast<AudioSourceType&>(get_audio_source());
}



template <>
void test_audio_source<buffer_audio_source>::unload_audio()
{
  get_original_audio_source().set_buffer(nullptr);
}



template <>
void test_audio_source<manual_stream_audio_source>::unload_audio()
{
  get_original_audio_source().set_stream(nullptr);
}



template <>
void test_audio_source<automatic_stream_audio_source>::unload_audio()
{
  get_original_audio_source().set_stream(nullptr);
}



template <>
void test_audio_source<buffer_audio_source>::load_wav(
  const std::string& filename)
{
  get_original_audio_source().set_buffer(
    std::make_shared<audio_buffer>(wav_file_in(filename)));
}



template <>
void test_audio_source<manual_stream_audio_source>::load_wav(
  const std::string& filename)
{
  get_original_audio_source().set_stream(
    std::make_unique<wav_file_in>(filename));
}



template <>
void test_audio_source<automatic_stream_audio_source>::load_wav(
  const std::string& filename)
{
  get_original_audio_source().set_stream(
    std::make_unique<wav_file_in>(filename));
}



using audio_source_types = Types<buffer_audio_source,
  automatic_stream_audio_source, manual_stream_audio_source>;
TYPED_TEST_CASE(test_audio_source, audio_source_types);



TYPED_TEST(test_audio_source, set_sample_pos_while_paused)
{
  auto& as = this->get_audio_source();
  EXPECT_EQ(0, as.get_sample_pos());
  as.set_sample_pos(100);
  EXPECT_EQ(100, as.get_sample_pos());
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_audio_source, set_sample_pos_while_playing)
{
  auto& as = this->get_audio_source();
  EXPECT_EQ(0, as.get_sample_pos());
  as.play();
  as.set_sample_pos(100);
  EXPECT_GE(100, as.get_sample_pos());
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, set_sample_pos_underflow_not_looping_while_paused)
{
  auto& as = this->get_audio_source();
  as.set_sample_pos(-1u);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_sample_pos_underflow_looping_while_paused)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(-3);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(as.get_sample_count() - 3, as.get_sample_pos());
}




TYPED_TEST(test_audio_source, set_sample_pos_overflow_not_looping_while_paused)
{
  auto& as = this->get_audio_source();
  as.set_sample_pos(as.get_sample_count() + 1);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_sample_pos_overflow_looping_while_paused)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(as.get_sample_count() + 3);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(3, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_sample_pos_underflow_not_looping_while_playing)
{
  auto& as = this->get_audio_source();
  as.play();
  as.set_sample_pos(-1u);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_sample_pos_underflow_looping_while_playing)
{
  auto& as = this->get_audio_source();
  as.play();
  as.set_looping(true);
  as.set_sample_pos(-3);
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, set_sample_pos_overflow_not_looping_while_playing)
{
  auto& as = this->get_audio_source();
  as.play();
  as.set_sample_pos(as.get_sample_count() + 1);
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_sample_pos_overflow_looping_while_playing)
{
  auto& as = this->get_audio_source();
  as.play();
  as.set_looping(true);
  as.set_sample_pos(as.get_sample_count() + 3);
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, set_time_pos_nanoseconds)
{
  auto& as = this->get_audio_source();
  EXPECT_EQ(std::chrono::nanoseconds(0), as.get_time_pos());
  EXPECT_EQ(0, as.get_sample_pos());
  as.set_time_pos(std::chrono::nanoseconds(30000000));
  EXPECT_EQ(std::chrono::nanoseconds(30000000), as.get_time_pos());
  EXPECT_EQ(1323, as.get_sample_pos());
  as.set_sample_pos(11025);
  EXPECT_EQ(std::chrono::nanoseconds(250000000), as.get_time_pos());
  EXPECT_EQ(11025, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_time_pos_microseconds)
{
  auto& as = this->get_audio_source();
  EXPECT_EQ(std::chrono::microseconds(0), as.get_time_pos());
  EXPECT_EQ(0, as.get_sample_pos());
  as.set_time_pos(std::chrono::microseconds(30000));
  EXPECT_EQ(std::chrono::microseconds(30000), as.get_time_pos());
  EXPECT_EQ(1323, as.get_sample_pos());
  as.set_sample_pos(11025);
  EXPECT_EQ(std::chrono::microseconds(250000), as.get_time_pos());
  EXPECT_EQ(11025, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_time_pos_milliseconds)
{
  auto& as = this->get_audio_source();
  EXPECT_EQ(std::chrono::milliseconds(0), as.get_time_pos());
  EXPECT_EQ(0, as.get_sample_pos());
  as.set_time_pos(std::chrono::milliseconds(30));
  EXPECT_EQ(std::chrono::milliseconds(30), as.get_time_pos());
  EXPECT_EQ(1323, as.get_sample_pos());
  as.set_sample_pos(11025);
  EXPECT_EQ(std::chrono::milliseconds(250), as.get_time_pos());
  EXPECT_EQ(11025, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, set_time_pos_float_seconds)
{
  auto& as = this->get_audio_source();
  EXPECT_EQ(std::chrono::duration<double>(0.), as.get_time_pos());
  EXPECT_EQ(0, as.get_sample_pos());
  as.set_time_pos(std::chrono::duration<double>(0.03));
  EXPECT_EQ(std::chrono::duration<double>(0.03), as.get_time_pos());
  EXPECT_EQ(1323, as.get_sample_pos());
  as.set_sample_pos(11025);
  EXPECT_EQ(std::chrono::duration<double>(0.25), as.get_time_pos());
  EXPECT_EQ(11025, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, looping)
{
  auto& as = this->get_audio_source();
  EXPECT_FALSE(as.is_looping());
  as.set_looping(true);
  EXPECT_TRUE(as.is_looping());
  as.set_looping(false);
  EXPECT_FALSE(as.is_looping());
}



TYPED_TEST(test_audio_source, play_at_initial_state)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, play_after_play)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.play();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, play_after_pause)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.pause();
  as.play();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, play_after_stop)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.stop();
  as.play();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, pause_at_initial_state)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(3);
  as.pause();
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(3, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, pause_after_play)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.pause();
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_audio_source, pause_after_pause)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.pause();
  as.pause();
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_audio_source, pause_after_stop)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.pause();
  as.stop();
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_audio_source, replay_at_initial_state)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.replay();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, replay_after_play)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.replay();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, replay_after_pause)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.pause();
  as.replay();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, replay_after_stop)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.play();
  as.stop();
  as.replay();
  EXPECT_TRUE(as.is_playing());
}



TYPED_TEST(test_audio_source, stop_at_initial_state)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(3);
  as.stop();
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, stop_after_play)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(3);
  as.play();
  as.stop();
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, stop_after_pause)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(3);
  as.play();
  as.pause();
  as.stop();
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, stop_after_stop)
{
  auto& as = this->get_audio_source();
  as.set_looping(true);
  as.set_sample_pos(3);
  as.play();
  as.stop();
  as.stop();
  EXPECT_FALSE(as.is_playing());
  EXPECT_EQ(0, as.get_sample_pos());
}



TYPED_TEST(test_audio_source, play_while_invalid_not_looping)
{
  auto& as = this->get_audio_source();
  this->unload_audio();
  EXPECT_FALSE(as.is_valid());
  as.play();
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_audio_source, play_while_invalid_looping)
{
  auto& as = this->get_audio_source();
  this->unload_audio();
  EXPECT_FALSE(as.is_valid());
  as.set_looping(true);
  as.play();
  EXPECT_FALSE(as.is_playing());
}



TYPED_TEST(test_audio_source, buffer_properties_mono8)
{
  auto& as = this->get_audio_source();
  this->load_wav(get_mono8_wav_filename());
  EXPECT_TRUE(as.is_valid());
  EXPECT_EQ(audio_buffer_format::mono8, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
  EXPECT_EQ(44100u, as.get_sample_rate());
  EXPECT_EQ(21231u, as.get_sample_count());
  EXPECT_EQ(std::chrono::nanoseconds(481428571), as.get_duration());
}



TYPED_TEST(test_audio_source, buffer_properties_mono16)
{
  auto& as = this->get_audio_source();
  this->load_wav(get_mono16_wav_filename());
  EXPECT_TRUE(as.is_valid());
  EXPECT_EQ(audio_buffer_format::mono16, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
  EXPECT_EQ(44100u, as.get_sample_rate());
  EXPECT_EQ(21231u, as.get_sample_count());
  EXPECT_EQ(std::chrono::nanoseconds(481428571), as.get_duration());
}



TYPED_TEST(test_audio_source, buffer_properties_stereo8)
{
  auto& as = this->get_audio_source();
  this->load_wav(get_stereo8_wav_filename());
  EXPECT_TRUE(as.is_valid());
  EXPECT_EQ(audio_buffer_format::stereo8, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
  EXPECT_EQ(44100u, as.get_sample_rate());
  EXPECT_EQ(21231u, as.get_sample_count());
  EXPECT_EQ(std::chrono::nanoseconds(481428571), as.get_duration());
}



TYPED_TEST(test_audio_source, buffer_properties_stereo16)
{
  auto& as = this->get_audio_source();
  this->load_wav(get_stereo16_wav_filename());
  EXPECT_TRUE(as.is_valid());
  EXPECT_EQ(audio_buffer_format::stereo16, as.get_format());
  EXPECT_EQ(2u, as.get_channel_count());
  EXPECT_EQ(2u, as.get_bytes_per_sample());
  EXPECT_EQ(44100u, as.get_sample_rate());
  EXPECT_EQ(21231u, as.get_sample_count());
  EXPECT_EQ(std::chrono::nanoseconds(481428571), as.get_duration());
}



TYPED_TEST(test_audio_source, buffer_properties_invalid)
{
  auto& as = this->get_audio_source();
  this->unload_audio();
  EXPECT_FALSE(as.is_valid());
  EXPECT_EQ(audio_buffer_format::mono8, as.get_format());
  EXPECT_EQ(1u, as.get_channel_count());
  EXPECT_EQ(1u, as.get_bytes_per_sample());
  EXPECT_EQ(1u, as.get_sample_rate());
  EXPECT_EQ(0u, as.get_sample_count());
  EXPECT_EQ(std::chrono::nanoseconds(0), as.get_duration());
}



TYPED_TEST(test_audio_source, pitch)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(1.f, as.get_pitch());
  as.set_pitch(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_pitch());
}



TYPED_TEST(test_audio_source, gain)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(1.f, as.get_gain());
  as.set_gain(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_gain());
}



TYPED_TEST(test_audio_source, invalid_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_gain(-3.f));
}



TYPED_TEST(test_audio_source, max_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(1.f, as.get_max_gain());
  as.set_max_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.get_max_gain());
}



TYPED_TEST(test_audio_source, invalid_max_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_max_gain(-3.f));
}



TYPED_TEST(test_audio_source, min_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(0.f, as.get_min_gain());
  as.set_min_gain(0.5f);
  EXPECT_FLOAT_EQ(0.5f, as.get_min_gain());
}



TYPED_TEST(test_audio_source, invalid_min_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_min_gain(-3.f));
}



TYPED_TEST(test_audio_source, max_distance)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(std::numeric_limits<float>::max(), as.get_max_distance());
  as.set_max_distance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_max_distance());
}



TYPED_TEST(test_audio_source, invalid_max_distance)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_max_distance(-3.f));
}



TYPED_TEST(test_audio_source, rolloff_factor)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(1.f, as.get_rolloff_factor());
  as.set_rolloff_factor(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_rolloff_factor());
}



TYPED_TEST(test_audio_source, invalid_rolloff_factor)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_rolloff_factor(-3.f));
}



TYPED_TEST(test_audio_source, reference_distance)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(1.f, as.get_reference_distance());
  as.set_reference_distance(3.f);
  EXPECT_FLOAT_EQ(3.f, as.get_reference_distance());
}



TYPED_TEST(test_audio_source, invalid_reference_distance)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_reference_distance(-3.f));
}



TYPED_TEST(test_audio_source, relative)
{
  auto& as = this->get_audio_source();
  EXPECT_FALSE(as.is_relative());
  as.set_relative(true);
  EXPECT_TRUE(as.is_relative());
}



TYPED_TEST(test_audio_source, cone_outer_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(0.f, as.get_cone_outer_gain());
  as.set_cone_outer_gain(1.f);
  EXPECT_FLOAT_EQ(1.f, as.get_cone_outer_gain());
}



TYPED_TEST(test_audio_source, invalid_cone_outer_gain)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_cone_outer_gain(-3.f));
}



TYPED_TEST(test_audio_source, cone_inner_angle)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_inner_angle());
  as.set_cone_inner_angle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.get_cone_inner_angle());
  as.set_cone_inner_angle(pi<float>());
  EXPECT_FLOAT_EQ(pi<float>(), as.get_cone_inner_angle());
  as.set_cone_inner_angle(2 * pi<float>());
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_inner_angle());
}



TYPED_TEST(test_audio_source, invalid_cone_inner_angle)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_cone_inner_angle(-pi<float>()));
  EXPECT_PRECOND_ERROR(as.set_cone_inner_angle(3 * pi<float>()));
}



TYPED_TEST(test_audio_source, cone_outer_angle)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_outer_angle());
  as.set_cone_outer_angle(0.f);
  EXPECT_FLOAT_EQ(0.f, as.get_cone_outer_angle());
  as.set_cone_outer_angle(pi<float>());
  EXPECT_FLOAT_EQ(pi<float>(), as.get_cone_outer_angle());
  as.set_cone_outer_angle(2 * pi<float>());
  EXPECT_FLOAT_EQ(2 * pi<float>(), as.get_cone_outer_angle());
}



TYPED_TEST(test_audio_source, invalid_cone_outer_angle)
{
  auto& as = this->get_audio_source();
  EXPECT_PRECOND_ERROR(as.set_cone_outer_angle(-pi<float>()));
  EXPECT_PRECOND_ERROR(as.set_cone_outer_angle(3 * pi<float>()));
}



TYPED_TEST(test_audio_source, position)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_position());
  vec3f pos_ref(1.f, -2.f, 3.f);
  as.set_position(pos_ref);
  EXPECT_FLOAT_CLOSE(pos_ref, as.get_position());
}



TYPED_TEST(test_audio_source, velocity)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_velocity());
  vec3f vel_ref(1.f, -2.f, 3.f);
  as.set_velocity(vel_ref);
  EXPECT_FLOAT_CLOSE(vel_ref, as.get_velocity());
}



TYPED_TEST(test_audio_source, direction)
{
  auto& as = this->get_audio_source();
  EXPECT_FLOAT_CLOSE(vec3f::zero(), as.get_direction());
  vec3f dir_ref(1.f, -2.f, 3.f);
  as.set_direction(dir_ref);
  EXPECT_FLOAT_CLOSE(dir_ref, as.get_direction());
}

}
