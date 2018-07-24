// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/color.hpp"



namespace hou
{

namespace
{

uint8_t float_to_uint8(float v) noexcept;

float uint8_to_float(uint8_t v) noexcept;



uint8_t float_to_uint8(float v) noexcept
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



float uint8_to_float(uint8_t v) noexcept
{
  return static_cast<float>(v) / 255.f;
}

}  // namespace



const color& color::white() noexcept
{
  static const color c(255, 255, 255, 255);
  return c;
}



const color& color::grey() noexcept
{
  static const color c(128, 128, 128, 255);
  return c;
}



const color& color::black() noexcept
{
  static const color c(0, 0, 0, 255);
  return c;
}



const color& color::red() noexcept
{
  static const color c(255, 0, 0, 255);
  return c;
}



const color& color::yellow() noexcept
{
  static const color c(255, 255, 0, 255);
  return c;
}



const color& color::green() noexcept
{
  static const color c(0, 255, 0, 255);
  return c;
}



const color& color::cyan() noexcept
{
  static const color c(0, 255, 255, 255);
  return c;
}



const color& color::blue() noexcept
{
  static const color c(0, 0, 255, 255);
  return c;
}



const color& color::magenta() noexcept
{
  static const color c(255, 0, 255, 255);
  return c;
}



const color& color::transparent() noexcept
{
  static const color c(0, 0, 0, 0);
  return c;
}



color::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept
  : m_red(red)
  , m_green(green)
  , m_blue(blue)
  , m_alpha(alpha)
{}



uint8_t color::get_red() const noexcept
{
  return m_red;
}



float color::get_red_f() const noexcept
{
  return uint8_to_float(m_red);
}



void color::set_red(uint8_t value) noexcept
{
  m_red = value;
}



void color::set_red_f(float value) noexcept
{
  m_red = float_to_uint8(value);
}



uint8_t color::get_green() const noexcept
{
  return m_green;
}



float color::get_green_f() const noexcept
{
  return uint8_to_float(m_green);
}



void color::set_green(uint8_t value) noexcept
{
  m_green = value;
}



void color::set_green_f(float value) noexcept
{
  m_green = float_to_uint8(value);
}



uint8_t color::get_blue() const noexcept
{
  return m_blue;
}



float color::get_blue_f() const noexcept
{
  return uint8_to_float(m_blue);
}



void color::set_blue(uint8_t value) noexcept
{
  m_blue = value;
}



void color::set_blue_f(float value) noexcept
{
  m_blue = float_to_uint8(value);
}



uint8_t color::get_alpha() const noexcept
{
  return m_alpha;
}



float color::get_alpha_f() const noexcept
{
  return uint8_to_float(m_alpha);
}



void color::set_alpha(uint8_t value) noexcept
{
  m_alpha = value;
}



void color::set_alpha_f(float value) noexcept
{
  m_alpha = float_to_uint8(value);
}



color color_f(float red, float green, float blue, float alpha) noexcept
{
  return color(float_to_uint8(red), float_to_uint8(green), float_to_uint8(blue),
    float_to_uint8(alpha));
}



bool operator==(const color& lhs, const color& rhs) noexcept
{
  return lhs.get_red() == rhs.get_red() && lhs.get_green() == rhs.get_green()
    && lhs.get_blue() == rhs.get_blue() && lhs.get_alpha() == rhs.get_alpha();
}



bool operator!=(const color& lhs, const color& rhs) noexcept
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
