// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_exceptions.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_object_handle.hpp"

#include <AL/al.h>
#include <AL/alc.h>



namespace hou
{

namespace al
{

namespace
{

std::string get_error_message(ALenum err);
std::string get_context_error_message(ALCenum err);

std::string get_error_message(ALenum err)
{
  switch(err)
  {
    case AL_INVALID_ENUM:
      return u8"invalud enum";
    case AL_INVALID_NAME:
      return u8"invalid name";
    case AL_INVALID_OPERATION:
      return u8"invalid operation";
    case AL_INVALID_VALUE:
      return u8"invalid value";
    case AL_OUT_OF_MEMORY:
      return u8"out of memory";
    default:
      return u8"unknown error";
  }
}



std::string get_context_error_message(ALCenum err)
{
  switch(err)
  {
    case ALC_INVALID_CONTEXT:
      return u8"invalid context";
    case ALC_INVALID_DEVICE:
      return u8"invalid device";
    case ALC_INVALID_ENUM:
      return u8"invalid enum";
    case ALC_INVALID_VALUE:
      return u8"invalid value";
    case ALC_OUT_OF_MEMORY:
      return u8"out of memory";
    default:
      return u8"unknown error";
  }
}

}  // namespace



context_creation_error::context_creation_error(
  const std::string& path, uint line)
  : exception(path, line, u8"Failed to create the OpenAL context.")
{}



context_destruction_error::context_destruction_error(
  const std::string& path, uint line)
  : exception(path, line, u8"Failed to destroy the OpenAL context.")
{}



context_switch_error::context_switch_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to switch the current OpenAL context.")
{}



missing_context_error::missing_context_error(const std::string& path, uint line)
  : exception(path, line, u8"No current OpenAL context.")
{}



invalid_context_error::invalid_context_error(const std::string& path, uint line)
  : exception(
      path, line, u8"The current OpenAL context does not own the object.")
{}



device_open_error::device_open_error(
  const std::string& path, uint line, const std::string& device_name)
  : exception(path, line,
      format_string(
        u8"Failed to open the OpenAL device '%s'.", device_name.c_str()))
{}



device_close_error::device_close_error(const std::string& path, uint line)
  : exception(path, line, format_string(u8"Failed to close the OpenAL device."))
{}



call_error::call_error(const std::string& path, uint line, ALenum ec)
  : exception(path, line,
      format_string(
        u8"OpenAL error with code %d: %s.", ec, get_error_message(ec).c_str()))
{}



context_call_error::context_call_error(
  const std::string& path, uint line, ALenum ec)
  : exception(path, line,
      format_string(u8"OpenAL context error with code %d: %s.", ec,
        get_context_error_message(ec).c_str()))
{}



void check_error(const std::string& path, int line)
{
  ALenum err_state = alGetError();
  if(err_state != AL_NO_ERROR)
  {
    HOU_ERROR_STD_N(call_error, path, line, err_state);
  }
}



void check_context_error(device& dev, const std::string& path, int line)
{
  ALCenum err_state = alcGetError(dev.get_handle());
  if(err_state != ALC_NO_ERROR)
  {
    HOU_ERROR_STD_N(context_call_error, path, line, err_state);
  }
}



void check_context_existence(const std::string& path, int line)
{
  if(context::get_current() == nullptr)
  {
    HOU_ERROR_STD_N(missing_context_error, path, line);
  }
}



void check_context_ownership(
  const device_owned_object_handle& o, const std::string& path, int line)
{
  check_context_existence(path, line);
  if(context::get_current()->get_device_uid() != o.get_owning_device_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}



void check_context_ownership(
  const context_owned_object_handle& o, const std::string& path, int line)
{
  check_context_existence(path, line);
  if(context::get_current()->get_uid() != o.get_owning_context_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}

}  // namespace al

}  // namespace hou
