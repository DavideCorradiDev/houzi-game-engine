// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_EXCEPTIONS_HPP
#define HOU_GL_GL_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/cor/basic_types.hpp"
#include "hou/cor/std_string.hpp"

#include "hou/gl/open_gl.hpp"

#include "hou/gl/gl_export.hpp"



namespace hou
{

namespace gl
{

class shared_object_handle;
class non_shared_object_handle;

class HOU_GL_API extension_initialization_error : public exception
{
public:
  extension_initialization_error(const std::string& path, uint line, int ec);
};

class HOU_GL_API context_creation_error : public exception
{
public:
  context_creation_error(const std::string& path, uint line);
};

class HOU_GL_API context_destruction_error : public exception
{
public:
  context_destruction_error(const std::string& path, uint line);
};

class HOU_GL_API context_switch_error : public exception
{
public:
  context_switch_error(const std::string& path, uint line);
};

class HOU_GL_API missing_context_error : public exception
{
public:
  missing_context_error(const std::string& path, uint line);
};

class HOU_GL_API invalid_context_error : public exception
{
public:
  invalid_context_error(const std::string& path, uint line);
};

class HOU_GL_API shader_compiler_error : public exception
{
public:
  shader_compiler_error(const std::string& path, uint line, GLenum shader_type,
    const std::string& message);
};

class HOU_GL_API shader_linker_error : public exception
{
public:
  shader_linker_error(
    const std::string& path, uint line, const std::string& message);
};

class HOU_GL_API invalid_uniform_error : public exception
{
public:
  invalid_uniform_error(
    const std::string& path, uint line, const std::string& uniform_name);
};

class HOU_GL_API vsync_error : public exception
{
public:
  vsync_error(const std::string& path, uint line);
};

class HOU_GL_API call_error : public exception
{
public:
  call_error(const std::string& path, uint line, GLenum ec);
};

void HOU_GL_API check_error(const std::string& path, uint line);
void HOU_GL_API check_context_existence(const std::string& path, uint line);
void HOU_GL_API check_context_ownership(
  const shared_object_handle& o, const std::string& path, uint line);
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
