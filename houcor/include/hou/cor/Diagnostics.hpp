// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_COR_DIAGNOSTICS_HPP
#define HOU_COR_DIAGNOSTICS_HPP


#if defined(HOU_COMPILER_MINGW)
  #define HOU_DO_PRAGMA(x) _Pragma(#x)
  #define GCC_DIAGNOSTIC_PUSH() HOU_DO_PRAGMA(GCC diagnostic push)
  #define GCC_DIAGNOSTIC_POP() HOU_DO_PRAGMA(GCC diagnostic pop)
  #define GCC_DIAGNOSTIC_IGNORED(w) HOU_DO_PRAGMA(GCC diagnostic ignored #w)
#else
  #define GCC_DIAGNOSTIC_PUSH()
  #define GCC_DIAGNOSTIC_POP()
  #define GCC_DIAGNOSTIC_IGNORED(warning)
#endif

#endif

