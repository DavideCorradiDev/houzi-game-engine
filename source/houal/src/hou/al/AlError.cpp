// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlError.hpp"



namespace hou
{

std::string get_text(AlError ec)
{
  switch(ec)
  {
    case AlError::context_create:
      return u8"Error creating AL ph_context.";
    case AlError::context_destroy:
      return u8"Error destroying AL ph_context.";
    case AlError::context_existence:
      return u8"No current AL context.";
    case AlError::context_make_current:
      return u8"Error setting current AL ph_context.";
    case AlError::DeviceClose:
      return u8"Error closing AL device.";
    case AlError::DeviceOpen:
      return u8"Error opening AL device (%s).";
    case AlError::InvalidContext:
      return u8"Invalid AL ph_context.";
    case AlError::InvalidDevice:
      return u8"Invalid AL device.";
    case AlError::invalid_enum:
      return u8"Invalid AL enum.";
    case AlError::InvalidName:
      return u8"Invalid AL name.";
    case AlError::InvalidOperation:
      return u8"Invalid AL operation.";
    case AlError::invalid_ownership:
      return u8"Current AL ph_context does not own object.";
    case AlError::invalid_value:
      return u8"Invalid AL value.";
    case AlError::out_of_memory:
      return u8"AL out of memory.";
    default:
      return u8"";
  }
}

}

