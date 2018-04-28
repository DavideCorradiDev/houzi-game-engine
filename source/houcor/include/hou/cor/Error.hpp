// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_ERROR
#define HOU_COR_ERROR

#include "hou/cor/cor_export.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/cor_error.hpp"
#include "hou/cor/std_string.hpp"

#include <iostream>
#include <stdexcept>



// Error codes to be defined in case they are not.
#ifndef EPROTO
  #define EPROTO 134
#endif
#ifndef EOWNERDEAD
  #define EOWNERDEAD 133
#endif



namespace hou
{

/** Creates a string containing a formatted error message.
 *
 *  \tparam FormattingVariables types of the formatting variables.
 *  \param filePath the ph_file path to be included in the message.
 *  \param line the ph_file line to be included in the message.
 *  \param message the format string for the error message.
 *  \param vars the variables used to generate the formatted string.
 *  \return the formatted error message.
 */
template <typename... FormattingVariables>
  std::string format_error_message(const std::string& filePath, int line
  , const std::string& message, const FormattingVariables&... vars);

}



#define HOU_ERRMSG(...) \
  ::hou::format_error_message(__FILE__, __LINE__, __VA_ARGS__)



#define HOU_TERMINATE(message) \
  do { \
    std::cerr << message << std::endl; \
    std::terminate(); \
  } while(false)



#if defined(HOU_DISABLE_EXCEPTIONS)
  #define HOU_THROW(ExceptionType, ...) \
    do { \
      HOU_TERMINATE(std::string(#ExceptionType) + std::string(u8" - ") \
        + std::string(ExceptionType(__VA_ARGS__).what())); \
    } while(false)
#else
  #define HOU_THROW(ExceptionType, ...) \
    do { \
      throw ExceptionType(__VA_ARGS__); \
    } while(false)
#endif



#define HOU_FATAL_ERROR(...) \
  HOU_TERMINATE(HOU_ERRMSG(__VA_ARGS__))



#define HOU_FATAL_CHECK(condition, ...) \
  do { \
    if(!(condition)) \
    { \
      HOU_FATAL_ERROR(__VA_ARGS__); \
    } \
  } while(false)



#if defined(NDEBUG)
  #define HOU_FATAL_CHECK_DEV(condition, ...)
#else
  #define HOU_FATAL_CHECK_DEV(condition, ...) \
    HOU_FATAL_CHECK(condition, __VA_ARGS__)
#endif



#define HOU_LOGIC_ERROR(...) \
  HOU_THROW(std::logic_error, HOU_ERRMSG(__VA_ARGS__))



#define HOU_LOGIC_CHECK(condition, ...) \
  do { \
    if(!(condition)) \
    { \
      HOU_LOGIC_ERROR(__VA_ARGS__); \
    } \
  } while(false)



#if defined(NDEBUG)
  #define HOU_LOGIC_CHECK_DEV(condition, ...)
#else
  #define HOU_LOGIC_CHECK_DEV(condition, ...) \
    HOU_LOGIC_CHECK(condition, __VA_ARGS__)
#endif



#define HOU_RUNTIME_ERROR(...) \
  HOU_THROW(std::runtime_error, HOU_ERRMSG(__VA_ARGS__))



#define HOU_RUNTIME_CHECK(condition, ...) \
  do { \
    if(!(condition)) \
    { \
      HOU_RUNTIME_ERROR(__VA_ARGS__); \
    } \
  } while(false)




#if defined(NDEBUG)
  #define HOU_RUNTIME_CHECK_DEV(condition, ...)
#else
  #define HOU_RUNTIME_CHECK_DEV(condition, ...) \
    HOU_RUNTIME_CHECK(condition, __VA_ARGS__)
#endif



#define HOU_EXPECT(condition) \
  HOU_LOGIC_CHECK(condition \
    , get_text(::hou::cor_error::pre_condition) + std::string(" (" #condition ")."))



#if defined(NDEBUG)
  #define HOU_EXPECT_DEV(condition)
#else
  #define HOU_EXPECT_DEV(condition) HOU_EXPECT(condition)
#endif



#define HOU_ENSURE(condition) \
  HOU_LOGIC_CHECK(condition \
    , get_text(::hou::cor_error::post_condition) + std::string(" (" #condition ")."))



#if defined(NDEBUG)
  #define HOU_ENSURE_DEV(condition)
#else
  #define HOU_ENSURE_DEV(condition) HOU_ENSURE(condition)
#endif



#define HOU_EXPECT_FATAL(condition) \
  HOU_FATAL_CHECK(condition \
    , get_text(::hou::cor_error::pre_condition) + std::string(" (" #condition ")."))




#if defined(NDEBUG)
  #define HOU_EXPECT_FATAL_DEV(condition)
#else
  #define HOU_EXPECT_FATAL_DEV(condition) HOU_EXPECT_FATAL(condition)
#endif



#define HOU_ENSURE_FATAL(condition) \
  HOU_FATAL_CHECK(condition \
    , get_text(::hou::cor_error::post_condition) + std::string(" (" #condition ")."))



#if defined(NDEBUG)
  #define HOU_ENSURE_FATAL_DEV(condition)
#else
  #define HOU_ENSURE_FATAL_DEV(condition) HOU_ENSURE_FATAL(condition)
#endif



#include "hou/cor/Error.inl"

#endif

