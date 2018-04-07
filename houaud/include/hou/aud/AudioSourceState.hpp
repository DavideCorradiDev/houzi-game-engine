// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AUD_AUDIO_SOURCE_STATE_HPP
#define HOU_AUD_AUDIO_SOURCE_STATE_HPP

#include "hou/aud/AudExport.hpp"



namespace hou
{

/** Enumeration class for the state of an audio source.
*/
enum class AudioSourceState
{
  /** The audio source is stopped, playing will be resumed from the beginning.*/
  Stopped,
  /** The audio source is playing.*/
  Playing,
  /** The audio source is paused, playing will be resumed from the current offset.*/
  Paused,
};

}

#endif

