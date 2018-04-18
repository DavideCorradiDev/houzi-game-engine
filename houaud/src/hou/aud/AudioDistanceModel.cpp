// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioDistanceModel.hpp"

#define AUDIO_DISTANCE_MODEL_CASE(dm, os) \
  case AudioDistanceModel::dm:            \
    return (os) << #dm



namespace hou
{

std::ostream& operator<<(std::ostream& os, AudioDistanceModel dm)
{
  switch(dm)
  {
    AUDIO_DISTANCE_MODEL_CASE(InverseDistance, os);
    AUDIO_DISTANCE_MODEL_CASE(InverseDistanceClamped, os);
    AUDIO_DISTANCE_MODEL_CASE(LinearDistance, os);
    AUDIO_DISTANCE_MODEL_CASE(LinearDistanceClamped, os);
    AUDIO_DISTANCE_MODEL_CASE(ExponentDistance, os);
    AUDIO_DISTANCE_MODEL_CASE(ExponentDistanceClamped, os);
  default:
    return os;
  }
}

}  // namespace hou
