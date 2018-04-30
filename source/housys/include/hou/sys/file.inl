// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
size_t file::read(T* buf, size_t buf_size)
{
  return read(buf, sizeof(T), buf_size);
}



template <typename T>
void file::write(const T* buf, size_t buf_size)
{
  write(buf, sizeof(T), buf_size);
}



template <typename Container>
size_t file::read(Container& buffer)
{
  // the const_cast is necessary because as of C++14 containers have a data()
  // call that returns a non-const pointer, but string don't. This will be a
  // feature in C++17 though.
  return read(
    const_cast<typename Container::value_type*>(buffer.data()), buffer.size());
}



template <typename Container>
void file::write(const Container& buffer)
{
  write(buffer.data(), buffer.size());
}

}  // namespace hou
