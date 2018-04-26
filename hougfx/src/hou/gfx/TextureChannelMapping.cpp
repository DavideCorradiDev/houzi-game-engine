// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/TextureChannelMapping.hpp"



namespace hou
{

const TextureChannelMapping TextureChannelMapping::Default
  ( TextureChannel::R
  , TextureChannel::G
  , TextureChannel::B
  , TextureChannel::A);



const TextureChannelMapping TextureChannelMapping::Luminosity
  ( TextureChannel::R
  , TextureChannel::R
  , TextureChannel::R
  , TextureChannel::One);



const TextureChannelMapping TextureChannelMapping::Alpha
  ( TextureChannel::One
  , TextureChannel::One
  , TextureChannel::One
  , TextureChannel::R);



TextureChannelMapping::TextureChannelMapping(TextureChannel r, TextureChannel g
  , TextureChannel b, TextureChannel a)
  : mR(r)
  , mG(g)
  , mB(b)
  , mA(a)
{}



TextureChannel TextureChannelMapping::getR() const
{
  return mR;
}



TextureChannel TextureChannelMapping::getG() const
{
  return mG;
}



TextureChannel TextureChannelMapping::getB() const
{
  return mB;
}



TextureChannel TextureChannelMapping::getA() const
{
  return mA;
}



void TextureChannelMapping::setR(TextureChannel channel)
{
  mR = channel;
}



void TextureChannelMapping::setG(TextureChannel channel)
{
  mG = channel;
}



void TextureChannelMapping::setB(TextureChannel channel)
{
  mB = channel;
}



void TextureChannelMapping::setA(TextureChannel channel)
{
  mA = channel;
}



bool operator==(const TextureChannelMapping& lhs
  , const TextureChannelMapping& rhs)
{
  return lhs.getR() == rhs.getR()
    && lhs.getG() == rhs.getG()
    && lhs.getB() == rhs.getB()
    && lhs.getA() == rhs.getA();
}



bool operator!=(const TextureChannelMapping& lhs
  , const TextureChannelMapping& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const TextureChannelMapping& tcm)
{
  return os
    << "{" << tcm.getR() << " -> R, "
    << tcm.getG() << " -> G, "
    << tcm.getB() << " -> B, "
    << tcm.getA() << " -> A}";
}

}

