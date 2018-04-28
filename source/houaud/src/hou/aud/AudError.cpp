// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudError.hpp"



namespace hou
{

std::string get_text(AudError ec)
{
  switch(ec)
  {
    case AudError::InvalidAudioFileExtension:
      return u8"Invalid audio ph_file extension ('%s').";
    case AudError::OggInvalidHeader:
      return u8"Invalid OGG ph_file header ('%s').";
    case AudError::WavInvalidHeader:
      return u8"Invalid WAV ph_file header ('%s').";
    default:
      return u8"";
  }
}

}

