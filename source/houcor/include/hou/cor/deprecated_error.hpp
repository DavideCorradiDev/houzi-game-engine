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
 * \tparam FormattingVariables types of the formatting variables.
 *
 * \param file_path the file path to be included in the message.
 *
 * \param line the file line to be included in the message.
 *
 * \param message the format string for the error message.
 *
 * \param vars the variables used to generate the formatted string.
 *
 * \return the formatted error message.
 */
template <typename... FormattingVariables>
std::string deprecated_format_error_message(
  const std::string& file_path, int line, const std::string& message,
  const FormattingVariables&... vars);

}  // namespace hou



#define DEPRECATED_HOU_ERRMSG(...) \
  ::hou::deprecated_format_error_message(__FILE__, __LINE__, __VA_ARGS__)



#define DEPRECATED_HOU_TERMINATE(message) \
  do \
  { \
    std::cerr << message << std::endl; \
    std::terminate(); \
  } while(false)



#if defined(HOU_DISABLE_EXCEPTIONS)
#define DEPRECATED_HOU_THROW(ExceptionType, ...) \
  do \
  { \
    DEPRECATED_HOU_TERMINATE( \
      std::string(#ExceptionType) + std::string(u8" - ") \
      + std::string(ExceptionType(__VA_ARGS__).what())); \
  } while(false)
#else
#define DEPRECATED_HOU_THROW(ExceptionType, ...) \
  do \
  { \
    throw ExceptionType(__VA_ARGS__); \
  } while(false)
#endif



#define DEPRECATED_HOU_FATAL_ERROR(...) DEPRECATED_HOU_TERMINATE(DEPRECATED_HOU_ERRMSG(__VA_ARGS__))



#define DEPRECATED_HOU_FATAL_CHECK(condition, ...) \
  do \
  { \
    if(!(condition)) \
    { \
      DEPRECATED_HOU_FATAL_ERROR(__VA_ARGS__); \
    } \
  } while(false)



#if defined(NDEBUG)
#define HOU_FATAL_CHECK_DEV(condition, ...)
#else
#define HOU_FATAL_CHECK_DEV(condition, ...) \
  DEPRECATED_HOU_FATAL_CHECK(condition, __VA_ARGS__)
#endif



#define DEPRECATED_HOU_LOGIC_ERROR(...) \
  DEPRECATED_HOU_THROW(std::logic_error, DEPRECATED_HOU_ERRMSG(__VA_ARGS__))



#define DEPRECATED_HOU_LOGIC_CHECK(condition, ...) \
  do \
  { \
    if(!(condition)) \
    { \
      DEPRECATED_HOU_LOGIC_ERROR(__VA_ARGS__); \
    } \
  } while(false)



#if defined(NDEBUG)
#define DEPRECATED_HOU_LOGIC_CHECK_DEV(condition, ...)
#else
#define DEPRECATED_HOU_LOGIC_CHECK_DEV(condition, ...) \
  DEPRECATED_HOU_LOGIC_CHECK(condition, __VA_ARGS__)
#endif



#define DEPRECATED_HOU_RUNTIME_ERROR(...) \
  DEPRECATED_HOU_THROW(std::runtime_error, DEPRECATED_HOU_ERRMSG(__VA_ARGS__))



#define DEPRECATED_HOU_RUNTIME_CHECK(condition, ...) \
  do \
  { \
    if(!(condition)) \
    { \
      DEPRECATED_HOU_RUNTIME_ERROR(__VA_ARGS__); \
    } \
  } while(false)



#if defined(NDEBUG)
#define DEPRECATED_HOU_RUNTIME_CHECK_DEV(condition, ...)
#else
#define DEPRECATED_HOU_RUNTIME_CHECK_DEV(condition, ...) \
  DEPRECATED_HOU_RUNTIME_CHECK(condition, __VA_ARGS__)
#endif



#define DEPRECATED_HOU_EXPECT(condition) \
  DEPRECATED_HOU_LOGIC_CHECK( \
    condition, \
    get_text(::hou::cor_error::pre_condition) \
      + std::string(" (" #condition ")."))



#if defined(NDEBUG)
#define DEPRECATED_HOU_EXPECT_DEV(condition)
#else
#define DEPRECATED_HOU_EXPECT_DEV(condition) DEPRECATED_HOU_EXPECT(condition)
#endif



#define DEPRECATED_HOU_ENSURE(condition) \
  DEPRECATED_HOU_LOGIC_CHECK( \
    condition, \
    get_text(::hou::cor_error::post_condition) \
      + std::string(" (" #condition ")."))



#if defined(NDEBUG)
#define DEPRECATED_HOU_ENSURE_DEV(condition)
#else
#define DEPRECATED_HOU_ENSURE_DEV(condition) DEPRECATED_HOU_ENSURE(condition)
#endif



#define DEPRECATED_HOU_EXPECT_FATAL(condition) \
  DEPRECATED_HOU_FATAL_CHECK( \
    condition, \
    get_text(::hou::cor_error::pre_condition) \
      + std::string(" (" #condition ")."))



#if defined(NDEBUG)
#define DEPRECATED_HOU_EXPECT_FATAL_DEV(condition)
#else
#define DEPRECATED_HOU_EXPECT_FATAL_DEV(condition) DEPRECATED_HOU_EXPECT_FATAL(condition)
#endif



#define DEPRECATED_HOU_ENSURE_FATAL(condition) \
  DEPRECATED_HOU_FATAL_CHECK( \
    condition, \
    get_text(::hou::cor_error::post_condition) \
      + std::string(" (" #condition ")."))



#if defined(NDEBUG)
#define DEPRECATED_HOU_ENSURE_FATAL_DEV(condition)
#else
#define DEPRECATED_HOU_ENSURE_FATAL_DEV(condition) DEPRECATED_HOU_ENSURE_FATAL(condition)
#endif



#include "hou/cor/deprecated_error.inl"

#endif
