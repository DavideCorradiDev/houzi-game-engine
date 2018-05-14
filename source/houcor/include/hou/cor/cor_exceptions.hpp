// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_EXCEPTIONS_HPP
#define HOU_COR_COR_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/** Overflow error.
 *
 * This exception is thrown when a numeric overflow happens.
 */
class HOU_COR_API overflow_error : public exception
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
  overflow_error(const std::string& path, uint line);
};

/** Overflow error.
 *
 * This exception is thrown when a numeric underflow happens.
 */
class HOU_COR_API underflow_error : public exception
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
  underflow_error(const std::string& path, uint line);
};

/** Out of range error.
 *
 * This exception is thrown when an index out of range is passed to a container
 * function.
 */
class HOU_COR_API out_of_range : public exception
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
  out_of_range(const std::string& path, uint line);
};

/** Bad union access error.
 *
 * This exception is thrown  when accessing a wrongly initialized union member.
 */
class HOU_COR_API bad_union_access : public exception
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
  bad_union_access(const std::string& path, uint line);
};

}  // namespace hou

#endif
