// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/color.hpp"



namespace hou
{

namespace
{

uint8_t float_to_uint8(float v);
float uint8_to_float(uint8_t v);

uint8_t float_to_uint8(float v)
{
  if(v > 1.f)
  {
    v = 1.f;
  }
  else if(v < 0.f)
  {
    v = 0.f;
  }
  return static_cast<uint8_t>(v * 255.f);
}



float uint8_to_float(uint8_t v)
{
  return static_cast<float>(v) / 255.f;
}

}  // namespace



const color color::white(255, 255, 255, 255);
const color color::grey(128, 128, 128, 255);
const color color::black(0, 0, 0, 255);
const color color::red(255, 0, 0, 255);
const color color::yellow(255, 255, 0, 255);
const color color::green(0, 255, 0, 255);
const color color::cyan(0, 255, 255, 255);
const color color::blue(0, 0, 255, 255);
const color color::magenta(255, 0, 255, 255);
const color color::transparent(0, 0, 0, 0);



color::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
  : m_red(red)
  , m_green(green)
  , m_blue(blue)
  , m_alpha(alpha)
{}



uint8_t color::get_red() const
{
  return m_red;
}



float color::get_red_f() const
{
  return uint8_to_float(m_red);
}



void color::set_red(uint8_t value)
{
  m_red = value;
}



void color::set_red_f(float value)
{
  m_red = float_to_uint8(value);
}



uint8_t color::get_green() const
{
  return m_green;
}



float color::get_green_f() const
{
  return uint8_to_float(m_green);
}



void color::set_green(uint8_t value)
{
  m_green = value;
}



void color::set_green_f(float value)
{
  m_green = float_to_uint8(value);
}



uint8_t color::get_blue() const
{
  return m_blue;
}



float color::get_blue_f() const
{
  return uint8_to_float(m_blue);
}



void color::set_blue(uint8_t value)
{
  m_blue = value;
}



void color::set_blue_f(float value)
{
  m_blue = float_to_uint8(value);
}



uint8_t color::get_alpha() const
{
  return m_alpha;
}



float color::get_alpha_f() const
{
  return uint8_to_float(m_alpha);
}



void color::set_alpha(uint8_t value)
{
  m_alpha = value;
}



void color::set_alpha_f(float value)
{
  m_alpha = float_to_uint8(value);
}



bool operator==(const color& lhs, const color& rhs)
{
  return lhs.get_red() == rhs.get_red() && lhs.get_green() == rhs.get_green()
    && lhs.get_blue() == rhs.get_blue() && lhs.get_alpha() == rhs.get_alpha();
}



bool operator!=(const color& lhs, const color& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const color& c)
{
  return os << "{red = " << static_cast<int>(c.get_red())
            << ", green = " << static_cast<int>(c.get_green())
            << ", blue = " << static_cast<int>(c.get_blue())
            << ", alpha = " << static_cast<int>(c.get_alpha()) << "}";
}

}  // namespace hou
