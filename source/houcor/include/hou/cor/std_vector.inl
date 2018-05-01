// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T, typename U, typename Enable>
bool close(const std::vector<U>& lhs, const std::vector<U>& rhs, T acc)
{
  return lhs.size() == rhs.size()
    && container_close(lhs.begin(), lhs.end(), rhs.begin(), acc);
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& c)
{
  return container_stream(os, c.begin(), c.end());
}

}  // namespace hou
