// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_GL_EXPORT_HPP
#define HOU_GL_EXPORT_HPP

#include "hou/Config.hpp"

#if defined(HOU_GL_EXPORTS)
  #define HOU_GL_API HOU_EXPORT
#else
  #define HOU_GL_API HOU_IMPORT
#endif

#endif
