// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_missing_context_error.hpp"

#include "hou/gl/gl_context.hpp"



namespace hou
{

namespace gl
{

missing_context_error::missing_context_error(const std::string& path, uint line)
  : exception(path, line, u8"No current OpenGL context.")
{}



void check_context_existence(const std::string& path, uint line)
{
  if(context::get_current() == nullptr)
  {
    HOU_ERROR_STD_N(missing_context_error, path, line);
  }
}

}  // namespace gl

}  // namespace hou
