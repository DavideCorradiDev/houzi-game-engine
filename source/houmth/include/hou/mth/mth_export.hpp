// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_EXPORT_HPP
#define HOU_MTH_EXPORT_HPP

#include "hou/config.hpp"

#if defined(HOU_MTH_EXPORTS)
  #define HOU_MTH_API HOU_EXPORT
#else
  #define HOU_MTH_API HOU_IMPORT
#endif

#endif

