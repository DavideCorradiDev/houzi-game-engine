// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/modifier_keys.hpp"

#include "hou/cor/core_functions.hpp"

#define MODIFIER_KEY_CASE(mk, os)                                              \
  case modifier_keys::mk:                                                      \
    (os) << #mk;                                                               \
    break



namespace hou
{

namespace
{

void printer(std::ostream& os, modifier_keys mk)
{
  switch(mk)
  {
    MODIFIER_KEY_CASE(none, os);
    MODIFIER_KEY_CASE(lalt, os);
    MODIFIER_KEY_CASE(ralt, os);
    MODIFIER_KEY_CASE(alt, os);
    MODIFIER_KEY_CASE(lctrl, os);
    MODIFIER_KEY_CASE(rctrl, os);
    MODIFIER_KEY_CASE(ctrl, os);
    MODIFIER_KEY_CASE(lshift, os);
    MODIFIER_KEY_CASE(rshift, os);
    MODIFIER_KEY_CASE(shift, os);
    MODIFIER_KEY_CASE(lsystem, os);
    MODIFIER_KEY_CASE(rsystem, os);
    MODIFIER_KEY_CASE(system, os);
    MODIFIER_KEY_CASE(num, os);
    MODIFIER_KEY_CASE(caps, os);
    MODIFIER_KEY_CASE(mode, os);
    default:
      STREAM_VALUE(os, modifier_keys, mk);
  }
}

}

std::ostream& operator<<(std::ostream& os, modifier_keys mk)
{
  return stream_bitfield<modifier_keys>(os, mk, printer);
}

}  // namespace hou
