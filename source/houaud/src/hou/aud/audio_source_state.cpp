// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/audio_source_state.hpp"

#include "hou/cor/core_functions.hpp"

#define AUDIO_SOURCE_STATE_CASE(state, os) \
  case audio_source_state::state: \
    return (os) << #state



namespace hou
{

std::ostream& operator<<(std::ostream& os, audio_source_state state)
{
  switch(state)
  {
    AUDIO_SOURCE_STATE_CASE(stopped, os);
    AUDIO_SOURCE_STATE_CASE(playing, os);
    AUDIO_SOURCE_STATE_CASE(paused, os);
  }
  return STREAM_VALUE(os, audio_source_state, state);
}

}  // namespace hou
