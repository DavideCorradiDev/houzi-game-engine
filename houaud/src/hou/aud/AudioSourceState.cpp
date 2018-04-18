// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudioSourceState.hpp"

#define AUDIO_SOURCE_STATE_CASE(state, os) \
  case AudioSourceState::state:            \
    return (os) << #state



namespace hou
{

std::ostream& operator<<(std::ostream& os, AudioSourceState state)
{
  switch(state)
  {
    AUDIO_SOURCE_STATE_CASE(Stopped, os);
    AUDIO_SOURCE_STATE_CASE(Playing, os);
    AUDIO_SOURCE_STATE_CASE(Paused, os);
  default:
    return os;
  }
}

}  // namespace hou
