// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_error.hpp"



namespace hou
{

std::string get_text(gl_error ec)
{
  switch(ec)
  {
    case gl_error::context_create:
      return u8"Error creating GL context.";
    case gl_error::context_destroy:
      return u8"Error destroying GL context.";
    case gl_error::context_existence:
      return u8"No current GL context.";
    case gl_error::context_lost:
      return u8"GL context lost.";
    case gl_error::context_make_current:
      return u8"Error setting current GL context.";
    case gl_error::extensions_initialization:
      return u8"Failed to initialize GL extensions (error code: %d).";
    case gl_error::invalid_enum:
      return u8"Invalid GL enum.";
    case gl_error::invalid_framebuffer_operation:
      return u8"Invalid GL Framebuffer operation.";
    case gl_error::invalid_operation:
      return u8"Invalid GL operation";
    case gl_error::invalid_ownership:
      return u8"Current GL ph_context does not own object.";
    case gl_error::invalid_value:
      return u8"Invalid GL value.";
    case gl_error::out_of_memory:
      return u8"GL out of memory.";
    case gl_error::program_invalid_uniform:
      return u8"Invalid GL Program uniform '%s'.";
    case gl_error::program_linking:
      return u8"Error linking GL Program:\n%s";
    case gl_error::shader_compilation:
      return u8"Error compiling GL %s shader:\n%s";
    case gl_error::stack_overflow:
      return u8"GL stack overflow.";
    case gl_error::stack_underflow:
      return u8"GL stack underflow.";
    case gl_error::table_too_large:
      return u8"GL table too large.";
    case gl_error::vertical_sync_set:
      return u8"Failed to set vertical Sync mode.";
    default:
      return u8"";
  }
}

}

