// Houzi Multimedia Library
// Copyright (c) 2016-2017 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_CONFIG_HPP
#define HOU_CONFIG_HPP

// Values from CMakeLists.txt
#define HOU_VERSION_MAJOR 0
#define HOU_VERSION_MINOR 1
#define HOU_VERSION_PATCH 0

// OS symbols definition
#if defined(_WIN32)
  #define HOU_SYSTEM_WINDOWS
  #define UNICODE
  #if defined(__MINGW32__)
    #define HOU_COMPILER_MINGW
  #endif
#endif

// Define export statements
#if defined(HOU_STATIC)
  #define HOU_EXPORT
  #define HOU_IMPORT
#else
  #if defined(HOU_SYSTEM_WINDOWS)
    #define HOU_EXPORT __declspec(dllexport)
    #define HOU_IMPORT __declspec(dllimport)
  #else
    #if __GNUC__ >= 4
      #define HOU_EXPORT __attribute__((__visibility__("default")))
      #define HOU_IMPORT __attribute__((__visibility__("default")))
    #else
      #define HOU_EXPORT
      #define HOU_IMPORT
    #endif
  #endif
#endif

#endif

