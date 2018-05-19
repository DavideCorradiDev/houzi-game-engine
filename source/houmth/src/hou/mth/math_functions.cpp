// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/mth/math_functions.hpp"



namespace hou
{

float deg_to_rad(float deg) noexcept
{
  static constexpr float factor = pi_f / 180.f;
  return deg * factor;
}



double deg_to_rad(double deg) noexcept
{
  static constexpr double factor = pi_d / 180.f;
  return deg * factor;
}



float rad_to_deg(float rad) noexcept
{
  static constexpr float factor = 180.f / pi_f;
  return rad * factor;
}



double rad_to_deg(double rad) noexcept
{
  static constexpr double factor = 180.f / pi_d;
  return rad * factor;
}

}  // namespace hou
