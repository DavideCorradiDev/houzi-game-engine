// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gfx/texture_channel_mapping.hpp"



namespace hou
{

const texture_channel_mapping texture_channel_mapping::standard
  ( texture_channel::r
  , texture_channel::g
  , texture_channel::b
  , texture_channel::a);



const texture_channel_mapping texture_channel_mapping::luminosity
  ( texture_channel::r
  , texture_channel::r
  , texture_channel::r
  , texture_channel::one);



const texture_channel_mapping texture_channel_mapping::alpha
  ( texture_channel::one
  , texture_channel::one
  , texture_channel::one
  , texture_channel::r);



texture_channel_mapping::texture_channel_mapping(texture_channel r, texture_channel g
  , texture_channel b, texture_channel a)
  : m_r(r)
  , m_g(g)
  , m_b(b)
  , m_a(a)
{}



texture_channel texture_channel_mapping::get_r() const
{
  return m_r;
}



texture_channel texture_channel_mapping::get_g() const
{
  return m_g;
}



texture_channel texture_channel_mapping::get_b() const
{
  return m_b;
}



texture_channel texture_channel_mapping::get_a() const
{
  return m_a;
}



void texture_channel_mapping::set_r(texture_channel channel)
{
  m_r = channel;
}



void texture_channel_mapping::set_g(texture_channel channel)
{
  m_g = channel;
}



void texture_channel_mapping::set_b(texture_channel channel)
{
  m_b = channel;
}



void texture_channel_mapping::set_a(texture_channel channel)
{
  m_a = channel;
}



bool operator==(const texture_channel_mapping& lhs
  , const texture_channel_mapping& rhs)
{
  return lhs.get_r() == rhs.get_r()
    && lhs.get_g() == rhs.get_g()
    && lhs.get_b() == rhs.get_b()
    && lhs.get_a() == rhs.get_a();
}



bool operator!=(const texture_channel_mapping& lhs
  , const texture_channel_mapping& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const texture_channel_mapping& tcm)
{
  return os
    << "{" << tcm.get_r() << " -> r, "
    << tcm.get_g() << " -> g, "
    << tcm.get_b() << " -> b, "
    << tcm.get_a() << " -> a}";
}

}

