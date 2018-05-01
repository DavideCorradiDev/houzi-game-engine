// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUDIO_SOURCE_STATE_HPP
#define HOU_AUD_AUDIO_SOURCE_STATE_HPP

#include "hou/aud/aud_export.hpp"

#include <iostream>



namespace hou
{

/** Enumeration class for the state of an audio source.
 */
enum class audio_source_state
{
  /** The audio source is stopped, playing will be resumed from the beginning.*/
  stopped,
  /** The audio source is playing.*/
  playing,
  /** The audio source is paused, playing will be resumed from the current
   * offset.
   */
  paused,
};

/** Writes the object into a stream.
 *
 * \param os the stream.
 *
 * \param state the audio_source_state enum.
 *
 * \return a reference to the stream.
 */
HOU_AUD_API std::ostream& operator<<(
  std::ostream& os, audio_source_state state);

}  // namespace hou

#endif
