// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

#ifndef HOU_AUD_AUD_ERROR_HPP
#define HOU_AUD_AUD_ERROR_HPP

#include "hou/aud/AudExport.hpp"

#include <string>



namespace hou
{

/** Audio module error codes. */
enum class AudError
{
  InvalidAudioFileExtension,
  OggInvalidHeader,
  WavInvalidHeader,
};

/** Retrieves the message string associated to an audio module error code.
 *
 *  \param ec the error code.
 */
HOU_AUD_API std::string getText(AudError ec);

}

#endif

