// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_EXPORT_HPP
#define HOU_AL_EXPORT_HPP

#include "hou/config.hpp"

#if defined(HOU_AL_EXPORTS)
  #define HOU_AL_API HOU_EXPORT
#else
  #define HOU_AL_API HOU_IMPORT
#endif

#endif
