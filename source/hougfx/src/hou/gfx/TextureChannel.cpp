// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextureChannel.hpp"

#include "hou/cor/error.hpp"

#define TEXTURE_CHANNEL_CASE(tc, os) \
  case TextureChannel::tc:           \
    return (os) << #tc



namespace hou
{

std::ostream& operator<<(std::ostream& os, TextureChannel tc)
{
  switch(tc)
  {
    TEXTURE_CHANNEL_CASE(R, os);
    TEXTURE_CHANNEL_CASE(G, os);
    TEXTURE_CHANNEL_CASE(B, os);
    TEXTURE_CHANNEL_CASE(A, os);
    TEXTURE_CHANNEL_CASE(Zero, os);
    TEXTURE_CHANNEL_CASE(One, os);
  default:
    return os;
  }
}

}  // namespace hou
