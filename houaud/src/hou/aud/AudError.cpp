// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/AudError.hpp"



namespace hou
{

std::string getText(AudError ec)
{
  switch(ec)
  {
    case AudError::InvalidAudioFileExtension:
      return u8"Invalid audio file extension ('%s').";
    case AudError::OggInvalidHeader:
      return u8"Invalid OGG file header ('%s').";
    case AudError::WavInvalidHeader:
      return u8"Invalid WAV file header ('%s').";
    default:
      return u8"";
  }
}

}

