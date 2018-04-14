// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/MthUtils.hpp"



namespace hou
{

float degToRad(float deg)
{
  static constexpr float factor = PI_F / 180.f;
  return deg * factor;
}



double degToRad(double deg)
{
  static constexpr double factor = PI_D / 180.f;
  return deg * factor;
}



float radToDeg(float rad)
{
  static constexpr float factor = 180.f / PI_F;
  return rad * factor;
}



double radToDeg(double rad)
{
  static constexpr double factor = 180.f / PI_D;
  return rad * factor;
}

}

