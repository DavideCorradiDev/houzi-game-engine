// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_listener.hpp"

#include "hou/al/al_check.hpp"



namespace hou
{

namespace al
{

void set_listener_gain(ALfloat value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerf(AL_GAIN, value);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_listener_gain()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALfloat value;
  alGetListenerf(AL_GAIN, &value);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_listener_position(const ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerfv(AL_POSITION, const_cast<ALfloat*>(value));
  HOU_AL_CHECK_ERROR();
}



void get_listener_position(ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alGetListenerfv(AL_POSITION, value);
  HOU_AL_CHECK_ERROR();
}



void set_listener_velocity(const ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerfv(AL_VELOCITY, const_cast<ALfloat*>(value));
  HOU_AL_CHECK_ERROR();
}



void get_listener_velocity(ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alGetListenerfv(AL_VELOCITY, value);
  HOU_AL_CHECK_ERROR();
}



void set_listener_orientation(const ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alListenerfv(AL_ORIENTATION, const_cast<ALfloat*>(value));
  HOU_AL_CHECK_ERROR();
}



void get_listener_orientation(ALfloat* value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alGetListenerfv(AL_ORIENTATION, value);
  HOU_AL_CHECK_ERROR();
}



}  // namespace al

}  // namespace hou
