// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.



namespace hou
{

template <typename T, typename Enable>
  T log(T x, int n)
{
  return std::log(x) / std::log(static_cast<T>(n));
}


}

