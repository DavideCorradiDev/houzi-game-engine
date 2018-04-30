// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/aud/aud_error.hpp"



namespace hou
{

std::string get_text(aud_error ec)
{
  switch(ec)
  {
    case aud_error::invalid_audio_file_extension:
      return u8"Invalid audio file extension ('%s').";
    case aud_error::ogg_invalid_header:
      return u8"Invalid OGG file header ('%s').";
    case aud_error::wav_invalid_header:
      return u8"Invalid WAV file header ('%s').";
    default:
      return u8"";
  }
}

}

