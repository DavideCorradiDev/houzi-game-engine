// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_MTH_MTH_EXCEPTIONS_HPP
#define HOU_MTH_MTH_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/mth/mth_config.hpp"



namespace hou
{

/**
 * Inversion error.
 *
 * Thrown when trying to invert a non-invertible object.
 */
class HOU_MTH_API inversion_error : public exception
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
  inversion_error(const std::string& path, uint line);
};

}  // namespace hou

#endif
