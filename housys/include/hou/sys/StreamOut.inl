// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license. See license.md for more details.

namespace hou
{

template <typename T>
  std::enable_if_t<std::is_pod<T>::value && !isContiguousContainer<T>::value
  , StreamOut>& StreamOut::write(const T& buf)
{
  onWrite(&buf, sizeof(T), 1u);
  return *this;
}



template <typename T>
  std::enable_if_t<isContiguousContainer<T>::value, StreamOut>&
  StreamOut::write(const T& buf)
{
  onWrite(buf.data(), sizeof(typename T::value_type), buf.size());
  return *this;
}



template <typename T>
  StreamOut& StreamOut::write(const T* buf, size_t bufSize)
{
  onWrite(buf, sizeof(T), bufSize);
  return *this;
}

}

