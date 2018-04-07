// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename T>
  size_t File::read(T* buf, size_t bufSize)
{
  return read(buf, sizeof(T), bufSize);
}



template <typename T>
  void File::write(const T* buf, size_t bufSize)
{
  write(buf, sizeof(T), bufSize);
}




template <typename Container>
  size_t File::read(Container& buffer)
{
  // the const_cast is necessary because as of C++14 containers have a data()
  // call that returns a non-const pointer, but string don't. This will be a
  // feature in C++17 though.
  return read(const_cast<typename Container::value_type*>(buffer.data())
    , buffer.size());
}



template <typename Container>
  void File::write(const Container& buffer)
{
  write(buffer.data(), buffer.size());
}

}

