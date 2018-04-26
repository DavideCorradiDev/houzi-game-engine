// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_SOUND_MODEL_HPP
#define HOU_AUD_SOUND_MODEL_HPP

#include "hou/aud/AudExport.hpp"

#include "hou/aud/SoundDistanceModel.hpp"



namespace hou
{

/** Functions related to the state of the sound propagation model.
 *
 * The sound propagation model is defined by three main attributes:
 * * The distance model.
 * * The doppler factor.
 * * The speed of sound.
 *
 * The distance model describes the mathematical law relating the gain of audio
 * sources to the distance of the listener from the audio source. The
 * attenuation can be linearly proportional to the distance, inversely
 * proportional to the distance, or inversey exponentially to the distance. The
 * distance model also specifies if the gain should be clamped for short or
 * large distances.
 *
 * The distance model together with some properties of the audio source, namely:
 * * Reference distance: it is the distance at which the gain is equal to 1, and
 * before which the gain is eventually clamped.
 * * Maximum distance: it is the distance after which the gain is eventually
 * clamped. In case of a linear distance model, it is the distance at which the
 * gain becomes 0.
 * * Rolloff factor: it is a factor describing how quickly the gain decreases
 * with the distance. The higher the rolloff factor, the quicker the decrease.
 *
 * The doppler factor and speed of sound are constants used to simulate the
 * doppler effect.
 */
namespace SoundModel
{

/** Gets the currently used sound distance model.
 *
 * The default value is InverseDistanceClamped.
 *
 * \return the currently used sound distance model.
 */
HOU_AUD_API SoundDistanceModel getDistanceModel();

/** Sets the current sound distance model.
 *
 * \param model the sound distance model.
 */
HOU_AUD_API void setDistanceModel(SoundDistanceModel model);

/** Gets the current doppler factor.
 *
 * The default value is 1.
 *
 * \return the current doppler factor.
 */
HOU_AUD_API float getDopplerFactor();

/** Sets the current doppler factor.
 *
 * Throws if dopplerFactor is negative.
 *
 * \param dopplerFactor the doppler factor.
 */
HOU_AUD_API void setDopplerFactor(float dopplerFactor);

/** Gets the current speed of sound in meters per second.
 *
 * The default value is 343.3 meters per second.
 *
 * \return the current speed of sound.
 */
HOU_AUD_API float getSpeedOfSound();

/** Sets the current speed of sound.
 *
 * Throws if speedOfSound is zero or negative.
 *
 * \param speedOfSound the speed of sound.
 */
HOU_AUD_API void setSpeedOfSound(float speedOfSound);

}  // namespace SoundModel

}  // namespace hou

#endif
