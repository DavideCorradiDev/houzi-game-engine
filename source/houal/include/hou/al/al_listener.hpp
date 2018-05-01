// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_LISTENER_HPP
#define HOU_AL_AL_LISTENER_HPP

#include "hou/al/al_export.hpp"

#include "hou/al/open_al.hpp"



namespace hou
{

namespace al
{

HOU_AL_API void set_listener_gain(ALfloat value);
HOU_AL_API ALfloat get_listener_gain();

HOU_AL_API void set_listener_position(const ALfloat* value);
HOU_AL_API void get_listener_position(ALfloat* value);

HOU_AL_API void set_listener_velocity(const ALfloat* value);
HOU_AL_API void get_listener_velocity(ALfloat* value);

HOU_AL_API void set_listener_orientation(const ALfloat* value);
HOU_AL_API void get_listener_orientation(ALfloat* value);

}  // namespace al

}  // namespace hou

#endif
