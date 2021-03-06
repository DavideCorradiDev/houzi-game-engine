// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

#include "hou/cor/core_functions.hpp"

#include <cmath>



namespace hou
{

template <typename T, typename Enable>
bool close(T lhs, T rhs, T acc) noexcept
{
  return std::abs(lhs - rhs) <= acc;
}

template bool close<float>(float, float, float) noexcept;
template bool close<double>(double, double, double) noexcept;

}  // namespace hou
