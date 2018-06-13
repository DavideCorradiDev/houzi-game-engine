// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/modifier_keys.hpp"

#include <string>

#define MODIFIER_KEY_BITFIELD_CASE(bitfield, bit, os)                          \
  do                                                                           \
  {                                                                            \
    if(check_bit(bitfield, modifier_keys::bit))                                \
    {                                                                          \
      os << (match_found ? " | " : "") << #bit;                                \
      match_found = true;                                                      \
    }                                                                          \
  } while(false)



namespace hou
{

std::ostream& operator<<(std::ostream& os, modifier_keys mkf)
{
  bool match_found = false;
  MODIFIER_KEY_BITFIELD_CASE(mkf, lalt, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, ralt, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, lctrl, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, rctrl, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, lshift, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, rshift, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, lsystem, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, rsystem, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, num, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, caps, os);
  MODIFIER_KEY_BITFIELD_CASE(mkf, mode, os);
  return os;
}

}  // namespace hou
