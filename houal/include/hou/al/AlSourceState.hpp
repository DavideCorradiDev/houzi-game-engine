// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_SOURCE_STATE_HPP
#define HOU_AL_AL_SOURCE_STATE_HPP

#include "hou/al/AlExport.hpp"
#include "hou/al/OpenAl.hpp"



namespace hou
{

namespace al
{

enum class SourceState : ALenum
{
  Initial = AL_INITIAL,
  Paused = AL_PAUSED,
  Playing = AL_PLAYING,
  Stopped = AL_STOPPED,
};

}

}

#endif

