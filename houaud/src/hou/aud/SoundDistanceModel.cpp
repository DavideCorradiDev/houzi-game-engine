// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/SoundDistanceModel.hpp"

#define SOUND_DISTANCE_MODEL_CASE(dm, os) \
  case SoundDistanceModel::dm:            \
    return (os) << #dm



namespace hou
{

std::ostream& operator<<(std::ostream& os, SoundDistanceModel dm)
{
  switch(dm)
  {
    SOUND_DISTANCE_MODEL_CASE(InverseDistance, os);
    SOUND_DISTANCE_MODEL_CASE(InverseDistanceClamped, os);
    SOUND_DISTANCE_MODEL_CASE(LinearDistance, os);
    SOUND_DISTANCE_MODEL_CASE(LinearDistanceClamped, os);
    SOUND_DISTANCE_MODEL_CASE(ExponentDistance, os);
    SOUND_DISTANCE_MODEL_CASE(ExponentDistanceClamped, os);
  default:
    return os;
  }
}

}  // namespace hou
