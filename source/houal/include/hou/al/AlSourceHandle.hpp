// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_SOURCE_HANDLE_HPP
#define HOU_AL_AL_SOURCE_HANDLE_HPP

#include "hou/al/al_export.hpp"
#include "hou/al/al_object_handle.hpp"



namespace hou
{

namespace al
{

class buffer_handle;



class HOU_AL_API source_handle
  : public context_owned_object_handle
{
public:
  static source_handle generate();

  source_handle(source_handle&& other);
  virtual ~source_handle();

private:
  source_handle(ALuint name);
};



HOU_AL_API void set_source_pitch(const source_handle& s, ALfloat pitch);
HOU_AL_API ALfloat get_source_pitch(const source_handle& s);
HOU_AL_API void set_source_gain(const source_handle& s, ALfloat gain);
HOU_AL_API ALfloat get_source_gain(const source_handle& s);
HOU_AL_API void set_source_max_gain(const source_handle& s, ALfloat maxGain);
HOU_AL_API ALfloat get_source_max_gain(const source_handle& s);
HOU_AL_API void set_source_min_gain(const source_handle& s, ALfloat minGain);
HOU_AL_API ALfloat get_source_min_gain(const source_handle& s);
HOU_AL_API void set_source_max_distance(const source_handle& s, ALfloat distance);
HOU_AL_API ALfloat get_source_max_distance(const source_handle& s);
HOU_AL_API void set_source_rolloff_factor(const source_handle& s, ALfloat factor);
HOU_AL_API ALfloat get_source_rolloff_factor(const source_handle& s);
HOU_AL_API void set_source_cone_outer_gain(const source_handle& s, ALfloat gain);
HOU_AL_API ALfloat get_source_cone_outer_gain(const source_handle& s);
HOU_AL_API void set_source_cone_inner_angle(const source_handle& s, ALfloat angle);
HOU_AL_API ALfloat get_source_cone_inner_angle(const source_handle& s);
HOU_AL_API void set_source_cone_outer_angle(const source_handle& s, ALfloat angle);
HOU_AL_API ALfloat getSourceConeOuterAngle(const source_handle& s);
HOU_AL_API void set_source_reference_distance(const source_handle& s, ALfloat dist);
HOU_AL_API ALfloat get_source_reference_distance(const source_handle& s);
HOU_AL_API void set_source_position(const source_handle& s, const ALfloat* pos);
HOU_AL_API void get_source_position(const source_handle& s, ALfloat* pos);
HOU_AL_API void set_source_velocity(const source_handle& s, const ALfloat* vel);
HOU_AL_API void get_source_velocity(const source_handle& s, ALfloat* vel);
HOU_AL_API void set_source_direction(const source_handle& s, const ALfloat* dir);
HOU_AL_API void get_source_direction(const source_handle& s, ALfloat* dir);
HOU_AL_API void set_source_relative(const source_handle& s, ALboolean relative);
HOU_AL_API ALboolean get_source_relative(const source_handle& s);
HOU_AL_API void set_source_looping(const source_handle& s, ALboolean looping);
HOU_AL_API ALboolean get_source_looping(const source_handle& s);

HOU_AL_API void set_source_state(const source_handle& s, ALenum state);
HOU_AL_API ALenum get_source_state(const source_handle& s);
HOU_AL_API void play_source(const source_handle& s);
HOU_AL_API void pause_source(const source_handle& s);
HOU_AL_API void stop_source(const source_handle& s);
HOU_AL_API void rewind_source(const source_handle& s);

HOU_AL_API void set_source_buffer(const source_handle& s, ALuint buffer);
HOU_AL_API ALuint get_source_buffer(const source_handle& s);
HOU_AL_API void source_queue_buffers(const source_handle& s, ALsizei n
  , ALuint* buffers);
HOU_AL_API void source_unqueue_buffers(const source_handle& s, ALsizei n
  , ALuint* buffers);
HOU_AL_API ALint get_source_queued_buffers(const source_handle& s);
HOU_AL_API ALint get_source_processed_buffers(const source_handle& s);

HOU_AL_API void set_source_sec_offset(const source_handle& s, ALfloat offset);
HOU_AL_API ALfloat get_source_sec_offset(const source_handle& s);
HOU_AL_API void set_source_sample_offset(const source_handle& s, ALint offset);
HOU_AL_API ALint get_source_sample_offset(const source_handle& s);
HOU_AL_API void set_source_byte_offset(const source_handle& s, ALint offset);
HOU_AL_API ALint get_source_byte_offset(const source_handle& s);

}

}

#endif

