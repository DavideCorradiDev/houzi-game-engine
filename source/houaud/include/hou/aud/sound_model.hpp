// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_SOUND_MODEL_HPP
#define HOU_AUD_SOUND_MODEL_HPP

#include "hou/aud/sound_distance_model.hpp"

#include "hou/aud/aud_config.hpp"

#include "hou/cor/checked_variable.hpp"



namespace hou
{

/**
 * Functions related to the state of the sound propagation model.
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
namespace sound_model
{

/**
 * Gets the currently used sound distance model.
 *
 * The default value is inverse_distance_clamped.
 *
 * \return the currently used sound distance model.
 */
HOU_AUD_API sound_distance_model get_distance_model();

/**
 * Sets the current sound distance model.
 *
 * \param model the sound distance model.
 */
HOU_AUD_API void set_distance_model(sound_distance_model model);

/**
 * Gets the current doppler factor.
 *
 * The default value is 1.
 *
 * \return the current doppler factor.
 */
HOU_AUD_API non_negative<float> get_doppler_factor();

/**
 * Sets the current doppler factor.
 *
 * Throws if dopplerFactor is negative.
 *
 * \param dopplerFactor the doppler factor.
 */
HOU_AUD_API void set_doppler_factor(non_negative<float> dopplerFactor);

/**
 * Gets the current speed of sound in meters per second.
 *
 * The default value is 343.3 meters per second.
 *
 * \return the current speed of sound.
 */
HOU_AUD_API positive<float> get_speed_of_sound();

/**
 * Sets the current speed of sound.
 *
 * Throws if speedOfSound is zero or negative.
 *
 * \param speedOfSound the speed of sound.
 */
HOU_AUD_API void set_speed_of_sound(positive<float> speedOfSound);

}  // namespace sound_model

}  // namespace hou

#endif
