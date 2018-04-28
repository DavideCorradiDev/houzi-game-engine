// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/GlCheck.hpp"

#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/GlObjectHandle.hpp"

#include "hou/cor/error.hpp"



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
      return get_text(GlError::ContextLost);
    case GL_INVALID_ENUM:
      return get_text(GlError::invalid_enum);
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return get_text(GlError::InvalidFramebufferOperation);
    case GL_INVALID_OPERATION:
      return get_text(GlError::InvalidOperation);
    case GL_INVALID_VALUE:
      return get_text(GlError::InvalidValue);
    case GL_OUT_OF_MEMORY:
      return get_text(GlError::OutOfMemory);
    case GL_STACK_OVERFLOW:
      return get_text(GlError::StackOverflow);
    case GL_STACK_UNDERFLOW:
      return get_text(GlError::StackUnderflow);
    case GL_TABLE_TOO_LARGE:
      return get_text(GlError::TableTooLarge);
    default:
      HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(err));
      return u8"";
  }
}

}



void checkError(const std::string& filename, int line)
{
  for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , getErrorMessage(err)));
  }
}



void checkContextExistence(const std::string& filename, int line)
{
  if(Context::getCurrent() == nullptr)
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , get_text(GlError::ContextExistence)));
  }
}



void checkContextOwnership(const SharedObjectHandle& object
  , const std::string& filename, int line)
{
  checkContextExistence(filename, line);
  if(Context::getCurrent()->getSharingGroupUid()
    != object.getOwningSharingGroupUid())
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , get_text(GlError::InvalidOwnership)));
  }
}



void checkContextOwnership(const NonSharedObjectHandle& object
  , const std::string& filename, int line)
{
  checkContextExistence(filename, line);
  if(Context::getCurrent()->get_uid()
    != object.getOwningContextUid())
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , get_text(GlError::InvalidOwnership)));
  }
}

}

}

