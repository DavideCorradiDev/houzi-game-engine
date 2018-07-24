// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_context_exceptions.hpp"



namespace hou
{

namespace al
{

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



device_open_error::device_open_error(
  const std::string& path, uint line, const std::string& device_name)
  : exception(path, line,
      format_string(
        u8"Failed to open the OpenAL device '%s'.", device_name.c_str()))
{}



device_close_error::device_close_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to close the OpenAL device.")
{}

}  // namespace al

}  // namespace hou
