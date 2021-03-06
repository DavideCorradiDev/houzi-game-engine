// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_exceptions.hpp"



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
      return u8"invalid value";
    case GL_OUT_OF_MEMORY:
      return u8"out of memory";
    case GL_STACK_OVERFLOW:
      return u8"stack overflow";
    case GL_STACK_UNDERFLOW:
      return u8"stack underflow";
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
      return u8"fragment";
    case GL_GEOMETRY_SHADER:
      return u8"geometry";
    case GL_TESS_CONTROL_SHADER:
      return u8"tesselation control";
    case GL_TESS_EVALUATION_SHADER:
      return u8"tesselation evaluation";
    case GL_VERTEX_SHADER:
      return u8"vertex";
    default:
      return u8"unknown type";
  }
}

}  // namespace



vsync_error::vsync_error(
  const std::string& path, uint line, const std::string& details)
  : exception(path, line,
      format_string(
        u8"Failed to set the vertical sync mode.\n%s", details.c_str()))
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
      format_string(u8"The uniform '%s' was not defined in the shader program.",
        uniform_name.c_str()))
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

}  // namespace gl

}  // namespace hou
