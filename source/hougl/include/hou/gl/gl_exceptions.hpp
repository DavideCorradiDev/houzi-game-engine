// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_EXCEPTIONS_HPP
#define HOU_GL_GL_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_config.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace gl
{

/** Vertical sync error.
 *
 * This exception is thrown when setting the vertical sync mode failed.
 */
class HOU_GL_API vsync_error : public exception
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
  vsync_error(const std::string& path, uint line, const std::string& details);
};

/** Shader compiler error.
 *
 * This exception is thrown when compiling a shader has failed.
 */
class HOU_GL_API shader_compiler_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param shader_type the shader type.
   *
   * \param message the compiler error message.
   *
   * \throws std::bad_alloc.
   */
  shader_compiler_error(const std::string& path, uint line, GLenum shader_type,
    const std::string& message);
};

/** Shader linker error.
 *
 * This exception is thrown when linking a shader program has failed.
 */
class HOU_GL_API shader_linker_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the linker error message.
   *
   * \throws std::bad_alloc.
   */
  shader_linker_error(
    const std::string& path, uint line, const std::string& message);
};

/** Invalid uniform error.
 *
 * This exception is thrown when trying to access a non-existing uniform in
 * a shader program.
 */
class HOU_GL_API invalid_uniform_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param uniform_name the name of the uniform.
   *
   * \throws std::bad_alloc.
   */
  invalid_uniform_error(
    const std::string& path, uint line, const std::string& uniform_name);
};

/** OpenGL call error.
 *
 * This exception is thrown when an OpenGL call fails.
 * This is normally a programmer error and execution should be terminated.
 */
class HOU_GL_API call_error : public exception
{
public:
  /** Constructor.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
   *
   * \throws std::bad_alloc.
   */
  call_error(const std::string& path, uint line, GLenum ec);
};

/** Checks if an OpenGL call has failed and throws an exception in case.
 *
 * \param path the source file path to be written in the exception in case of
 * an error.
 *
 * \param line the source file line to be written in the exception in case of
 * an error.
 *
 * \throws hou::gl::call_error if a previous OpenGL call has failed.
 */
void HOU_GL_API check_error(const std::string& path, uint line);

}  // namespace gl

}  // namespace hou



#ifdef HOU_ENABLE_GL_ERROR_CHECKS
#define HOU_GL_CHECK_ERROR() ::hou::gl::check_error(__FILE__, __LINE__)
#else
#define HOU_GL_CHECK_ERROR()
#endif

#endif
