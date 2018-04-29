// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_EXPORT_HPP
#define HOU_GL_EXPORT_HPP

#include "hou/config.hpp"

#if defined(HOU_GL_EXPORTS)
  #define HOU_GL_API HOU_EXPORT
#else
  #define HOU_GL_API HOU_IMPORT
#endif

#endif

