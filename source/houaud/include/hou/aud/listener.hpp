// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_LISTENER_HPP
#define HOU_AUD_LISTENER_HPP

#include "hou/aud/aud_config.hpp"

#include "hou/cor/checked_variable.hpp"

#include "hou/mth/matrix_fwd.hpp"
#include "hou/mth/rotation3_fwd.hpp"



namespace hou
{

/**
 * Functions related to the state of the audio listener.
 *
 * The audio listener represents the position from which sounds are heard.
 * There is only one listener per audio_context.
 * all functions in this namespace are thread safe.
 */
namespace listener
{

/**
 * Gets the gain of the listener.
 *
 * \return the gain of the listener.
 */
HOU_AUD_API non_negative<float> get_gain();

/**
 * Sets the gain of the listener.
 *
 * The default value is 1.
 * Throws if the value is negative.
 * Higher gain values will make the sounds louder.
 *
 * \param gain the gain.
 */
HOU_AUD_API void set_gain(non_negative<float> gain);

/**
 * Gets the current position of the listener in 3d space.
 *
 * \return the current position of the listener.
 */
HOU_AUD_API vec3f get_position();

/**
 * Sets the position of the listener in 3d space.
 *
 * The default value is (0, 0, 0).
 *
 * \param pos the position.
 */
HOU_AUD_API void set_position(const vec3f& pos);

/**
 * Gets the current linear velocity of the listener.
 *
 * \return the linear velocity.
 */
HOU_AUD_API vec3f get_velocity();

/**
 * Sets the current linear velocity of the listener.
 *
 * The default value is (0, 0, 0).
 *
 * \param vel the velocity.
 */
HOU_AUD_API void set_velocity(const vec3f& vel);

/**
 * Gets the orientation of the listener.
 *
 * \return the orientation of the listener.
 */
HOU_AUD_API rot3f get_orientation();

/**
 * Gets the current orientation of the listener.
 *
 * The default value is the zero rotation.
 * In the zero rotation configuration, the listener "at" vector is the negative
 * z axis, and the listener "up" vector is the positive y axis.
 *
 * \param ori the orientation.
 */
HOU_AUD_API void set_orientation(const rot3f& ori);

}  // namespace listener

}  // namespace hou

#endif
