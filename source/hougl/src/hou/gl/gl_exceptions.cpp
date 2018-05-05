// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_exceptions.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_object_handle.hpp"



namespace hou
{

namespace gl
{

namespace
{

std::string get_error_message(GLenum err);
std::string get_shader_type_name(GLenum shader_type);

std::string get_error_message(GLenum err)
{
  switch(err)
  {
    case GL_CONTEXT_LOST:
      return u8"context lost";
    case GL_INVALID_ENUM:
      return u8"invalid enum";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return u8"invalid framebuffer operation";
    case GL_INVALID_OPERATION:
      return u8"invalid operation";
    case GL_INVALID_VALUE:
      return u8"invalud value";
    case GL_OUT_OF_MEMORY:
      return u8"out of memory";
    case GL_STACK_OVERFLOW:
      return u8"stack overflow";
    case GL_STACK_UNDERFLOW:
      return u8"stack underflow";
    case GL_TABLE_TOO_LARGE:
      return u8"table too large";
    default:
      return u8"unknown error";
  }
}

std::string get_shader_type_name(GLenum shader_type)
{
  switch(shader_type)
  {
    case GL_COMPUTE_SHADER:
      return u8"compute";
    case GL_FRAGMENT_SHADER:
      return u8"Fragment";
    case GL_GEOMETRY_SHADER:
      return u8"geometry";
    case GL_TESS_CONTROL_SHADER:
      return u8"tess control";
    case GL_TESS_EVALUATION_SHADER:
      return u8"tess evaluation";
    case GL_VERTEX_SHADER:
      return u8"vertex";
    default:
      return u8"unknown type";
  }
}

}  // namespace



extension_initialization_error::extension_initialization_error(
  const std::string& path, uint line, int ec)
  : exception(path, line,
      format_string(
        u8"Failed to initialize the OpenGL extensions (error code %d).", ec))
{}



context_creation_error::context_creation_error(
  const std::string& path, uint line)
  : exception(path, line, u8"Failed to create the OpenGL context.")
{}



context_destruction_error::context_destruction_error(
  const std::string& path, uint line)
  : exception(path, line, u8"Failed to destroy the OpenGL context.")
{}



context_switch_error::context_switch_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to switch the current OpenGL context.")
{}



missing_context_error::missing_context_error(const std::string& path, uint line)
  : exception(path, line, u8"No current OpenGL context.")
{}



invalid_context_error::invalid_context_error(const std::string& path, uint line)
  : exception(
      path, line, u8"The current OpenGL context does not own the object.")
{}



shader_compiler_error::shader_compiler_error(const std::string& path, uint line,
  GLenum shader_type, const std::string& message)
  : exception(path, line,
      format_string(u8"Error compiling OpenGL %s shader:\n%s",
        get_shader_type_name(shader_type).c_str(), message.c_str()))
{}



shader_linker_error::shader_linker_error(
  const std::string& path, uint line, const std::string& message)
  : exception(path, line,
      format_string(
        u8"Error linking OpenGL shader program:\n%s", message.c_str()))
{}



invalid_uniform_error::invalid_uniform_error(
  const std::string& path, uint line, const std::string& uniform_name)
  : exception(path, line,
      format_string(
        u8"Invalid OpenGL program uniform '%s'.", uniform_name.c_str()))
{}



vsync_error::vsync_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to change vertical sync mode.")
{}



call_error::call_error(const std::string& path, uint line, GLenum ec)
  : exception(path, line,
      format_string(
        u8"OpenGL error with code %d: %s.", ec, get_error_message(ec).c_str()))
{}



void check_error(const std::string& path, uint line)
{
  for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
  {
    HOU_ERROR_STD_N(call_error, path, line, err);
  }
}



void check_context_existence(const std::string& path, uint line)
{
  if(context::get_current() == nullptr)
  {
    HOU_ERROR_STD_N(missing_context_error, path, line);
  }
}



void check_context_ownership(
  const shared_object_handle& object, const std::string& path, uint line)
{
  check_context_existence(path, line);
  if(context::get_current()->get_sharing_group_uid()
    != object.get_owning_sharing_group_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}



void check_context_ownership(
  const non_shared_object_handle& object, const std::string& path, uint line)
{
  check_context_existence(path, line);
  if(context::get_current()->get_uid() != object.get_owning_context_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}

}  // namespace gl

}  // namespace hou
