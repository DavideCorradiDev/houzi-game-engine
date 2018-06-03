// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_ASSERTIONS_HPP
#define HOU_COR_ASSERTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/** Precondition violation error.
 *
 * This exception is thrown when a function precondition has been violated.
 * This reflects a programming error, and exection should be terminated.
 */
class HOU_COR_API precondition_violation : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  precondition_violation(const std::string& path, uint line);
};

/** Postcondition violation error.
 *
 * This exception is thrown when a function postcondition has been violated.
 * This reflects a programming error, and exection should be terminated.
 */
class HOU_COR_API postcondition_violation : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  postcondition_violation(const std::string& path, uint line);
};

/** Invariant violation error.
 *
 * This exception is thrown when an invariant has been violated.
 * This reflects a programming error, and exection should be terminated.
 */
class HOU_COR_API invariant_violation : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  invariant_violation(const std::string& path, uint line);
};

}  // namespace hou

#define HOU_PRECOND(condition)                                                 \
  HOU_CHECK_0(condition, ::hou::precondition_violation)

#define HOU_POSTCOND(condition)                                                \
  HOU_CHECK_0(condition, ::hou::postcondition_violation)

#define HOU_INVARIANT(condition)                                               \
  HOU_CHECK_0(condition, ::hou::invariant_violation)

#endif
