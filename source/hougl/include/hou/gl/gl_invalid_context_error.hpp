// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_INVALID_CONTEXT_ERROR_HPP
#define HOU_GL_GL_INVALID_CONTEXT_ERROR_HPP

#include "hou/cor/exception.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace gl
{

class shared_object_handle;
class non_shared_object_handle;

/** Invalid OpenGL context error.
 *
 * This exception is thrown when an OpenGL call is made using an OpenGL object
 * which is not owned by the current context.
 */
class HOU_GL_API invalid_context_error : public exception
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
  invalid_context_error(const std::string& path, uint line);
};

/** Checks if the object is owned by the current context, and throws an
 * exception if it is not.
 *
 * \param o the object whose ownership has to be checked.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::gl::invalid_context_error if the current OpenGL context does
 * not own the object.
 */
void HOU_GL_API check_context_ownership(
  const shared_object_handle& o, const std::string& path, uint line);

/** Checks if the object is owned by the current context, and throws an
 * exception if it is not.
 *
 * \param o the object whose ownership has to be checked.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::gl::invalid_context_error if the current OpenGL context does
 * not own the object.
 */
void HOU_GL_API check_context_ownership(
  const non_shared_object_handle& o, const std::string& path, uint line);

}  // namespace gl

}  // namespace hou



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
#define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle)                           \
  ::hou::gl::check_context_ownership(objectHandle, __FILE__, __LINE__)
#else
#define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#endif

#endif
