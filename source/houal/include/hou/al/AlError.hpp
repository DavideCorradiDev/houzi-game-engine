// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#ifndef HOU_AL_AL_ERROR_HPP
#define HOU_AL_AL_ERROR_HPP

#include "hou/al/AlExport.hpp"

#include <string>



namespace hou
{

enum class AlError
{
  context_create,
  context_destroy,
  context_existence,
  context_make_current,
  DeviceClose,
  DeviceOpen,
  InvalidContext,
  InvalidDevice,
  invalid_enum,
  InvalidName,
  InvalidOperation,
  invalid_ownership,
  invalid_value,
  out_of_memory,
};

HOU_AL_API std::string get_text(AlError ec);

}

#endif

