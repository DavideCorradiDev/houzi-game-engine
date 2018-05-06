// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_ASSERTIONS_HPP
#define HOU_COR_ASSERTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_export.hpp"



namespace hou
{

/** Precondition violation error.
 *
 * This exception is thrown when a function precondition has been violated.
 * This reflects a programming error, and exection should be aborted.
 */
class HOU_COR_API precondition_violation : public exception
{
public:
  /** Creates an precondition_violation object with the given path, line, and
   * message.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the error message.
   */
  precondition_violation(const std::string& path, uint line);
};

/** Postcondition violation error.
 *
 * This exception is thrown when a function postcondition has been violated.
 * This reflects a programming error, and exection should be aborted.
 */
class HOU_COR_API postcondition_violation : public exception
{
public:
  /** Creates an postcondition_violation object with the given path, line, and
   * message.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the error message.
   */
  postcondition_violation(const std::string& path, uint line);
};

/** Invariant violation error.
 *
 * This exception is thrown when an invariant has been violated.
 * This reflects a programming error, and exection should be aborted.
 */
class HOU_COR_API invariant_violation : public exception
{
public:
  /** Creates an invariant_violation object with the given path, line, and
   * message.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the error message.
   */
  invariant_violation(const std::string& path, uint line);
};




/** Unreachable code error.
 *
 * This exception is thrown when an unreachable code path has been reached.
 * This reflects a programming error, and exection should be aborted.
 */
class HOU_COR_API unreachable_error : public exception
{
public:
  /** Creates an unreachable_error object with the given path, line, and
   * message.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the error message.
   */
  unreachable_error(const std::string& path, uint line);
};

}  // namespace hou

#define HOU_PRECOND(condition) HOU_CHECK_0(condition, precondition_violation)

#define HOU_DEV_PRECOND(condition)                                             \
  HOU_DEV_CHECK_0(condition, precondition_violation)

#define HOU_POSTCOND(condition) HOU_CHECK_0(condition, postcondition_violation)

#define HOU_DEV_POSTCOND(condition)                                            \
  HOU_DEV_CHECK_0(condition, postcondition_violation)

#define HOU_INVARIANT(condition) HOU_CHECK_0(condition, invariant_violation)

#define HOU_DEV_INVARIANT(condition)                                           \
  HOU_DEV_CHECK_0(condition, invariant_violation)

#define HOU_UNREACHABLE() HOU_ERROR_0(unreachable_error)

#endif
