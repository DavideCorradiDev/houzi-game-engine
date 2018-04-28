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
  ContextCreate,
  ContextDestroy,
  ContextExistence,
  ContextMakeCurrent,
  DeviceClose,
  DeviceOpen,
  InvalidContext,
  InvalidDevice,
  invalid_enum,
  InvalidName,
  InvalidOperation,
  InvalidOwnership,
  InvalidValue,
  OutOfMemory,
};

HOU_AL_API std::string get_text(AlError ec);

}

#endif

