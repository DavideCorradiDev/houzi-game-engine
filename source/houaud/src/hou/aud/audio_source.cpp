// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_source.hpp"

#include "hou/cor/assertions.hpp"
#include "hou/cor/cor_exceptions.hpp"
#include "hou/cor/narrow_cast.hpp"

#include "hou/mth/math_functions.hpp"



namespace hou
{

namespace
{

audio_source::sample_position normalize(audio_source::sample_position value,
  audio_source::sample_position max) noexcept;

audio_source::sample_position normalize(audio_source::sample_position value,
  audio_source::sample_position max) noexcept
{
  if(max == 0)
  {
    return 0;
  }

  while(value < 0)
  {
    value += max;
  }
  return value % max;
}

}  // namespace



audio_source::audio_source()
  : non_copyable()
  , m_handle(al::source_handle::generate())
  , m_requested_sample_pos(0)
{}



audio_source::~audio_source()
{}



const al::source_handle& audio_source::get_handle() const noexcept
{
  return m_handle;
}



void audio_source::play()
{
  if(!is_playing())
  {
    on_play();
    // The actual sample pos is updated to the requested sample position.
    on_set_sample_pos(m_requested_sample_pos);
    // The requested pos has to be set to 0 in case playback ends on its own.
    m_requested_sample_pos = 0;
    al::play_source(m_handle);
  }
}



void audio_source::pause()
{
  if(is_playing())
  {
    on_pause();
    // pause() is called instead of stop() order not to reset the sample
    // position. The current pos is saved to resume playing from the same point.
    al::pause_source(m_handle);
    m_requested_sample_pos = on_get_sample_pos();
    // The source is actually stopped to reduce the number of different states
    // to be managed.
    al::stop_source(m_handle);
  }
}



void audio_source::stop()
{
  on_pause();
  al::stop_source(m_handle);
  // The requested pos is reset to the beginning.
  m_requested_sample_pos = 0;
}



void audio_source::replay()
{
  stop();
  play();
}



bool audio_source::is_playing() const
{
  return al::get_source_state(m_handle) == AL_PLAYING;
}



audio_buffer_format audio_source::get_format() const
{
  return has_audio() ? get_format_internal() : audio_buffer_format::mono8;
}



uint audio_source::get_channel_count() const
{
  return has_audio() ? get_channel_count_internal() : 1;
}



uint audio_source::get_bytes_per_sample() const
{
  return has_audio() ? get_bytes_per_sample_internal() : 1;
}



uint audio_source::get_sample_rate() const
{
  return has_audio() ? get_sample_rate_internal() : 1;
}



void audio_source::set_time_pos(std::chrono::nanoseconds nsPos)
{
  using rep = std::chrono::nanoseconds::rep;
  set_sample_pos(narrow_cast<sample_position>(static_cast<rep>(nsPos.count())
    * static_cast<rep>(get_sample_rate()) / 1000000000));
}



std::chrono::nanoseconds audio_source::get_time_pos() const
{
  using rep = std::chrono::nanoseconds::rep;
  return std::chrono::nanoseconds(static_cast<rep>(get_sample_pos())
    * 1000000000 / static_cast<rep>(get_sample_rate()));
}



std::chrono::nanoseconds audio_source::get_duration() const
{
  using rep = std::chrono::nanoseconds::rep;
  return std::chrono::nanoseconds(static_cast<rep>(get_sample_count())
    * 1000000000 / static_cast<rep>(get_sample_rate()));
}



void audio_source::set_sample_pos(sample_position pos)
{
  uint sample_count = get_sample_count();

  if((pos < 0 || pos >= sample_count) && !is_looping())
  {
    stop();
    return;
  }

  pos = normalize(pos, sample_count);
  if(is_playing())
  {
    // In order to ensure correct behavior in derived classes, before changing
    // the the sample position the audio source must be stopped and playback
    // resumed afterwards.
    al::stop_source(get_handle());
    on_set_sample_pos(pos);
    al::play_source(get_handle());
  }
  else
  {
    m_requested_sample_pos = pos;
  }
}



audio_source::sample_position audio_source::get_sample_pos() const
{
  if(is_playing())
  {
    return on_get_sample_pos();
  }
  else
  {
    return m_requested_sample_pos;
  }
}



uint audio_source::get_sample_count() const
{
  return has_audio() ? get_sample_count_internal() : 0u;
}



void audio_source::set_looping(bool looping)
{
  // If the looping state is not really changing, do nothing.
  if(looping == is_looping())
  {
    return;
  }

  if(is_playing())
  {
    // In order to ensure correct behavior in derived classes, before changing
    // the looping state the playback should be paused, and then resumed.
    pause();
    on_set_looping(looping);
    play();
  }
  else
  {
    on_set_looping(looping);
  }
}



bool audio_source::is_looping() const
{
  return static_cast<bool>(al::get_source_looping(m_handle));
}



void audio_source::set_pitch(non_negative<float> value)
{
  al::set_source_pitch(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_pitch() const
{
  return static_cast<float>(al::get_source_pitch(m_handle));
}



void audio_source::set_gain(non_negative<float> value)
{
  al::set_source_gain(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_gain() const
{
  return static_cast<float>(al::get_source_gain(m_handle));
}



void audio_source::set_max_gain(non_negative<float> value)
{
  al::set_source_max_gain(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_max_gain() const
{
  return static_cast<float>(al::get_source_max_gain(m_handle));
}



void audio_source::set_min_gain(non_negative<float> value)
{
  al::set_source_min_gain(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_min_gain() const
{
  return static_cast<float>(al::get_source_min_gain(m_handle));
}



void audio_source::set_max_distance(non_negative<float> value)
{
  al::set_source_max_distance(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_max_distance() const
{
  return static_cast<float>(al::get_source_max_distance(m_handle));
}



void audio_source::set_rolloff_factor(non_negative<float> value)
{
  al::set_source_rolloff_factor(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_rolloff_factor() const
{
  return static_cast<float>(al::get_source_rolloff_factor(m_handle));
}



void audio_source::set_reference_distance(non_negative<float> value)
{
  al::set_source_reference_distance(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_reference_distance() const
{
  return static_cast<float>(al::get_source_reference_distance(m_handle));
}



void audio_source::set_relative(bool value)
{
  al::set_source_relative(m_handle, static_cast<ALboolean>(value));
}



bool audio_source::is_relative() const
{
  return static_cast<bool>(al::get_source_relative(m_handle));
}



void audio_source::set_cone_outer_gain(non_negative<float> value)
{
  al::set_source_cone_outer_gain(m_handle, static_cast<ALfloat>(value));
}



non_negative<float> audio_source::get_cone_outer_gain() const
{
  return static_cast<float>(al::get_source_cone_outer_gain(m_handle));
}



void audio_source::set_cone_inner_angle(float value)
{
  HOU_PRECOND(value >= 0.f && value <= 2.f * pi<float>());
  al::set_source_cone_inner_angle(
    m_handle, static_cast<ALfloat>(rad_to_deg(value)));
}



float audio_source::get_cone_inner_angle() const
{
  return deg_to_rad(
    static_cast<float>(al::get_source_cone_inner_angle(m_handle)));
}



void audio_source::set_cone_outer_angle(float value)
{
  HOU_PRECOND(value >= 0.f && value <= 2.f * pi<float>());
  al::set_source_cone_outer_angle(
    m_handle, static_cast<ALfloat>(rad_to_deg(value)));
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



void audio_source::on_set_looping(bool looping)
{
  al::set_source_looping(m_handle, static_cast<ALboolean>(looping));
}



void audio_source::on_set_sample_pos(sample_position pos)
{
  al::set_source_sample_offset(m_handle, narrow_cast<ALint>(pos));
}



audio_source::sample_position audio_source::on_get_sample_pos() const
{
  return narrow_cast<sample_position>(al::get_source_sample_offset(m_handle));
}



void audio_source::on_play()
{
  // Do nothing.
}



void audio_source::on_pause()
{
  // Do nothing.
}

}  // namespace hou
