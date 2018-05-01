// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/sound_distance_model.hpp"

#define SOUND_DISTANCE_MODEL_CASE(dm, os) \
  case sound_distance_model::dm: \
    return (os) << #dm



namespace hou
{

std::ostream& operator<<(std::ostream& os, sound_distance_model dm)
{
  switch(dm)
  {
    SOUND_DISTANCE_MODEL_CASE(inverse_distance, os);
    SOUND_DISTANCE_MODEL_CASE(inverse_distance_clamped, os);
    SOUND_DISTANCE_MODEL_CASE(linear_distance, os);
    SOUND_DISTANCE_MODEL_CASE(linear_distance_clamped, os);
    SOUND_DISTANCE_MODEL_CASE(exponent_distance, os);
    SOUND_DISTANCE_MODEL_CASE(exponent_distance_clamped, os);
    default:
      return os;
  }
}

}  // namespace hou
