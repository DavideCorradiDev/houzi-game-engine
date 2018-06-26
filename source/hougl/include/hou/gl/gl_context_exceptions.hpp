// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_CONTEXT_EXCEPTIONS_HPP
#define HOU_GL_GL_CONTEXT_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace gl
{

/** Context creation error.
 *
 * This exception is thrown when creating an OpenGL context fails.
 */
class HOU_GL_API context_creation_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param details details about the error.
   *
   * \throws std::bad_alloc.
   */
  context_creation_error(
    const std::string& path, uint line, const std::string& details);
};

/** OpenGL context switch error.
 *
 * This exceptions is thrown when switching the current OpenGL context fails.
 */
class HOU_GL_API context_switch_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param details details about the error.
   *
   * \throws std::bad_alloc.
   */
  context_switch_error(
    const std::string& path, uint line, const std::string& details);
};

}  // namespace gl

}  // namespace hou

#endif
