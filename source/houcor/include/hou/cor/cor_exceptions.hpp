// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_COR_COR_EXCEPTIONS_HPP
#define HOU_COR_COR_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/cor_config.hpp"



namespace hou
{

/**
 * Overflow error.
 *
 * This exception is thrown when a numeric overflow happens.
 */
class HOU_COR_API overflow_error : public exception
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  overflow_error(const std::string& path, uint line);
};

/**
 * Overflow error.
 *
 * This exception is thrown when a numeric underflow happens.
 */
class HOU_COR_API underflow_error : public exception
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  underflow_error(const std::string& path, uint line);
};

/**
 * Out of range error.
 *
 * This exception is thrown when an index out of range is passed to a container
 * function.
 */
class HOU_COR_API out_of_range : public exception
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  out_of_range(const std::string& path, uint line);
};

/**
 * Bad union access error.
 *
 * This exception is thrown  when accessing a wrongly initialized union member.
 */
class HOU_COR_API bad_union_access : public exception
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  bad_union_access(const std::string& path, uint line);
};

/**
 * Narrowing cast error.
 *
 * This exception is thrown in case of narrowing casts.
 */
class HOU_COR_API narrowing_error : public exception
{
public:
  /**
   * Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \throws std::bad_alloc.
   */
  narrowing_error(const std::string& path, uint line);
};



/**
 * Module initialization error.
 *
 * This exception is thrown when the initialization of a library module has
 * failed.
 */
class HOU_COR_API module_initialization_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param module_name the name of the module.
   *
   * \throws std::bad_alloc.
   */
  module_initialization_error(
    const std::string& path, uint line, const std::string& module_name);
};



/**
 * Unsupported feature error.
 *
 * This exception is thrown when a specific feature is not supported.
 */
class HOU_COR_API unsupported_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param details a string with additional details.
   *
   * \throws std::bad_alloc.
   */
  unsupported_error(
    const std::string& path, uint line, const std::string& details);
};



/**
 * Invalid enumeration value.
 *
 * This exception is thrown when an invalid enumeration value is used.
 */
class HOU_COR_API invalid_enum : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param value the invalid enumeration value.
   *
   * \throws std::bad_alloc.
   */
  invalid_enum(const std::string& path, uint line, int value);
};

}  // namespace hou

#endif
