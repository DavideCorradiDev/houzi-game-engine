// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/gl/GlError.hpp"



namespace hou
{

std::string getText(GlError ec)
{
  switch(ec)
  {
    case GlError::ContextCreate:
      return u8"Error creating GL Context.";
    case GlError::ContextDestroy:
      return u8"Error destroying GL Context.";
    case GlError::ContextExistence:
      return u8"No current GL Context.";
    case GlError::ContextLost:
      return u8"GL Context lost.";
    case GlError::ContextMakeCurrent:
      return u8"Error setting current GL Context.";
    case GlError::ExtensionsInitialization:
      return u8"Failed to initialize GL extensions (error code: %d).";
    case GlError::InvalidEnum:
      return u8"Invalid GL enum.";
    case GlError::InvalidFramebufferOperation:
      return u8"Invalid GL Framebuffer operation.";
    case GlError::InvalidOperation:
      return u8"Invalid GL operation";
    case GlError::InvalidOwnership:
      return u8"Current GL context does not own object.";
    case GlError::InvalidValue:
      return u8"Invalid GL value.";
    case GlError::OutOfMemory:
      return u8"GL out of memory.";
    case GlError::ProgramInvalidUniform:
      return u8"Invalid GL Program uniform '%s'.";
    case GlError::ProgramLinking:
      return u8"Error linking GL Program:\n%s";
    case GlError::ShaderCompilation:
      return u8"Error compiling GL %s Shader:\n%s";
    case GlError::StackOverflow:
      return u8"GL stack overflow.";
    case GlError::StackUnderflow:
      return u8"GL stack underflow.";
    case GlError::TableTooLarge:
      return u8"GL table too large.";
    case GlError::VerticalSyncSet:
      return u8"Failed to set Vertical Sync mode.";
    default:
      return u8"";
  }
}

}

