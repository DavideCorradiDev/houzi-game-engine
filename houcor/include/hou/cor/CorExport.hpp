// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_EXPORT_HPP
#define HOU_EXPORT_HPP

#include "hou/Config.hpp"

#if defined(HOU_COR_EXPORTS)
  #define HOU_COR_API HOU_EXPORT
#else
  #define HOU_COR_API HOU_IMPORT
#endif

#endif

