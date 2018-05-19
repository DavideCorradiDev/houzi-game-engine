// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.



namespace hou
{

template <typename T, typename Enable>
constexpr T log(T x, int n) noexcept
{
  return std::log(x) / std::log(narrow_cast<T>(n));
}


}  // namespace hou
