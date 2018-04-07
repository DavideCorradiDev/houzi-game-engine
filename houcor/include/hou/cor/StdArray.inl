// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename T, typename U, std::size_t N, typename Enable>
  bool close(const std::array<U, N>& lhs, const std::array<U, N>& rhs, T acc)
{
  return containerClose(lhs.begin(), lhs.end(), rhs.begin(), acc);
}



template <typename T, std::size_t N>
  std::ostream& operator<<(std::ostream& os, const std::array<T, N>& c)
{
  return containerStream(os, c.begin(), c.end());
}

}

