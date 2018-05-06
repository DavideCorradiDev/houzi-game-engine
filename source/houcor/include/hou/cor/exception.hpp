// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_EXCEPTION_HPP
#define HOU_COR_EXCEPTION_HPP

#include "hou/cor/basic_types.hpp"
#include "hou/cor/std_string.hpp"

#include "hou/cor/cor_export.hpp"

#include <memory>
#include <stdexcept>



namespace hou
{

namespace prv
{

/** Creates a properly formatted error message string.
 *
 * The error message string has the form "<path>:<line> - <message>".
 *
 * \param path the path to the source file where the error happened.
 *
 * \param line the line where the error happened.
 *
 * \param message the error message.
 *
 * \return the formatted error string.
 */
HOU_COR_API std::string format_error_message(
  const std::string& path, uint line, const std::string& message);
}  // namespace prv

/** Base class for all exceptions.
 */
class HOU_COR_API exception : public std::exception
{
public:
  /** Creates an exception object with the given path, line, and message.
   *
   * The exception stores a formatted error message internally.
   * The message is reference counted, therefore copying or moving an exception
   * object cannot throw.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the error message.
   */
  exception(const std::string& path, uint line, const std::string& message);

  /** Retrieves the exception error message.
   *
   * \return the exception error message.
   */
  const char* what() const noexcept final;

private:
  // The message string is reference counted to avoid allocation in case
  // of object copies.
  std::shared_ptr<std::string> m_message;
};

/** Prints the given message to the console error stream and terminates
 * execution.
 *
 * \param message the error message to be printed.
 */
void HOU_COR_API terminate(const std::string& message) noexcept;

}  // namespace hou



#define HOU_TERMINATE(message)                                                 \
  ::hou::terminate(                                                            \
    ::hou::prv::format_error_message(__FILE__, __LINE__, message));

#ifdef HOU_DISABLE_EXCEPTIONS

#define HOU_ERROR_STD_0(exception_type)                                        \
  do                                                                           \
  {                                                                            \
    ::hou::terminate(exception_type().what());                                 \
  } while(false)

#define HOU_ERROR_TEMPLATE(exception_type, ...)                                \
  do                                                                           \
  {                                                                            \
    ::hou::terminate(exception_type(__VA_ARGS__).what());                      \
  } while(false)

#else

#define HOU_ERROR_STD_0(exception_type)                                        \
  do                                                                           \
  {                                                                            \
    throw exception_type();                                                    \
  } while(false)

#define HOU_ERROR_TEMPLATE(exception_type, ...)                                \
  do                                                                           \
  {                                                                            \
    throw exception_type(__VA_ARGS__);                                         \
  } while(false)

#endif

#define HOU_ERROR_STD_N(exception_type, ...)                                   \
  HOU_ERROR_TEMPLATE(exception_type, __VA_ARGS__)

#define HOU_ERROR_0(exception_type)                                            \
  HOU_ERROR_TEMPLATE(exception_type, __FILE__, __LINE__)

#define HOU_ERROR_N(exception_type, ...)                                       \
  HOU_ERROR_TEMPLATE(exception_type, __FILE__, __LINE__, __VA_ARGS__)

#define HOU_CHECK_TEMPLATE(condition, failure_action)                          \
  do                                                                           \
  {                                                                            \
    if(!(condition))                                                           \
    {                                                                          \
      failure_action;                                                          \
    }                                                                          \
  } while(false)

#define HOU_ASSERT(statement, message)                                         \
  HOU_CHECK_TEMPLATE(statement, HOU_TERMINATE(message))

#define HOU_ASSERT_0(statement)                                                \
  HOU_CHECK_TEMPLATE(statement, HOU_TERMINATE(#statement))

#define HOU_CHECK_STD_0(condition, exception_type)                             \
  HOU_CHECK_TEMPLATE(condition, HOU_ERROR_STD_0(exception_type))

#define HOU_CHECK_STD_N(condition, exception_type, ...)                        \
  HOU_CHECK_TEMPLATE(condition, HOU_ERROR_STD_N(exception_type, __VA_ARGS__))

#define HOU_CHECK_0(condition, exception_type)                                 \
  HOU_CHECK_TEMPLATE(condition, HOU_ERROR_0(exception_type))

#define HOU_CHECK_N(condition, exception_type, ...)                            \
  HOU_CHECK_TEMPLATE(condition, HOU_ERROR_N(exception_type, __VA_ARGS__))

#ifdef NDEBUG
#define HOU_DEV_CHECK_TEMPLATE(condition, failure_action)
#else
#define HOU_DEV_CHECK_TEMPLATE(condition, failure_action)                      \
  HOU_CHECK_TEMPLATE(condition, failure_action)
#endif

#define HOU_DEV_ASSERT(statement, message)                                     \
  HOU_DEV_CHECK_TEMPLATE(statement, HOU_TERMINATE(message))

#define HOU_DEV_ASSERT_0(statement)                                            \
  HOU_DEV_CHECK_TEMPLATE(statement, HOU_TERMINATE(#statement))

#define HOU_DEV_CHECK_STD_0(condition, exception_type)                         \
  HOU_DEV_CHECK_TEMPLATE(condition, HOU_ERROR_STD_0(exception_type))

#define HOU_DEV_CHECK_STD_N(condition, exception_type, ...)                    \
  HOU_DEV_CHECK_TEMPLATE(                                                      \
    condition, HOU_ERROR_STD_N(exception_type, __VA_ARGS__))

#define HOU_DEV_CHECK_0(condition, exception_type)                             \
  HOU_DEV_CHECK_TEMPLATE(condition, HOU_ERROR_0(exception_type))

#define HOU_DEV_CHECK_N(condition, exception_type, ...)                        \
  HOU_DEV_CHECK_TEMPLATE(condition, HOU_ERROR_N(exception_type, __VA_ARGS__))

#ifdef HOU_DISABLE_EXCEPTIONS

#define HOU_DISABLE_EXCEPTIONS_BEGIN
#define HOU_DISABLE_EXCEPTIONS_END

#else

#define HOU_DISABLE_EXCEPTIONS_BEGIN                                           \
  try                                                                          \
  {
#define HOU_DISABLE_EXCEPTIONS_END                                             \
  }                                                                            \
  catch(const ::std::exception& ex)                                            \
  {                                                                            \
    HOU_TERMINATE(ex.what());                                                  \
  }

#endif

#endif
