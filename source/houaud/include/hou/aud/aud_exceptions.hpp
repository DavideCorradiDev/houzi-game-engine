// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUD_EXCEPTIONS_HPP
#define HOU_AUD_AUD_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/aud/aud_export.hpp"



namespace hou
{

/** Audio read error.
 *
 * This exception is thrown when reading audio data fails.
 *
 * This normally means that the data is corrupted or in a wrong format.
 */
class HOU_AUD_API audio_read_error : public exception
{
public:
  /** Creates an audio_read_error object.
   *
   * \param path the path to the source file where the error happened.
   *
   * \param line the line where the error happened.
   *
   * \param filepath the path to the file.
   */
  audio_read_error(
    const std::string& path, uint line, const std::string& filepath);
};
}  // namespace hou

#endif
