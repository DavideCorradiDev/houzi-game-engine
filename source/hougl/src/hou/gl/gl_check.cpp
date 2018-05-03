// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_check.hpp"

#include "hou/gl/gl_context.hpp"
#include "hou/gl/gl_error.hpp"
#include "hou/gl/gl_object_handle.hpp"

#include "hou/cor/deprecated_error.hpp"



namespace hou
{

namespace gl
{

namespace
{

std::string getErrorMessage(GLenum err);

std::string getErrorMessage(GLenum err)
{
  switch(err)
  {
    case GL_CONTEXT_LOST:
      return get_text(gl_error::context_lost);
    case GL_INVALID_ENUM:
      return get_text(gl_error::invalid_enum);
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return get_text(gl_error::invalid_framebuffer_operation);
    case GL_INVALID_OPERATION:
      return get_text(gl_error::invalid_operation);
    case GL_INVALID_VALUE:
      return get_text(gl_error::invalid_value);
    case GL_OUT_OF_MEMORY:
      return get_text(gl_error::out_of_memory);
    case GL_STACK_OVERFLOW:
      return get_text(gl_error::stack_overflow);
    case GL_STACK_UNDERFLOW:
      return get_text(gl_error::stack_underflow);
    case GL_TABLE_TOO_LARGE:
      return get_text(gl_error::table_too_large);
    default:
      DEPRECATED_HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(err));
      return u8"";
  }
}

}



void check_error(const std::string& filename, int line)
{
  for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
  {
    DEPRECATED_HOU_THROW(std::logic_error, deprecated_format_error_message(filename, line
      , getErrorMessage(err)));
  }
}



void check_context_existence(const std::string& filename, int line)
{
  if(context::get_current() == nullptr)
  {
    DEPRECATED_HOU_THROW(std::logic_error, deprecated_format_error_message(filename, line
      , get_text(gl_error::context_existence)));
  }
}



void check_context_ownership(const shared_object_handle& object
  , const std::string& filename, int line)
{
  check_context_existence(filename, line);
  if(context::get_current()->get_sharing_group_uid()
    != object.get_owning_sharing_group_uid())
  {
    DEPRECATED_HOU_THROW(std::logic_error, deprecated_format_error_message(filename, line
      , get_text(gl_error::invalid_ownership)));
  }
}



void check_context_ownership(const non_shared_object_handle& object
  , const std::string& filename, int line)
{
  check_context_existence(filename, line);
  if(context::get_current()->get_uid()
    != object.get_owning_context_uid())
  {
    DEPRECATED_HOU_THROW(std::logic_error, deprecated_format_error_message(filename, line
      , get_text(gl_error::invalid_ownership)));
  }
}

}

}

