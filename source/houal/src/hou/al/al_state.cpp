// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_state.hpp"

#include "hou/al/al_exceptions.hpp"



namespace hou
{

namespace al
{

void set_distance_model(ALenum value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alDistanceModel(value);
  HOU_AL_CHECK_ERROR();
}



ALenum get_distance_model()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALint value = alGetInteger(AL_DISTANCE_MODEL);
  HOU_AL_CHECK_ERROR();
  return static_cast<ALenum>(value);
}



void set_doppler_factor(ALfloat value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alDopplerFactor(value);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_doppler_factor()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALfloat value = alGetFloat(AL_DOPPLER_FACTOR);
  HOU_AL_CHECK_ERROR();
  return value;
}



void set_speed_of_sound(ALfloat value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alSpeedOfSound(value);
  HOU_AL_CHECK_ERROR();
}



ALfloat get_speed_of_sound()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALfloat value = alGetFloat(AL_SPEED_OF_SOUND);
  HOU_AL_CHECK_ERROR();
  return value;
}

}  // namespace al

}  // namespace hou
