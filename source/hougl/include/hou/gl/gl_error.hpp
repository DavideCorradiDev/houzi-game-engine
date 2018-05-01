// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_ERROR_HPP
#define HOU_GL_GL_ERROR_HPP

#include "hou/gl/gl_export.hpp"

#include <string>



namespace hou
{

enum class gl_error
{
  context_create,
  context_destroy,
  context_existence,
  context_lost,
  context_make_current,
  extensions_initialization,
  invalid_enum,
  invalid_framebuffer_operation,
  invalid_operation,
  invalid_ownership,
  invalid_value,
  out_of_memory,
  program_invalid_uniform,
  program_linking,
  shader_compilation,
  stack_overflow,
  stack_underflow,
  table_too_large,
  vertical_sync_set,
};

HOU_GL_API std::string get_text(gl_error ec);

}  // namespace hou

#endif
