// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, typename U, std::size_t N, typename Enable>
constexpr bool close(
  const std::array<U, N>& lhs, const std::array<U, N>& rhs, T acc) noexcept
{
  return container_close(lhs.begin(), lhs.end(), rhs.begin(), acc);
}



template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& c)
{
  return container_stream(os, c.begin(), c.end());
}

}  // namespace hou
