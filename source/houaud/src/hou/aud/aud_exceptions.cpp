// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/aud_exceptions.hpp"



namespace hou
{

audio_read_error::audio_read_error(
  const std::string& path, uint line, const std::string& filepath)
  : exception(path, line,
      format_string(u8"Failed to read audio from file '%s'", filepath.c_str()))
{}

}  // namespace hou
