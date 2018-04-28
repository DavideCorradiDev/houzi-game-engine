// Houzi Game Engine
// Copyright (c) 2018 Davide Corradi
// Licensed under the MIT license.

namespace hou
{

template <typename T>
  std::enable_if_t<std::is_pod<T>::value && !isContiguousContainer<T>::value
  , StreamIn>& StreamIn::read(T& buf)
{
  onRead(&buf, sizeof(T), 1u);
  return *this;
}



template <typename T>
  std::enable_if_t<isContiguousContainer<T>::value, StreamIn>&
  StreamIn::read(T& buf)
{
  onRead(const_cast<typename T::pointer>(buf.data())
    , sizeof(typename T::value_type), buf.size());
  return *this;
}



template <typename T>
  StreamIn& StreamIn::read(T* buf, size_t bufSize)
{
  onRead(buf, sizeof(T), bufSize);
  return *this;
}

}

