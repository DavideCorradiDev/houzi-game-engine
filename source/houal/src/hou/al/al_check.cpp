// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_check.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_error.hpp"
#include "hou/al/al_object_handle.hpp"

#include "hou/cor/cor_error.hpp"
#include "hou/cor/assertions.hpp"

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
      return get_text(al_error::invalid_enum);
    case AL_INVALID_NAME:
      return get_text(al_error::invalid_name);
    case AL_INVALID_OPERATION:
      return get_text(al_error::invalid_operation);
    case AL_INVALID_VALUE:
      return get_text(al_error::invalid_value);
    case AL_OUT_OF_MEMORY:
      return get_text(al_error::out_of_memory);
    default:
      DEPRECATED_HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(err));
      return u8"";
  }
}



std::string getContextErrorMessage(ALCenum err)
{
  switch(err)
  {
    case ALC_INVALID_CONTEXT:
      return get_text(al_error::invalid_context);
    case ALC_INVALID_DEVICE:
      return get_text(al_error::invalid_device);
    case ALC_INVALID_ENUM:
      return get_text(al_error::invalid_enum);
    case ALC_INVALID_VALUE:
      return get_text(al_error::invalid_value);
    case ALC_OUT_OF_MEMORY:
      return get_text(al_error::out_of_memory);
    default:
      DEPRECATED_HOU_LOGIC_ERROR(get_text(cor_error::invalid_enum), static_cast<int>(err));
      return u8"";
  }
}

}  // namespace



void check_error(const std::string& filename, int line)
{
  ALenum errState = alGetError();
  if(errState != AL_NO_ERROR)
  {
    DEPRECATED_HOU_THROW(std::logic_error,
      deprecated_format_error_message(filename, line, getErrorMessage(errState)));
  }
}



void check_context_error(
  device& dev, const std::string& filename, int line)
{
  ALCenum errState = alcGetError(dev.get_handle());
  if(errState != ALC_NO_ERROR)
  {
    DEPRECATED_HOU_THROW(std::logic_error,
      deprecated_format_error_message(filename, line, getContextErrorMessage(errState)));
  }
}



void check_context_existence(const std::string& filename, int line)
{
  if(context::get_current() == nullptr)
  {
    DEPRECATED_HOU_THROW(std::logic_error,
      deprecated_format_error_message(
        filename, line, get_text(al_error::context_existence)));
  }
}



void check_context_ownership(
  const device_owned_object_handle& o, const std::string& filename, int line)
{
  check_context_existence(filename, line);
  if(context::get_current()->get_device_uid() != o.get_owning_device_uid())
  {
    DEPRECATED_HOU_THROW(std::logic_error,
      deprecated_format_error_message(
        filename, line, get_text(al_error::invalid_ownership)));
  }
}



void check_context_ownership(
  const context_owned_object_handle& o, const std::string& filename, int line)
{
  check_context_existence(filename, line);
  if(context::get_current()->get_uid() != o.get_owning_context_uid())
  {
    DEPRECATED_HOU_THROW(std::logic_error,
      deprecated_format_error_message(
        filename, line, get_text(al_error::invalid_ownership)));
  }
}

}  // namespace al

}  // namespace hou
