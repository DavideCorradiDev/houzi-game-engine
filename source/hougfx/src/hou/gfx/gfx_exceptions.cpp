// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/gfx_exceptions.hpp"



namespace hou
{

font_creation_error::font_creation_error(const std::string& path, uint line)
  : exception(path, line, u8"Failed to create the font face object.")
{}

font_destruction_error::font_destruction_error(
  const std::string& path, uint line)
  : exception(path, line, u8"Failed to destroy the font face object.")
{}

}  // namespace hou
