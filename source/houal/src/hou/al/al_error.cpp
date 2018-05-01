// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_error.hpp"



namespace hou
{

std::string get_text(al_error ec)
{
  switch(ec)
  {
    case al_error::context_create:
      return u8"Error creating AL ph_context.";
    case al_error::context_destroy:
      return u8"Error destroying AL ph_context.";
    case al_error::context_existence:
      return u8"No current AL context.";
    case al_error::context_make_current:
      return u8"Error setting current AL ph_context.";
    case al_error::device_close:
      return u8"Error closing AL ph_device.";
    case al_error::device_open:
      return u8"Error opening AL ph_device (%s).";
    case al_error::invalid_context:
      return u8"Invalid AL ph_context.";
    case al_error::invalid_device:
      return u8"Invalid AL ph_device.";
    case al_error::invalid_enum:
      return u8"Invalid AL enum.";
    case al_error::invalid_name:
      return u8"Invalid AL name.";
    case al_error::invalid_operation:
      return u8"Invalid AL operation.";
    case al_error::invalid_ownership:
      return u8"Current AL ph_context does not own object.";
    case al_error::invalid_value:
      return u8"Invalid AL value.";
    case al_error::out_of_memory:
      return u8"AL out of memory.";
    default:
      return u8"";
  }
}

}  // namespace hou
