// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_EXPORT_HPP
#define HOU_SYS_EXPORT_HPP

#include "hou/config.hpp"

#if defined(HOU_SYS_EXPORTS)
  #define HOU_SYS_API HOU_EXPORT
#else
  #define HOU_SYS_API HOU_IMPORT
#endif

#endif

