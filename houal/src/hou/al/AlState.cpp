// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/al/AlState.hpp"

#include "hou/al/AlCheck.hpp"



namespace hou
{

namespace al
{

void setDistanceModel(DistanceModel value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alDistanceModel(static_cast<ALenum>(value));
  HOU_AL_CHECK_ERROR();
}



DistanceModel getDistanceModel()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALint value = alGetInteger(AL_DISTANCE_MODEL);
  HOU_AL_CHECK_ERROR();
  return static_cast<DistanceModel>(value);
}



void setDopplerFactor(ALfloat value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alDopplerFactor(value);
  HOU_AL_CHECK_ERROR();
}



ALfloat getDopplerFactor()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALfloat value = alGetFloat(AL_DOPPLER_FACTOR);
  HOU_AL_CHECK_ERROR();
  return value;
}



void setSpeedOfSound(ALfloat value)
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  alSpeedOfSound(value);
  HOU_AL_CHECK_ERROR();
}



ALfloat getSpeedOfSound()
{
  HOU_AL_CHECK_CONTEXT_EXISTENCE();
  ALfloat value = alGetFloat(AL_SPEED_OF_SOUND);
  HOU_AL_CHECK_ERROR();
  return value;
}

}

}

