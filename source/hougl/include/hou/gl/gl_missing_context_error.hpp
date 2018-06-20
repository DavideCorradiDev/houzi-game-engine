// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_MISSING_CONTEXT_ERROR_HPP
#define HOU_GL_GL_MISSING_CONTEXT_ERROR_HPP

#include "hou/cor/exception.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace gl
{

/** Missing OpenGL context error.
 *
 * This exception is thrown when an OpenGL call is made without a current
 * context.
 */
class HOU_GL_API missing_context_error : public exception
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
  missing_context_error(const std::string& path, uint line);
};

/** Checks if there is a current OpenGL context and throws an exception if not.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::gl::missing_context_error if there is no current OpenGL context.
 */
void HOU_GL_API check_context_existence(const std::string& path, uint line);

}  // namespace gl

}  // namespace hou



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
#define HOU_GL_CHECK_CONTEXT_EXISTENCE()                                       \
  ::hou::gl::check_context_existence(__FILE__, __LINE__)
#else
#define HOU_GL_CHECK_CONTEXT_EXISTENCE()
#endif

#endif
