// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GFX_EXCEPTIONS_HPP
#define HOU_GFX_GFX_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/gfx/gfx_export.hpp"



namespace hou
{

/** Font creation error.
 *
 * This exception is thrown when creating a font object fails.
 * This normally means that the font data is corrupted or in a wrong format.
 */
class HOU_GFX_API font_creation_error : public exception
{
public:
  /** Creates a font_creation_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  font_creation_error(const std::string& path, uint line);
};

/** Font destruction error.
 *
 * This exception is thrown when destructing a font object fails.
 */
class HOU_GFX_API font_destruction_error : public exception
{
public:
  /** Creates a font_destruction_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  font_destruction_error(const std::string& path, uint line);
};

}  // namespace hou

#endif
