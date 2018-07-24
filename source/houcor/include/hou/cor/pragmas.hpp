// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_PRAGMAS_HPP
#define HOU_COR_PRAGMAS_HPP

#include "hou/cor/cor_config.hpp"

// The macros in this file can be called to use pragmas in an almost
// platform-indipendent way.
// Pragmas are still defined according to a specific compiler, but they will
// be ignored if a different compiler is used, resulting in portable code.

// clang-format off
#if defined(HOU_COMPILER_MINGW) || defined(HOU_COMPILER_GCC) || defined(HOU_COMPILER_CLANG)
  #define HOU_DO_PRAGMA(x) _Pragma(#x)
#elif defined(HOU_COMPILER_MSVC)
  #define HOU_DO_PRAGMA(x) __pragma(x)
#endif

#if defined(HOU_COMPILER_MINGW) || defined(HOU_COMPILER_GCC) || defined(HOU_COMPILER_CLANG)
  #define HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH() HOU_DO_PRAGMA(GCC diagnostic push)
  #define HOU_PRAGMA_GCC_DIAGNOSTIC_POP() HOU_DO_PRAGMA(GCC diagnostic pop)
  #define HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(w)                                 \
    HOU_DO_PRAGMA(GCC diagnostic ignored #w)
  #define HOU_PRAGMA_PACK_PUSH(n) HOU_DO_PRAGMA(pack(push, n))
  #define HOU_PRAGMA_PACK_POP() HOU_DO_PRAGMA(pack(pop))
#else
  #define HOU_PRAGMA_GCC_DIAGNOSTIC_PUSH()
  #define HOU_PRAGMA_GCC_DIAGNOSTIC_POP()
  #define HOU_PRAGMA_GCC_DIAGNOSTIC_IGNORED(warning)
  #define HOU_PRAGMA_PACK_PUSH(n)
  #define HOU_PRAGMA_PACK_POP()
#endif


#if defined(HOU_COMPILER_MSVC)
  #define HOU_PRAGMA_MSVC_WARNING_PUSH() HOU_DO_PRAGMA(warning(push))
  #define HOU_PRAGMA_MSVC_WARNING_POP() HOU_DO_PRAGMA(warning(pop))
  #define HOU_PRAGMA_MSVC_WARNING_DISABLE(w)                                   \
    HOU_DO_PRAGMA(warning(disable:##w))
#else
  #define HOU_PRAGMA_MSVC_WARNING_PUSH()
  #define HOU_PRAGMA_MSVC_WARNING_POP()
  #define HOU_PRAGMA_MSVC_WARNING_DISABLE(warning)
#endif
// clang-format on

#endif
