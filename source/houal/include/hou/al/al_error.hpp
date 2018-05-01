// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_ERROR_HPP
#define HOU_AL_AL_ERROR_HPP

#include "hou/al/al_export.hpp"

#include <string>



namespace hou
{

enum class al_error
{
  context_create,
  context_destroy,
  context_existence,
  context_make_current,
  device_close,
  device_open,
  invalid_context,
  invalid_device,
  invalid_enum,
  invalid_name,
  invalid_operation,
  invalid_ownership,
  invalid_value,
  out_of_memory,
};

HOU_AL_API std::string get_text(al_error ec);

}  // namespace hou

#endif
