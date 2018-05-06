// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_EXCEPTIONS_HPP
#define HOU_COR_COR_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_export.hpp"



namespace hou
{

/** Overflow error.
 *
 * This exception is thrown when a numeric overflow happens.
 */
class HOU_COR_API overflow_error : public exception
{
public:
  /** Creates an overflow_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
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
  /** Creates an underflow_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  underflow_error(const std::string& path, uint line);
};

}  // namespace hou

#endif
