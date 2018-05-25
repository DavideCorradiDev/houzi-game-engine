// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <>
constexpr float pi<float>() noexcept
{
  return 3.1415927f;
}



template <>
constexpr double pi<double>() noexcept
{
  return 3.141592653589793;
}



template <typename T>
constexpr T deg_to_rad(T deg) noexcept
{
  constexpr T factor = pi<T>() / T(180);
  return deg * factor;
}



template <typename T>
constexpr T rad_to_deg(T rad) noexcept
{
  constexpr T factor = T(180) / pi<T>();
  return rad * factor;
}



template <typename T, typename Enable>
constexpr T log(T x, int n) noexcept
{
  return std::log(x) / std::log(narrow_cast<T>(n));
}

}  // namespace hou
