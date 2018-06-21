// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_invalid_context_error.hpp"

#include "hou/al/al_context.hpp"
#include "hou/al/al_device.hpp"
#include "hou/al/al_object_handle.hpp"

#include <AL/al.h>
#include <AL/alc.h>



namespace hou
{

namespace al
{

invalid_context_error::invalid_context_error(const std::string& path, uint line)
  : exception(
      path, line, u8"The current OpenAL context does not own the object.")
{}



void check_context_ownership(
  const device_owned_object_handle& o, const std::string& path, int line)
{
  if(context::get_current()->get_device_uid() != o.get_owning_device_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}



void check_context_ownership(
  const context_owned_object_handle& o, const std::string& path, int line)
{
  if(context::get_current()->get_uid() != o.get_owning_context_uid())
  {
    HOU_ERROR_STD_N(invalid_context_error, path, line);
  }
}

}  // namespace al

}  // namespace hou
