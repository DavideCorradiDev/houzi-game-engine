// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/aud_exceptions.hpp"



namespace hou
{

invalid_audio_data::invalid_audio_data(const std::string& path, uint line)
  : exception(path, line, u8"Invalid or corrupted audio data.")
{}

}  // namespace hou
