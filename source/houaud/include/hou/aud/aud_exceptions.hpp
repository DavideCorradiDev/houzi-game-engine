// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AUD_AUD_EXCEPTIONS_HPP
#define HOU_AUD_AUD_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/aud/aud_export.hpp"



namespace hou
{

class HOU_AUD_API audio_read_error : public exception
{
public:
  audio_read_error(
    const std::string& path, uint line, const std::string& filepath);
};
}  // namespace hou

#endif
