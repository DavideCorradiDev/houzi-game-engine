// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_exceptions.hpp"

#include "hou/al/al_device.hpp"


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
      return u8"invalid enum";
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
  ALCenum err_state = alcGetError(dev.get_impl());
  if(err_state != ALC_NO_ERROR)
  {
    HOU_ERROR_STD_N(context_call_error, path, line, err_state);
  }
}

}  // namespace al

}  // namespace hou
