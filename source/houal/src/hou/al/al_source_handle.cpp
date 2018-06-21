// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_source_handle.hpp"

#include "hou/al/al_buffer_handle.hpp"
#include "hou/al/al_exceptions.hpp"
#include "hou/al/al_invalid_context_error.hpp"
#include "hou/al/al_missing_context_error.hpp"



namespace hou
{

namespace al
{

source_handle source_handle::generate()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALuint name;
  alGenSources(1u, &name);
  HOU_AL_CHECK_ERROR();
  return source_handle(name);
}



source_handle::~source_handle()
{
  if(get_name() != 0)
  {
    HOU_AL_CHECK_CONTEXT_EXISTENCE();
    HOU_AL_CHECK_CONTEXT_OWNERSHIP(*this);
    ALuint name = get_name();
    alDeleteSources(1u, &name);
    HOU_AL_CHECK_ERROR();
  }
}



source_handle::source_handle(ALuint name)
  : context_owned_object_handle(name)
{}



void set_source_pitch(const source_handle& s, ALfloat pitch)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_PITCH, pitch);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_pitch(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_PITCH, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_gain(const source_handle& s, ALfloat gain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_GAIN, gain);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_gain(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_max_gain(const source_handle& s, ALfloat maxGain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_MAX_GAIN, maxGain);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_max_gain(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_MAX_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_min_gain(const source_handle& s, ALfloat minGain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_MIN_GAIN, minGain);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_min_gain(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_MIN_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_max_distance(const source_handle& s, ALfloat distance)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_MAX_DISTANCE, distance);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_max_distance(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_MAX_DISTANCE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_rolloff_factor(const source_handle& s, ALfloat factor)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_ROLLOFF_FACTOR, factor);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_rolloff_factor(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_ROLLOFF_FACTOR, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_cone_outer_gain(const source_handle& s, ALfloat gain)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_CONE_OUTER_GAIN, gain);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_cone_outer_gain(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_CONE_OUTER_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_cone_inner_angle(const source_handle& s, ALfloat angle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_CONE_INNER_ANGLE, angle);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_cone_inner_angle(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_CONE_INNER_ANGLE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_cone_outer_angle(const source_handle& s, ALfloat angle)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_CONE_OUTER_ANGLE, angle);
  HOU_AL_CHECK_ERROR();
}



ALfloat getSourceConeOuterAngle(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_CONE_OUTER_ANGLE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_reference_distance(const source_handle& s, ALfloat dist)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_REFERENCE_DISTANCE, dist);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_reference_distance(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_REFERENCE_DISTANCE, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_position(const source_handle& s, const ALfloat* pos)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcefv(s.get_name(), AL_POSITION, const_cast<ALfloat*>(pos));
  HOU_AL_CHECK_ERROR();
}



void get_source_position(const source_handle& s, ALfloat* pos)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alGetSourcefv(s.get_name(), AL_POSITION, pos);
  HOU_AL_CHECK_ERROR();
}



void set_source_velocity(const source_handle& s, const ALfloat* vel)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcefv(s.get_name(), AL_VELOCITY, const_cast<ALfloat*>(vel));
  HOU_AL_CHECK_ERROR();
}



void get_source_velocity(const source_handle& s, ALfloat* vel)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alGetSourcefv(s.get_name(), AL_VELOCITY, vel);
  HOU_AL_CHECK_ERROR();
}



void set_source_direction(const source_handle& s, const ALfloat* dir)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcefv(s.get_name(), AL_DIRECTION, const_cast<ALfloat*>(dir));
  HOU_AL_CHECK_ERROR();
}



void get_source_direction(const source_handle& s, ALfloat* dir)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alGetSourcefv(s.get_name(), AL_DIRECTION, dir);
  HOU_AL_CHECK_ERROR();
}



void set_source_relative(const source_handle& s, ALboolean relative)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_SOURCE_RELATIVE, static_cast<ALint>(relative));
  HOU_AL_CHECK_ERROR();
}



ALboolean get_source_relative(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_SOURCE_RELATIVE, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALboolean>(value);
}



void set_source_looping(const source_handle& s, ALboolean looping)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_LOOPING, static_cast<ALint>(looping));
  HOU_AL_CHECK_ERROR();
}



ALboolean get_source_looping(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_LOOPING, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALboolean>(value);
}



void set_source_state(const source_handle& s, ALenum state)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_SOURCE_STATE, state);
  HOU_AL_CHECK_ERROR();
}



ALenum get_source_state(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_SOURCE_STATE, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALenum>(value);
}



void play_source(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcePlay(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void pause_source(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcePause(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void stop_source(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceStop(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void rewind_source(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceRewind(s.get_name());
  HOU_AL_CHECK_ERROR();
}



void set_source_buffer(const source_handle& s, ALuint buffer)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_BUFFER, static_cast<ALint>(buffer));
  HOU_AL_CHECK_ERROR();
}



ALuint get_source_buffer(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BUFFER, &value);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALuint>(value);
}



void source_queue_buffers(const source_handle& s, ALsizei n, ALuint* buffers)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceQueueBuffers(s.get_name(), n, buffers);
  HOU_AL_CHECK_ERROR();
}



void source_unqueue_buffers(const source_handle& s, ALsizei n, ALuint* buffers)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourceUnqueueBuffers(s.get_name(), n, buffers);
  HOU_AL_CHECK_ERROR();
}



ALint get_source_queued_buffers(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BUFFERS_QUEUED, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint get_source_processed_buffers(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BUFFERS_PROCESSED, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_sec_offset(const source_handle& s, ALfloat offset)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcef(s.get_name(), AL_SEC_OFFSET, offset);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_source_sec_offset(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALfloat value;
  alGetSourcef(s.get_name(), AL_SEC_OFFSET, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



ALint get_source_sample_offset(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_SAMPLE_OFFSET, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_sample_offset(const source_handle& s, ALint offset)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_SAMPLE_OFFSET, offset);
  HOU_AL_CHECK_ERROR();
}



ALint get_source_byte_offset(const source_handle& s)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  ALint value;
  alGetSourcei(s.get_name(), AL_BYTE_OFFSET, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_source_byte_offset(const source_handle& s, ALint offset)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  HOU_AL_CHECK_CONTEXT_OWNERSHIP(s);
  alSourcei(s.get_name(), AL_BYTE_OFFSET, offset);
  HOU_AL_CHECK_ERROR();
}

}  // namespace al

}  // namespace hou
