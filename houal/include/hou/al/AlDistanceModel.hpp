// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_AL_DISTANCE_MODEL_HPP
#define HOU_AL_AL_DISTANCE_MODEL_HPP

#include "hou/al/AlExport.hpp"
#include "hou/al/OpenAl.hpp"



namespace hou
{

namespace al
{

enum class DistanceModel : ALenum
{
  None = AL_NONE,
  InverseDistance = AL_INVERSE_DISTANCE,
  InverseDistanceClamped = AL_INVERSE_DISTANCE_CLAMPED,
  LinearDistance = AL_LINEAR_DISTANCE,
  LinearDistanceClamped = AL_LINEAR_DISTANCE_CLAMPED,
  ExponentDistance = AL_EXPONENT_DISTANCE,
  ExponentDistanceClamped = AL_EXPONENT_DISTANCE_CLAMPED,
};

}

}

#endif

