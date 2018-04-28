// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_SOURCE_STATE_HPP
#define HOU_AUD_AUDIO_SOURCE_STATE_HPP

#include "hou/aud/AudExport.hpp"

#include <iostream>



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
  /** The audio source is paused, playing will be resumed from the current
   * offset.
   */
  Paused,
};

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param state the AudioSourceState enum.
 *  \return a reference to the stream.
 */
HOU_AUD_API std::ostream& operator<<(std::ostream& os, AudioSourceState state);

}  // namespace hou

#endif
