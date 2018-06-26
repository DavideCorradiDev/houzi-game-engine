// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/gl/gl_color_format.hpp"



namespace hou
{

namespace gl
{

color_format::color_format(uint red, uint green, uint blue, uint alpha)
  : m_red_bit_count(red)
  , m_green_bit_count(green)
  , m_blue_bit_count(blue)
  , m_alpha_bit_count(alpha)
{}



uint color_format::get_red_bit_count() const
{
  return m_red_bit_count;
}



uint color_format::get_green_bit_count() const
{
  return m_green_bit_count;
}



uint color_format::get_blue_bit_count() const
{
  return m_blue_bit_count;
}



uint color_format::get_alpha_bit_count() const
{
  return m_alpha_bit_count;
}



uint color_format::get_bit_count() const
{
  return m_red_bit_count + m_green_bit_count + m_blue_bit_count
    + m_alpha_bit_count;
}



bool operator==(const color_format& lhs, const color_format& rhs)
{
  return lhs.get_red_bit_count() == rhs.get_red_bit_count()
    && lhs.get_green_bit_count() == rhs.get_green_bit_count()
    && lhs.get_blue_bit_count() == rhs.get_blue_bit_count()
    && lhs.get_alpha_bit_count() == rhs.get_alpha_bit_count();
}



bool operator!=(const color_format& lhs, const color_format& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const color_format& cf)
{
  return os << "{red_bit_count = " << cf.get_red_bit_count()
            << ", green_bit_count = " << cf.get_green_bit_count()
            << ", blue_bit_count = " << cf.get_blue_bit_count()
            << ", alpha_bit_count = " << cf.get_alpha_bit_count() << "}";
}

}  // namespace gl

}  // namespace hou
