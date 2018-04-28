// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/sys/Color.hpp"



namespace hou
{

namespace
{

uint8_t floatToUInt8(float v);
float uint8ToFloat(uint8_t v);

uint8_t floatToUInt8(float v)
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



float uint8ToFloat(uint8_t v)
{
   return static_cast<float>(v) / 255.f;
}

}



const Color Color::White(255, 255, 255, 255);
const Color Color::Grey(128, 128, 128, 255);
const Color Color::Black(0, 0, 0, 255);
const Color Color::Red(255, 0, 0, 255);
const Color Color::Yellow(255, 255, 0, 255);
const Color Color::Green(0, 255, 0, 255);
const Color Color::Cyan(0, 255, 255, 255);
const Color Color::Blue(0, 0, 255, 255);
const Color Color::Magenta(255, 0, 255, 255);
const Color Color::Transparent(0, 0, 0, 0);



Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
  : mRed(red)
  , mGreen(green)
  , mBlue(blue)
  , mAlpha(alpha) {}



uint8_t Color::getRed() const
{
  return mRed;
}



float Color::getRedf() const
{
  return uint8ToFloat(mRed);
}



void Color::setRed(uint8_t value)
{
  mRed = value;
}



void Color::setRedf(float value)
{
  mRed = floatToUInt8(value);
}



uint8_t Color::getGreen() const
{
  return mGreen;
}



float Color::getGreenf() const
{
  return uint8ToFloat(mGreen);
}



void Color::setGreen(uint8_t value)
{
  mGreen = value;
}



void Color::setGreenf(float value)
{
  mGreen = floatToUInt8(value);
}



uint8_t Color::getBlue() const
{
  return mBlue;
}



float Color::getBluef() const
{
  return uint8ToFloat(mBlue);
}



void Color::setBlue(uint8_t value)
{
  mBlue = value;
}



void Color::setBluef(float value)
{
  mBlue = floatToUInt8(value);
}



uint8_t Color::getAlpha() const
{
  return mAlpha;
}



float Color::getAlphaf() const
{
  return uint8ToFloat(mAlpha);
}



void Color::setAlpha(uint8_t value)
{
  mAlpha = value;
}



void Color::setAlphaf(float value)
{
  mAlpha = floatToUInt8(value);
}




bool operator==(const Color& lhs, const Color& rhs)
{
  return lhs.getRed() == rhs.getRed() && lhs.getGreen() == rhs.getGreen()
    && lhs.getBlue() == rhs.getBlue() && lhs.getAlpha() == rhs.getAlpha();
}



bool operator!=(const Color& lhs, const Color& rhs)
{
  return !(lhs == rhs);
}



std::ostream& operator<<(std::ostream& os, const Color& c)
{
  return os
    << "{Red = " << static_cast<int>(c.getRed())
    << ", Green = " << static_cast<int>(c.getGreen())
    << ", Blue = " << static_cast<int>(c.getBlue())
    << ", Alpha = " << static_cast<int>(c.getAlpha()) << "}";
}



}

