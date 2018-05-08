// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_STATE_HPP
#define HOU_AL_AL_STATE_HPP

#include "hou/al/open_al.hpp"

#include "hou/al/al_export.hpp"



namespace hou
{

namespace al
{

void HOU_AL_API set_distance_model(ALenum value);
ALenum HOU_AL_API get_distance_model();

void HOU_AL_API set_doppler_factor(ALfloat value);
ALfloat HOU_AL_API get_doppler_factor();

void HOU_AL_API set_speed_of_sound(ALfloat value);
ALfloat HOU_AL_API get_speed_of_sound();

}  // namespace al

}  // namespace hou

#endif
