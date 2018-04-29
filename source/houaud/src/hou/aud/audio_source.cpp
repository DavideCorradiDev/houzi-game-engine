// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_source.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"

#include "hou/mth/math_functions.hpp"



namespace hou
{

namespace
{

audio_source_state alSourceStateToAudioSourceState(ALenum state);
uint normalize(uint value, uint max);

audio_source_state alSourceStateToAudioSourceState(ALenum state)
{
  switch(state)
  {
  case AL_PLAYING:
    return audio_source_state::playing;
  case AL_PAUSED:
    return audio_source_state::paused;
  case AL_INITIAL:
  case AL_STOPPED:
    return audio_source_state::stopped;
  default:
    HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(state));
    return audio_source_state::stopped;
  }
}



uint normalize(uint value, uint max)
{
  return max == 0u ? 0u : value % max;
}

}  // namespace



audio_source::audio_source()
  : non_copyable()
  , m_handle(al::source_handle::generate())
  , m_requested_sample_pos(0u)
{}



audio_source::audio_source(audio_source&& other)
  : m_handle(std::move(other.m_handle))
  , m_requested_sample_pos(std::move(other.m_requested_sample_pos))
{}



audio_source::~audio_source()
{}



const al::source_handle& audio_source::get_handle() const
{
  return m_handle;
}



void audio_source::play()
{
  if(get_state() != audio_source_state::playing)
  {
    al::stop_source(m_handle);
    on_set_sample_pos(m_requested_sample_pos);
    al::play_source(m_handle);
    // The requested pos has to be set to 0 in case playback ends on its own.
    m_requested_sample_pos = 0u;
  }
}



void audio_source::pause()
{
  if(get_state() != audio_source_state::paused)
  {
    al::pause_source(m_handle);
    // The requested pos is updated. Another call to play will resume from
    // the current pos.
    m_requested_sample_pos = on_get_sample_pos();
  }
}



void audio_source::stop()
{
  if(get_state() != audio_source_state::stopped)
  {
    al::stop_source(m_handle);
  }
  // Stopping resets the pos to 0.
  m_requested_sample_pos = 0u;
}



void audio_source::replay()
{
  stop();
  play();
}



audio_source_state audio_source::get_state() const
{
  return alSourceStateToAudioSourceState(al::get_source_state(m_handle));
}



void audio_source::set_time_pos(std::chrono::nanoseconds nsPos)
{
  set_sample_pos(static_cast<int64_t>(nsPos.count())
    * static_cast<int64_t>(get_sample_rate()) / 1000000000);
}



std::chrono::nanoseconds audio_source::get_time_pos() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(get_sample_pos())
    * 1000000000 / static_cast<int64_t>(get_sample_rate()));
}



std::chrono::nanoseconds audio_source::get_duration() const
{
  return std::chrono::nanoseconds(static_cast<int64_t>(get_sample_count())
    * 1000000000 / static_cast<int64_t>(get_sample_rate()));
}



void audio_source::set_sample_pos(uint pos)
{
  if(get_state() == audio_source_state::playing)
  {
    on_set_sample_pos(normalize(pos, get_sample_count()));
  }
  else
  {
    m_requested_sample_pos = normalize(pos, get_sample_count());
  }
}



uint audio_source::get_sample_pos() const
{
  if(get_state() == audio_source_state::playing)
  {
    return on_get_sample_pos();
  }
  else
  {
    return m_requested_sample_pos;
  }
}



void audio_source::set_looping(bool looping)
{
  al::set_source_looping(m_handle, static_cast<ALboolean>(looping));
}



bool audio_source::is_looping() const
{
  return static_cast<bool>(al::get_source_looping(m_handle));
}



void audio_source::set_pitch(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_pitch(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_pitch() const
{
  return static_cast<float>(al::get_source_pitch(m_handle));
}



void audio_source::set_gain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_gain(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_gain() const
{
  return static_cast<float>(al::get_source_gain(m_handle));
}



void audio_source::set_max_gain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_max_gain(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_max_gain() const
{
  return static_cast<float>(al::get_source_max_gain(m_handle));
}



void audio_source::set_min_gain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_min_gain(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_min_gain() const
{
  return static_cast<float>(al::get_source_min_gain(m_handle));
}



void audio_source::set_max_distance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_max_distance(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_max_distance() const
{
  return static_cast<float>(al::get_source_max_distance(m_handle));
}



void audio_source::set_rolloff_factor(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_rolloff_factor(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_rolloff_factor() const
{
  return static_cast<float>(al::get_source_rolloff_factor(m_handle));
}



void audio_source::set_reference_distance(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_reference_distance(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_reference_distance() const
{
  return static_cast<float>(al::get_source_reference_distance(m_handle));
}



void audio_source::set_relative(bool value)
{
  al::set_source_relative(m_handle, static_cast<ALfloat>(value));
}



bool audio_source::is_relative() const
{
  return static_cast<bool>(al::get_source_relative(m_handle));
}



void audio_source::set_cone_outer_gain(float value)
{
  HOU_EXPECT(value >= 0.f);
  al::set_source_cone_outer_gain(m_handle, static_cast<ALfloat>(value));
}



float audio_source::get_cone_outer_gain() const
{
  return static_cast<float>(al::get_source_cone_outer_gain(m_handle));
}



void audio_source::set_cone_inner_angle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * pi_f);
  al::set_source_cone_inner_angle(m_handle, static_cast<ALfloat>(rad_to_deg(value)));
}



float audio_source::get_cone_inner_angle() const
{
  return deg_to_rad(static_cast<float>(al::get_source_cone_inner_angle(m_handle)));
}



void audio_source::set_cone_outer_angle(float value)
{
  HOU_EXPECT(value >= 0.f && value <= 2.f * pi_f);
  al::set_source_cone_outer_angle(m_handle, static_cast<ALfloat>(rad_to_deg(value)));
}



float audio_source::get_cone_outer_angle() const
{
  return deg_to_rad(static_cast<float>(al::getSourceConeOuterAngle(m_handle)));
}



void audio_source::set_position(const vec3f& pos)
{
  al::set_source_position(m_handle, static_cast<const ALfloat*>(pos.data()));
}



vec3f audio_source::get_position() const
{
  vec3f retval;
  al::get_source_position(
    m_handle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void audio_source::set_velocity(const vec3f& vel)
{
  al::set_source_velocity(m_handle, static_cast<const ALfloat*>(vel.data()));
}



vec3f audio_source::get_velocity() const
{
  vec3f retval;
  al::get_source_velocity(
    m_handle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void audio_source::set_direction(const vec3f& dir)
{
  al::set_source_direction(m_handle, static_cast<const ALfloat*>(dir.data()));
}



vec3f audio_source::get_direction() const
{
  vec3f retval;
  al::get_source_direction(
    m_handle, static_cast<ALfloat*>(const_cast<float*>(retval.data())));
  return retval;
}



void audio_source::on_set_sample_pos(uint pos)
{
  al::set_source_sample_offset(m_handle, static_cast<ALint>(pos));
}



uint audio_source::on_get_sample_pos() const
{
  return static_cast<uint>(al::get_source_sample_offset(m_handle));
}

}  // namespace hou
