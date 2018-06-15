// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/modifier_keys.hpp"

#include <string>

#define MODIFIER_KEY_BITFIELD_CASE(bitfield, bit, os)                          \
  do                                                                           \
  {                                                                            \
    if(check_all(bitfield, modifier_keys::bit))                                \
    {                                                                          \
      os << (match_found ? " | " : "") << #bit;                                \
      match_found = true;                                                      \
    }                                                                          \
  } while(false)



namespace hou
{

std::ostream& operator<<(std::ostream& os, modifier_keys mk)
{
  if(mk == modifier_keys::none)
  {
    return os << "none";
  }

  bool match_found = false;
  MODIFIER_KEY_BITFIELD_CASE(mk, lalt, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, ralt, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, lctrl, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, rctrl, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, lshift, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, rshift, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, lsystem, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, rsystem, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, num, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, caps, os);
  MODIFIER_KEY_BITFIELD_CASE(mk, mode, os);

  return os;
}

}  // namespace hou
