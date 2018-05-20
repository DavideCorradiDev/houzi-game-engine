// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_PRAGMAS_HPP
#define HOU_COR_PRAGMAS_HPP

#include "hou/cor/cor_config.hpp"

// clang-format off
#if defined(HOU_COMPILER_MINGW)
  #define HOU_DO_PRAGMA(x) _Pragma(#x)
#elif defined(HOU_COMPILER_MSVC)
  #define HOU_DO_PRAGMA(x) __pragma(x)
#endif

#if defined(HOU_COMPILER_MINGW)
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
  #define HOU_PRAGMA_MSVC_WARNING_DISABLE(w)                             \
    HOU_DO_PRAGMA(warning(disable:##w))
#else
  #define HOU_PRAGMA_MSVC_WARNING_PUSH()
  #define HOU_PRAGMA_MSVC_WARNING_POP()
  #define HOU_PRAGMA_MSVC_WARNING_DISABLE(warning)
#endif

// clang-format on

#endif
