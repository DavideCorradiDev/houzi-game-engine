// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_EXPORT_HPP
#define HOU_GFX_EXPORT_HPP

#include "hou/Config.hpp"

#if defined(HOU_GFX_EXPORTS)
  #define HOU_GFX_API HOU_EXPORT
#else
  #define HOU_GFX_API HOU_IMPORT
#endif

#endif

