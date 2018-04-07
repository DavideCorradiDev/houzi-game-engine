// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/al/AlError.hpp"



namespace hou
{

std::string getText(AlError ec)
{
  switch(ec)
  {
    case AlError::ContextCreate:
      return u8"Error creating AL context.";
    case AlError::ContextDestroy:
      return u8"Error destroying AL context.";
    case AlError::ContextExistence:
      return u8"No current AL Context.";
    case AlError::ContextMakeCurrent:
      return u8"Error setting current AL context.";
    case AlError::DeviceClose:
      return u8"Error closing AL device.";
    case AlError::DeviceOpen:
      return u8"Error opening AL device (%s).";
    case AlError::InvalidContext:
      return u8"Invalid AL context.";
    case AlError::InvalidDevice:
      return u8"Invalid AL device.";
    case AlError::InvalidEnum:
      return u8"Invalid AL enum.";
    case AlError::InvalidName:
      return u8"Invalid AL name.";
    case AlError::InvalidOperation:
      return u8"Invalid AL operation.";
    case AlError::InvalidOwnership:
      return u8"Current AL context does not own object.";
    case AlError::InvalidValue:
      return u8"Invalid AL value.";
    case AlError::OutOfMemory:
      return u8"AL out of memory.";
    default:
      return u8"";
  }
}

}

