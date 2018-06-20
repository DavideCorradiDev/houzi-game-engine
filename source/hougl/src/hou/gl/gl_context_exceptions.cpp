// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_context_exceptions.hpp"



namespace hou
{

namespace gl
{

context_creation_error::context_creation_error(
  const std::string& path, uint line, const std::string& details)
  : exception(path, line,
      format_string(
        u8"Failed to create the OpenGL context.\n%s", details.c_str()))
{}



context_switch_error::context_switch_error(
  const std::string& path, uint line, const std::string& details)
  : exception(path, line,
      format_string(
        u8"Failed to switch the current OpenGL context.\n%s", details.c_str()))
{}

}  // namespace gl

}  // namespace hou

