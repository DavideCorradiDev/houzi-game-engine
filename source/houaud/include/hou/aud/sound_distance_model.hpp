// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_SOUND_DISTANCE_MODEL_HPP
#define HOU_AUD_SOUND_DISTANCE_MODEL_HPP

#include "hou/aud/aud_config.hpp"

#include "hou/al/open_al.hpp"

#include <iostream>



namespace hou
{

/** Enumeration class for sound distance models.
 */
enum class sound_distance_model : ALenum
{
  /** Sound is attenuated proportionally to the inverse of the distance from the
   * audio source.
   */
  inverse_distance = AL_INVERSE_DISTANCE,
  /** Sound is attenauted proportionally to the inverse of the distance from the
   * audio source and is clamped.
   *
   * The gain is clamped for distances lower than the reference distance of the
   * source and greater than the maximum distance of the source.
   */
  inverse_distance_clamped = AL_INVERSE_DISTANCE_CLAMPED,
  /** Sound is attenuated proportionally to the the distance from the audio
   * source.
   *
   * The gain is clamped to 0 for distances greater than the maximum distance of
   * the source.
   */
  linear_distance = AL_LINEAR_DISTANCE,
  /** Sound is attenuated proportionally to the the distance from the audio
   * source and is clamped.
   *
   * The gain is clamped for distances lower than the reference distance
   * of the source and greater than the maximum distance of the source.
   */
  linear_distance_clamped = AL_LINEAR_DISTANCE_CLAMPED,
  /** Sound is attenuated exponentially with the distance.
   */
  exponent_distance = AL_EXPONENT_DISTANCE,
  /** Sound is attenuated exponentially with the distance and is clamped.
   *
   * The gain is clamped for distances lower than the reference distance of the
   * source and greater than the maximum distance of the source.
   */
  exponent_distance_clamped = AL_EXPONENT_DISTANCE_CLAMPED,
};

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param dm the sound_distance_model enum.
 *  \return a reference to the stream.
 */
HOU_AUD_API std::ostream& operator<<(std::ostream& os, sound_distance_model dm);

}  // namespace hou

#endif
