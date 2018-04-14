// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_STATE_HPP
#define HOU_AL_AL_STATE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/al/OpenAl.hpp"

#include "hou/al/AlDistanceModel.hpp"



namespace hou
{

namespace al
{

void HOU_AL_API setDistanceModel(DistanceModel value);
DistanceModel HOU_AL_API getDistanceModel();

void HOU_AL_API setDopplerFactor(ALfloat value);
ALfloat HOU_AL_API getDopplerFactor();

void HOU_AL_API setSpeedOfSound(ALfloat value);
ALfloat HOU_AL_API getSpeedOfSound();

}

}

#endif

