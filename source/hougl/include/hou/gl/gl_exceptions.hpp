// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_EXCEPTIONS_HPP
#define HOU_GL_GL_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_export.hpp"

#include "hou/cor/std_string.hpp"



namespace hou
{

namespace gl
{

class shared_object_handle;
class non_shared_object_handle;

/** Extension initalization error.
 *
 * This exception is thrown when initializing the OpenGL extensions fails.
 */
class HOU_GL_API extension_initialization_error : public exception
{
public:
  /** Creates an extension_initialization_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
   */
  extension_initialization_error(const std::string& path, uint line, int ec);
};

/** Context creation error.
 *
 * This exception is thrown when creating an OpenGL context fails.
 */
class HOU_GL_API context_creation_error : public exception
{
public:
  /** Creates a context_creation_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  context_creation_error(const std::string& path, uint line);
};

/** Context destruction error.
 *
 * This exception is thrown when destroying an OpenGL context fails.
 */
class HOU_GL_API context_destruction_error : public exception
{
public:
  /** Creates a context_destruction_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  context_destruction_error(const std::string& path, uint line);
};

/** OpenGL context switch error.
 *
 * This exceptions is thrown when switching the current OpenGL context fails.
 */
class HOU_GL_API context_switch_error : public exception
{
public:
  /** Creates a context_switch_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  context_switch_error(const std::string& path, uint line);
};

/** Missing OpenGL context error.
 *
 * This exception is thrown when an OpenGL call is made without a current
 * context.
 */
class HOU_GL_API missing_context_error : public exception
{
public:
  /** Creates a missing_context_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  missing_context_error(const std::string& path, uint line);
};

/** Invalid OpenGL context error.
 *
 * This exception is thrown when an OpenGL call is made using an OpenGL object
 * which is not owned by the current context.
 */
class HOU_GL_API invalid_context_error : public exception
{
public:
  /** Creates an invalid_context_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  invalid_context_error(const std::string& path, uint line);
};

/** Shader compiler error.
 *
 * This exception is thrown when compiling a shader has failed.
 */
class HOU_GL_API shader_compiler_error : public exception
{
public:
  /** Creates a shader_compiler_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param shader_type the shader type.
   *
   * \param message the compiler error message.
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
  /** Creates a shader_linker_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param message the linker error message.
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
  /** Creates an invalid_uniform_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param uniform_name the name of the uniform.
   */
  invalid_uniform_error(
    const std::string& path, uint line, const std::string& uniform_name);
};

/** Vertical sync error.
 *
 * This exception is thrown when setting the vertical sync mode failed.
 */
class HOU_GL_API vsync_error : public exception
{
public:
  /** Creates a vsync_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   */
  vsync_error(const std::string& path, uint line);
};

/** OpenGL call error.
 *
 * This exception is thrown when an OpenGL call fails.
 * This is normally a programmer error and execution should be terminated.
 */
class HOU_GL_API call_error : public exception
{
public:
  /** Creates a call_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param ec the error code.
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

/** Checks if the object is owned by the current context, and throws an exception
 * if it is not.
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

/** Checks if the object is owned by the current context, and throws an exception
 * if it is not.
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
#define HOU_GL_CHECK_ERROR() ::hou::gl::check_error(__FILE__, __LINE__)
#else
#define HOU_GL_CHECK_ERROR()
#endif



#ifdef HOU_ENABLE_GL_CONTEXT_EXISTENCE_CHECKS
#define HOU_GL_CHECK_CONTEXT_EXISTENCE()                                       \
  ::hou::gl::check_context_existence(__FILE__, __LINE__)
#else
#define HOU_GL_CHECK_CONTEXT_EXISTENCE()
#endif



#ifdef HOU_ENABLE_GL_CONTEXT_OWNERSHIP_CHECKS
#define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle)                           \
  ::hou::gl::check_context_ownership(objectHandle, __FILE__, __LINE__)
#else
#define HOU_GL_CHECK_CONTEXT_OWNERSHIP(objectHandle)
#endif

#endif
