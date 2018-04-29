// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/AlCheck.hpp"

#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"
#include "hou/al/AlError.hpp"
#include "hou/al/AlObjectHandle.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/error.hpp"

#include <AL/al.h>
#include <AL/alc.h>



namespace hou
{

namespace al
{

namespace
{

std::string getErrorMessage(ALenum err);
std::string getContextErrorMessage(ALCenum err);

std::string getErrorMessage(ALenum err)
{
  switch(err)
  {
    case AL_INVALID_ENUM:
      return get_text(AlError::invalid_enum);
    case AL_INVALID_NAME:
      return get_text(AlError::InvalidName);
    case AL_INVALID_OPERATION:
      return get_text(AlError::InvalidOperation);
    case AL_INVALID_VALUE:
      return get_text(AlError::invalid_value);
    case AL_OUT_OF_MEMORY:
      return get_text(AlError::out_of_memory);
    default:
      HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(err));
      return u8"";
  }
}



std::string getContextErrorMessage(ALCenum err)
{
  switch(err)
  {
    case ALC_INVALID_CONTEXT:
      return get_text(AlError::InvalidContext);
    case ALC_INVALID_DEVICE:
      return get_text(AlError::InvalidDevice);
    case ALC_INVALID_ENUM:
      return get_text(AlError::invalid_enum);
    case ALC_INVALID_VALUE:
      return get_text(AlError::invalid_value);
    case ALC_OUT_OF_MEMORY:
      return get_text(AlError::out_of_memory);
    default:
      HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(err));
      return u8"";
  }
}

}



void check_error(const std::string& filename, int line)
{
  ALenum errState = alGetError();
  if(errState != AL_NO_ERROR)
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , getErrorMessage(errState)));
  }
}



void checkContextError(Device& device, const std::string& filename, int line)
{
  ALCenum errState = alcGetError(device.get_handle());
  if(errState != ALC_NO_ERROR)
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , getContextErrorMessage(errState)));
  }
}



void check_context_existence(const std::string& filename, int line)
{
  if(context::getCurrent() == nullptr)
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , get_text(AlError::context_existence)));
  }
}




void check_context_ownership(const DeviceOwnedObjectHandle& o
  , const std::string& filename, int line)
{
  check_context_existence(filename, line);
  if(context::getCurrent()->getDeviceUid() != o.getOwningDeviceUid())
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , get_text(AlError::invalid_ownership)));
  }
}



void check_context_ownership(const ContextOwnedObjectHandle& o
  , const std::string& filename, int line)
{
  check_context_existence(filename, line);
  if(context::getCurrent()->get_uid() != o.get_owning_context_uid())
  {
    HOU_THROW(std::logic_error, format_error_message(filename, line
      , get_text(AlError::invalid_ownership)));
  }
}

}

}

