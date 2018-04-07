// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlCheck.hpp"

#include "hou/gl/GlContext.hpp"
#include "hou/gl/GlError.hpp"
#include "hou/gl/GlObjectHandle.hpp"

#include "hou/cor/Error.hpp"



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
      return getText(GlError::ContextLost);
    case GL_INVALID_ENUM:
      return getText(GlError::InvalidEnum);
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return getText(GlError::InvalidFramebufferOperation);
    case GL_INVALID_OPERATION:
      return getText(GlError::InvalidOperation);
    case GL_INVALID_VALUE:
      return getText(GlError::InvalidValue);
    case GL_OUT_OF_MEMORY:
      return getText(GlError::OutOfMemory);
    case GL_STACK_OVERFLOW:
      return getText(GlError::StackOverflow);
    case GL_STACK_UNDERFLOW:
      return getText(GlError::StackUnderflow);
    case GL_TABLE_TOO_LARGE:
      return getText(GlError::TableTooLarge);
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(err));
      return u8"";
  }
}

}



void checkError(const std::string& filename, int line)
{
  for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getErrorMessage(err)));
  }
}



void checkContextExistence(const std::string& filename, int line)
{
  if(Context::getCurrent() == nullptr)
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getText(GlError::ContextExistence)));
  }
}



void checkContextOwnership(const SharedObjectHandle& object
  , const std::string& filename, int line)
{
  checkContextExistence(filename, line);
  if(Context::getCurrent()->getSharingGroupUid()
    != object.getOwningSharingGroupUid())
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getText(GlError::InvalidOwnership)));
  }
}



void checkContextOwnership(const NonSharedObjectHandle& object
  , const std::string& filename, int line)
{
  checkContextExistence(filename, line);
  if(Context::getCurrent()->getUid()
    != object.getOwningContextUid())
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getText(GlError::InvalidOwnership)));
  }
}

}

}

