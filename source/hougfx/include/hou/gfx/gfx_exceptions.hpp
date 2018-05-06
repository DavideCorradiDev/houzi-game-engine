// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_GFX_GFX_EXCEPTIONS_HPP
#define HOU_GFX_GFX_EXCEPTIONS_HPP

#include "hou/cor/exception.hpp"

#include "hou/gfx/gfx_export.hpp"



namespace hou
{

class HOU_GFX_API font_creation_error : public exception
{
public:
  font_creation_error(const std::string& path, uint line);
};

class HOU_GFX_API font_destruction_error : public exception
{
public:
  font_destruction_error(const std::string& path, uint line);
};

}  // namespace hou

#endif
