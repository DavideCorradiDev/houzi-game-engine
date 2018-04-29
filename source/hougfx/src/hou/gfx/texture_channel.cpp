// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_channel.hpp"

#include "hou/cor/error.hpp"

#define TEXTURE_CHANNEL_CASE(tc, os) \
  case texture_channel::tc:           \
    return (os) << #tc



namespace hou
{

std::ostream& operator<<(std::ostream& os, texture_channel tc)
{
  switch(tc)
  {
    TEXTURE_CHANNEL_CASE(r, os);
    TEXTURE_CHANNEL_CASE(g, os);
    TEXTURE_CHANNEL_CASE(b, os);
    TEXTURE_CHANNEL_CASE(a, os);
    TEXTURE_CHANNEL_CASE(zero, os);
    TEXTURE_CHANNEL_CASE(one, os);
  default:
    return os;
  }
}

}  // namespace hou
