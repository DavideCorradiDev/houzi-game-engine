// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUD_ERROR_HPP
#define HOU_AUD_AUD_ERROR_HPP

#include "hou/aud/aud_export.hpp"

#include <string>



namespace hou
{

/** Audio module error codes. */
enum class aud_error
{
  invalid_audio_file_extension,
  ogg_invalid_header,
  wav_invalid_header,
};

/** Retrieves the message string associated to an audio module error code.
 *
 * \param ec the error code.
 */
HOU_AUD_API std::string get_text(aud_error ec);

}  // namespace hou

#endif
