// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_ASSERTIONS_HPP
#define HOU_COR_ASSERTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/**
 * Assertion violation error.
 *
 * This exception is the base class for all exception classes used for
 * assertions.
 */
class HOU_COR_API assertion_violation : public exception
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the error message condition.
   *
   * \param condition the violated condition.
   *
   * \throws std::bad_alloc.
   */
  assertion_violation(const std::string& path, uint line,
    const std::string& message, const std::string& condition);
};

/**
 * Precondition violation error.
 *
 * This exception is thrown when a function precondition has been violated.
 * This reflects a programming error, and exection should be terminated.
 */
class HOU_COR_API precondition_violation : public assertion_violation
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param condition the violated condition.
   *
   * \throws std::bad_alloc.
   */
  precondition_violation(
    const std::string& path, uint line, const std::string& condition);
};

/**
 * Postcondition violation error.
 *
 * This exception is thrown when a function postcondition has been violated.
 * This reflects a programming error, and exection should be terminated.
 */
class HOU_COR_API postcondition_violation : public assertion_violation
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param condition the violated condition.
   *
   * \throws std::bad_alloc.
   */
  postcondition_violation(
    const std::string& path, uint line, const std::string& condition);
};

/**
 * Invariant violation error.
 *
 * This exception is thrown when an invariant has been violated.
 * This reflects a programming error, and exection should be terminated.
 */
class HOU_COR_API invariant_violation : public assertion_violation
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param condition the violated condition.
   *
   * \throws std::bad_alloc.
   */
  invariant_violation(
    const std::string& path, uint line, const std::string& condition);
};

}  // namespace hou

#define HOU_PRECOND(condition)                                                 \
  HOU_CHECK_N(condition, ::hou::precondition_violation, #condition)

#define HOU_POSTCOND(condition)                                                \
  HOU_CHECK_N(condition, ::hou::postcondition_violation, #condition)

#define HOU_INVARIANT(condition)                                               \
  HOU_CHECK_N(condition, ::hou::invariant_violation, #condition)

#endif
