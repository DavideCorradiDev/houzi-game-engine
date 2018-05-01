// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_EXPORT_HPP
#define HOU_AUD_EXPORT_HPP

#include "hou/config.hpp"

#if defined(HOU_AUD_EXPORTS)
  #define HOU_AUD_API HOU_EXPORT
#else
  #define HOU_AUD_API HOU_IMPORT
#endif

#endif
