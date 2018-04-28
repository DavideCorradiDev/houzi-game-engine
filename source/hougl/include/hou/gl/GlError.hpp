// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GL_GL_ERROR_HPP
#define HOU_GL_GL_ERROR_HPP

#include "hou/gl/GlExport.hpp"

#include <string>



namespace hou
{

enum class GlError
{
  ContextCreate,
  ContextDestroy,
  ContextExistence,
  ContextLost,
  ContextMakeCurrent,
  ExtensionsInitialization,
  invalid_enum,
  InvalidFramebufferOperation,
  InvalidOperation,
  InvalidOwnership,
  InvalidValue,
  OutOfMemory,
  ProgramInvalidUniform,
  ProgramLinking,
  ShaderCompilation,
  StackOverflow,
  StackUnderflow,
  TableTooLarge,
  VerticalSyncSet,
};

HOU_GL_API std::string get_text(GlError ec);

}

#endif

