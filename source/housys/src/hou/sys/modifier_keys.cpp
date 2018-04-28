// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/modifier_keys.hpp"

#include <string>



#define MODIFIER_KEY_BITFIELD_CASE(bitfield, mkf) \
  (checkBit(bitfield, modifier_keys::mkf) ? #mkf : "0")



namespace hou
{

std::ostream& operator<<(std::ostream& os, modifier_keys mkf)
{
  return os
    << MODIFIER_KEY_BITFIELD_CASE(mkf, alt) << " | "
    << MODIFIER_KEY_BITFIELD_CASE(mkf, ctrl) << " | "
    << MODIFIER_KEY_BITFIELD_CASE(mkf, shift) << " | "
    << MODIFIER_KEY_BITFIELD_CASE(mkf, system);
}

}

