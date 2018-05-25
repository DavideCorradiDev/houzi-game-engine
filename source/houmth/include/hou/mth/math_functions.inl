// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <>
constexpr float pi<float>()
{
  return 3.1415927f;
}



template <>
constexpr double pi<double>()
{
  return 3.141592653589793;
}



template <typename T, typename Enable>
constexpr T log(T x, int n) noexcept
{
  return std::log(x) / std::log(narrow_cast<T>(n));
}


}  // namespace hou
