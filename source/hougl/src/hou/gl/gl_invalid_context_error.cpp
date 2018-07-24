// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_invalid_context_error.hpp"

#include "hou/gl/gl_object_handle.hpp"



namespace hou
{

namespace gl
{

invalid_context_error::invalid_context_error(const std::string& path, uint line)
  : exception(
      path, line, u8"The current OpenGL context does not own the object.")
{}



void check_context_ownership(
  const shared_object_handle& object, const std::string& path, uint line)
{
  if(context::get_current()->get_sharing_group_uid()
    != object.get_owning_sharing_group_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}



void check_context_ownership(
  const non_shared_object_handle& object, const std::string& path, uint line)
{
  if(context::get_current()->get_uid() != object.get_owning_context_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}

}  // namespace gl

}  // namespace hou
