// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

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
  InvalidEnum,
  InvalidName,
  InvalidOperation,
  InvalidOwnership,
  InvalidValue,
  OutOfMemory,
};

HOU_AL_API std::string getText(AlError ec);

}

#endif

