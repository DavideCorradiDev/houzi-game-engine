// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_SYS_WIN_WIN_ERROR_HPP
#define HOU_SYS_WIN_WIN_ERROR_HPP

#include "hou/sys/SysExport.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/error.hpp"



namespace hou
{

template <typename... FormattingVariables>
  std::string formatWinErrorMessage(std::string filename, int line
    , std::string message, FormattingVariables... vars);

HOU_SYS_API std::string getLastWinErrorMessage();

}



#define HOU_WIN_ERRMSG(...) \
  hou::formatWinErrorMessage(__FILE__, __LINE__, __VA_ARGS__)



#define HOU_WIN_FATAL_ERROR(...) \
  HOU_TERMINATE(HOU_WIN_ERRMSG(__VA_ARGS__))



#define HOU_WIN_FATAL_CHECK(condition, ...) \
  do { \
    if(!(condition)) \
    { \
      HOU_WIN_FATAL_ERROR(__VA_ARGS__); \
    } \
  } while(false)




#if defined(NDEBUG)
  #define HOU_WIN_FATAL_CHECK_DEV(condition, ...)
#else
  #define HOU_WIN_FATAL_CHECK_DEV(condition, ...) \
    HOU_WIN_FATAL_CHECK(condition, __VA_ARGS__)
#endif



#define HOU_WIN_LOGIC_ERROR(...) \
  HOU_THROW(std::logic_error, HOU_WIN_ERRMSG(__VA_ARGS__))



#define HOU_WIN_LOGIC_CHECK(condition, ...) \
  do { \
    if(!(condition)) \
    { \
      HOU_WIN_LOGIC_ERROR(__VA_ARGS__); \
    } \
  } while(false)



#if defined(NDEBUG)
  #define HOU_WIN_LOGIC_CHECK_DEV(condition, ...)
#else
  #define HOU_WIN_LOGIC_CHECK_DEV(condition, ...) \
    HOU_WIN_LOGIC_CHECK(condition, __VA_ARGS__)
#endif



#define HOU_WIN_RUNTIME_ERROR(...) \
  HOU_THROW(std::runtime_error, HOU_WIN_ERRMSG(__VA_ARGS__))



#define HOU_WIN_RUNTIME_CHECK(condition, ...) \
  do { \
    if(!(condition)) \
    { \
      HOU_WIN_RUNTIME_ERROR(__VA_ARGS__); \
    } \
  } while(false)




#if defined(NDEBUG)
  #define HOU_WIN_RUNTIME_CHECK_DEV(condition, ...)
#else
  #define HOU_WIN_RUNTIME_CHECK_DEV(condition, ...) \
    HOU_WIN_RUNTIME_CHECK(condition, __VA_ARGS__)
#endif



#define HOU_WIN_EXPECT(condition) \
  HOU_LOGIC_CHECK(condition \
    , get_text(hou::cor_error::pre_condition) + std::string(" (" #condition ")."))



#if defined(NDEBUG)
  #define HOU_WIN_EXPECT_DEV(condition)
#else
  #define HOU_WIN_EXPECT_DEV(condition) HOU_WIN_EXPECT(condition)
#endif



#define HOU_WIN_ENSURE(condition) \
  HOU_WIN_LOGIC_CHECK(condition \
    , get_text(hou::cor_error::post_condition) + std::string(" (" #condition ")."))



#if defined(NDEBUG)
  #define HOU_WIN_ENSURE_DEV(condition)
#else
  #define HOU_WIN_ENSURE_DEV(condition) HOU_WIN_ENSURE(condition)
#endif



#include "hou/sys/win/WinError.inl"

#endif

