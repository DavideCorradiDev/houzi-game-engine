// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/al/al_missing_context_error.hpp"

#include "hou/al/al_context.hpp"



namespace hou
{

namespace al
{

missing_context_error::missing_context_error(const std::string& path, uint line)
  : exception(path, line, u8"No current OpenAL context.")
{}



void check_context_existence(const std::string& path, int line)
{
  if(context::get_current() == nullptr)
  {
    HOU_ERROR_STD_N(missing_context_error, path, line);
  }
}

}  // namespace al

}  // namespace hou
