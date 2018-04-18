// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_SOUND_DISTANCE_MODEL_HPP
#define HOU_AUD_SOUND_DISTANCE_MODEL_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/al/OpenAl.hpp"

#include <iostream>



namespace hou
{

/** Enumeration class for sound distance models.
 */
enum class SoundDistanceModel : ALenum
{
  InverseDistance = AL_INVERSE_DISTANCE,
  InverseDistanceClamped = AL_INVERSE_DISTANCE_CLAMPED,
  LinearDistance = AL_LINEAR_DISTANCE,
  LinearDistanceClamped = AL_LINEAR_DISTANCE_CLAMPED,
  ExponentDistance = AL_EXPONENT_DISTANCE,
  ExponentDistanceClamped = AL_EXPONENT_DISTANCE_CLAMPED,
};

/** Writes the object into a stream.
 *
 *  \param os the stream.
 *  \param dm the SoundDistanceModel enum.
 *  \return a reference to the stream.
 */
HOU_AUD_API std::ostream& operator<<(std::ostream& os, SoundDistanceModel dm);

}  // namespace hou

#endif
