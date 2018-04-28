// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/ModifierKeys.hpp"

#include <string>



#define MODIFIER_KEY_BITFIELD_CASE(bitfield, mkf) \
  (checkBit(bitfield, ModifierKeys::mkf) ? #mkf : "0")



namespace hou
{

std::ostream& operator<<(std::ostream& os, ModifierKeys mkf)
{
  return os
    << MODIFIER_KEY_BITFIELD_CASE(mkf, Alt) << " | "
    << MODIFIER_KEY_BITFIELD_CASE(mkf, Ctrl) << " | "
    << MODIFIER_KEY_BITFIELD_CASE(mkf, Shift) << " | "
    << MODIFIER_KEY_BITFIELD_CASE(mkf, System);
}

}

