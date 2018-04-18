// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_LISTENER_HPP
#define HOU_AL_AL_LISTENER_HPP

#include "hou/al/AlExport.hpp"

#include "hou/al/OpenAl.hpp"



namespace hou
{

namespace al
{

HOU_AL_API void setListenerGain(ALfloat value);
HOU_AL_API ALfloat getListenerGain();

HOU_AL_API void setListenerPosition(const ALfloat* value);
HOU_AL_API void getListenerPosition(ALfloat* value);

HOU_AL_API void setListenerVelocity(const ALfloat* value);
HOU_AL_API void getListenerVelocity(ALfloat* value);

HOU_AL_API void setListenerOrientation(const ALfloat* value);
HOU_AL_API void getListenerOrientation(ALfloat* value);

}  // namespace al

}  // namespace hou

#endif
