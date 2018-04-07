// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AL_OPEN_AL_HPP
#define HOU_AL_OPEN_AL_HPP

#include "hou/al/AlExport.hpp"

#ifndef TARGET_OS_MAC
  #define TARGET_OS_MAC 0
#endif
#include <AL/al.h>
#undef TARGET_OS_MAC

#include <AL/alc.h>

#endif

