// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextureChannelMapping.hpp"



namespace hou
{

const TextureChannelMapping TextureChannelMapping::standard
  ( TextureChannel::r
  , TextureChannel::G
  , TextureChannel::B
  , TextureChannel::A);



const TextureChannelMapping TextureChannelMapping::Luminosity
  ( TextureChannel::r
  , TextureChannel::r
  , TextureChannel::r
  , TextureChannel::One);



const TextureChannelMapping TextureChannelMapping::Alpha
  ( TextureChannel::One
  , TextureChannel::One
  , TextureChannel::One
  , TextureChannel::r);



TextureChannelMapping::TextureChannelMapping(TextureChannel r, TextureChannel g
  , TextureChannel b, TextureChannel a)
  : mR(r)
  , mG(g)
  , mB(b)
  , mA(a)
{}



TextureChannel TextureChannelMapping::get_r() const
{
  return mR;
}



TextureChannel TextureChannelMapping::get_g() const
{
  return mG;
}



TextureChannel TextureChannelMapping::get_b() const
{
  return mB;
}



TextureChannel TextureChannelMapping::get_a() const
{
  return mA;
}



void TextureChannelMapping::set_r(TextureChannel channel)
{
  mR = channel;
}



void TextureChannelMapping::set_g(TextureChannel channel)
{
  mG = channel;
}



void TextureChannelMapping::set_b(TextureChannel channel)
{
  mB = channel;
}



void TextureChannelMapping::set_a(TextureChannel channel)
{
  mA = channel;
}



bool operator==(const TextureChannelMapping& lhs
  , const TextureChannelMapping& rhs)
{
  return lhs.get_r() == rhs.get_r()
    && lhs.get_g() == rhs.get_g()
    && lhs.get_b() == rhs.get_b()
    && lhs.get_a() == rhs.get_a();
}



bool operator!=(const TextureChannelMapping& lhs
  , const TextureChannelMapping& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const TextureChannelMapping& tcm)
{
  return os
    << "{" << tcm.get_r() << " -> r, "
    << tcm.get_g() << " -> G, "
    << tcm.get_b() << " -> B, "
    << tcm.get_a() << " -> A}";
}

}

