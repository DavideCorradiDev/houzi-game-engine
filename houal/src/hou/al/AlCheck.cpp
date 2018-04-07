// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#include "hou/al/AlCheck.hpp"

#include "hou/al/AlContext.hpp"
#include "hou/al/AlDevice.hpp"
#include "hou/al/AlError.hpp"
#include "hou/al/AlObjectHandle.hpp"

#include "hou/cor/CorError.hpp"
#include "hou/cor/Error.hpp"

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
      return getText(AlError::InvalidEnum);
    case AL_INVALID_NAME:
      return getText(AlError::InvalidName);
    case AL_INVALID_OPERATION:
      return getText(AlError::InvalidOperation);
    case AL_INVALID_VALUE:
      return getText(AlError::InvalidValue);
    case AL_OUT_OF_MEMORY:
      return getText(AlError::OutOfMemory);
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(err));
      return u8"";
  }
}



std::string getContextErrorMessage(ALCenum err)
{
  switch(err)
  {
    case ALC_INVALID_CONTEXT:
      return getText(AlError::InvalidContext);
    case ALC_INVALID_DEVICE:
      return getText(AlError::InvalidDevice);
    case ALC_INVALID_ENUM:
      return getText(AlError::InvalidEnum);
    case ALC_INVALID_VALUE:
      return getText(AlError::InvalidValue);
    case ALC_OUT_OF_MEMORY:
      return getText(AlError::OutOfMemory);
    default:
      HOU_LOGIC_ERROR(getText(CorError::InvalidEnum), static_cast<int>(err));
      return u8"";
  }
}

}



void checkError(const std::string& filename, int line)
{
  ALenum errState = alGetError();
  if(errState != AL_NO_ERROR)
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getErrorMessage(errState)));
  }
}



void checkContextError(Device& device, const std::string& filename, int line)
{
  ALCenum errState = alcGetError(device.getHandle());
  if(errState != ALC_NO_ERROR)
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getContextErrorMessage(errState)));
  }
}



void checkContextExistence(const std::string& filename, int line)
{
  if(Context::getCurrent() == nullptr)
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getText(AlError::ContextExistence)));
  }
}




void checkContextOwnership(const DeviceOwnedObjectHandle& o
  , const std::string& filename, int line)
{
  checkContextExistence(filename, line);
  if(Context::getCurrent()->getDeviceUid() != o.getOwningDeviceUid())
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getText(AlError::InvalidOwnership)));
  }
}



void checkContextOwnership(const ContextOwnedObjectHandle& o
  , const std::string& filename, int line)
{
  checkContextExistence(filename, line);
  if(Context::getCurrent()->getUid() != o.getOwningContextUid())
  {
    HOU_THROW(std::logic_error, formatErrorMessage(filename, line
      , getText(AlError::InvalidOwnership)));
  }
}

}

}

