// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_CONFIG_HPP
#define HOU_GL_CONFIG_HPP

#include "hou/config.hpp"

#if defined(HOU_GL_EXPORTS)
  #define HOU_GL_API HOU_EXPORT
#else
  #define HOU_GL_API HOU_IMPORT
#endif

#if defined(HOU_SYSTEM_WINDOWS)
  #ifdef HOU_COMPILER_MSVC
    #ifndef NOMINMAX
      #define NOMINMAX
    #endif
  #endif
  #define HOU_GL_WGL
#elif defined(HOU_SYSTEM_LINUX)
  #define HOU_GL_GLX
#endif

#endif
