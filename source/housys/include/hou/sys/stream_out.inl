// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
std::enable_if_t<std::is_pod<T>::value && !is_contiguous_container<T>::value,
  stream_out>&
  stream_out::write(const T& buf)
{
  on_write(&buf, sizeof(T), 1u);
  return *this;
}



template <typename T>
std::enable_if_t<is_contiguous_container<T>::value, stream_out>&
  stream_out::write(const T& buf)
{
  on_write(buf.data(), sizeof(typename T::value_type), buf.size());
  return *this;
}



template <typename T>
stream_out& stream_out::write(const T* buf, size_t buf_size)
{
  on_write(buf, sizeof(T), buf_size);
  return *this;
}

}  // namespace hou
