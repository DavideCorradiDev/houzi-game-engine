// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, typename U, typename Enable>
constexpr bool close(
  const std::set<U>& lhs, const std::set<U>& rhs, T acc) noexcept
{
  return lhs.size() == rhs.size()
    && container_close(lhs.begin(), lhs.end(), rhs.begin(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& c)
{
  return container_stream(os, c.begin(), c.end());
}

}  // namespace hou

